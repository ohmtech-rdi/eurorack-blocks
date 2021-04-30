##############################################################################
#
#     __init__.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os

from . import ast
from .parser import Parser
from .generators.ui.code import Code as uiCode
from .generators.vcvrack.panel import Panel as vcvrackPanel
from .generators.vcvrack.manifest import Manifest as vcvrackManifest
from .generators.vcvrack.code import Code as vcvrackCode
from .generators.vcvrack.deploy import Deploy as vcvrackDeploy
from .generators.daisy.code import Code as daisyCode
from .generators.front_panel.milling import Milling as front_panelMilling
from .generators.front_panel.printing import Printing as front_panelPrinting
from .generators.front_pcb.kicad_pcb import KicadPcb as kicad_pcbKicadPcb

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))



"""
==============================================================================
Name: parse
==============================================================================
"""

def parse (filepath):
   with open (filepath, "r") as data:
      input_text = data.read ()

   parser = Parser ()
   return parser.parse (input_text, filepath)



"""
==============================================================================
Name: generate_ui
==============================================================================
"""

def generate_ui (path, ast):
   generate_ui_code (path, ast)



"""
==============================================================================
Name: generate_ui_code
==============================================================================
"""

def generate_ui_code (path, ast):
   generator = uiCode ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_vcvrack
==============================================================================
"""

def generate_vcvrack (path, ast):
   generate_vcvrack_panel (path, ast)
   generate_vcvrack_manifest (path, ast)
   generate_vcvrack_code (path, ast)
   generate_vcvrack_deploy (path, ast)



"""
==============================================================================
Name: generate_vcvrack_panel
==============================================================================
"""

def generate_vcvrack_panel (path, ast):
   generator = vcvrackPanel ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_vcvrack_manifest
==============================================================================
"""

def generate_vcvrack_manifest (path, ast):
   generator = vcvrackManifest ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_vcvrack_code
==============================================================================
"""

def generate_vcvrack_code (path, ast):
   generator = vcvrackCode ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_vcvrack_deploy
==============================================================================
"""

def generate_vcvrack_deploy (path, ast):
   generator = vcvrackDeploy ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_daisy
==============================================================================
"""

def generate_daisy (path, ast):
   generate_daisy_code (path, ast)



"""
==============================================================================
Name: generate_daisy_code
==============================================================================
"""

def generate_daisy_code (path, module):
   generator = daisyCode ()
   generator.generate (path, module)



"""
==============================================================================
Name: generate_front_panel
==============================================================================
"""

def generate_front_panel (path, ast):
   generate_front_panel_milling (path, ast)
   generate_front_panel_printing (path, ast)



"""
==============================================================================
Name: generate_front_panel_milling
==============================================================================
"""

def generate_front_panel_milling (path, module):
   generator = front_panelMilling ()
   generator.generate (path, module)



"""
==============================================================================
Name: generate_front_panel_printing
==============================================================================
"""

def generate_front_panel_printing (path, ast):
   generator = front_panelPrinting ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_front_pcb
==============================================================================
"""

def generate_front_pcb (path, ast):
   generate_front_pcb_kicad_pcb (path, ast)



"""
==============================================================================
Name: generate_front_pcb_kicad_pcb
==============================================================================
"""

def generate_front_pcb_kicad_pcb (path, ast):
   generator = kicad_pcbKicadPcb ()
   generator.generate (path, ast)






