##############################################################################
#
#     analyser.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from . import adapter
from . import ast
from . import error

import os
from difflib import get_close_matches



class Analyser:

   def __init__ (self):
      self._board_definition = {}
      self._used_pins = {} # map from physical pin number to declaration
      self._cascade_index = 0

   #--------------------------------------------------------------------------

   def analyse (self, global_namespace):
      assert global_namespace.is_global_namespace

      for module in global_namespace.modules:
         self.analyse_module (module)

   #--------------------------------------------------------------------------

   def analyse_module (self, module):
      assert module.is_module

      self.analyse_section (module)

      for sources in module.sources:
         self.analyse_sources (module, sources)

      for resources in module.resources:
         self.analyse_resources (resources)

   #--------------------------------------------------------------------------

   def analyse_section (self, module):
      assert module.is_module

      sections = [e for e in module.entities if e.is_section]
      nbr_sections = len (sections)

      if nbr_sections > 1:
         raise error.multiple_definition (module, sections)

      if nbr_sections == 0:
         section = ast.Section (adapter.BuiltIn ('flash'))
         module.add (section)

   #--------------------------------------------------------------------------

   def analyse_sources (self, module, sources):
      assert sources.is_sources

      for file in sources.files:
         filename, file_extension = os.path.splitext (file.path)
         if file_extension == '.dsp':
            module.source_language = 'faust'

   #--------------------------------------------------------------------------

   def analyse_resources (self, resources):
      assert resources.is_resources

      for data in resources.datas:
         self.analyse_data (data)

   #--------------------------------------------------------------------------

   def analyse_data (self, data):
      assert data.is_data

      files = [e for e in data.entities if e.is_file]
      nbr_files = len (files)

      if nbr_files == 0:
         raise error.missing_required (data, ast.File)
      elif nbr_files > 1:
         raise error.multiple_definition (data, files)

      streams = [e for e in data.entities if e.is_stream]
      nbr_streams = len (streams)

      if nbr_streams == 1:
         stream = streams [0]
         if data.type_ != 'AudioSample':
            err = error.Error ()
            context = stream.source_context
            err.add_error ("stream format in only available for AudioSample data type", context)
            err.add_context (context)
            raise err

      elif nbr_streams > 1:
         raise error.multiple_definition (data, streams)
