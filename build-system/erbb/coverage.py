##############################################################################
#
#     coverage.py
#     Copyright (c) 2026 Ohm Force
#
#Tab=3########################################################################



import json
import os
import platform
import shutil
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))



"""
==============================================================================
Name : report
Description :
   Takes artifacts/acceptance/Coverage/profiles and generate the reports
   from it in artifacts/acceptance/Coverage/profiles:
   - merged.profdata: all profiles merged
   - coverage.json: the llvm-cov export
   - summary.txt: one line per file
   - uncovered.txt: the functions never executed and the unexecuted
     lines of the executed ones with 'file:lines'
   - html/index.html: annotated sources
   (excludes scenarios, rig, glue, etc. out of it)
==============================================================================
"""

def report (path, module, names):
   path_coverage = os.path.join (path, 'artifacts', 'acceptance', 'Coverage')
   path_profiles = os.path.join (path_coverage, 'profiles')
   path_report = os.path.join (path_coverage, 'report')

   profiles = sorted ([
      os.path.join (path_profiles, filename)
      for filename in os.listdir (path_profiles)
      if filename.endswith ('.profraw')
   ]) if os.path.isdir (path_profiles) else []

   if not profiles:
      print ('error: no profile in %s' % path_profiles, file = sys.stderr)
      return False

   executables = []

   for name in names:
      executable = os.path.join (path_coverage, name)

      if platform.system () == 'Windows':
         executable += '.exe'

      if os.path.exists (executable):
         executables.append (executable)

   if not executables:
      print ('error: no acceptance executable in %s' % path_coverage, file = sys.stderr)
      return False

   os.makedirs (path_report, exist_ok = True)

   llvm_profdata = find_tool ('llvm-profdata')
   llvm_cov = find_tool ('llvm-cov')

   path_profdata = os.path.join (path_report, 'merged.profdata')

   subprocess.check_call ([llvm_profdata, 'merge', '--sparse', '--output=' + path_profdata] + profiles)

   objects = [executables [0]]
   for executable in executables [1:]:
      objects.extend (['-object', executable])

   export = subprocess.run (
      [llvm_cov, 'export', '-instr-profile=' + path_profdata] + objects,
      capture_output = True, text = True, check = True
   )

   data = json.loads (export.stdout) ['data'][0]

   tiers = make_tiers (path, module)
   tier_of = {}

   for file in data ['files']:
      tier = tier_index (tiers, file ['filename'])
      if tier is not None:
         tier_of [file ['filename']] = tier
         tiers [tier]['files'].append (file)

   for tier in tiers:
      tier ['files'].sort (key = lambda file: file ['filename'])

   functions = [
      function for function in data ['functions']
      if function ['filenames'] and function ['filenames'][0] in tier_of
   ]

   names_demangled = demangle ([function ['name'] for function in functions])

   with open (os.path.join (path_report, 'coverage.json'), 'w', encoding = 'utf-8') as file:
      json.dump ({
         'files': [file for tier in tiers for file in tier ['files']],
         'functions': functions,
      }, file)

   write_summary (os.path.join (path_report, 'summary.txt'), tiers)
   write_uncovered (os.path.join (path_report, 'uncovered.txt'), tiers, tier_of, functions, names_demangled)

   sources = [file ['filename'] for tier in tiers for file in tier ['files']]

   path_html = os.path.join (path_report, 'html')
   shutil.rmtree (path_html, ignore_errors = True)

   subprocess.check_call (
      [
         llvm_cov, 'show', '-instr-profile=' + path_profdata,
         '-format=html', '-output-dir=' + path_html,
         '-show-branches=count', '-project-title=' + module.name,
      ] + ['-Xdemangler=' + arg for arg in find_demangler ()] + objects + sources
   )

   for tier in tiers:
      print ('COVERAGE %s %s' % (tier ['name'], summary_line (tier_totals (tier))), flush = True)

   print ('REPORT %s' % os.path.relpath (os.path.join (path_html, 'index.html'), path), flush = True)

   return True



"""
==============================================================================
Name : find_tool
Description :
   An llvm tool on the PATH, or in the Xcode toolchain on macOS
==============================================================================
"""

def find_tool (name, required = True):
   tool = shutil.which (name)

   if tool is not None:
      return tool

   if platform.system () == 'Darwin':
      developer = subprocess.run (['xcode-select', '--print-path'], capture_output = True, text = True)

      if developer.returncode == 0:
         tool = os.path.join (
            developer.stdout.strip (), 'Toolchains', 'XcodeDefault.xctoolchain', 'usr', 'bin', name
         )

         if os.path.exists (tool):
            return tool

   if not required:
      return None

   print ('error: %s not found' % name, file = sys.stderr)
   sys.exit (1)



"""
==============================================================================
Name : make_tiers
==============================================================================
"""

