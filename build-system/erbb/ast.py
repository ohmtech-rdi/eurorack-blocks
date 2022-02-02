##############################################################################
#
#     ast.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from . import adapter
from . import grammar



# -- Node AST ----------------------------------------------------------------

class Node:
   def __init__ (self):
      self.parent = None
      self.extra_tokens = lambda: None

   @property
   def parent_scope (self):
      parent = self.parent
      if parent is not None:
         return parent if parent.is_scope else parent.parent_scope
      return None

   def source_context_part (self, part):
      # This method needs to be overloaded by subclasses
      assert False # pragma: no cover

   @property
   def is_literal (self): return isinstance (self, Literal)

   @property
   def is_string_literal (self): return isinstance (self, StringLiteral)

   @property
   def is_global_namespace (self): return isinstance (self, GlobalNamespace)

   @property
   def is_module (self): return isinstance (self, Module)

   @property
   def is_section (self): return isinstance (self, Section)

   @property
   def is_library (self): return isinstance (self, Library)

   @property
   def is_file (self): return isinstance (self, File)

   @property
   def is_import (self): return isinstance (self, Import)

   @property
   def is_define (self): return isinstance (self, Define)

   @property
   def is_sources (self): return isinstance (self, Sources)

   @property
   def is_resources (self): return isinstance (self, Resources)

   @property
   def is_data (self): return isinstance (self, Data)

   @property
   def is_stream (self): return isinstance (self, Stream)

   @property
   def is_base (self): return isinstance (self, Base)



# -- Scope -------------------------------------------------------------------

class Scope (Node):
   def __init__ (self):
      super (Scope, self).__init__ ()
      self.entities = []

   def add (self, entity_or_entities):
      if isinstance (entity_or_entities, list):
         entities = entity_or_entities
         for entity in entities:
            self.add (entity)

      else:
         entity = entity_or_entities
         assert entity not in self.entities
         entity.parent = self
         self.entities.append (entity)



# -- Literals ----------------------------------------------------------------

class Literal (Node):
   def __init__ (self, literal):
      super (Literal, self).__init__ ()
      self.literal = literal

   @property
   def source_context (self):
      return self.source_context_part ('full')

   def source_context_part (self, part):
      if part == 'full':
         return adapter.SourceContext.from_token (self.literal)

      return super (Literal, self).source_context_part (part) # pragma: no cover


class StringLiteral (Literal):
   def __init__ (self, literal):
      assert isinstance (literal, adapter.Literal)
      super (StringLiteral, self).__init__ (literal)

   @property
   def value (self): return str (self.literal.value.strip ('"'))



# -- GlobalNamespace ---------------------------------------------------------

class GlobalNamespace (Scope):
   def __init__ (self):
      super (GlobalNamespace, self).__init__ ()

   @property
   def modules (self):
      entities = [e for e in self.entities if e.is_module]
      return entities



# -- Module ------------------------------------------------------------------

class Module (Scope):
   def __init__ (self, identifier):
      assert isinstance (identifier, adapter.Identifier)
      super (Module, self).__init__ ()
      self.identifier = identifier
      self.source_language = 'cpp'

   @staticmethod
   def typename (): return 'module'

   @property
   def name (self): return self.identifier.name

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.identifier)

      return super (Module, self).source_context_part (part) # pragma: no cover

   @property
   def section (self):
      entities = [e for e in self.entities if e.is_section]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def imports (self):
      entities = [e for e in self.entities if e.is_import]
      return entities

   @property
   def defines (self):
      entities = [e for e in self.entities if e.is_define]
      return entities

   @property
   def sources (self):
      entities = [e for e in self.entities if e.is_sources]
      return entities

   @property
   def resources (self):
      entities = [e for e in self.entities if e.is_resources]
      return entities

   @property
   def bases (self):
      entities = [e for e in self.entities if e.is_base]
      return entities



# -- Library -----------------------------------------------------------------

class Section (Scope):
   def __init__ (self, section_keyword):
      super (Section, self).__init__ ()
      self.name_keyword = section_keyword

   @staticmethod
   def typename (): return 'section'

   @property
   def name (self):
      return self.name_keyword.value

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.name_keyword)

      return super (Section, self).source_context_part (part) # pragma: no cover



# -- Library -----------------------------------------------------------------

