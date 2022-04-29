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
from .generators.daisy.code import Code as daisyCode
from .generators.front_panel.dxf import Dxf as front_panelDxf
from .generators.front_panel.pdf import Pdf as front_panelPdf
from .generators.front_pcb.kicad_pcb import KicadPcb as kicad_pcbKicadPcb
from .generators.front_pcb.bom import Bom as front_pcbBom
from .generators.front_pcb.centroid import Centroid as front_pcbCentroid
from .generators.max.code import Code as maxCode
from .generators.faust.code import Code as faustCode

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (PATH_THIS)))



"""
==============================================================================
Name: parse
==============================================================================
"""

def parse (filepath):
   with open (filepath, 'r', encoding='utf-8') as data:
      input_text = data.read ()

   parser = Parser ()
   return parser.parse (input_text, filepath)



"""
==============================================================================
Name: generate_max
==============================================================================
"""

def generate_max (path, ast):
   generator = maxCode ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_faust
==============================================================================
"""

def generate_faust (path, ast):
   generator = faustCode ()
   generator.generate (path, ast)



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
Name: generate_hardware
==============================================================================
"""

def generate_hardware (path, ast):
   path_hardware = os.path.join (path, 'hardware')
   if not os.path.exists (path_hardware):
      os.makedirs (path_hardware)

   for generator in ast.modules [0].manufacturer_data ['generators']:
      generator_id = generator ['id']
      if generator_id == 'front_panel/dxf':
         generate_front_panel_dxf (path_hardware, ast)
      elif generator_id == 'front_panel/pdf':
         generate_front_panel_pdf (path_hardware, ast)
      elif generator_id == 'front_pcb/kicad_pcb':
         generate_front_pcb_kicad_pcb (path_hardware, ast)
      elif generator_id == 'front_pcb/bom':
         generate_front_pcb_bom (path_hardware, ast)
      elif generator_id == 'front_pcb/centroid':
         generate_front_pcb_centroid (path_hardware, ast)



"""
==============================================================================
Name: generate_front_panel_dxf
==============================================================================
"""

def generate_front_panel_dxf (path, ast):
   generator = front_panelDxf ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_front_panel_pdf
==============================================================================
"""

def generate_front_panel_pdf (path, ast):
   generator = front_panelPdf ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_front_pcb_kicad_pcb
==============================================================================
"""

def generate_front_pcb_kicad_pcb (path, ast):
   generator = kicad_pcbKicadPcb ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_front_pcb_bom
==============================================================================
"""

def generate_front_pcb_bom (path, ast):
   generator = front_pcbBom ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_front_pcb_centroid
==============================================================================
"""

def generate_front_pcb_centroid (path, ast):
   generator = front_pcbCentroid ()
   generator.generate (path, ast)



"""
==============================================================================
Name: generate_front_pcb_gerber
==============================================================================
"""

def generate_front_pcb_gerber (path, ast):
   path_hardware = os.path.join (path, 'hardware')
   if not os.path.exists (path_hardware):
      os.makedirs (path_hardware)

   generator = kicad_pcbKicadPcb ()
   generator.generate_gerber (path_hardware, ast)
