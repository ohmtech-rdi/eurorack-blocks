##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import platform

from .arpeggio import RegExMatch as _
from .arpeggio import ParserPython, NoMatch, ZeroOrMore, EOF


def identifier ():                     return _(r'(?!\b({})\b)([a-zA-Z]\w*)')
def value ():                          return _(r'\S+')
def name ():                           return '--name', identifier

def language ():                       return '--language', ['c++', 'max', 'faust']
def configuration ():                  return '--configuration', ['debug', 'release']
def programmer ():                     return '--programmer', ['dfu', 'stlink']
def logger ():                         return '--logger', ['usb', 'semihosting']
def xcode ():                          return '--xcode'
def semihosting ():                    return '--semihosting'
def fast_boot ():                      return '--fast-boot'
def only_gerber ():                    return '--only-gerber'
def with_xcode_support ():             return '--with-xcode-support'
def with_vscode_support ():            return '--with-vscode-support'
def with_max_support ():               return '--with-max-support'
def with_apt ():                       return '--with-apt'

def build_simulator ():                return 'simulator', ZeroOrMore ([configuration, xcode])
def build_firmware ():                 return 'firmware', ZeroOrMore ([configuration, semihosting])
def build_performance ():              return 'performance', ZeroOrMore ([logger])
def build_fuzz ():                     return 'fuzz', ZeroOrMore ([logger])
def build_hardware ():                 return 'hardware', ZeroOrMore ([only_gerber])

def monitor_action ():                 return ['stream', 'ping', 'load', 'prof']
def monitor_build ():                  return '--build'
def monitor_rebuild ():                return '--rebuild'
def monitor_install ():                return '--install'
def monitor_speed_khz ():              return '--speed-khz', value
def monitor_duration ():               return '--duration', value
def monitor_blocks ():                 return '--blocks', value
def monitor_log ():                    return '--log', value

def install_firmware ():               return 'firmware', ZeroOrMore ([configuration, programmer])
def install_performance ():            return 'performance'
def install_fuzz ():                   return 'fuzz'
def install_bootloader ():             return 'bootloader', ZeroOrMore ([fast_boot])
def install_simulator ():              return 'simulator', ZeroOrMore ([configuration])

def run_performance ():                return 'performance'
def run_fuzz ():                       return 'fuzz'

def setup ():
   if platform.system () == 'Darwin':
                                       return 'setup', ZeroOrMore ([with_xcode_support, with_vscode_support, with_max_support])
   elif platform.system () == 'Windows':
                                       return 'setup', ZeroOrMore ([with_vscode_support, with_max_support])
   elif platform.system () == 'Linux':
                                       return 'setup', ZeroOrMore ([with_vscode_support, with_apt])

def init ():                           return 'init', ZeroOrMore ([name, language])
def configure ():                      return 'configure'
def build ():                          return 'build', [build_simulator, build_firmware, build_performance, build_fuzz, build_hardware]
def monitor ():                        return 'monitor', ZeroOrMore ([monitor_action, monitor_build, monitor_rebuild, monitor_install, monitor_speed_khz, monitor_duration, monitor_blocks, monitor_log])
def install ():                        return 'install', [install_firmware, install_performance, install_fuzz, install_bootloader, install_simulator]
def run ():                            return 'run ', [run_performance, run_fuzz]

def commands ():                       return [setup, init, configure, build, monitor, install, run]

def erbb_cli ():                       return 'erbb', commands

GRAMMAR_ROOT = erbb_cli, EOF

DESCRIPTION = {
   'setup': 'install all dependencies',
   '--with-xcode-support': 'for Xcode support',
   '--with-vscode-support': 'for Visual Studio Code support',
   '--with-max-support': 'for Cycling\'74 Max support',
   '--with-apt': 'using the apt package manager',
   'init': 'create a new project in current directory',
   '--name': 'name of project, random name if not specified',
   '--language': 'the language to use, defaults to c++',
   'c++': 'for c++',
   'max': 'for Max/gen~',
   'faust': 'for Faust',
   'configure': 'create the simulator IDE projects and firmware make file',
   'build': 'build the simulator, firmware or hardware files',
   'simulator': 'the simulator to run in the virtual environment',
   '--configuration': 'the build configuration to use, defaults to release',
   '--xcode': 'build using Xcode',
   'firmware': 'the firmware to run on the target platform',
   '--semihosting': 'enable semihosting',
   'hardware': 'the files to manufacture the module',
   '--only-gerber': 'generate gerber from pcb layout only',
   '--fast-boot': 'install fast boot variant',
   'install': 'install the firmware or bootloader',
   '--programmer': 'the programmer to use, defaults to automatic selection',
   'performance': 'the performance analysis firmware',
   'fuzz': 'the fuzz testing firmware',
   '--logger': 'the logger to use, defaults to automatic selection',
   'bootloader': 'the bootloader',
   'monitor': 'communicate with a running module',
   'stream': 'feed the module text output',
   'ping': 'round-trip check',
   'load': 'audio callback load',
   'prof': 'profiler window dump',
   '--build': 'configure and build the firmware first',
   '--rebuild': 'like --build, but wipe artifacts/daisy first',
   '--install': 'flash the firmware before monitoring',
   '--speed-khz': 'debug probe adapter speed, in kHz',
   '--duration': 'stream duration in seconds, unlimited if not specified',
   '--blocks': 'profiler window length in audio blocks, defaults to 3000',
   '--log': 'tee the streamed lines to this file',
   'debug': 'for debugging',
   'release': 'for testing or distribution',
   'auto': 'automatic selection',
   'dfu': 'for flashing using a USB cable',
   'stlink': 'for flashing using a ST-link programmer',
   'usb': 'using USB',
   'semihosting': 'using semihosting',
   'run ': 'run the firmware',
}


def complete (line, add_description=False):
   parser = ParserPython (GRAMMAR_ROOT, autokwd=True)
   try:
      parser.parse (line, '')
      return []

   except NoMatch as err:
      matches = [str (rule) for rule in err.rules if str (rule).startswith (line [err.position:])]

      # raw regex terminals (identifier, option values) are not suggestions
      regex_rules = ['(?!\\b({})\\b)([a-zA-Z]\\w*)', '\\S+']
      matches = [rule for rule in matches if rule not in regex_rules]

      if add_description:
         matches = [rule.rstrip () + '\t' + DESCRIPTION [rule] for rule in matches]

      return matches
