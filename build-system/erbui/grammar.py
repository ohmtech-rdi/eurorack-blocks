##############################################################################
#
#     grammar.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################

from .arpeggio import RegExMatch as _
from .arpeggio import Optional, ZeroOrMore, EOF, Combine, And



KEYWORDS = (
   'module', 'board', 'width', 'material', 'route', 'auto', 'wire', 'header', 'footer', 'line',
   'control', 'label', 'sticker', 'image', 'pin', 'pins', 'cascade', 'mode', 'normalized', 'bipolar',
   'position', 'rotation', 'offset', 'style',
   'positioning', 'center', 'left', 'top', 'right', 'bottom',
   'aluminum', 'brushed_aluminum', 'aluminum_coated', 'natural', 'white', 'black',
)
UNITS = ('mm', 'cm', 'hp', '°', '°ccw', '°cw')
CONTROL_KINDS = ('AudioIn', 'AudioOut', 'Button', 'CvIn', 'CvOut', 'GateIn', 'GateOut', 'Led', 'LedBi', 'LedRgb', 'Pot', 'Switch', 'Trim')
CONTROL_STYLES = (
   'rogan.6ps', 'rogan.5ps', 'rogan.3ps', 'rogan.2ps', 'rogan.1ps',
   'songhuei.9mm',
   'dailywell.2ms1', 'dailywell.2ms3',
   'led.3mm.green_red', 'led.3mm.rgb', 'led.3mm.red', 'led.3mm.green', 'led.3mm.yellow', 'led.3mm.orange',
   'thonk.pj398sm.knurled', 'thonk.pj398sm.hex',
   'tl1105', 'ck.d6r.black',
)

SYMBOLS = (',', '{', '}', '(', ')')


def identifier ():                     return _(r'(?!\b({})\b)([a-zA-Z]\w*)')
def name ():                           return identifier
def comment ():                        return _(r'(/\*(.|\n)*?\*/)|(//.*)')

# Literals
def string_literal ():                 return _(r'\".*\"')
def float_mm_literal ():               return _(r'[0-9\.]+mm')
def float_cm_literal ():               return _(r'[0-9\.]+cm')
def float_hp_literal ():               return _(r'[0-9\.]+hp')
def float_deg_literal ():              return _(r'[0-9\.]+°')
def float_deg_ccw_literal ():          return _(r'[0-9\.]+°ccw')
def float_deg_cw_literal ():           return _(r'[0-9\.]+°cw')

# Metrics
def distance_declaration ():           return [float_mm_literal, float_cm_literal, float_hp_literal]
def angle_declaration ():              return [float_deg_ccw_literal, float_deg_cw_literal, float_deg_literal]

# Positioning
def positioning_name ():               return ['center', 'left', 'top', 'right', 'bottom']
def positioning_declaration ():        return 'positioning', positioning_name

# Pin & Pins
def pin_name ():                       return name
def pin_declaration ():                return 'pin', pin_name
def pins_declaration ():               return 'pins', pin_name, ZeroOrMore (',', pin_name)

# Image
def image_declaration ():              return 'image', string_literal

# Label
def label_entities ():                 return ZeroOrMore ([position_declaration, positioning_declaration, offset_declaration])
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
def offset_declaration ():             return 'offset', distance_declaration, ',', distance_declaration

# Line
def line_entities ():                  return ZeroOrMore (position_declaration)
def line_body ():                      return '{', line_entities, '}'
def line_declaration ():               return 'line', line_body

# Style
def style_name ():                     return list (CONTROL_STYLES)
def style_declaration ():              return 'style', style_name

# Mode
def mode_value ():                     return ['normalized', 'bipolar']
def mode_declaration ():               return 'mode', mode_value

# Cascade
def cascade_reference ():              return name
def cascade_declaration ():            return 'cascade', cascade_reference

# Alias
def alias_name ():                     return name
def alias_reference ():                return name
def alias_declaration ():              return 'alias', alias_name, alias_reference

# Control
def control_entities ():               return ZeroOrMore ([mode_declaration, position_declaration, rotation_declaration, style_declaration, label_declaration, image_declaration, pins_declaration, pin_declaration, cascade_declaration])
def control_body ():                   return '{', control_entities, '}'
def control_kind ():                   return list (CONTROL_KINDS)
def control_name ():                   return name
def control_declaration ():            return 'control', control_name, control_kind, control_body

# Footer
def footer_entities ():                return ZeroOrMore ([label_declaration, image_declaration])
def footer_body ():                    return '{', footer_entities, '}'
def footer_declaration ():             return 'footer', footer_body

# Header
def header_entities ():                return ZeroOrMore ([label_declaration, image_declaration])
def header_body ():                    return '{', header_entities, '}'
def header_declaration ():             return 'header', header_body

# Module Width
def width_declaration ():              return 'width', distance_declaration

# Module Board
def board_name ():                     return name
def board_declaration ():              return 'board', board_name

# Module Material
def material_color ():                 return ['natural', 'black', 'white']
def material_name ():                  return ['aluminum', 'brushed_aluminum', 'aluminum_coated']
def material_declaration ():           return 'material', material_name, Optional (material_color)

# Module Route
def route_mode ():                     return ['auto', 'wire']
def route_declaration ():              return 'route', route_mode

# Module
def module_entities ():                return ZeroOrMore ([board_declaration, width_declaration, material_declaration, route_declaration, header_declaration, footer_declaration, line_declaration, label_declaration, sticker_declaration, image_declaration, control_declaration, alias_declaration])
def module_body ():                    return '{', module_entities, '}'
def module_name ():                    return name
def module_inheritance_clause ():      return 'extends', board_name
def module_declaration ():             return 'module', module_name, Optional (module_inheritance_clause), module_body, EOF

GRAMMAR_ROOT = module_declaration
