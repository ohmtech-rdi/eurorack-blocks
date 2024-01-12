##############################################################################
#
#     grammar.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

from .arpeggio import RegExMatch as _
from .arpeggio import Optional, ZeroOrMore, EOF, Combine, And



KEYWORDS = (
   'import',
   'module', 'board', 'width', 'format', 'material', 'header', 'footer', 'line',
   'control', 'label', 'sticker', 'image', 'pin', 'pins', 'normalling', 'nothing', 'mode', 'normalized', 'bipolar',
   'position', 'rotation', 'offset', 'style',
   'positioning', 'center', 'left', 'top', 'right', 'bottom',
   'layer', 'silkscreen', 'translucence',
   'aluminum', 'brushed_aluminum', 'aluminum_coated', 'natural', 'white', 'black', 'pcb',
   '3u', '1590bb2_portrait',
   'route', 'wire', 'manual',
   'faust', 'address', 'init', 'value',
   'manufacturer', 'generator', 'arg', 'parts',
)
UNITS = ('mm', 'cm', 'hp', '°', '°ccw', '°cw')
CONTROL_KINDS = ('AudioIn', 'AudioOut', 'Button', 'CvIn', 'CvOut', 'Display', 'Encoder', 'EncoderButton', 'GateIn', 'GateOut', 'Led', 'LedBi', 'LedRgb', 'Pot', 'Switch', 'Trim')

SYMBOLS = (',', '{', '}', '(', ')')


def identifier ():                     return _(r'(?!\b({})\b)([a-zA-Z]\w*)')
def name ():                           return identifier
def comment ():                        return _(r'(/\*(.|\n)*?\*/)|(//.*)')

# Literals
def string_literal ():                 return _(r'(\")((?<!\\)\\\1|.)*?\1')
def integer_literal ():                return _(r'[0-9]+')
def float_literal ():                  return _(r'[0-9\.]+')
def float_mm_literal ():               return _(r'-?[0-9\.]+mm')
def float_cm_literal ():               return _(r'-?[0-9\.]+cm')
def float_hp_literal ():               return _(r'-?[0-9\.]+hp')
def float_pos_mm_literal ():           return _(r'[0-9\.]+mm')
def float_pos_cm_literal ():           return _(r'[0-9\.]+cm')
def float_pos_hp_literal ():           return _(r'[0-9\.]+hp')
def float_deg_literal ():              return _(r'[0-9\.]+°')
def float_deg_ccw_literal ():          return _(r'[0-9\.]+°ccw')
def float_deg_cw_literal ():           return _(r'[0-9\.]+°cw')

# Metrics
def distance_declaration ():           return [float_pos_mm_literal, float_pos_cm_literal, float_pos_hp_literal]
def signed_distance_declaration ():    return [float_mm_literal, float_cm_literal, float_hp_literal]
def angle_declaration ():              return [float_deg_ccw_literal, float_deg_cw_literal, float_deg_literal]

# Positioning
def positioning_name ():               return ['center', 'left', 'top', 'right', 'bottom']
def positioning_declaration ():        return 'positioning', positioning_name

# Pin & Pins
def pin_name ():                       return name
def pin_declaration ():                return 'pin', pin_name
def pins_declaration ():               return 'pins', pin_name, ZeroOrMore (',', pin_name)

# Import
def import_declaration ():             return 'import', string_literal

# File
def file_declaration ():               return 'file', string_literal

# Layer
def layer_name ():                     return ['silkscreen', 'translucence']
def layer_declaration ():              return 'layer', layer_name

# Image
def image_entities ():                 return ZeroOrMore ([layer_declaration])
def image_body ():                     return '{', image_entities, '}'
def image_declaration ():              return 'image', string_literal, Optional (image_body)

# Label
def label_entities ():                 return ZeroOrMore ([position_declaration, positioning_declaration, offset_declaration, layer_declaration])
def label_body ():                     return '{', label_entities, '}'
def label_declaration ():              return 'label', string_literal, Optional (label_body)

# Sticker
def sticker_entities ():                 return ZeroOrMore ([position_declaration, positioning_declaration, offset_declaration])
def sticker_body ():                     return '{', sticker_entities, '}'
def sticker_declaration ():              return 'sticker', string_literal, Optional (sticker_body)