class Library (Scope):
   def __init__ (self):
      super (Library, self).__init__ ()

   @staticmethod
   def typename (): return 'library'

   @property
   def imports (self):
      entities = [e for e in self.entities if e.is_import]
      return entities

   @property
   def defines (self):
      entities = [e for e in self.entities if e.is_define]
      return entities

   @property
   def sources (self):
      entities = [e for e in self.entities if e.is_sources]
      return entities

   @property
   def bases (self):
      entities = [e for e in self.entities if e.is_base]
      return entities



# -- File --------------------------------------------------------------------

class File (Node):
   def __init__ (self, filepath, literal):
      assert isinstance (filepath, str)
      assert isinstance (literal, StringLiteral)
      super (File, self).__init__ ()
      self.filepath = filepath
      self.literal = literal

   @staticmethod
   def typename (): return 'file'

   @property
   def path (self):
      return self.filepath

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.literal.literal)

      return super (File, self).source_context_part (part) # pragma: no cover



# -- Import ------------------------------------------------------------------

class Import (Node):
   def __init__ (self, filepath, literal):
      assert isinstance (filepath, str)
      assert isinstance (literal, StringLiteral)
      super (Import, self).__init__ ()
      self.filepath = filepath
      self.literal = literal

   @staticmethod
   def typename (): return 'import'

   @property
   def path (self):
      return self.filepath

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.literal.literal)

      return super (Import, self).source_context_part (part) # pragma: no cover



# -- Base --------------------------------------------------------------------

class Base (Node):
   def __init__ (self, filepath, literal):
      assert isinstance (filepath, str)
      assert isinstance (literal, StringLiteral)
      super (Base, self).__init__ ()
      self.filepath = filepath
      self.literal = literal

   @staticmethod
   def typename (): return 'base'

   @property
   def path (self):
      return self.filepath

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.literal.literal)

      return super (Base, self).source_context_part (part) # pragma: no cover



# -- Define ------------------------------------------------------------------

class Define (Node):
   def __init__ (self, key_identifier, value_literal):
      assert isinstance (key_identifier, adapter.Identifier)
      assert isinstance (value_literal, adapter.Literal)
      super (Define, self).__init__ ()
      self.key_identifier = key_identifier
      self.value_literal = value_literal

   @staticmethod
   def typename (): return 'define'

   @property
   def key (self): return self.key_identifier.name

   @property
   def value (self): return self.value_literal.value

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.key_identifier)

      return super (Define, self).source_context_part (part) # pragma: no cover



# -- Sources -----------------------------------------------------------------

class Sources (Scope):
   def __init__ (self):
      super (Sources, self).__init__ ()

   @staticmethod
   def typename (): return 'sources'

   @property
   def files (self):
      entities = [e for e in self.entities if e.is_file]
      return entities



# -- Resources ---------------------------------------------------------------

class Resources (Scope):
   def __init__ (self):
      super (Resources, self).__init__ ()

   @staticmethod
   def typename (): return 'resources'

   @property
   def datas (self):
      entities = [e for e in self.entities if e.is_data]
      return entities



# -- Data --------------------------------------------------------------------

class Data (Scope):
   def __init__ (self, name_identifier, type_identifier):
      assert isinstance (name_identifier, adapter.Identifier)
      assert type_identifier is None or isinstance (type_identifier, adapter.Identifier)
      super (Data, self).__init__ ()
      self.name_identifier = name_identifier
      self.type_identifier = type_identifier

   @staticmethod
   def typename (): return 'data'

   @property
   def name (self): return self.name_identifier.name

   @property
   def type_ (self): return self.type_identifier.name if self.type_identifier is not None else None

   @property
   def source_context (self):
      return self.source_context_part ('name')

   def source_context_part (self, part):
      if part == 'name':
         return adapter.SourceContext.from_token (self.name_identifier)

      return super (Data, self).source_context_part (part) # pragma: no cover

   @property
   def file (self):
      entities = [e for e in self.entities if e.is_file]
      assert (len (entities) == 1)
      return entities [0]

   @property
   def stream (self):
      entities = [e for e in self.entities if e.is_stream]
      assert (len (entities) <= 1)
      if entities:
         return entities [0]
      else:
         return None



# -- Stream ------------------------------------------------------------------

class Stream (Node):
   def __init__ (self, format):
      assert isinstance (format, adapter.Keyword)
      super (Stream, self).__init__ ()
      self.format_keyword = format

   @property
   def format (self): return self.format_keyword.value

   @property
   def source_context (self):
      return self.source_context_part ('format')

   def source_context_part (self, part):
      if part == 'format':
         return adapter.SourceContext.from_token (self.format_keyword)

      return super (Stream, self).source_context_part (part) # pragma: no cover
