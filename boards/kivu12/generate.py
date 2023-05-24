##############################################################################
#
#     build.py
#
#Tab=3########################################################################



##### IMPORT #################################################################

from __future__ import print_function
from collections import Counter
import logging
import math
import os
import platform
import subprocess
import sys

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_BUILD_SYSTEM = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))
PATH_TOOLCHAIN = os.path.join (PATH_BUILD_SYSTEM, 'toolchain')

if platform.system () == 'Darwin':
   sys.path.insert (0, os.path.join (PATH_TOOLCHAIN, 'KiCad.app', 'Contents', 'Frameworks', 'Python.framework', 'Versions', '3.8', 'lib', 'python3.8', 'site-packages'))
elif platform.system () == 'Windows':
   sys.path.insert (0, os.path.join (PATH_TOOLCHAIN, 'KiCad', '6.0', 'bin', 'Lib', 'site-packages'))

import pcbnew



##############################################################################

if sys.version_info < (2, 7):
   print ('This script requires python 2.7 or greater.', file = sys.stderr)
   sys.exit (1)



"""
==============================================================================
Name: generate_gerber
==============================================================================
"""

def generate_gerber (output_dir, pcb_path):

   board = pcbnew.LoadBoard (pcb_path)
   plot_controller = pcbnew.PLOT_CONTROLLER (board)

   plot_options = plot_controller.GetPlotOptions ()
   plot_options.SetOutputDirectory (output_dir)
   plot_options.SetPlotFrameRef (False)
   plot_options.SetSketchPadLineWidth (pcbnew.FromMM (0.1))
   plot_options.SetAutoScale (False)
   plot_options.SetScale (1)
   plot_options.SetMirror (False)

   plot_options.SetUseGerberAttributes (True)
   plot_options.SetUseGerberProtelExtensions (True)

   plot_options.SetExcludeEdgeLayer (True)
   plot_options.SetUseAuxOrigin (False)
   plot_controller.SetColorMode (True)

   plot_options.SetSubtractMaskFromSilk (True)
   plot_options.SetPlotReference (True)
   plot_options.SetPlotValue (False)

   layers = [
      ("F.Cu", pcbnew.F_Cu, "Top layer"),
      ("B.Cu", pcbnew.B_Cu, "Bottom layer"),
      ("F.Paste", pcbnew.F_Paste, "Paste top"),
      ("B.Paste", pcbnew.B_Paste, "Paste bottom"),
      ("F.SilkS", pcbnew.F_SilkS, "Silk top"),
      ("B.SilkS", pcbnew.B_SilkS, "Silk top"),
      ("F.Mask", pcbnew.F_Mask, "Mask top"),
      ("B.Mask", pcbnew.B_Mask, "Mask bottom"),
      ("Edge.Cuts", pcbnew.Edge_Cuts, "Edges"),
   ]

   for layer_info in layers:
      plot_controller.SetLayer (layer_info[1])
      plot_controller.OpenPlotfile (layer_info[0], pcbnew.PLOT_FORMAT_GERBER, layer_info[2])
      plot_controller.PlotLayer ()

   plot_controller.ClosePlot()



"""
==============================================================================
Name: generate_drill
==============================================================================
"""

def generate_drill (output_dir, pcb_path):

   board = pcbnew.LoadBoard (pcb_path)
   excellon_writer = pcbnew.EXCELLON_WRITER (board)

   excellon_writer.SetMapFileFormat (pcbnew.PLOT_FORMAT_GERBER)

   mirror = False
   minimal_header = False
   merge_pth_npth = True
   offset = pcbnew.wxPoint (0, 0)
   excellon_writer.SetOptions (mirror, minimal_header, offset, merge_pth_npth)

   metric_format = True
   excellon_writer.SetFormat (metric_format)

   generate_drill = True
   generate_map = False

   excellon_writer.CreateDrillandMapFilesSet (
      output_dir, generate_drill, generate_map
   )



"""
==============================================================================
Name : generate
==============================================================================
"""

def generate ():
   output_path = os.path.join (PATH_THIS, 'artifacts')
   pcb_path = os.path.join (PATH_THIS, 'kivu12.kicad_pcb')

   output_dir = os.path.join (output_path, 'gerber')
   if not os.path.exists (output_dir):
      os.makedirs (output_dir)

   generate_gerber (output_dir, pcb_path)
   generate_drill (output_dir, pcb_path)



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (generate ())

   except subprocess.CalledProcessError as error:
      print ('Build command exited with %d' % error.returncode, file = sys.stderr)
      sys.exit(1)
