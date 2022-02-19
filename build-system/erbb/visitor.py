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


   #-- Module ----------------------------------------------------------------

   def visit_module_declaration (self, node, children):
      global_namespace = ast.GlobalNamespace ()

      module_identifier = children.module_name [0]

      module = ast.Module (module_identifier)
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


   #-- Section ---------------------------------------------------------------

   def visit_section_declaration (self, node, children):
      section_keyword = children.section_name [0]
      section = ast.Section (section_keyword)

      return section

   def visit_section_name (self, node, children):
      return self.to_keyword (node)


   #-- Library ---------------------------------------------------------------

   def visit_library_declaration (self, node, children):
      library = ast.Library ()

      if children.module_entities:
         entities = children.module_entities [0]
         library.add (entities)

      return library


   #-- File ------------------------------------------------------------------

   def visit_file_declaration (self, node, children):
      string_literal = children.string_literal [0]
      dir_name = os.path.dirname (self.filename)
      file_path = os.path.join (dir_name, string_literal.value)
      file_path_str = str (file_path)
      file = ast.File (file_path_str, string_literal)

      return file


   #-- Import ----------------------------------------------------------------

   def visit_import_declaration (self, node, children):
      string_literal = children.string_literal [0]
      dir_name = os.path.dirname (self.filename)
      file_path = os.path.join (dir_name, string_literal.value)
      file_path_str = str (file_path)
      import_ = ast.Import (file_path_str, string_literal)

      return import_


   #-- Define ----------------------------------------------------------------

   def visit_define_declaration (self, node, children):
      define_key_identifier = children.define_key [0]
      define_value = children.define_value [0]

      define = ast.Define (define_key_identifier, define_value)

      return define

   def visit_define_key (self, node, children):
      return self.visit_identifier (node, children)

   def visit_define_value (self, node, children):
      return self.to_literal (node)


   #-- Sources ---------------------------------------------------------------

   def visit_sources_declaration (self, node, children):

      sources = ast.Sources ()

      if children.sources_body:
         entities = children.sources_body [0]
         sources.add (entities)

      return sources

   def visit_sources_body (self, node, children):
      return children [0] if children else []

   def visit_sources_entities (self, node, children):
      return list (children)


   #-- Stream ----------------------------------------------------------------

   def visit_stream_declaration (self, node, children):
      stream_format = children.stream_format [0]
      stream = ast.Stream (stream_format)
      return stream

   def visit_stream_format (self, node, children):
      return self.to_keyword (node)


   #-- Faust Address ---------------------------------------------------------

   def visit_faust_address_declaration (self, node, children):
      string_literal = children.string_literal [0]
      address = ast.FaustAddress (string_literal)
      return address


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


   #-- Faust -----------------------------------------------------------------

   def visit_faust_declaration (self, node, children):
      faust = ast.Faust ()

      if children.faust_body:
         entities = children.faust_body [0]
         faust.add (entities)

      return faust

   def visit_faust_body (self, node, children):
      return children [0] if children else []

   def visit_faust_entities (self, node, children):
      return list (children)


   #-- Data ------------------------------------------------------------------

   def visit_data_declaration (self, node, children):
      data_name_identifier = children.data_name [0]

      data_type_identifier = None
      if children.data_type:
         data_type_identifier = children.data_type [0]

      data = ast.Data (data_name_identifier, data_type_identifier)

      if children.data_body:
         entities = children.data_body [0]
         data.add (entities)

      return data

   def visit_data_name (self, node, children):
      return self.visit_identifier (node, children)

   def visit_data_type (self, node, children):
      return self.visit_identifier (node, children)

   def visit_data_body (self, node, children):
      return children [0] if children else []

   def visit_data_entities (self, node, children):
      return list (children)


   #-- Resources -------------------------------------------------------------

   def visit_resources_declaration (self, node, children):

      resources = ast.Resources ()

      if children.resources_body:
         entities = children.resources_body [0]
         resources.add (entities)

      return resources

   def visit_resources_body (self, node, children):
      return children [0] if children else []

   def visit_resources_entities (self, node, children):
      return list (children)


   #-- Base ------------------------------------------------------------------

   def visit_base_declaration (self, node, children):
      string_literal = children.string_literal [0]
      dir_name = os.path.dirname (self.filename)
      file_path = os.path.join (dir_name, string_literal.value)
      file_path_str = str (file_path)
      base = ast.Base (file_path_str, string_literal)

      return base