# Position
def position_declaration ():           return 'position', distance_declaration, ',', distance_declaration

# Rotation
def rotation_declaration ():           return 'rotation', angle_declaration

# Offset
def offset_declaration ():             return 'offset', signed_distance_declaration, ',', signed_distance_declaration

# Line
def line_entities ():                  return ZeroOrMore ([position_declaration, layer_declaration])
def line_body ():                      return '{', line_entities, '}'
def line_declaration ():               return 'line', line_body

# Style
def style_name ():                     return _(r'(?!\b({})\b)((\w|\.)*)')
def style_declaration ():              return 'style', style_name, ZeroOrMore (',', style_name)

# Mode
def mode_value ():                     return ['normalized', 'bipolar']
def mode_declaration ():               return 'mode', mode_value

# Normalling
def normalling_reference ():           return name
def normalling_nothing ():             return 'nothing'
def normalling_declaration ():         return 'normalling', [normalling_nothing, normalling_reference]

# Alias
def alias_name ():                     return name
def alias_reference ():                return name
def alias_declaration ():              return 'alias', alias_name, alias_reference

# Faust Value
def faust_value_declaration ():    return 'value', float_literal

# Faust Property
def faust_property_name ():            return name
def faust_property_declaration ():     return 'property', faust_property_name

# Faust Address
def faust_address_declaration ():      return 'address', string_literal

# Faust Bind
def faust_bind_entities ():            return ZeroOrMore ([faust_property_declaration, faust_address_declaration])
def faust_bind_body ():                return '{', faust_bind_entities, '}'
def faust_bind_declaration ():         return 'bind', faust_bind_body

# Control Faust Init
def ctrl_faust_init_entities ():       return ZeroOrMore ([faust_property_declaration, faust_value_declaration])
def ctrl_faust_init_body ():           return '{', ctrl_faust_init_entities, '}'
def ctrl_faust_init_declaration ():    return 'init', ctrl_faust_init_body

# Control Faust
def ctrl_faust_entities ():            return ZeroOrMore ([faust_bind_declaration, ctrl_faust_init_declaration])
def ctrl_faust_body ():                return '{', ctrl_faust_entities, '}'
def ctrl_faust_declaration ():         return 'faust', ctrl_faust_body

# Control
def control_entities ():               return ZeroOrMore ([mode_declaration, position_declaration, rotation_declaration, style_declaration, label_declaration, image_declaration, pins_declaration, pin_declaration, normalling_declaration, ctrl_faust_declaration])
def control_body ():                   return '{', control_entities, '}'
def control_kind ():                   return list (CONTROL_KINDS)
def control_name ():                   return name
def control_declaration ():            return 'control', control_name, control_kind, control_body

# Exclude Pins
def exclude_declaration ():            return 'exclude', [pins_declaration, pin_declaration]

# Module Faust Init
def mod_faust_init_entities ():        return ZeroOrMore ([faust_address_declaration, faust_value_declaration])
def mod_faust_init_body ():            return '{', mod_faust_init_entities, '}'
def mod_faust_init_declaration ():     return 'init', mod_faust_init_body

# Module Faust
def mod_faust_entities ():             return ZeroOrMore ([mod_faust_init_declaration])
def mod_faust_body ():                 return '{', mod_faust_entities, '}'
def mod_faust_declaration ():          return 'faust', mod_faust_body

# Footer
def footer_entities ():                return ZeroOrMore ([label_declaration, image_declaration])
def footer_body ():                    return '{', footer_entities, '}'
def footer_declaration ():             return 'footer', footer_body

# Header
def header_entities ():                return ZeroOrMore ([label_declaration, image_declaration])
def header_body ():                    return '{', header_entities, '}'
def header_declaration ():             return 'header', header_body

# Module Route
def route_mode ():                     return ['wire', 'manual']
def route_declaration ():              return 'route', route_mode

# Module Width
def width_declaration ():              return 'width', distance_declaration

# Module Format
def format_name ():                     return ['3u', '1590bb2_portrait']
def format_declaration ():              return 'format', format_name

# Module Manufacturer Reference
def manufacturer_name ():              return name
def manufacturer_reference ():         return 'manufacturer', manufacturer_name

# Module Board Reference
def board_name ():                     return name
def board_declaration ():              return 'board', board_name

