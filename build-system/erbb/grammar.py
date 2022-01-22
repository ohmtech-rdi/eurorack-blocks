##############################################################################
#
#     grammar.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

from .arpeggio import RegExMatch as _
from .arpeggio import Optional, ZeroOrMore, EOF, Combine, And



KEYWORDS = (
   'module',
   'import', 'define', 'sources', 'resources', 'section',
   'file', 'data', 'flash', 'qspi'
)

SYMBOLS = (',', '{', '}', '=')


def identifier ():                     return _(r'(?!\b({})\b)([a-zA-Z]\w*)')
def name ():                           return identifier
def comment ():                        return _(r'(/\*(.|\n)*?\*/)|(//.*)')

# Literals
def string_literal ():                 return _(r'\".*\"')

# File
def file_declaration ():               return 'file', string_literal

# Import
def import_declaration ():             return 'import', string_literal

# Define
def define_key ():                     return name
def define_value ():                   return _(r'(\w*)')
def define_declaration ():             return 'define', define_key, '=', define_value

# Sources
def sources_entities ():               return ZeroOrMore (file_declaration)
def sources_body ():                   return '{', sources_entities, '}'
def sources_declaration ():            return 'sources', sources_body

# Data

def data_entities ():                  return ZeroOrMore (file_declaration)
def data_body ():                      return '{', data_entities, '}'
def data_name ():                      return name
def data_type ():                      return name
def data_declaration ():               return 'data', data_name, Optional (data_type), data_body

# Resources
def resources_entities ():             return ZeroOrMore (data_declaration)
def resources_body ():                 return '{', resources_entities, '}'
def resources_declaration ():          return 'resources', resources_body

# Base
def base_declaration ():               return 'base', string_literal

# Base
def section_name ():                   return ['flash', 'qspi']
def section_declaration ():            return 'section', section_name

# Module
def module_entities ():                return ZeroOrMore ([section_declaration, import_declaration, define_declaration, sources_declaration, resources_declaration, base_declaration])
def module_body ():                    return '{', module_entities, '}'
def module_name ():                    return name
def module_declaration ():             return 'module', module_name, module_body, EOF

# Library
def library_declaration ():             return module_entities, EOF

GRAMMAR_ROOT = module_declaration
GRAMMAR_LIBRARY_ROOT = library_declaration
