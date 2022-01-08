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