# Module Board Inline
def board_class_declaration ():        return 'class', string_literal
def board_include_declaration ():      return 'include', string_literal
def board_pcb_declaration ():          return 'pcb', string_literal
def board_sch_declaration ():          return 'sch', string_literal
def board_pin_kind ():                 return list (CONTROL_KINDS)
def board_pin_kinds ():                return board_pin_kind, ZeroOrMore (',', board_pin_kind)
def board_pin_bind_declaration ():     return 'bind', string_literal
def board_pin_type_name ():            return ['gpio', 'pwm', 'dac']
def board_pin_type_declaration ():     return 'type', board_pin_type_name
def board_pin_entities ():             return ZeroOrMore ([board_pin_bind_declaration, board_pin_type_declaration])
def board_pin_body ():                 return '{', board_pin_entities, '}'
def board_pin_name ():                 return name
def board_pin_declaration ():          return 'pin', board_pin_name, board_pin_kinds, board_pin_body
def board_pin_range ():                return '..', integer_literal
def board_pins_declaration ():         return 'pins', board_pin_name, board_pin_range, board_pin_kinds, board_pin_body
def board_entities ():                 return ZeroOrMore ([board_class_declaration, board_include_declaration, board_pcb_declaration, board_sch_declaration, width_declaration, format_declaration, board_pin_declaration, board_pins_declaration])
def board_body ():                     return '{', board_entities, '}'
def board_inline_declaration ():       return 'board', board_body

# Module Material
def material_color ():                 return ['natural', 'black', 'white']
def material_name ():                  return ['aluminum', 'brushed_aluminum', 'aluminum_coated', 'pcb']
def material_declaration ():           return 'material', material_name, Optional (material_color)

# Module
def module_entities ():                return ZeroOrMore ([manufacturer_reference, board_declaration, board_inline_declaration, width_declaration, material_declaration, header_declaration, footer_declaration, line_declaration, label_declaration, sticker_declaration, image_declaration, control_declaration, alias_declaration, exclude_declaration, route_declaration, mod_faust_declaration])
def module_body ():                    return '{', module_entities, '}'
def module_name ():                    return name
def module_inheritance_clause ():      return 'extends', board_name
def module_declaration ():             return 'module', module_name, Optional (module_inheritance_clause), module_body, EOF

def global_namespace_declaration ():   return Optional (import_declaration), module_declaration, EOF

GRAMMAR_ROOT = global_namespace_declaration

# Generator Arg
def generator_arg_name ():             return name
def generator_arg_string ():           return 'arg', generator_arg_name, string_literal
def generator_arg_dict_entities ():    return ZeroOrMore ([generator_arg_string, generator_arg_dict])
def generator_arg_dict ():             return 'arg', generator_arg_name, '{', generator_arg_dict_entities, '}'
def generator_arg_declaration ():      return [generator_arg_string, generator_arg_dict]

# Generator
def generator_entities ():             return ZeroOrMore ([generator_arg_declaration])
def generator_body ():                 return '{', generator_entities, '}'
def generator_name ():                 return string_literal
def generator_declaration ():          return 'generator', generator_name, Optional (generator_body)

# Manufacturer Control
def manufacturer_control_class ():        return 'class', string_literal
def manufacturer_control_part_name ():    return _(r'(?!\b({})\b)((\w|\.)*)')
def manufacturer_control_parts ():        return 'parts', manufacturer_control_part_name, ZeroOrMore (',', manufacturer_control_part_name)
def manufacturer_control_entities ():     return style_declaration, manufacturer_control_parts, manufacturer_control_class
def manufacturer_control_body ():         return '{', manufacturer_control_entities, '}'
def manufacturer_control_kind ():         return list (CONTROL_KINDS)
def manufacturer_control_kinds ():        return manufacturer_control_kind, ZeroOrMore (',', manufacturer_control_kind)
def manufacturer_control_declaration ():  return 'control', manufacturer_control_kinds, manufacturer_control_body

# Manufacturer
def manufacturer_entities ():          return ZeroOrMore ([generator_declaration, manufacturer_control_declaration])
def manufacturer_body ():              return '{', manufacturer_entities, '}'
def manufacturer_declaration ():       return 'manufacturer', manufacturer_name, manufacturer_body, EOF

GRAMMAR_MANUFACTURER_ROOT = manufacturer_declaration
