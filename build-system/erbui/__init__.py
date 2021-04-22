##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

from . import ast
from .parser import Parser
from .generators.vcvrack.panel import Panel as vcvrackPanel
from .generators.vcvrack.manifest import Manifest as vcvrackManifest
from .generators.vcvrack.code import Code as vcvrackCode
from .generators.vcvrack.deploy import Deploy as vcvrackDeploy
from .generators.front_panel.milling import Milling as front_panelMilling
from .generators.front_panel.printing import Printing as front_panelPrinting

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))



"""
==============================================================================
Name: parse_ui
==============================================================================
"""

def parse_ui (name, path):
   filepath = os.path.join (path, name)

   with open (filepath, "r") as data:
      input_text = data.read ()

   parser = Parser ()
   return parser.parse (input_text, filepath)



"""
==============================================================================
Name: generate_vcvrack_panel
==============================================================================
"""

def generate_vcvrack_panel (name, path, module):
   generator = vcvrackPanel ()
   generator.generate (name, path, module)



"""
==============================================================================
Name: generate_vcvrack_manifest
==============================================================================
"""

def generate_vcvrack_manifest (name, path, module):
   generator = vcvrackManifest ()
   generator.generate (name, path, module)



"""
==============================================================================
Name: generate_vcvrack_code
==============================================================================
"""

def generate_vcvrack_code (name, path, module):
   generator = vcvrackCode ()
   generator.generate (name, path, module)



"""
==============================================================================
Name: generate_vcvrack_deploy
==============================================================================
"""

def generate_vcvrack_deploy (name, path, module):
   generator = vcvrackDeploy ()
   generator.generate (name, path, module)



"""
==============================================================================
Name: generate_front_panel_milling
==============================================================================
"""

def generate_front_panel_milling (name, path, module):
   generator = front_panelMilling ()
   generator.generate (name, path, module)



"""
==============================================================================
Name: generate_front_panel_printing
==============================================================================
"""

def generate_front_panel_printing (name, path, module):
   generator = front_panelPrinting ()
   generator.generate (name, path, module)
