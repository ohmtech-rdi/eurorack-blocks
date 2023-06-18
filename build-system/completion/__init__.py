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
def name ():                           return '--name', identifier

def language ():                       return '--language', ['c++', 'max', 'faust']
def configuration ():                  return '--configuration', ['debug', 'release']
def programmer ():                     return '--programmer', ['dfu', 'stlink']
def xcode ():                          return '--xcode'
def semihosting ():                    return '--semihosting'
def only_gerber ():                    return '--only-gerber'
def with_xcode_support ():             return '--with-xcode-support'

def build_simulator ():                return 'simulator', ZeroOrMore ([configuration, xcode])
def build_firmware ():                 return 'firmware', ZeroOrMore ([configuration, semihosting])
def build_hardware ():                 return 'hardware', ZeroOrMore ([only_gerber])

def install_firmware ():               return 'firmware', ZeroOrMore ([configuration, programmer])
def install_bootloader ():             return 'bootloader'

def setup ():
   if platform.system () == 'Darwin':
                                       return 'setup', ZeroOrMore ([with_xcode_support])
   else:
                                       return 'setup'
def init ():                           return 'init', ZeroOrMore ([name, language])
def configure ():                      return 'configure'
def build ():                          return 'build', [build_simulator, build_firmware, build_hardware]
def install ():                        return 'install', [install_firmware, install_bootloader]

def commands ():                       return [setup, init, configure, build, install]

def erbb_cli ():                       return 'erbb', commands

GRAMMAR_ROOT = erbb_cli, EOF

DESCRIPTION = {
   'setup': 'install all dependencies',
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
   'install': 'install the firmware or bootloader',
   '--programmer': 'the programmer to use, defaults to automatic selection',
   'bootloader': 'the bootloader',
   'debug': 'for debugging',
   'release': 'for testing or distribution',
   'auto': 'automatic selection of programmer',
   'dfu': 'for flashing using a USB cable',
   'stlink': 'for flashing using a ST-link programmer',
}


def complete (line, add_description=False):
   parser = ParserPython (GRAMMAR_ROOT, autokwd=True)
   try:
      parser.parse (line, '')
      return []

   except NoMatch as err:
      matches = [str (rule) for rule in err.rules if str (rule).startswith (line [err.position:])]
      if matches == ['(?!\\b({})\\b)([a-zA-Z]\\w*)']:
         return []
      else:
         if add_description:
            matches = [rule + '\t' + DESCRIPTION [rule] for rule in matches]

         return matches
