##############################################################################
#
#     pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import logging
import math
import os
import platform
import shutil
import subprocess
import sys
import zipfile

from ..detail.panel import Panel as detailPanel
from ..kicad import pcb as kicadPcb
from ..kicad import s_expression

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))

if platform.system () == 'Windows':
   bin_dir = os.path.join (PATH_BUILD_SYSTEM, 'toolchain', 'msys2_mingw64', 'bin')
   os.environ ['PATH'] = '%s;%s' % (bin_dir, os.environ ['PATH'])
   if sys.version_info >= (3, 8):
      os.add_dll_directory (bin_dir)

import cairocffi

from svg2mod.importer import Svg2ModImport
from svg2mod.exporter import (DEFAULT_DPI, Svg2ModExportPretty)
from svg2mod.coloredlogger import logger

PATH_GENERATORS = os.path.abspath (os.path.dirname (PATH_THIS))

MM_TO_PT = 72.0 / 25.4
MODULE_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm



class Pcb:

   #--------------------------------------------------------------------------

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):
      if not module.material.is_pcb: return # not needed

      self.generate_module_kicad_mod (path, module)
      self.generate_module_fp_lib_table (path, module)
      self.generate_module_kicad_pcb (path, module)
      self.fill_zones (path, module)
      self.generate_module_gerber (path, module)


   #--------------------------------------------------------------------------

   def generate_module_kicad_mod (self, path, module):
      path_svg = os.path.join (path, '%s.panel.svg' % module.name)

      surface = cairocffi.SVGSurface (path_svg, module.width.pt, MODULE_HEIGHT * MM_TO_PT)
      surface.set_document_unit (cairocffi.SVG_UNIT_PT)
      context = cairocffi.Context (surface)

      panel = detailPanel ()
      panel.generate_module (context, module)

      surface.finish ()

      logger.setLevel (logging.WARNING)

      imported = Svg2ModImport (
         path_svg,
         'silkscreen',
         None,
         False,
         'F.SilkS'
      )

      exported = Svg2ModExportPretty (
         imported,
         os.path.join (path, '%s.panel.kicad_mod' % module.name),
         False,
         1.0,
         0.1,
         dpi = DEFAULT_DPI,
         pads = False,
      )

      exported.write ()


   #--------------------------------------------------------------------------

   def generate_module_fp_lib_table (self, path, module):
      path_fp_lib_table = os.path.join (path, 'fp-lib-table')

      content =  '(fp_lib_table\n'
      content += '  (lib (name Local)(type KiCad)(uri ${KIPRJMOD})(options "")(descr ""))\n'
      content += ')\n'

      with open (path_fp_lib_table, 'w', encoding='utf-8') as file:
         file.write (content)


   #--------------------------------------------------------------------------

   def generate_module_kicad_pcb (self, path, module):
      path_pcb = os.path.join (path, '%s.panel.kicad_pcb' % module.name)
      path_mod = os.path.join (path, '%s.panel.kicad_mod' % module.name)

      panel_pcb = kicadPcb.Root ()
      panel_pcb.version = 20211014
      panel_pcb.generator = 'pcbnew'
      panel_pcb.general.thickness = 1.6
      panel_pcb.paper = 'A4'

      layer = kicadPcb.Layer ()
      layer.index = 0
      layer.name = 'F.Cu'
      layer.type = 'signal'
      panel_pcb.layers.append (layer)

      layer = kicadPcb.Layer ()
      layer.index = 31
      layer.name = 'B.Cu'
      layer.type = 'signal'
      panel_pcb.layers.append (layer)

      layer = kicadPcb.Layer ()
      layer.index = 36
      layer.name = 'B.SilkS'
      layer.type = 'user'
      layer.user_name = 'B.Silkscreen'
      panel_pcb.layers.append (layer)

      layer = kicadPcb.Layer ()
      layer.index = 37
      layer.name = 'F.SilkS'
      layer.type = 'user'
      layer.user_name = 'F.Silkscreen'
      panel_pcb.layers.append (layer)

      layer = kicadPcb.Layer ()
      layer.index = 38
      layer.name = 'B.Mask'
      layer.type = 'user'
      panel_pcb.layers.append (layer)

      layer = kicadPcb.Layer ()
      layer.index = 39
      layer.name = 'F.Mask'
      layer.type = 'user'
      panel_pcb.layers.append (layer)

      layer = kicadPcb.Layer ()
      layer.index = 44
      layer.name = 'Edge.Cuts'
      layer.type = 'user'
      panel_pcb.layers.append (layer)

      panel_pcb.setup.pad_to_mask_clearance = 0.2
      panel_pcb.setup.grid_origin = None
      panel_pcb.setup.pcbplotparams.layerselection = '0x00010fc_ffffffff'
      panel_pcb.setup.pcbplotparams.disableapertmacros = 'false'
      panel_pcb.setup.pcbplotparams.usegerberextensions = 'false'
      panel_pcb.setup.pcbplotparams.usegerberattributes = 'false'
      panel_pcb.setup.pcbplotparams.usegerberadvancedattributes = 'false'
      panel_pcb.setup.pcbplotparams.creategerberjobfile = 'false'
      panel_pcb.setup.pcbplotparams.svguseinch = 'false'
      panel_pcb.setup.pcbplotparams.svgprecision = 6
      panel_pcb.setup.pcbplotparams.excludeedgelayer = 'true'
      panel_pcb.setup.pcbplotparams.plotframeref = 'false'
      panel_pcb.setup.pcbplotparams.viasonmask = 'false'
      panel_pcb.setup.pcbplotparams.mode = 1
      panel_pcb.setup.pcbplotparams.useauxorigin = 'false'
      panel_pcb.setup.pcbplotparams.hpglpennumber = 1
      panel_pcb.setup.pcbplotparams.hpglpenspeed = 20
      panel_pcb.setup.pcbplotparams.hpglpendiameter = 15.000000
      panel_pcb.setup.pcbplotparams.dxfpolygonmode = 'true'
      panel_pcb.setup.pcbplotparams.dxfimperialunits = 'true'
      panel_pcb.setup.pcbplotparams.dxfusepcbnewfont = 'true'
      panel_pcb.setup.pcbplotparams.psnegative = 'false'
      panel_pcb.setup.pcbplotparams.psa4output = 'false'
      panel_pcb.setup.pcbplotparams.plotreference = 'true'
      panel_pcb.setup.pcbplotparams.plotvalue = 'true'
      panel_pcb.setup.pcbplotparams.plotinvisibletext = 'false'
      panel_pcb.setup.pcbplotparams.sketchpadsonfab = 'false'
      panel_pcb.setup.pcbplotparams.subtractmaskfromsilk = 'false'
      panel_pcb.setup.pcbplotparams.outputformat = 1
      panel_pcb.setup.pcbplotparams.mirror = 'false'
      panel_pcb.setup.pcbplotparams.drillshape = 1
      panel_pcb.setup.pcbplotparams.scaleselection = 1
      panel_pcb.setup.pcbplotparams.outputdirectory = ''

      footprint = kicadPcb.Footprint ()
      footprint.name = 'Local:%s.panel' % module.name
      footprint.locked = True
      footprint.layer = 'F.Cu'
      footprint.tedit = '64651566'
      footprint.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
      footprint.at.x = 0.0
      footprint.at.y = 0.0
      footprint.path = '/d90f81ac-9d83-4f16-b87d-ae4c6fb48b47'

      with open (path_mod, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      root_node = parser.parse (content, path_mod)

      for fp_shape_node in root_node.filter_kind ('fp_poly'):
         fp_shape = kicadPcb.Footprint.FpPoly.parse (fp_shape_node)
         fp_shape.fill = 'solid'
         fp_shape.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
         footprint.fp_shapes.append (fp_shape)

      panel_pcb.footprints.append (footprint)

      width_hp = round (module.width.mm / HP_TO_MM)
      final_width = self.get_final_width (width_hp)

      gr_line = kicadPcb.GrLine ()
      gr_line.start.x = 0
      gr_line.start.y = 0
      gr_line.end.x = final_width
      gr_line.end.y = 0
      gr_line.layer = 'Edge.Cuts'
      gr_line.width = 0.15
      gr_line.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
      panel_pcb.gr_shapes.append (gr_line)

      gr_line = kicadPcb.GrLine ()
      gr_line.start.x = final_width
      gr_line.start.y = 0
      gr_line.end.x = final_width
      gr_line.end.y = MODULE_HEIGHT
      gr_line.layer = 'Edge.Cuts'
      gr_line.width = 0.15
      gr_line.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
      panel_pcb.gr_shapes.append (gr_line)

      gr_line = kicadPcb.GrLine ()
      gr_line.start.x = final_width
      gr_line.start.y = MODULE_HEIGHT
      gr_line.end.x = 0
      gr_line.end.y = MODULE_HEIGHT
      gr_line.layer = 'Edge.Cuts'
      gr_line.width = 0.15
      gr_line.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
      panel_pcb.gr_shapes.append (gr_line)

      gr_line = kicadPcb.GrLine ()
      gr_line.start.x = 0
      gr_line.start.y = MODULE_HEIGHT
      gr_line.end.x = 0
      gr_line.end.y = 0
      gr_line.layer = 'Edge.Cuts'
      gr_line.width = 0.15
      gr_line.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
      panel_pcb.gr_shapes.append (gr_line)

      for control in module.controls:
         for part in control.parts:
            for gr_shape in part.pcb.gr_shapes:
               if isinstance (gr_shape, kicadPcb.GrCircle) and gr_shape.layer == 'Eco1.User':
                  gr_hole = kicadPcb.GrCircle ()
                  gr_hole.center = gr_shape.center
                  gr_hole.end = gr_shape.end
                  gr_hole.layer = 'Edge.Cuts'
                  gr_hole.width = 0.15
                  gr_hole.fill = 'none'
                  gr_hole.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
                  panel_pcb.gr_shapes.append (gr_hole)


      def add_mounting_hole (x, y):
         footprint = kicadPcb.Footprint ()
         footprint.name = 'Local::MountingHole'
         footprint.locked = True
         footprint.layer = 'F.Cu'
         footprint.tedit = '64651566'
         footprint.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
         footprint.at.x = x
         footprint.at.y = y
         footprint.path = '/d90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
         footprint.attr.attributes = ['through_hole']
         pad = kicadPcb.Footprint.Pad ()
         pad.name = ''
         pad.type = 'thru_hole'
         pad.shape = 'oval'
         pad.at.x = 0
         pad.at.y = 0
         pad.size.x = 7.4
         pad.size.y = 4.2
         pad.drill.type = 'oval'
         pad.drill.size_x = 6.4
         pad.drill.size_y = 3.2
         pad.layers.names = ['*.Cu', '*.Mask']
         pad.net = None
         pad.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
         footprint.pads.append (pad)
         panel_pcb.footprints.append (footprint)

      left = 7.5
      hole_size = 3.2
      edge_v = 3.0
      add_mounting_hole (left, edge_v)
      add_mounting_hole (left, MODULE_HEIGHT - edge_v)

      width_hp = round (module.width.mm / HP_TO_MM)

      if width_hp >= 10:
         right = left + (width_hp - 3) * HP_TO_MM
         add_mounting_hole (right, edge_v)
         add_mounting_hole (right, MODULE_HEIGHT - edge_v)

      zone = kicadPcb.Zone ()
      zone.net = 0
      zone.net_name = ''
      zone.layer = 'F.Cu'
      zone.tstamp = 'd90f81ac-9d83-4f16-b87d-ae4c6fb48b47'
      zone.hatch.display = 'edge'
      zone.hatch.distance = 0.508
      zone.connect_pads.clearance = 0.508
      zone.min_thickness = 0.254
      zone.fill.thermal_gap = 0.508
      zone.fill.thermal_bridge_width = 0.508
      xy = kicadPcb.Xy ()
      xy.x = 0
      xy.y = 0
      zone.polygon.pts.items.append (xy)
      xy = kicadPcb.Xy ()
      xy.x = final_width
      xy.y = 0
      zone.polygon.pts.items.append (xy)
      xy = kicadPcb.Xy ()
      xy.x = final_width
      xy.y = MODULE_HEIGHT
      zone.polygon.pts.items.append (xy)
      xy = kicadPcb.Xy ()
      xy.x = 0
      xy.y = MODULE_HEIGHT
      zone.polygon.pts.items.append (xy)
      zone.filled_polygon = None
      panel_pcb.zones.append (zone)

      panel_pcb.write (path_pcb)


   #--------------------------------------------------------------------------

   def fill_zones (self, path, module):
      path_pcb = os.path.join (path, '%s.panel.kicad_pcb' % module.name)

      if platform.system () == 'Darwin':
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/3.8/bin/python3.8'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
      elif platform.system () == 'Windows':
         kicad_python_path = 'c:/Program Files/KiCad/6.0/bin/python.exe'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = 'c:/Program Files/KiCad/bin/python.exe'
      else:
         kicad_python_path = 'python'

      subprocess.check_call (
         [
            kicad_python_path,
            os.path.join (PATH_GENERATORS, 'front_pcb', 'fill_zones.py'),
            path_pcb
         ],
         cwd = PATH_THIS
      )


   #--------------------------------------------------------------------------

   def generate_module_gerber (self, path, module):
      path_pcb = os.path.join (path, '%s.panel.kicad_pcb' % module.name)
      gerber_dir = os.path.join (path, 'gerber')

      if os.path.exists (gerber_dir):
         shutil.rmtree (gerber_dir)

      if platform.system () == 'Darwin':
         kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/3.8/bin/python3.8'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = '/Applications/KiCad/kicad.app/Contents/Frameworks/Python.framework/Versions/2.7/bin/python2.7'
      elif platform.system () == 'Windows':
         kicad_python_path = 'c:/Program Files/KiCad/6.0/bin/python.exe'
         if not os.path.exists (kicad_python_path):
            # pre KiCad 6
            kicad_python_path = 'c:/Program Files/KiCad/bin/python.exe'
      else:
         kicad_python_path = 'python'

      subprocess.check_call (
         [
            kicad_python_path,
            os.path.join (PATH_GENERATORS, 'front_pcb', 'generate_gerber.py'),
            path, path_pcb
         ],
         cwd = PATH_THIS
      )

      def zipdir (path, zip_file):
         for root, dirs, files in os.walk (path):
            for file in files:
               zip_file.write (os.path.join (root, file), file)

      path_zip = os.path.join (path, '%s.panel.gerber.zip' % module.name)
      zip_file = zipfile.ZipFile (path_zip, 'w', zipfile.ZIP_DEFLATED)
      zipdir (gerber_dir, zip_file)
      zip_file.close ()


   #--------------------------------------------------------------------------
   #
   # Reference: http://www.doepfer.de/a100_man/a100m_e.htm

   def get_final_width (self, width_hp):
      hp_width_map = {
         2: 9.8,
         4: 20.00,
         6: 30.00,
         8: 40.30,
         10: 50.50,
         12: 60.60,
         14: 70.80,
         16: 80.90,
         18: 91.30,
         20: 101.30,
         21: 106.30, # quarter of 84Hp
         22: 111.40,
         28: 141.90,
         42: 213.00,
      }

      if width_hp in hp_width_map:
         return hp_width_map [width_hp]

      else:
         raise Exception ('unsupported module width hp %d' % width_hp)
