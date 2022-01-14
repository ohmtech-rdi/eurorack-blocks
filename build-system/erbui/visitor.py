##############################################################################
#
#     visitor.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
from .arpeggio import PTNodeVisitor
from . import ast
from . import adapter
from . import grammar



class Visitor (PTNodeVisitor):

   def __init__ (self, parser, **kwargs):
      super (Visitor, self).__init__ (defaults=True, **kwargs)
      self.parser = parser
      self.filename = None

   def set_filename (self, filename):
      self.filename = filename

   def to_identifier (self, node):
      return adapter.Identifier (self.parser, node)

   def to_keyword (self, node):
      return adapter.Keyword (self.parser, node)

   def to_symbol (self, node):
      return adapter.Symbol (self.parser, node)

   def to_literal (self, node):
      return adapter.Literal (self.parser, node)


   #-- Names -----------------------------------------------------------------

   def visit_identifier  (self, node, children):
      return self.to_identifier (node)

   def visit_name  (self, node, children):
      return self.visit_identifier (node, children)


   #-- Literals --------------------------------------------------------------

   def visit_string_literal (self, node, children):
      return ast.StringLiteral (self.to_literal (node))

   def visit_float_literal (self, node, children):
      return ast.FloatLiteral (self.to_literal (node))

   def visit_float_mm_literal (self, node, children):
      return ast.DistanceLiteral (self.to_literal (node), 'mm')

   def visit_float_cm_literal (self, node, children):
      return ast.DistanceLiteral (self.to_literal (node), 'cm')

   def visit_float_hp_literal (self, node, children):
      return ast.DistanceLiteral (self.to_literal (node), 'hp')

   def visit_float_deg_literal (self, node, children):
      return ast.RotationLiteral (self.to_literal (node), '°')

   def visit_float_deg_ccw_literal (self, node, children):
      return ast.RotationLiteral (self.to_literal (node), '°ccw')

   def visit_float_deg_cw_literal (self, node, children):
      return ast.RotationLiteral (self.to_literal (node), '°cw')


   #-- Module ----------------------------------------------------------------

   def visit_module_declaration (self, node, children):
      global_namespace = ast.GlobalNamespace ()

      module_identifier = children.module_name [0]

      module_base_identifier = None
      if children.module_inheritance_clause:
         module_base_identifier = children.module_inheritance_clause [0]

      module = ast.Module (module_identifier, module_base_identifier)
      global_namespace.add (module)

      if children.module_body:
         entities = children.module_body [0]
         module.add (entities)

      return global_namespace

   def visit_module_name (self, node, children):
      return self.visit_identifier (node, children)

   def visit_module_body (self, node, children):
      return children [0] if children else []

   def visit_module_entities (self, node, children):
      return list (children)


   #-- Board -----------------------------------------------------------------

   def visit_board_declaration (self, node, children):
      board_name = children.board_name [0]

      board = ast.Board (board_name)

      return board

   def visit_board_name (self, node, children):
      return self.visit_identifier (node, children)



   #-- Width -----------------------------------------------------------------

   def visit_width_declaration (self, node, children):
      distance = children.distance_declaration [0]

      width = ast.Width (distance)

      return width


   #-- Material --------------------------------------------------------------

   def visit_material_declaration (self, node, children):
      material_name = children.material_name [0]
      material_color = None
      if children.material_color:
         material_color = children.material_color [0]

      material = ast.Material (material_name, material_color)

      return material

   def visit_material_name (self, node, children):
      return self.to_keyword (node)

   def visit_material_color (self, node, children):
      return self.to_keyword (node)


   #-- Header ----------------------------------------------------------------

   def visit_header_declaration (self, node, children):
      header = ast.Header ()

      if children.header_body:
         entities = children.header_body [0]
         header.add (entities)

      return header

   def visit_header_body (self, node, children):
      return children [0] if children else []

   def visit_header_entities (self, node, children):
      return list (children)


   #-- Footer ----------------------------------------------------------------

   def visit_footer_declaration (self, node, children):
      footer = ast.Footer ()

      if children.footer_body:
         entities = children.footer_body [0]
         footer.add (entities)

      return footer

   def visit_footer_body (self, node, children):
      return children [0] if children else []

   def visit_footer_entities (self, node, children):
      return list (children)


   #-- Module Faust ----------------------------------------------------------

   def visit_mod_faust_declaration (self, node, children):
      faust = ast.ModuleFaust ()

      if children.mod_faust_body:
         entities = children.mod_faust_body [0]
         faust.add (entities)

      return faust

   def visit_mod_faust_body (self, node, children):
      return children [0] if children else []

   def visit_mod_faust_entities (self, node, children):
      return list (children)


   #-- Module Faust Init -----------------------------------------------------

   def visit_mod_faust_init_declaration (self, node, children):
      faust = ast.ModuleFaustInit ()

      if children.mod_faust_init_body:
         entities = children.mod_faust_init_body [0]
         faust.add (entities)

      return faust

   def visit_mod_faust_init_body (self, node, children):
      return children [0] if children else []

   def visit_mod_faust_init_entities (self, node, children):
      return list (children)


   #-- Faust Bind ------------------------------------------------------------

   def visit_faust_bind_declaration (self, node, children):
      bind = ast.FaustBind ()

      if children.faust_bind_body:
         entities = children.faust_bind_body [0]
         bind.add (entities)

      return bind

   def visit_faust_bind_body (self, node, children):
      return children [0] if children else []

   def visit_faust_bind_entities (self, node, children):
      return list (children)


   #-- Faust Property --------------------------------------------------------

   def visit_faust_property_declaration (self, node, children):
      property_name = children.faust_property_name [0]
      property = ast.FaustProperty (property_name)
      return property

   def visit_faust_property_name (self, node, children):
      return self.visit_identifier (node, children)


   #-- Faust Address ---------------------------------------------------------

   def visit_faust_address_declaration (self, node, children):
      string_literal = children.string_literal [0]
      address = ast.FaustAddress (string_literal)
      return address


   #-- Faust Value -----------------------------------------------------------

   def visit_faust_value_declaration (self, node, children):
      float_literal = children.float_literal [0]
      value = ast.FaustValue (float_literal)
      return value


   #-- File ------------------------------------------------------------------

   def visit_file_declaration (self, node, children):
      string_literal = children.string_literal [0]
      dir_name = os.path.dirname (self.filename)
      file_path = os.path.join (dir_name, string_literal.value)
      file_path_str = str (file_path)
      file = ast.File (file_path_str, string_literal)

      return file


   #-- Image -----------------------------------------------------------------

   def visit_image_declaration (self, node, children):
      string_literal = children.string_literal [0]
      dir_name = os.path.dirname (self.filename)
      image_path = os.path.join (dir_name, string_literal.value)
      image_path_str = str (image_path)
      image = ast.Image (image_path_str)

      return image


   #-- Label -----------------------------------------------------------------

   def visit_label_declaration (self, node, children):
      string_literal = children.string_literal [0]
      label = ast.Label (string_literal)

      if children.label_body:
         entities = children.label_body [0]
         label.add (entities)

      return label

   def visit_label_body (self, node, children):
      return children [0] if children else []

   def visit_label_entities (self, node, children):
      return list (children)


   #-- Sticker ---------------------------------------------------------------

   def visit_sticker_declaration (self, node, children):
      string_literal = children.string_literal [0]
      sticker = ast.Sticker (string_literal)

      if children.sticker_body:
         entities = children.sticker_body [0]
         sticker.add (entities)

      return sticker

   def visit_sticker_body (self, node, children):
      return children [0] if children else []

   def visit_sticker_entities (self, node, children):
      return list (children)


   #-- Control Faust ---------------------------------------------------------

   def visit_ctrl_faust_declaration (self, node, children):
      faust = ast.ControlFaust ()

      if children.ctrl_faust_body:
         entities = children.ctrl_faust_body [0]
         faust.add (entities)

      return faust

   def visit_ctrl_faust_body (self, node, children):
      return children [0] if children else []

   def visit_ctrl_faust_entities (self, node, children):
      return list (children)


   #-- Control Faust Init ----------------------------------------------------

   def visit_ctrl_faust_init_declaration (self, node, children):
      init = ast.ControlFaustInit ()

      if children.ctrl_faust_init_body:
         entities = children.ctrl_faust_init_body [0]
         init.add (entities)

      return init

   def visit_ctrl_faust_init_body (self, node, children):
      return children [0] if children else []

   def visit_ctrl_faust_init_entities (self, node, children):
      return list (children)


   #-- Control ---------------------------------------------------------------

   def visit_control_declaration (self, node, children):
      control_name = children.control_name [0]
      control_kind = children.control_kind [0]

      control = ast.Control (control_name, control_kind)

      if children.control_body:
         entities = children.control_body [0]
         control.add (entities)

      return control

   def visit_control_name (self, node, children):
      return self.visit_identifier (node, children)

   def visit_control_kind (self, node, children):
      return self.to_keyword (node)

   def visit_control_body (self, node, children):
      return children [0] if children else []

   def visit_control_entities (self, node, children):
      return list (children)


   #-- Cascade ---------------------------------------------------------------

   def visit_cascade_declaration (self, node, children):
      cascade_reference = children.cascade_reference [0]
      cascade = ast.CascadeTo (cascade_reference)

      return cascade

   def visit_cascade_reference (self, node, children):
      return self.visit_identifier (node, children)


   #-- Alias -----------------------------------------------------------------

   def visit_alias_declaration (self, node, children):
      alias_name = children.alias_name [0]
      alias_reference = children.alias_reference [0]
      alias = ast.Alias (alias_name, alias_reference)

      return alias

   def visit_alias_name (self, node, children):
      return self.visit_identifier (node, children)

   def visit_alias_reference (self, node, children):
      return self.visit_identifier (node, children)


   #-- Mode ------------------------------------------------------------------

   def visit_mode_declaration (self, node, children):
      mode_value = children.mode_value [0]
      mode = ast.Mode (mode_value)

      return mode

   def visit_mode_value (self, node, children):
      return self.to_keyword (node)


   #-- Position --------------------------------------------------------------

   def visit_position_declaration (self, node, children):
      distance_x = children.distance_declaration [0]
      distance_y = children.distance_declaration [1]
      position = ast.Position (distance_x, distance_y)

      return position


   #-- Rotation --------------------------------------------------------------

   def visit_rotation_declaration (self, node, children):
      angle = children.angle_declaration [0]
      rotation = ast.Rotation (angle)

      return rotation


   #-- Positioning -----------------------------------------------------------

   def visit_positioning_declaration (self, node, children):
      positioning_name = children.positioning_name [0]
      positioning = ast.Positioning (positioning_name)

      return positioning

   def visit_positioning_name (self, node, children):
      return self.to_keyword (node)


   #-- Style -----------------------------------------------------------------

   def visit_style_declaration (self, node, children):
      style_name = children.style_name [0]
      style = ast.Style (style_name)

      return style

   def visit_style_name (self, node, children):
      return self.to_keyword (node)


   #-- Pin & Pins ------------------------------------------------------------

   def visit_pin_declaration (self, node, children):
      pin_name = children.pin_name [0]
      pin = ast.Pin (pin_name)

      return pin

   def visit_pins_declaration (self, node, children):
      pin_names = []
      for pin_name in children.pin_name:
         pin_names.append (pin_name)
      pins = ast.Pins (pin_names)

      return pins

   def visit_pin_name (self, node, children):
      return self.visit_identifier (node, children)


   #-- Line ------------------------------------------------------------------

   def visit_line_declaration (self, node, children):
      line = ast.Line ()

      if children.line_body:
         entities = children.line_body [0]
         line.add (entities)

      return line

   def visit_line_body (self, node, children):
      return children [0] if children else []

   def visit_line_entities (self, node, children):
      return list (children)