def make_tiers (path, module):
   acceptance_files = set ()

   for acceptance in module.acceptances:
      for file in acceptance.files:
         acceptance_files.add (os.path.abspath (os.path.join (path, file.path)))

   tiers = []
   groups = [(module.name, module.sources [0])]

   for import_, sources in zip (module.imports, module.sources [1:]):
      groups.append ((os.path.splitext (os.path.basename (import_.path)) [0], sources))

   for name, sources in groups:
      files = set ()

      for file in sources.files:
         files.add (os.path.abspath (os.path.join (path, file.path)))

      tiers.append ({'name': name, 'match': lambda filename, files = files: filename in files, 'files': []})

   def match_erb (filename):
      relative = os.path.relpath (filename, PATH_ROOT)
      parts = relative.split (os.sep)

      if parts [:2] == ['include', 'erb'] or parts [:1] == ['src']:
         return 'rig' not in parts

      return False

   tiers.append ({'name': 'erb', 'match': match_erb, 'files': []})

   # the acceptance scenarios are never in a tier
   for tier in tiers:
      match = tier ['match']
      tier ['match'] = lambda filename, match = match: filename not in acceptance_files and match (filename)

   return tiers



def tier_index (tiers, filename):
   for index, tier in enumerate (tiers):
      if tier ['match'] (filename):
         return index

   return None



"""
==============================================================================
Name : find_demangler
==============================================================================
"""

def find_demangler ():
   for name in ('llvm-cxxfilt', 'c++filt'):
      tool = find_tool (name, required = False)

      if tool is not None:
         return [tool, '--no-strip-underscore']

   print ('error: no demangler found', file = sys.stderr)
   sys.exit (1)



"""
==============================================================================
Name : demangle
==============================================================================
"""

def demangle (names):
   if not names:
      return []

   result = subprocess.run (
      find_demangler (), input = '\n'.join (names) + '\n', capture_output = True, text = True
   )

   if result.returncode != 0:
      return names

   demangled = result.stdout.split ('\n')

   return demangled [:len (names)]



"""
==============================================================================
Name : write_summary
==============================================================================
"""

def tier_totals (tier):
   totals = {}

   for file in tier ['files']:
      for key, value in file ['summary'].items ():
         total = totals.setdefault (key, {'count': 0, 'covered': 0})
         total ['count'] += value ['count']
         total ['covered'] += value ['covered']

   return totals



def ratio (summary, key):
   value = summary.get (key, {'count': 0, 'covered': 0})

   if value ['count'] == 0:
      return '%5d/%-5d    -' % (0, 0)

   return '%5d/%-5d %3d%%' % (value ['covered'], value ['count'], 100 * value ['covered'] // value ['count'])



def summary_line (summary):
   return 'functions %s  lines %s  regions %s  branches %s' % (
      ratio (summary, 'functions'), ratio (summary, 'lines'), ratio (summary, 'regions'), ratio (summary, 'branches')
   )



def write_summary (path_summary, tiers):
   with open (path_summary, 'w', encoding = 'utf-8') as out:
      for tier in tiers:
         if not tier ['files']:
            continue

         out.write ('== %s\n' % tier ['name'])

         width = max (len (short_name (tier, file ['filename'])) for file in tier ['files'])

         for file in tier ['files']:
            out.write ('%-*s  %s\n' % (width, short_name (tier, file ['filename']), summary_line (file ['summary'])))

         out.write ('%-*s  %s\n\n' % (width, 'TOTAL', summary_line (tier_totals (tier))))



def short_name (tier, filename):
   common = os.path.commonpath ([file ['filename'] for file in tier ['files']])

   if os.path.isfile (common):
      common = os.path.dirname (common)

   return os.path.relpath (filename, common)



"""
==============================================================================
Name : write_uncovered
==============================================================================
"""

def write_uncovered (path_uncovered, tiers, tier_of, functions, names_demangled):
   never = {}      # filename -> [(line, name)]
   partial = {}    # filename -> [(line_start, line_end, name)]

   for function, name in zip (functions, names_demangled):
      regions = [region for region in function ['regions'] if region [7] == 0]

      if not regions:
         continue

      filename = function ['filenames'][0]

      if function ['count'] == 0:
         never.setdefault (filename, []).append ((regions [0][0], name))
         continue

      ranges = sorted (
         (region [0], region [2]) for region in regions
         if region [4] == 0 and function ['filenames'][region [5]] == filename
      )

      merged = []

      for start, end in ranges:
         if merged and start <= merged [-1][1] + 1:
            merged [-1][1] = max (merged [-1][1], end)
         else:
            merged.append ([start, end])

      for start, end in merged:
         partial.setdefault (filename, []).append ((start, end, name))

   with open (path_uncovered, 'w', encoding = 'utf-8') as out:
      for tier in tiers:
         if not tier ['files']:
            continue

         out.write ('== %s\n' % tier ['name'])

         for file in tier ['files']:
            filename = file ['filename']
            entries = []

            for line, name in sorted (never.get (filename, [])):
               entries.append ('   %-5d        never  %s' % (line, name))

            for start, end, name in sorted (partial.get (filename, [])):
               lines = '%d' % start if start == end else '%d-%d' % (start, end)
               entries.append ('   %-12s partial  in %s' % (lines, name))

            if not entries:
               continue

            out.write ('%s\n' % short_name (tier, filename))
            out.write ('\n'.join (entries) + '\n')

         out.write ('\n')
