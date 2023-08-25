##############################################################################
#
#     kicad_pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import math
import os
import platform
import re
import shutil
import subprocess
import zipfile
from ..kicad import pcb


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS)))))
PATH_BOARDS = os.path.join (PATH_ROOT, 'boards')

PANEL_HEIGHT = 128.5#mm
HP_TO_MM = 5.08#mm

class KicadPcb:

   def generate (self, path, root):
      for module in root.modules:
         self.generate_module (path, module)


   #--------------------------------------------------------------------------

   def generate_gerber (self, path, root):
      for module in root.modules:
         self.fill_zones (path, module)
         self.generate_module_gerber (path, module)


   #--------------------------------------------------------------------------

   def generate_module (self, path, module):

      for generator in module.manufacturer_data ['generators']:
         if generator ['id'] == 'front_pcb/kicad_pcb':
            remove_all_pads = not module.route.is_wire
            self.remove_board_pads (module, remove_all_pads)

            for control in module.controls:
               self.generate_control (module, control)

            path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

            if os.path.exists (path_pcb) and module.route.is_manual:
               ## update pcb rather than overwrite

               kicad_pcb = pcb.Root.read (os.path.abspath (path_pcb))

               # only footprints for now
               kicad_pcb.footprints = module.pcb.footprints

               self.fix_net_indexes (kicad_pcb)
               kicad_pcb.write (path_pcb)

            else:
               module.pcb.write (path_pcb)

            if module.route.is_wire:
               self.fill_zones (path, module)

            self.generate_module_gerber (path, module)


   #--------------------------------------------------------------------------
   # Remove wire pads and associated traces either:
   # - When the associated pin is unused
   # - Or always, when 'all' is True

   def remove_board_pads (self, module, all=False):
      net_numbers = []

      # filter pins to remove and collect net numbers of traces to remove
      def filter_footprint (footprint):
         if footprint.name.startswith ('TestPoint:TestPoint_Pad'):
            net_number = footprint.pads [0].net.index

            if all:
               net_numbers.append (net_number)
               return False

            if footprint.reference in module.unused_pins:
               net_numbers.append (net_number)
               return False

         return True

      module.pcb.footprints = list (filter (filter_footprint, module.pcb.footprints))

      # filter segments (traces) with matchin net number to remove
      def filter_segment (segment):
         return segment.net not in net_numbers

      module.pcb.segments = list (filter (filter_segment, module.pcb.segments))


   #--------------------------------------------------------------------------
   # When loading an existing board, KiCad might have changed net indexes
   # eg. typically, busses net indexes can disappear
   # Make sure that the net index matches the name in all footprints

   def fix_net_indexes (self, kicad_pcb):
      net_name_index_map = {}
      for net in kicad_pcb.nets:
         net_name_index_map [net.name] = net.index

      for footprint in kicad_pcb.footprints:
         for pad in footprint.pads:
            if pad.net:
               pad.net.index = net_name_index_map [pad.net.name]


   #--------------------------------------------------------------------------

   def get_kicad_python_path (self):
      if platform.system () == 'Darwin':
         return os.path.join (PATH_TOOLCHAIN, 'KiCad.app', 'Contents', 'Frameworks', 'Python.framework', 'Versions', '3.8', 'bin', 'python3.8')

      elif platform.system () == 'Windows':
         return os.path.join (PATH_TOOLCHAIN, 'KiCad', '6.0', 'bin', 'python.exe')

      else:
         return 'python'


   #--------------------------------------------------------------------------

   def fill_zones (self, path, module):
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)

      subprocess.check_call (
         [
            self.get_kicad_python_path (),
            os.path.join (PATH_THIS, 'fill_zones.py'),
            path_pcb
         ],
         cwd = PATH_THIS
      )


   #--------------------------------------------------------------------------

   def generate_module_gerber (self, path, module):
      path_pcb = os.path.join (path, '%s.kicad_pcb' % module.name)
      gerber_dir = os.path.join (path, 'gerber')

      if os.path.exists (gerber_dir):
         shutil.rmtree (gerber_dir)

      subprocess.check_call (
         [
            self.get_kicad_python_path (),
            os.path.join (PATH_THIS, 'generate_gerber.py'),
            path, path_pcb
         ],
         cwd = PATH_THIS
      )

      def zipdir (path, zip_file):
         for root, dirs, files in os.walk (path):
            for file in files:
               zip_file.write (os.path.join (root, file), file)

      path_zip = os.path.join (path, '%s.gerber.zip' % module.name)
      zip_file = zipfile.ZipFile (path_zip, 'w', zipfile.ZIP_DEFLATED)
      zipdir (gerber_dir, zip_file)
      zip_file.close ()


   #--------------------------------------------------------------------------

   def generate_control (self, module, control):
      for part in control.parts:
         module.pcb.footprints.extend (part.pcb.footprints)
         module.pcb.gr_shapes.extend (part.pcb.gr_shapes)
         module.pcb.segments.extend (part.pcb.segments)
         module.pcb.zones.extend (part.pcb.zones)
