#!/usr/bin/env python
#
#     test_s_expression.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
import unittest
import traceback
from ..generators.front_pcb import s_expression


PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.abspath (os.path.join (PATH_THIS, 'artifacts'))


class TestSExpression (unittest.TestCase):
   def setUp(self):
      if not os.path.exists (PATH_ARTIFACTS):
         os.makedirs (PATH_ARTIFACTS)

   def test_001 (self):
      source = '()'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 0)

   def test_002 (self):
      source = 'foo'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_symbol)
      self.assertEqual (root.value, 'foo')

   def test_002b (self):
      source = 'foo1'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_symbol)
      self.assertEqual (root.value, 'foo1')

   def test_002c (self):
      source = '1foo'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_symbol)
      self.assertEqual (root.value, '1foo')

   def test_002d (self):
      source = '+1foo2'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_symbol)
      self.assertEqual (root.value, '+1foo2')

   def test_002e (self):
      source = '-1foo+.'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_symbol)
      self.assertEqual (root.value, '-1foo+.')

   def test_003 (self):
      source = '0\n'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_integer_literal)
      self.assertEqual (root.value, 0)

   def test_003b (self):
      source = '-0\n'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_integer_literal)
      self.assertEqual (root.value, 0)

   def test_003c (self):
      source = '123\n'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_integer_literal)
      self.assertEqual (root.value, 123)

   def test_004 (self):
      source = '0.0\n'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_float_literal)
      self.assertEqual (root.value, 0)

   def test_004b (self):
      source = '-123.456\n'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_float_literal)
      self.assertEqual (root.value, -123.456)

   def test_005 (self):
      source = '(0)'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      integer_literal = root.entities [0]
      self.assertTrue (integer_literal.is_integer_literal)
      self.assertEqual (integer_literal.value, 0)

   def test_006 (self):
      source = '(foo)'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      symbol = root.entities [0]
      self.assertTrue (symbol.is_symbol)
      self.assertEqual (symbol.value, 'foo')

   def test_007 (self):
      source = '(1foo1+)'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      symbol = root.entities [0]
      self.assertTrue (symbol.is_symbol)
      self.assertEqual (symbol.value, '1foo1+')

   def test_008 (self):
      source = '(12.2)'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      float_literal = root.entities [0]
      self.assertTrue (float_literal.is_float_literal)
      self.assertEqual (float_literal.value, 12.2)

   def test_008b (self):
      source = '("bar")'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      string_literal = root.entities [0]
      self.assertTrue (string_literal.is_string_literal)
      self.assertEqual (string_literal.value, 'bar')

   def test_008c (self):
      source = '("foo\\nbar")'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      string_literal = root.entities [0]
      self.assertTrue (string_literal.is_string_literal)
      self.assertEqual (string_literal.value, 'foo\\nbar')

   def test_009 (self):
      source = '(kicad_pcb (version 20171130) (host pcbnew "(5.1.9-0-10_14)"))'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 3)
      symbol = root.entities [0]
      self.assertTrue (symbol.is_symbol)
      self.assertEqual (symbol.value, 'kicad_pcb')
      list = root.entities [1]
      self.assertTrue (list.is_list)
      self.assertEqual (len (list.entities), 2)
      symbol = list.entities [0]
      self.assertTrue (symbol.is_symbol)
      self.assertEqual (symbol.value, 'version')
      integer_literal = list.entities [1]
      self.assertTrue (integer_literal.is_integer_literal)
      self.assertEqual (integer_literal.value, 20171130)
      list = root.entities [2]
      self.assertTrue (list.is_list)
      self.assertEqual (len (list.entities), 3)
      symbol = list.entities [0]
      self.assertTrue (symbol.is_symbol)
      self.assertEqual (symbol.value, 'host')
      symbol = list.entities [1]
      self.assertTrue (symbol.is_symbol)
      self.assertEqual (symbol.value, 'pcbnew')
      string_literal = list.entities [2]
      self.assertTrue (string_literal.is_string_literal)
      self.assertEqual (string_literal.value, '(5.1.9-0-10_14)')

   def test_010 (self):
      source = '(kicad_pcb (version 20171130) (host pcbnew "(5.1.9-0-10_14)"))'
      filepath = os.path.join (PATH_ARTIFACTS, 'test_generators_front_pcb_s_expression_007.txt')
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
         w = s_expression.Writer ()
         w.write (root, filepath)
         root2 = p.parse (w.write_any (root), 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertEqual (root, root2)

   def test_011 (self):
      source = '''
      (kicad_pcb (version 20171130) (host pcbnew "(5.1.9-0-10_14)")
        (general
          (thickness 1.6)
          (drawings 21)
        )
        (page A4)
        (layers
          (0 F.Cu signal)
        )
      )
      '''
      filepath = os.path.join (PATH_ARTIFACTS, 'test_generators_front_pcb_s_expression_008.txt')
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
         w = s_expression.Writer ()
         w.write (root, filepath)
         root2 = p.parse (w.write_any (root), 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertEqual (root, root2)

   def test_012 (self):
      source = '+12V'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_symbol)
      self.assertEqual (root.value, '+12V')

   def test_013 (self):
      source = '(+12V)'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      symbol = root.entities [0]
      self.assertTrue (symbol.is_symbol)
      self.assertEqual (symbol.value, '+12V')

   def test_014 (self):
      source = '(-0.1)'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      float_literal = root.entities [0]
      self.assertTrue (float_literal.is_float_literal)
      self.assertEqual (float_literal.value, -0.1)

   def test_015 (self):
      source = '(-1)'
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover

      self.assertTrue (root.is_list)
      self.assertEqual (len (root.entities), 1)
      integer_literal = root.entities [0]
      self.assertTrue (integer_literal.is_integer_literal)
      self.assertEqual (integer_literal.value, -1)

   def test_017 (self):
      source = '''
      (kicad_pcb (version 20171130) (host pcbnew "(5.1.9-0-10_14)")

        (general
          (thickness 1.6)
          (drawings 21)
          (tracks 88)
          (zones 0)
          (modules 13)
          (nets 11)
        )

        (page A4)
        (layers
          (0 F.Cu signal)
          (31 B.Cu signal)
          (32 B.Adhes user)
          (33 F.Adhes user)
          (34 B.Paste user)
          (35 F.Paste user)
          (36 B.SilkS user)
          (37 F.SilkS user)
          (38 B.Mask user)
          (39 F.Mask user)
          (40 Dwgs.User user)
          (41 Cmts.User user)
          (42 Eco1.User user)
          (43 Eco2.User user)
          (44 Edge.Cuts user)
          (45 Margin user)
          (46 B.CrtYd user hide)
          (47 F.CrtYd user hide)
          (48 B.Fab user hide)
          (49 F.Fab user hide)
        )

        (setup
          (last_trace_width 0.1524)
          (user_trace_width 0.1524)
          (user_trace_width 0.254)
          (user_trace_width 0.4064)
          (user_trace_width 0.635)
          (trace_clearance 0.1524)
          (zone_clearance 0.508)
          (zone_45_only no)
          (trace_min 0.1524)
          (via_size 0.6858)
          (via_drill 0.3048)
          (via_min_size 0.6858)
          (via_min_drill 0.3048)
          (uvia_size 0.3048)
          (uvia_drill 0.1524)
          (uvias_allowed no)
          (uvia_min_size 0.2)
          (uvia_min_drill 0.1)
          (edge_width 0.15)
          (segment_width 0.2)
          (pcb_text_width 0.3)
          (pcb_text_size 1.5 1.5)
          (mod_edge_width 0.15)
          (mod_text_size 1 1)
          (mod_text_width 0.15)
          (pad_size 1.524 1.524)
          (pad_drill 0.762)
          (pad_to_mask_clearance 0.2)
          (aux_axis_origin 0 0)
          (visible_elements FFFFFF7F)
          (pcbplotparams
            (layerselection 0x010fc_ffffffff)
            (usegerberextensions false)
            (usegerberattributes false)
            (usegerberadvancedattributes false)
            (creategerberjobfile false)
            (excludeedgelayer true)
            (linewidth 0.100000)
            (plotframeref false)
            (viasonmask false)
            (mode 1)
            (useauxorigin false)
            (hpglpennumber 1)
            (hpglpenspeed 20)
            (hpglpendiameter 15.000000)
            (psnegative false)
            (psa4output false)
            (plotreference true)
            (plotvalue true)
            (plotinvisibletext false)
            (padsonsilk false)
            (subtractmaskfromsilk false)
            (outputformat 1)
            (mirror false)
            (drillshape 1)
            (scaleselection 1)
            (outputdirectory ""))
        )

        (net 0 "")
        (net 1 "Net-(C1-Pad1)")
        (net 2 GND)
        (net 3 "Net-(C2-Pad1)")
        (net 4 "Net-(C1-Pad2)")
        (net 5 "Net-(C2-Pad2)")
        (net 6 +12V)
        (net 7 -12V)
        (net 8 NOP)
        (net 9 OUT)
        (net 10 DI)

        (net_class Default "This is the default net class."
          (clearance 0.1524)
          (trace_width 0.1524)
          (via_dia 0.6858)
          (via_drill 0.3048)
          (uvia_dia 0.3048)
          (uvia_drill 0.1524)
          (diff_pair_width 0.1524)
          (diff_pair_gap 0.1524)
          (add_net +12V)
          (add_net -12V)
          (add_net DI)
          (add_net GND)
          (add_net NOP)
          (add_net "Net-(C1-Pad1)")
          (add_net "Net-(C1-Pad2)")
          (add_net "Net-(C2-Pad1)")
          (add_net "Net-(C2-Pad2)")
          (add_net OUT)
        )

        (module Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical (layer B.Cu) (tedit 5FC942ED) (tstamp 5FCA2D88)
          (at 116.34 73.16 90)
          (descr "Through hole straight pin header, 1x06, 2.54mm pitch, single row")
          (tags "Through hole pin header THT 1x06 2.54mm single row")
          (path /5FC933AD)
          (fp_text reference J2 (at 0 2.33 90) (layer B.SilkS) hide
            (effects (font (size 1 1) (thickness 0.15)) (justify mirror))
          )
          (fp_text value OUT (at 0 -15.03 90) (layer B.Fab)
            (effects (font (size 1 1) (thickness 0.15)) (justify mirror))
          )
          (fp_line (start -0.635 1.27) (end 1.27 1.27) (layer B.Fab) (width 0.1))
          (fp_line (start 1.27 1.27) (end 1.27 -13.97) (layer B.Fab) (width 0.1))
          (fp_line (start 1.27 -13.97) (end -1.27 -13.97) (layer B.Fab) (width 0.1))
          (fp_line (start -1.27 -13.97) (end -1.27 0.635) (layer B.Fab) (width 0.1))
          (fp_line (start -1.27 0.635) (end -0.635 1.27) (layer B.Fab) (width 0.1))
          (fp_line (start -1.8 1.8) (end -1.8 -14.5) (layer B.CrtYd) (width 0.05))
          (fp_line (start -1.8 -14.5) (end 1.8 -14.5) (layer B.CrtYd) (width 0.05))
          (fp_line (start 1.8 -14.5) (end 1.8 1.8) (layer B.CrtYd) (width 0.05))
          (fp_line (start 1.8 1.8) (end -1.8 1.8) (layer B.CrtYd) (width 0.05))
          (fp_text user %R (at 0 -6.35) (layer B.Fab)
            (effects (font (size 1 1) (thickness 0.15)) (justify mirror))
          )
          (pad 1 thru_hole oval (at 0 0 90) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 9 OUT))
          (pad 2 thru_hole oval (at 0 -2.54 90) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 10 DI))
          (pad 3 thru_hole oval (at 0 -5.08 90) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 8 NOP))
          (pad 4 thru_hole oval (at 0 -7.62 90) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 2 GND))
          (pad 5 thru_hole oval (at 0 -10.16 90) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 2 GND))
          (pad 6 thru_hole oval (at 0 -12.7 90) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 2 GND))
          (model ${KISYS3DMOD}/Connector_PinHeader_2.54mm.3dshapes/PinHeader_1x06_P2.54mm_Vertical.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical (layer B.Cu) (tedit 5FC942C9) (tstamp 5FCA2C6E)
          (at 103.64 57.92 270)
          (descr "Through hole straight pin header, 1x06, 2.54mm pitch, single row")
          (tags "Through hole pin header THT 1x06 2.54mm single row")
          (path /5FCA991E)
          (fp_text reference J3 (at 0 2.33 270) (layer B.SilkS) hide
            (effects (font (size 1 1) (thickness 0.15)) (justify mirror))
          )
          (fp_text value POWER (at 0 -15.03 270) (layer B.Fab)
            (effects (font (size 1 1) (thickness 0.15)) (justify mirror))
          )
          (fp_line (start 1.8 1.8) (end -1.8 1.8) (layer B.CrtYd) (width 0.05))
          (fp_line (start 1.8 -14.5) (end 1.8 1.8) (layer B.CrtYd) (width 0.05))
          (fp_line (start -1.8 -14.5) (end 1.8 -14.5) (layer B.CrtYd) (width 0.05))
          (fp_line (start -1.8 1.8) (end -1.8 -14.5) (layer B.CrtYd) (width 0.05))
          (fp_line (start -1.27 0.635) (end -0.635 1.27) (layer B.Fab) (width 0.1))
          (fp_line (start -1.27 -13.97) (end -1.27 0.635) (layer B.Fab) (width 0.1))
          (fp_line (start 1.27 -13.97) (end -1.27 -13.97) (layer B.Fab) (width 0.1))
          (fp_line (start 1.27 1.27) (end 1.27 -13.97) (layer B.Fab) (width 0.1))
          (fp_line (start -0.635 1.27) (end 1.27 1.27) (layer B.Fab) (width 0.1))
          (fp_text user %R (at 0 -6.35 180) (layer B.Fab)
            (effects (font (size 1 1) (thickness 0.15)) (justify mirror))
          )
          (pad 6 thru_hole oval (at 0 -12.7 270) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 7 -12V))
          (pad 5 thru_hole oval (at 0 -10.16 270) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 6 +12V))
          (pad 4 thru_hole oval (at 0 -7.62 270) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 2 GND))
          (pad 3 thru_hole oval (at 0 -5.08 270) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 2 GND))
          (pad 2 thru_hole oval (at 0 -2.54 270) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 2 GND))
          (pad 1 thru_hole oval (at 0 0 270) (size 1.7 1.7) (drill 1) (layers *.Cu *.Mask)
            (net 2 GND))
          (model ${KISYS3DMOD}/Connector_PinHeader_2.54mm.3dshapes/PinHeader_1x06_P2.54mm_Vertical.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Capacitor_SMD:C_0603_1608Metric (layer F.Cu) (tedit 5B301BBE) (tstamp 5FCA2467)
          (at 122.055 57.539 180)
          (descr "Capacitor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags capacitor)
          (path /5FC94BD6)
          (attr smd)
          (fp_text reference C1 (at -2.54 0.135 180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 47p (at 0 1.43 180) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_text user %R (at 0 0 180) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 1 smd roundrect (at -0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 1 "Net-(C1-Pad1)"))
          (pad 2 smd roundrect (at 0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 4 "Net-(C1-Pad2)"))
          (model ${KISYS3DMOD}/Capacitor_SMD.3dshapes/C_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Capacitor_SMD:C_0603_1608Metric (layer F.Cu) (tedit 5B301BBE) (tstamp 5FCA2557)
          (at 120.785 73.287 180)
          (descr "Capacitor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags capacitor)
          (path /5FC94DF7)
          (attr smd)
          (fp_text reference C2 (at -2.54 -0.119 180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 560p (at 0 1.43 180) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_text user %R (at 0 0 180) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 2 smd roundrect (at 0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 5 "Net-(C2-Pad2)"))
          (pad 1 smd roundrect (at -0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 3 "Net-(C2-Pad1)"))
          (model ${KISYS3DMOD}/Capacitor_SMD.3dshapes/C_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Capacitor_SMD:C_0603_1608Metric (layer F.Cu) (tedit 5B301BBE) (tstamp 5FCA2527)
          (at 124.595 68.08 270)
          (descr "Capacitor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags capacitor)
          (path /5FC94671)
          (attr smd)
          (fp_text reference C3 (at 2.286 0.127) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 100n (at 0 1.43 270) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_text user %R (at 0 0 270) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 1 smd roundrect (at -0.7875 0 270) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 6 +12V))
          (pad 2 smd roundrect (at 0.7875 0 270) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 2 GND))
          (model ${KISYS3DMOD}/Capacitor_SMD.3dshapes/C_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Capacitor_SMD:C_0603_1608Metric (layer F.Cu) (tedit 5B301BBE) (tstamp 5FCA24F7)
          (at 116.975 63.635 90)
          (descr "Capacitor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags capacitor)
          (path /5FCA8BA7)
          (attr smd)
          (fp_text reference C4 (at 2.285 -0.015 180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 100n (at 0 1.43 90) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_text user %R (at 0 0 90) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 2 smd roundrect (at 0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 7 -12V))
          (pad 1 smd roundrect (at -0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 2 GND))
          (model ${KISYS3DMOD}/Capacitor_SMD.3dshapes/C_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Connector_Thonk:ThonkiconnJack (layer F.Cu) (tedit 5FC94102) (tstamp 5FCA18D8)
          (at 109.355 65.54 270)
          (path /5FC82E98)
          (fp_text reference J1 (at 0 -7.5 270) (layer F.SilkS) hide
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value IN (at 0 9.3 270) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_circle (center 0 0) (end 2.2 0) (layer F.SilkS) (width 0.15))
          (fp_line (start -4.5 4.5) (end 4.5 4.5) (layer F.SilkS) (width 0.15))
          (fp_line (start 4.5 -6) (end 4.5 4.5) (layer F.SilkS) (width 0.15))
          (fp_line (start -4.5 -6) (end -4.5 4.5) (layer F.SilkS) (width 0.15))
          (fp_line (start -4.5 -6) (end 4.5 -6) (layer F.SilkS) (width 0.15))
          (fp_circle (center 0 0) (end 1.8 0) (layer F.SilkS) (width 0.15))
          (pad S thru_hole oval (at 0 6.48 270) (size 2.3 1.6) (drill oval 1.3 0.6) (layers *.Cu *.Mask)
            (net 2 GND))
          (pad TN thru_hole oval (at 0 3.38 270) (size 2.5 1.6) (drill oval 1.5 0.6) (layers *.Cu *.Mask)
            (net 8 NOP))
          (pad T thru_hole oval (at 0 -4.92 270) (size 2.5 1.5) (drill oval 1.5 0.5) (layers *.Cu *.Mask)
            (net 10 DI))
          (pad "" np_thru_hole circle (at 0 0 270) (size 3 3) (drill 3) (layers *.Cu *.Mask))
        )

        (module Resistor_SMD:R_0603_1608Metric (layer F.Cu) (tedit 5B301BBD) (tstamp 5FCA24C7)
          (at 118.88 59.825 90)
          (descr "Resistor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags resistor)
          (path /5FC92D66)
          (attr smd)
          (fp_text reference R1 (at 2.159 0 180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 100k (at 0 1.43 90) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_text user %R (at 0 0 90) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 1 smd roundrect (at -0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 4 "Net-(C1-Pad2)"))
          (pad 2 smd roundrect (at 0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 10 DI))
          (model ${KISYS3DMOD}/Resistor_SMD.3dshapes/R_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Resistor_SMD:R_0603_1608Metric (layer F.Cu) (tedit 5B301BBD) (tstamp 5FCA2497)
          (at 122.055 59.444 180)
          (descr "Resistor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags resistor)
          (path /5FCA6E46)
          (attr smd)
          (fp_text reference R2 (at -2.54 0.262 180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 100k (at 0 1.43 180) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_text user %R (at 0 0 180) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 2 smd roundrect (at 0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 4 "Net-(C1-Pad2)"))
          (pad 1 smd roundrect (at -0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 1 "Net-(C1-Pad1)"))
          (model ${KISYS3DMOD}/Resistor_SMD.3dshapes/R_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Resistor_SMD:R_0603_1608Metric (layer F.Cu) (tedit 5B301BBD) (tstamp 5FCA2587)
          (at 124.595 63 90)
          (descr "Resistor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags resistor)
          (path /5FCA85EE)
          (attr smd)
          (fp_text reference R3 (at 2.286 0.127 180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 100k (at 0 1.43 90) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_text user %R (at 0 0 90) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 1 smd roundrect (at -0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 5 "Net-(C2-Pad2)"))
          (pad 2 smd roundrect (at 0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 1 "Net-(C1-Pad1)"))
          (model ${KISYS3DMOD}/Resistor_SMD.3dshapes/R_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Resistor_SMD:R_0603_1608Metric (layer F.Cu) (tedit 5B301BBD) (tstamp 5FCA263B)
          (at 120.785 71.382 180)
          (descr "Resistor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags resistor)
          (path /5FC9316D)
          (attr smd)
          (fp_text reference R4 (at -2.54 -0.5 180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 10k (at 0 1.43 180) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_text user %R (at 0 0 180) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 2 smd roundrect (at 0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 5 "Net-(C2-Pad2)"))
          (pad 1 smd roundrect (at -0.7875 0 180) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 3 "Net-(C2-Pad1)"))
          (model ${KISYS3DMOD}/Resistor_SMD.3dshapes/R_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Resistor_SMD:R_0603_1608Metric (layer F.Cu) (tedit 5B301BBD) (tstamp 5FC96AFD)
          (at 116.975 67.445 90)
          (descr "Resistor SMD 0603 (1608 Metric), square (rectangular) end terminal, IPC_7351 nominal, (Body size source: http://www.tortai-tech.com/upload/download/2011102023233369053.pdf), generated with kicad-footprint-generator")
          (tags resistor)
          (path /5FC9323B)
          (attr smd)
          (fp_text reference R5 (at -2.151 0 -180) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value 1k (at 0 1.43 90) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start -0.8 0.4) (end -0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.8 -0.4) (end 0.8 -0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 -0.4) (end 0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start 0.8 0.4) (end -0.8 0.4) (layer F.Fab) (width 0.1))
          (fp_line (start -0.162779 -0.51) (end 0.162779 -0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -0.162779 0.51) (end 0.162779 0.51) (layer F.SilkS) (width 0.12))
          (fp_line (start -1.48 0.73) (end -1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start -1.48 -0.73) (end 1.48 -0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 -0.73) (end 1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_line (start 1.48 0.73) (end -1.48 0.73) (layer F.CrtYd) (width 0.05))
          (fp_text user %R (at 0 0 90) (layer F.Fab)
            (effects (font (size 0.4 0.4) (thickness 0.06)))
          )
          (pad 1 smd roundrect (at -0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 9 OUT))
          (pad 2 smd roundrect (at 0.7875 0 90) (size 0.875 0.95) (layers F.Cu F.Paste F.Mask) (roundrect_rratio 0.25)
            (net 3 "Net-(C2-Pad1)"))
          (model ${KISYS3DMOD}/Resistor_SMD.3dshapes/R_0603_1608Metric.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (module Package_SO:SOIC-8_3.9x4.9mm_P1.27mm (layer F.Cu) (tedit 5A02F2D3) (tstamp 5FCA25C3)
          (at 120.785 65.54 270)
          (descr "8-Lead Plastic Small Outline (SN) - Narrow, 3.90 mm Body [SOIC] (see Microchip Packaging Specification 00000049BS.pdf)")
          (tags "SOIC 1.27")
          (path /5FC92B57)
          (attr smd)
          (fp_text reference U1 (at 0.41 -3.805) (layer F.SilkS)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_text value TL072 (at 0 3.5 270) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (fp_line (start -0.95 -2.45) (end 1.95 -2.45) (layer F.Fab) (width 0.1))
          (fp_line (start 1.95 -2.45) (end 1.95 2.45) (layer F.Fab) (width 0.1))
          (fp_line (start 1.95 2.45) (end -1.95 2.45) (layer F.Fab) (width 0.1))
          (fp_line (start -1.95 2.45) (end -1.95 -1.45) (layer F.Fab) (width 0.1))
          (fp_line (start -1.95 -1.45) (end -0.95 -2.45) (layer F.Fab) (width 0.1))
          (fp_line (start -3.73 -2.7) (end -3.73 2.7) (layer F.CrtYd) (width 0.05))
          (fp_line (start 3.73 -2.7) (end 3.73 2.7) (layer F.CrtYd) (width 0.05))
          (fp_line (start -3.73 -2.7) (end 3.73 -2.7) (layer F.CrtYd) (width 0.05))
          (fp_line (start -3.73 2.7) (end 3.73 2.7) (layer F.CrtYd) (width 0.05))
          (fp_line (start -2.075 -2.575) (end -2.075 -2.525) (layer F.SilkS) (width 0.15))
          (fp_line (start 2.075 -2.575) (end 2.075 -2.43) (layer F.SilkS) (width 0.15))
          (fp_line (start 2.075 2.575) (end 2.075 2.43) (layer F.SilkS) (width 0.15))
          (fp_line (start -2.075 2.575) (end -2.075 2.43) (layer F.SilkS) (width 0.15))
          (fp_line (start -2.075 -2.575) (end 2.075 -2.575) (layer F.SilkS) (width 0.15))
          (fp_line (start -2.075 2.575) (end 2.075 2.575) (layer F.SilkS) (width 0.15))
          (fp_line (start -2.075 -2.525) (end -3.475 -2.525) (layer F.SilkS) (width 0.15))
          (fp_text user %R (at 0 0 270) (layer F.Fab)
            (effects (font (size 1 1) (thickness 0.15)))
          )
          (pad 1 smd rect (at -2.7 -1.905 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 1 "Net-(C1-Pad1)"))
          (pad 2 smd rect (at -2.7 -0.635 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 4 "Net-(C1-Pad2)"))
          (pad 3 smd rect (at -2.7 0.635 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 2 GND))
          (pad 4 smd rect (at -2.7 1.905 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 7 -12V))
          (pad 5 smd rect (at 2.7 1.905 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 2 GND))
          (pad 6 smd rect (at 2.7 0.635 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 5 "Net-(C2-Pad2)"))
          (pad 7 smd rect (at 2.7 -0.635 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 3 "Net-(C2-Pad1)"))
          (pad 8 smd rect (at 2.7 -1.905 270) (size 1.55 0.6) (layers F.Cu F.Paste F.Mask)
            (net 6 +12V))
          (model ${KISYS3DMOD}/Package_SO.3dshapes/SOIC-8_3.9x4.9mm_P1.27mm.wrl
            (at (xyz 0 0 0))
            (scale (xyz 1 1 1))
            (rotate (xyz 0 0 0))
          )
        )

        (gr_text NOP (at 111.26 71.255) (layer F.SilkS) (tstamp 5FF68CC9)
          (effects (font (size 1 0.8) (thickness 0.15)))
        )
        (gr_text DI (at 113.8 71.255) (layer F.SilkS) (tstamp 5FE0C7D5)
          (effects (font (size 1 1) (thickness 0.15)))
        )
        (gr_circle (center 122.77 64.35) (end 123.052843 64.35) (layer F.SilkS) (width 0.15))
        (gr_text "Audio\\nIN" (at 103 69) (layer F.SilkS) (tstamp 5FC9695F)
          (effects (font (size 1 0.8) (thickness 0.15)))
        )
        (gr_line (start 101 56) (end 101 75) (layer Edge.Cuts) (width 0.15))
        (gr_line (start 126 56) (end 101 56) (layer Edge.Cuts) (width 0.15))
        (gr_line (start 126 75) (end 126 56) (layer Edge.Cuts) (width 0.15))
        (gr_line (start 101 75) (end 126 75) (layer Edge.Cuts) (width 0.15))
        (gr_text OUT (at 116.34 71.255) (layer F.SilkS) (tstamp 5FCA3192)
          (effects (font (size 1 0.8) (thickness 0.15)))
        )
        (gr_line (start 109.355 71.255) (end 109.355 71.89) (layer F.SilkS) (width 0.2))
        (gr_line (start 108.085 71.255) (end 109.355 71.255) (layer F.SilkS) (width 0.2))
        (gr_line (start 103.005 71.255) (end 104.275 71.255) (layer F.SilkS) (width 0.2))
        (gr_line (start 103.005 71.89) (end 103.005 71.255) (layer F.SilkS) (width 0.2))
        (gr_text GND (at 106.18 71.255) (layer F.SilkS) (tstamp 5FCA3176)
          (effects (font (size 1 1) (thickness 0.15)))
        )
        (gr_line (start 111.895 59.825) (end 111.895 59.19) (layer F.SilkS) (width 0.2))
        (gr_line (start 109.355 59.825) (end 111.895 59.825) (layer F.SilkS) (width 0.2))
        (gr_line (start 103.005 59.825) (end 105.545 59.825) (layer F.SilkS) (width 0.2))
        (gr_line (start 103.005 59.19) (end 103.005 59.825) (layer F.SilkS) (width 0.2))
        (gr_text GND (at 107.45 59.825) (layer F.SilkS) (tstamp 5FCA316C)
          (effects (font (size 1 1) (thickness 0.15)))
        )
        (gr_text -12 (at 116.34 59.825) (layer F.SilkS) (tstamp 5FCA3144)
          (effects (font (size 1 0.8) (thickness 0.15)))
        )
        (gr_text +12 (at 113.8 59.825) (layer F.SilkS)
          (effects (font (size 1 0.8) (thickness 0.15)))
        )

        (segment (start 122.8425 57.539) (end 122.8425 59.444) (width 0.4064) (layer F.Cu) (net 1))
        (segment (start 123.3175 62.2125) (end 122.69 62.84) (width 0.4064) (layer F.Cu) (net 1))
        (segment (start 124.595 62.2125) (end 123.3175 62.2125) (width 0.4064) (layer F.Cu) (net 1))
        (segment (start 122.69 59.5965) (end 122.8425 59.444) (width 0.4064) (layer F.Cu) (net 1))
        (segment (start 122.69 62.84) (end 122.69 59.5965) (width 0.4064) (layer F.Cu) (net 1))
        (via (at 118.4 72.13) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 115.9 65.65) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 118.47 69.91) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 118.47 71.02) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 123.04 70.16) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 124.84 71.71) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 124.88 73.17) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 115.63 63.92) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 118.53 64.52) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (via (at 120.18 64.45) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 2))
        (segment (start 121.5725 71.382) (end 121.5725 73.287) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 118.0825 65.55) (end 117.436612 66.195888) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 117.436612 66.195888) (end 116.975 66.6575) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 120.66 65.55) (end 118.0825 65.55) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 121.42 66.31) (end 120.66 65.55) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 121.42 68.24) (end 121.42 66.31) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 121.42 71.2295) (end 121.5725 71.382) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 121.42 68.24) (end 121.42 71.2295) (width 0.4064) (layer F.Cu) (net 3))
        (segment (start 121.2675 57.539) (end 121.2675 59.444) (width 0.4064) (layer F.Cu) (net 4))
        (segment (start 120.099 60.6125) (end 121.2675 59.444) (width 0.4064) (layer F.Cu) (net 4))
        (segment (start 118.88 60.6125) (end 120.099 60.6125) (width 0.4064) (layer F.Cu) (net 4))
        (segment (start 121.42 59.5965) (end 121.2675 59.444) (width 0.4064) (layer F.Cu) (net 4))
        (segment (start 121.42 62.84) (end 121.42 59.5965) (width 0.4064) (layer F.Cu) (net 4))
        (segment (start 119.9975 71.382) (end 119.9975 73.287) (width 0.4064) (layer F.Cu) (net 5))
        (via (at 124.61 64.93) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 5))
        (segment (start 124.595 64.915) (end 124.61 64.93) (width 0.4064) (layer F.Cu) (net 5))
        (segment (start 124.595 63.7875) (end 124.595 64.915) (width 0.4064) (layer F.Cu) (net 5))
        (segment (start 120.15 68.24) (end 120.15 66.52) (width 0.4064) (layer F.Cu) (net 5))
        (segment (start 120.15 66.52) (end 120.24 66.43) (width 0.4064) (layer F.Cu) (net 5))
        (via (at 120.24 66.43) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 5))
        (segment (start 120.15 71.2295) (end 119.9975 71.382) (width 0.4064) (layer F.Cu) (net 5))
        (segment (start 120.15 68.24) (end 120.15 71.2295) (width 0.4064) (layer F.Cu) (net 5))
        (segment (start 120.724933 66.43) (end 120.24 66.43) (width 0.4064) (layer B.Cu) (net 5))
        (segment (start 123.42 66.43) (end 120.724933 66.43) (width 0.4064) (layer B.Cu) (net 5))
        (segment (start 124.61 65.24) (end 123.42 66.43) (width 0.4064) (layer B.Cu) (net 5))
        (segment (start 124.61 64.93) (end 124.61 65.24) (width 0.4064) (layer B.Cu) (net 5))
        (segment (start 123.6375 67.2925) (end 122.69 68.24) (width 0.4064) (layer F.Cu) (net 6))
        (segment (start 124.595 67.2925) (end 123.6375 67.2925) (width 0.4064) (layer F.Cu) (net 6))
        (via (at 121.39 64.22) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 6))
        (via (at 122.05 64.88) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 6))
        (segment (start 121.39 64.22) (end 122.09 64.92) (width 0.4064) (layer B.Cu) (net 6))
        (segment (start 122.392899 65.222899) (end 122.05 64.88) (width 0.4064) (layer F.Cu) (net 6))
        (segment (start 122.69 68.24) (end 122.69 65.52) (width 0.4064) (layer F.Cu) (net 6))
        (segment (start 122.69 65.52) (end 122.392899 65.222899) (width 0.4064) (layer B.Cu) (net 6))
        (segment (start 122.69 65.52) (end 122.392899 65.222899) (width 0.4064) (layer F.Cu) (net 6))
        (segment (start 122.392899 65.222899) (end 122.05 64.88) (width 0.4064) (layer B.Cu) (net 6))
        (via (at 122.69 65.52) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 6) (tstamp 5FCA2F63))
        (via (at 122.69 65.52) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 6))
        (segment (start 122.05 64.88) (end 121.39 64.22) (width 0.4064) (layer F.Cu) (net 6))
        (segment (start 113.8 59.122081) (end 113.8 57.92) (width 0.4064) (layer B.Cu) (net 6))
        (segment (start 113.8 60.45) (end 113.8 59.122081) (width 0.4064) (layer B.Cu) (net 6))
        (segment (start 115.99 62.64) (end 113.8 60.45) (width 0.4064) (layer B.Cu) (net 6))
        (segment (start 119.81 62.64) (end 115.99 62.64) (width 0.4064) (layer B.Cu) (net 6))
        (segment (start 121.39 64.22) (end 119.81 62.64) (width 0.4064) (layer B.Cu) (net 6))
        (segment (start 116.9825 62.84) (end 116.975 62.8475) (width 0.4064) (layer F.Cu) (net 7))
        (segment (start 118.88 62.84) (end 116.9825 62.84) (width 0.4064) (layer F.Cu) (net 7))
        (via (at 116.99 60.34) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 7))
        (via (at 116.99 61.12) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 7))
        (segment (start 116.99 60.34) (end 116.99 61.12) (width 0.4064) (layer F.Cu) (net 7))
        (via (at 116.98 61.86) (size 0.6858) (drill 0.3048) (layers F.Cu B.Cu) (net 7))
        (segment (start 116.975 62.8475) (end 116.975 61.865) (width 0.4064) (layer F.Cu) (net 7))
        (segment (start 116.99 60.34) (end 116.99 61.85) (width 0.4064) (layer B.Cu) (net 7))
        (segment (start 116.99 61.85) (end 116.98 61.86) (width 0.4064) (layer B.Cu) (net 7))
        (segment (start 116.975 61.865) (end 116.98 61.86) (width 0.4064) (layer F.Cu) (net 7))
        (segment (start 116.99 61.12) (end 116.99 61.85) (width 0.4064) (layer F.Cu) (net 7))
        (segment (start 116.99 61.85) (end 116.98 61.86) (width 0.4064) (layer F.Cu) (net 7))
        (segment (start 116.34 58.41) (end 116.99 59.06) (width 0.4064) (layer B.Cu) (net 7))
        (segment (start 116.99 59.06) (end 116.99 60.34) (width 0.4064) (layer B.Cu) (net 7))
        (segment (start 116.34 57.92) (end 116.34 58.41) (width 0.4064) (layer B.Cu) (net 7))
        (segment (start 105.975 67.1964) (end 107.3586 68.58) (width 0.4064) (layer F.Cu) (net 8))
        (segment (start 105.975 65.54) (end 105.975 67.1964) (width 0.4064) (layer F.Cu) (net 8))
        (segment (start 107.3586 68.58) (end 110.236 68.58) (width 0.4064) (layer F.Cu) (net 8))
        (segment (start 111.26 69.604) (end 111.26 73.16) (width 0.4064) (layer F.Cu) (net 8))
        (segment (start 110.236 68.58) (end 111.26 69.604) (width 0.4064) (layer F.Cu) (net 8))
        (segment (start 116.34 68.8675) (end 116.975 68.2325) (width 0.4064) (layer F.Cu) (net 9))
        (segment (start 116.34 73.16) (end 116.34 68.8675) (width 0.4064) (layer F.Cu) (net 9))
        (segment (start 114.275 63.8836) (end 114.275 65.54) (width 0.4064) (layer F.Cu) (net 10))
        (segment (start 118.88 59.0375) (end 117.278716 59.0375) (width 0.4064) (layer F.Cu) (net 10))
        (segment (start 114.275 62.041216) (end 114.275 63.8836) (width 0.4064) (layer F.Cu) (net 10))
        (segment (start 117.278716 59.0375) (end 114.275 62.041216) (width 0.4064) (layer F.Cu) (net 10))
        (segment (start 113.792 73.152) (end 113.8 73.16) (width 0.4064) (layer F.Cu) (net 10))
        (segment (start 113.792 66.023) (end 113.792 73.152) (width 0.4064) (layer F.Cu) (net 10))
        (segment (start 114.275 65.54) (end 113.792 66.023) (width 0.4064) (layer F.Cu) (net 10))

        (zone (net 2) (net_name GND) (layer F.Cu) (tstamp 0) (hatch edge 0.508)
          (connect_pads (clearance 0.508))
          (min_thickness 0.254)
          (fill yes (arc_segments 16) (thermal_gap 0.508) (thermal_bridge_width 0.508))
          (polygon
            (pts
              (xy 101 56) (xy 101 75) (xy 126 75) (xy 126 56)
            )
          )
          (filled_polygon
            (pts
              (xy 124.722 68.7405) (xy 124.742 68.7405) (xy 124.742 68.9945) (xy 124.722 68.9945) (xy 124.722 69.78125)
              (xy 124.88075 69.94) (xy 125.07 69.943072) (xy 125.194482 69.930812) (xy 125.29 69.901837) (xy 125.29 74.29)
              (xy 122.20305 74.29) (xy 122.267275 74.255671) (xy 122.397115 74.149115) (xy 122.503671 74.019275) (xy 122.58285 73.871142)
              (xy 122.631608 73.710408) (xy 122.648072 73.54325) (xy 122.648072 73.03075) (xy 122.631608 72.863592) (xy 122.58285 72.702858)
              (xy 122.503671 72.554725) (xy 122.4107 72.441439) (xy 122.4107 72.227561) (xy 122.503671 72.114275) (xy 122.58285 71.966142)
              (xy 122.631608 71.805408) (xy 122.648072 71.63825) (xy 122.648072 71.12575) (xy 122.631608 70.958592) (xy 122.58285 70.797858)
              (xy 122.503671 70.649725) (xy 122.397115 70.519885) (xy 122.267275 70.413329) (xy 122.2582 70.408478) (xy 122.2582 69.638592)
              (xy 122.265518 69.640812) (xy 122.39 69.653072) (xy 122.99 69.653072) (xy 123.114482 69.640812) (xy 123.23418 69.604502)
              (xy 123.344494 69.545537) (xy 123.441185 69.466185) (xy 123.491736 69.404588) (xy 123.494188 69.429482) (xy 123.530498 69.54918)
              (xy 123.589463 69.659494) (xy 123.668815 69.756185) (xy 123.765506 69.835537) (xy 123.87582 69.894502) (xy 123.995518 69.930812)
              (xy 124.12 69.943072) (xy 124.30925 69.94) (xy 124.468 69.78125) (xy 124.468 68.9945) (xy 124.448 68.9945)
              (xy 124.448 68.7405) (xy 124.468 68.7405) (xy 124.468 68.7205) (xy 124.722 68.7205)
            )
          )
          (filled_polygon
            (pts
              (xy 119.2621 66.526315) (xy 119.29968 66.715243) (xy 119.311801 66.744505) (xy 119.311801 66.841408) (xy 119.304482 66.839188)
              (xy 119.18 66.826928) (xy 119.16575 66.83) (xy 119.007 66.98875) (xy 119.007 68.113) (xy 119.027 68.113)
              (xy 119.027 68.367) (xy 119.007 68.367) (xy 119.007 69.49125) (xy 119.16575 69.65) (xy 119.18 69.653072)
              (xy 119.304482 69.640812) (xy 119.3118 69.638592) (xy 119.311801 70.408478) (xy 119.302725 70.413329) (xy 119.172885 70.519885)
              (xy 119.066329 70.649725) (xy 118.98715 70.797858) (xy 118.938392 70.958592) (xy 118.921928 71.12575) (xy 118.921928 71.63825)
              (xy 118.938392 71.805408) (xy 118.98715 71.966142) (xy 119.066329 72.114275) (xy 119.1593 72.227562) (xy 119.159301 72.441438)
              (xy 119.066329 72.554725) (xy 118.98715 72.702858) (xy 118.938392 72.863592) (xy 118.921928 73.03075) (xy 118.921928 73.54325)
              (xy 118.938392 73.710408) (xy 118.98715 73.871142) (xy 119.066329 74.019275) (xy 119.172885 74.149115) (xy 119.302725 74.255671)
              (xy 119.36695 74.29) (xy 117.310107 74.29) (xy 117.493475 74.106632) (xy 117.65599 73.863411) (xy 117.767932 73.593158)
              (xy 117.825 73.30626) (xy 117.825 73.01374) (xy 117.767932 72.726842) (xy 117.65599 72.456589) (xy 117.493475 72.213368)
              (xy 117.286632 72.006525) (xy 117.1782 71.934073) (xy 117.1782 69.308072) (xy 117.23125 69.308072) (xy 117.398408 69.291608)
              (xy 117.559142 69.24285) (xy 117.707275 69.163671) (xy 117.837115 69.057115) (xy 117.94247 68.928739) (xy 117.941928 69.015)
              (xy 117.954188 69.139482) (xy 117.990498 69.25918) (xy 118.049463 69.369494) (xy 118.128815 69.466185) (xy 118.225506 69.545537)
              (xy 118.33582 69.604502) (xy 118.455518 69.640812) (xy 118.58 69.653072) (xy 118.59425 69.65) (xy 118.753 69.49125)
              (xy 118.753 68.367) (xy 118.733 68.367) (xy 118.733 68.113) (xy 118.753 68.113) (xy 118.753 66.98875)
              (xy 118.59425 66.83) (xy 118.58 66.826928) (xy 118.455518 66.839188) (xy 118.33582 66.875498) (xy 118.225506 66.934463)
              (xy 118.128815 67.013815) (xy 118.052304 67.107044) (xy 118.071608 67.043408) (xy 118.088072 66.87625) (xy 118.088072 66.729821)
              (xy 118.429694 66.3882) (xy 119.2621 66.3882)
            )
          )
          (filled_polygon
            (pts
              (xy 102.639731 56.822412) (xy 102.444822 57.038645) (xy 102.295843 57.288748) (xy 102.198519 57.563109) (xy 102.319186 57.793)
              (xy 103.513 57.793) (xy 103.513 57.773) (xy 103.767 57.773) (xy 103.767 57.793) (xy 106.053 57.793)
              (xy 106.053 57.773) (xy 106.307 57.773) (xy 106.307 57.793) (xy 108.593 57.793) (xy 108.593 57.773)
              (xy 108.847 57.773) (xy 108.847 57.793) (xy 111.133 57.793) (xy 111.133 57.773) (xy 111.387 57.773)
              (xy 111.387 57.793) (xy 111.407 57.793) (xy 111.407 58.047) (xy 111.387 58.047) (xy 111.387 59.240155)
              (xy 111.61689 59.361476) (xy 111.764099 59.316825) (xy 112.02692 59.191641) (xy 112.260269 59.017588) (xy 112.455178 58.801355)
              (xy 112.524805 58.684466) (xy 112.646525 58.866632) (xy 112.853368 59.073475) (xy 113.096589 59.23599) (xy 113.366842 59.347932)
              (xy 113.65374 59.405) (xy 113.94626 59.405) (xy 114.233158 59.347932) (xy 114.503411 59.23599) (xy 114.746632 59.073475)
              (xy 114.953475 58.866632) (xy 115.07 58.69224) (xy 115.186525 58.866632) (xy 115.393368 59.073475) (xy 115.636589 59.23599)
              (xy 115.819195 59.311627) (xy 113.711418 61.419405) (xy 113.679436 61.445652) (xy 113.574691 61.573285) (xy 113.496858 61.7189)
              (xy 113.448929 61.876901) (xy 113.4368 62.000047) (xy 113.4368 62.000053) (xy 113.432746 62.041216) (xy 113.4368 62.082379)
              (xy 113.436801 63.842421) (xy 113.4368 63.842431) (xy 113.4368 63.936198) (xy 113.29092 64.055919) (xy 113.117843 64.266812)
              (xy 112.989236 64.507419) (xy 112.91004 64.768493) (xy 112.89 64.971963) (xy 112.89 66.108036) (xy 112.91004 66.311506)
              (xy 112.9538 66.455763) (xy 112.953801 71.939418) (xy 112.853368 72.006525) (xy 112.646525 72.213368) (xy 112.53 72.38776)
              (xy 112.413475 72.213368) (xy 112.206632 72.006525) (xy 112.0982 71.934073) (xy 112.0982 69.645163) (xy 112.102254 69.604)
              (xy 112.0982 69.562837) (xy 112.0982 69.56283) (xy 112.086071 69.439684) (xy 112.038142 69.281683) (xy 111.960309 69.136068)
              (xy 111.855564 69.008436) (xy 111.823589 68.982195) (xy 110.857811 68.016418) (xy 110.831564 67.984436) (xy 110.703932 67.879691)
              (xy 110.558317 67.801858) (xy 110.400316 67.753929) (xy 110.27717 67.7418) (xy 110.277163 67.7418) (xy 110.236 67.737746)
              (xy 110.194837 67.7418) (xy 107.705794 67.7418) (xy 106.98307 67.019076) (xy 106.994607 67.009608) (xy 107.173932 66.791101)
              (xy 107.307182 66.541808) (xy 107.371386 66.330154) (xy 107.462988 66.551302) (xy 107.696637 66.900983) (xy 107.994017 67.198363)
              (xy 108.343698 67.432012) (xy 108.732244 67.592953) (xy 109.144721 67.675) (xy 109.565279 67.675) (xy 109.977756 67.592953)
              (xy 110.366302 67.432012) (xy 110.715983 67.198363) (xy 111.013363 66.900983) (xy 111.247012 66.551302) (xy 111.407953 66.162756)
              (xy 111.49 65.750279) (xy 111.49 65.329721) (xy 111.407953 64.917244) (xy 111.247012 64.528698) (xy 111.013363 64.179017)
              (xy 110.715983 63.881637) (xy 110.366302 63.647988) (xy 109.977756 63.487047) (xy 109.565279 63.405) (xy 109.144721 63.405)
              (xy 108.732244 63.487047) (xy 108.343698 63.647988) (xy 107.994017 63.881637) (xy 107.696637 64.179017) (xy 107.462988 64.528698)
              (xy 107.371386 64.749846) (xy 107.307182 64.538192) (xy 107.173932 64.288899) (xy 106.994608 64.070392) (xy 106.776101 63.891068)
              (xy 106.526808 63.757818) (xy 106.256309 63.675764) (xy 105.975 63.648057) (xy 105.693692 63.675764) (xy 105.423193 63.757818)
              (xy 105.1739 63.891068) (xy 104.955393 64.070392) (xy 104.776068 64.288899) (xy 104.642818 64.538192) (xy 104.560764 64.808691)
              (xy 104.54 65.019508) (xy 104.54 66.060491) (xy 104.560764 66.271308) (xy 104.642818 66.541807) (xy 104.776068 66.7911)
              (xy 104.955392 67.009607) (xy 105.136504 67.158243) (xy 105.132746 67.1964) (xy 105.148929 67.360715) (xy 105.196858 67.518716)
              (xy 105.274691 67.664331) (xy 105.331106 67.733072) (xy 105.379437 67.791964) (xy 105.411413 67.818206) (xy 106.736791 69.143585)
              (xy 106.763036 69.175564) (xy 106.890668 69.280309) (xy 107.036283 69.358142) (xy 107.194284 69.406071) (xy 107.31743 69.4182)
              (xy 107.317437 69.4182) (xy 107.3586 69.422254) (xy 107.399763 69.4182) (xy 109.888807 69.4182) (xy 110.4218 69.951194)
              (xy 110.421801 71.934073) (xy 110.313368 72.006525) (xy 110.106525 72.213368) (xy 109.984805 72.395534) (xy 109.915178 72.278645)
              (xy 109.720269 72.062412) (xy 109.48692 71.888359) (xy 109.224099 71.763175) (xy 109.07689 71.718524) (xy 108.847 71.839845)
              (xy 108.847 73.033) (xy 108.867 73.033) (xy 108.867 73.287) (xy 108.847 73.287) (xy 108.847 73.307)
              (xy 108.593 73.307) (xy 108.593 73.287) (xy 106.307 73.287) (xy 106.307 73.307) (xy 106.053 73.307)
              (xy 106.053 73.287) (xy 103.767 73.287) (xy 103.767 73.307) (xy 103.513 73.307) (xy 103.513 73.287)
              (xy 102.319186 73.287) (xy 102.198519 73.516891) (xy 102.295843 73.791252) (xy 102.444822 74.041355) (xy 102.639731 74.257588)
              (xy 102.683185 74.29) (xy 101.71 74.29) (xy 101.71 72.803109) (xy 102.198519 72.803109) (xy 102.319186 73.033)
              (xy 103.513 73.033) (xy 103.513 71.839845) (xy 103.767 71.839845) (xy 103.767 73.033) (xy 106.053 73.033)
              (xy 106.053 71.839845) (xy 106.307 71.839845) (xy 106.307 73.033) (xy 108.593 73.033) (xy 108.593 71.839845)
              (xy 108.36311 71.718524) (xy 108.215901 71.763175) (xy 107.95308 71.888359) (xy 107.719731 72.062412) (xy 107.524822 72.278645)
              (xy 107.45 72.404255) (xy 107.375178 72.278645) (xy 107.180269 72.062412) (xy 106.94692 71.888359) (xy 106.684099 71.763175)
              (xy 106.53689 71.718524) (xy 106.307 71.839845) (xy 106.053 71.839845) (xy 105.82311 71.718524) (xy 105.675901 71.763175)
              (xy 105.41308 71.888359) (xy 105.179731 72.062412) (xy 104.984822 72.278645) (xy 104.91 72.404255) (xy 104.835178 72.278645)
              (xy 104.640269 72.062412) (xy 104.40692 71.888359) (xy 104.144099 71.763175) (xy 103.99689 71.718524) (xy 103.767 71.839845)
              (xy 103.513 71.839845) (xy 103.28311 71.718524) (xy 103.135901 71.763175) (xy 102.87308 71.888359) (xy 102.639731 72.062412)
              (xy 102.444822 72.278645) (xy 102.295843 72.528748) (xy 102.198519 72.803109) (xy 101.71 72.803109) (xy 101.71 66.728004)
              (xy 101.752399 66.792839) (xy 101.950105 66.9945) (xy 102.183354 67.153715) (xy 102.443182 67.264367) (xy 102.525961 67.281904)
              (xy 102.748 67.159915) (xy 102.748 65.667) (xy 103.002 65.667) (xy 103.002 67.159915) (xy 103.224039 67.281904)
              (xy 103.306818 67.264367) (xy 103.566646 67.153715) (xy 103.799895 66.9945) (xy 103.997601 66.792839) (xy 104.152166 66.556483)
              (xy 104.25765 66.294514) (xy 104.31 66.017) (xy 104.31 65.667) (xy 103.002 65.667) (xy 102.748 65.667)
              (xy 102.728 65.667) (xy 102.728 65.413) (xy 102.748 65.413) (xy 102.748 63.920085) (xy 103.002 63.920085)
              (xy 103.002 65.413) (xy 104.31 65.413) (xy 104.31 65.063) (xy 104.25765 64.785486) (xy 104.152166 64.523517)
              (xy 103.997601 64.287161) (xy 103.799895 64.0855) (xy 103.566646 63.926285) (xy 103.306818 63.815633) (xy 103.224039 63.798096)
              (xy 103.002 63.920085) (xy 102.748 63.920085) (xy 102.525961 63.798096) (xy 102.443182 63.815633) (xy 102.183354 63.926285)
              (xy 101.950105 64.0855) (xy 101.752399 64.287161) (xy 101.71 64.351996) (xy 101.71 58.276891) (xy 102.198519 58.276891)
              (xy 102.295843 58.551252) (xy 102.444822 58.801355) (xy 102.639731 59.017588) (xy 102.87308 59.191641) (xy 103.135901 59.316825)
              (xy 103.28311 59.361476) (xy 103.513 59.240155) (xy 103.513 58.047) (xy 103.767 58.047) (xy 103.767 59.240155)
              (xy 103.99689 59.361476) (xy 104.144099 59.316825) (xy 104.40692 59.191641) (xy 104.640269 59.017588) (xy 104.835178 58.801355)
              (xy 104.91 58.675745) (xy 104.984822 58.801355) (xy 105.179731 59.017588) (xy 105.41308 59.191641) (xy 105.675901 59.316825)
              (xy 105.82311 59.361476) (xy 106.053 59.240155) (xy 106.053 58.047) (xy 106.307 58.047) (xy 106.307 59.240155)
              (xy 106.53689 59.361476) (xy 106.684099 59.316825) (xy 106.94692 59.191641) (xy 107.180269 59.017588) (xy 107.375178 58.801355)
              (xy 107.45 58.675745) (xy 107.524822 58.801355) (xy 107.719731 59.017588) (xy 107.95308 59.191641) (xy 108.215901 59.316825)
              (xy 108.36311 59.361476) (xy 108.593 59.240155) (xy 108.593 58.047) (xy 108.847 58.047) (xy 108.847 59.240155)
              (xy 109.07689 59.361476) (xy 109.224099 59.316825) (xy 109.48692 59.191641) (xy 109.720269 59.017588) (xy 109.915178 58.801355)
              (xy 109.99 58.675745) (xy 110.064822 58.801355) (xy 110.259731 59.017588) (xy 110.49308 59.191641) (xy 110.755901 59.316825)
              (xy 110.90311 59.361476) (xy 111.133 59.240155) (xy 111.133 58.047) (xy 108.847 58.047) (xy 108.593 58.047)
              (xy 106.307 58.047) (xy 106.053 58.047) (xy 103.767 58.047) (xy 103.513 58.047) (xy 102.319186 58.047)
              (xy 102.198519 58.276891) (xy 101.71 58.276891) (xy 101.71 56.71) (xy 102.790439 56.71)
            )
          )
          (filled_polygon
            (pts
              (xy 116.079787 61.477929) (xy 116.03968 61.574757) (xy 116.0021 61.763685) (xy 116.0021 61.956315) (xy 116.034371 62.118555)
              (xy 116.006329 62.152725) (xy 115.92715 62.300858) (xy 115.878392 62.461592) (xy 115.861928 62.62875) (xy 115.861928 63.06625)
              (xy 115.878392 63.233408) (xy 115.92715 63.394142) (xy 116.006329 63.542275) (xy 116.0241 63.56393) (xy 115.969463 63.630506)
              (xy 115.910498 63.74082) (xy 115.874188 63.860518) (xy 115.861928 63.985) (xy 115.865 64.13675) (xy 116.02375 64.2955)
              (xy 116.848 64.2955) (xy 116.848 64.2755) (xy 117.102 64.2755) (xy 117.102 64.2955) (xy 117.92625 64.2955)
              (xy 118.085 64.13675) (xy 118.087449 64.01578) (xy 118.128815 64.066185) (xy 118.225506 64.145537) (xy 118.33582 64.204502)
              (xy 118.455518 64.240812) (xy 118.58 64.253072) (xy 119.18 64.253072) (xy 119.304482 64.240812) (xy 119.42418 64.204502)
              (xy 119.515 64.155957) (xy 119.60582 64.204502) (xy 119.725518 64.240812) (xy 119.85 64.253072) (xy 119.86425 64.25)
              (xy 120.023 64.09125) (xy 120.023 62.967) (xy 120.003 62.967) (xy 120.003 62.713) (xy 120.023 62.713)
              (xy 120.023 62.693) (xy 120.277 62.693) (xy 120.277 62.713) (xy 120.297 62.713) (xy 120.297 62.967)
              (xy 120.277 62.967) (xy 120.277 64.09125) (xy 120.4121 64.22635) (xy 120.4121 64.316315) (xy 120.44968 64.505243)
              (xy 120.523396 64.68321) (xy 120.542499 64.7118) (xy 118.123663 64.7118) (xy 118.084714 64.707964) (xy 117.92625 64.5495)
              (xy 117.102 64.5495) (xy 117.102 64.5695) (xy 116.848 64.5695) (xy 116.848 64.5495) (xy 116.02375 64.5495)
              (xy 115.865 64.70825) (xy 115.861928 64.86) (xy 115.874188 64.984482) (xy 115.910498 65.10418) (xy 115.969463 65.214494)
              (xy 116.048815 65.311185) (xy 116.145506 65.390537) (xy 116.25582 65.449502) (xy 116.375518 65.485812) (xy 116.5 65.498072)
              (xy 116.68925 65.495) (xy 116.847998 65.336252) (xy 116.847998 65.495) (xy 116.952107 65.495) (xy 116.865179 65.581928)
              (xy 116.71875 65.581928) (xy 116.551592 65.598392) (xy 116.390858 65.64715) (xy 116.242725 65.726329) (xy 116.112885 65.832885)
              (xy 116.006329 65.962725) (xy 115.92715 66.110858) (xy 115.878392 66.271592) (xy 115.861928 66.43875) (xy 115.861928 66.87625)
              (xy 115.878392 67.043408) (xy 115.92715 67.204142) (xy 116.006329 67.352275) (xy 116.082426 67.445) (xy 116.006329 67.537725)
              (xy 115.92715 67.685858) (xy 115.878392 67.846592) (xy 115.861928 68.01375) (xy 115.861928 68.160179) (xy 115.776413 68.245694)
              (xy 115.744437 68.271936) (xy 115.718195 68.303912) (xy 115.718192 68.303915) (xy 115.639691 68.399569) (xy 115.561858 68.545184)
              (xy 115.513929 68.703185) (xy 115.497746 68.8675) (xy 115.501801 68.908672) (xy 115.5018 71.934073) (xy 115.393368 72.006525)
              (xy 115.186525 72.213368) (xy 115.07 72.38776) (xy 114.953475 72.213368) (xy 114.746632 72.006525) (xy 114.6302 71.928728)
              (xy 114.6302 67.379572) (xy 114.80758 67.325764) (xy 115.048187 67.197157) (xy 115.25908 67.024081) (xy 115.432157 66.813188)
              (xy 115.560764 66.572581) (xy 115.63996 66.311507) (xy 115.66 66.108037) (xy 115.66 64.971963) (xy 115.63996 64.768493)
              (xy 115.560764 64.507419) (xy 115.432157 64.266812) (xy 115.259081 64.055919) (xy 115.1132 63.936197) (xy 115.1132 62.388409)
              (xy 116.063354 61.438255)
            )
          )
        )
        (zone (net 2) (net_name GND) (layer B.Cu) (tstamp 0) (hatch edge 0.508)
          (connect_pads (clearance 0.508))
          (min_thickness 0.254)
          (fill yes (arc_segments 16) (thermal_gap 0.508) (thermal_bridge_width 0.508))
          (polygon
            (pts
              (xy 101 56) (xy 101 75) (xy 126 75) (xy 126 56)
            )
          )
          (filled_polygon
            (pts
              (xy 102.639731 56.822412) (xy 102.444822 57.038645) (xy 102.295843 57.288748) (xy 102.198519 57.563109) (xy 102.319186 57.793)
              (xy 103.513 57.793) (xy 103.513 57.773) (xy 103.767 57.773) (xy 103.767 57.793) (xy 106.053 57.793)
              (xy 106.053 57.773) (xy 106.307 57.773) (xy 106.307 57.793) (xy 108.593 57.793) (xy 108.593 57.773)
              (xy 108.847 57.773) (xy 108.847 57.793) (xy 111.133 57.793) (xy 111.133 57.773) (xy 111.387 57.773)
              (xy 111.387 57.793) (xy 111.407 57.793) (xy 111.407 58.047) (xy 111.387 58.047) (xy 111.387 59.240155)
              (xy 111.61689 59.361476) (xy 111.764099 59.316825) (xy 112.02692 59.191641) (xy 112.260269 59.017588) (xy 112.455178 58.801355)
              (xy 112.524805 58.684466) (xy 112.646525 58.866632) (xy 112.853368 59.073475) (xy 112.9618 59.145927) (xy 112.9618 59.16325)
              (xy 112.961801 59.16326) (xy 112.9618 60.408837) (xy 112.957746 60.45) (xy 112.9618 60.491163) (xy 112.9618 60.491169)
              (xy 112.973929 60.614315) (xy 113.021858 60.772316) (xy 113.099691 60.917931) (xy 113.204436 61.045564) (xy 113.236418 61.071811)
              (xy 115.368191 63.203585) (xy 115.394436 63.235564) (xy 115.522068 63.340309) (xy 115.667683 63.418142) (xy 115.825684 63.466071)
              (xy 115.94883 63.4782) (xy 115.948837 63.4782) (xy 115.99 63.482254) (xy 116.031163 63.4782) (xy 119.462807 63.4782)
              (xy 120.439706 64.4551) (xy 120.44968 64.505243) (xy 120.523396 64.68321) (xy 120.630415 64.843375) (xy 120.766625 64.979585)
              (xy 120.92679 65.086604) (xy 121.104757 65.16032) (xy 121.108863 65.161137) (xy 121.10968 65.165243) (xy 121.183396 65.34321)
              (xy 121.290415 65.503375) (xy 121.37884 65.5918) (xy 120.74572 65.5918) (xy 120.70321 65.563396) (xy 120.525243 65.48968)
              (xy 120.336315 65.4521) (xy 120.143685 65.4521) (xy 119.954757 65.48968) (xy 119.77679 65.563396) (xy 119.616625 65.670415)
              (xy 119.480415 65.806625) (xy 119.373396 65.96679) (xy 119.29968 66.144757) (xy 119.2621 66.333685) (xy 119.2621 66.526315)
              (xy 119.29968 66.715243) (xy 119.373396 66.89321) (xy 119.480415 67.053375) (xy 119.616625 67.189585) (xy 119.77679 67.296604)
              (xy 119.954757 67.37032) (xy 120.143685 67.4079) (xy 120.336315 67.4079) (xy 120.525243 67.37032) (xy 120.70321 67.296604)
              (xy 120.74572 67.2682) (xy 123.378837 67.2682) (xy 123.42 67.272254) (xy 123.461163 67.2682) (xy 123.46117 67.2682)
              (xy 123.584316 67.256071) (xy 123.742317 67.208142) (xy 123.887932 67.130309) (xy 124.015564 67.025564) (xy 124.041811 66.993582)
              (xy 125.173587 65.861807) (xy 125.205564 65.835564) (xy 125.29 65.732678) (xy 125.29 74.29) (xy 117.310107 74.29)
              (xy 117.493475 74.106632) (xy 117.65599 73.863411) (xy 117.767932 73.593158) (xy 117.825 73.30626) (xy 117.825 73.01374)
              (xy 117.767932 72.726842) (xy 117.65599 72.456589) (xy 117.493475 72.213368) (xy 117.286632 72.006525) (xy 117.043411 71.84401)
              (xy 116.773158 71.732068) (xy 116.48626 71.675) (xy 116.19374 71.675) (xy 115.906842 71.732068) (xy 115.636589 71.84401)
              (xy 115.393368 72.006525) (xy 115.186525 72.213368) (xy 115.07 72.38776) (xy 114.953475 72.213368) (xy 114.746632 72.006525)
              (xy 114.503411 71.84401) (xy 114.233158 71.732068) (xy 113.94626 71.675) (xy 113.65374 71.675) (xy 113.366842 71.732068)
              (xy 113.096589 71.84401) (xy 112.853368 72.006525) (xy 112.646525 72.213368) (xy 112.53 72.38776) (xy 112.413475 72.213368)
              (xy 112.206632 72.006525) (xy 111.963411 71.84401) (xy 111.693158 71.732068) (xy 111.40626 71.675) (xy 111.11374 71.675)
              (xy 110.826842 71.732068) (xy 110.556589 71.84401) (xy 110.313368 72.006525) (xy 110.106525 72.213368) (xy 109.984805 72.395534)
              (xy 109.915178 72.278645) (xy 109.720269 72.062412) (xy 109.48692 71.888359) (xy 109.224099 71.763175) (xy 109.07689 71.718524)
              (xy 108.847 71.839845) (xy 108.847 73.033) (xy 108.867 73.033) (xy 108.867 73.287) (xy 108.847 73.287)
              (xy 108.847 73.307) (xy 108.593 73.307) (xy 108.593 73.287) (xy 106.307 73.287) (xy 106.307 73.307)
              (xy 106.053 73.307) (xy 106.053 73.287) (xy 103.767 73.287) (xy 103.767 73.307) (xy 103.513 73.307)
              (xy 103.513 73.287) (xy 102.319186 73.287) (xy 102.198519 73.516891) (xy 102.295843 73.791252) (xy 102.444822 74.041355)
              (xy 102.639731 74.257588) (xy 102.683185 74.29) (xy 101.71 74.29) (xy 101.71 72.803109) (xy 102.198519 72.803109)
              (xy 102.319186 73.033) (xy 103.513 73.033) (xy 103.513 71.839845) (xy 103.767 71.839845) (xy 103.767 73.033)
              (xy 106.053 73.033) (xy 106.053 71.839845) (xy 106.307 71.839845) (xy 106.307 73.033) (xy 108.593 73.033)
              (xy 108.593 71.839845) (xy 108.36311 71.718524) (xy 108.215901 71.763175) (xy 107.95308 71.888359) (xy 107.719731 72.062412)
              (xy 107.524822 72.278645) (xy 107.45 72.404255) (xy 107.375178 72.278645) (xy 107.180269 72.062412) (xy 106.94692 71.888359)
              (xy 106.684099 71.763175) (xy 106.53689 71.718524) (xy 106.307 71.839845) (xy 106.053 71.839845) (xy 105.82311 71.718524)
              (xy 105.675901 71.763175) (xy 105.41308 71.888359) (xy 105.179731 72.062412) (xy 104.984822 72.278645) (xy 104.91 72.404255)
              (xy 104.835178 72.278645) (xy 104.640269 72.062412) (xy 104.40692 71.888359) (xy 104.144099 71.763175) (xy 103.99689 71.718524)
              (xy 103.767 71.839845) (xy 103.513 71.839845) (xy 103.28311 71.718524) (xy 103.135901 71.763175) (xy 102.87308 71.888359)
              (xy 102.639731 72.062412) (xy 102.444822 72.278645) (xy 102.295843 72.528748) (xy 102.198519 72.803109) (xy 101.71 72.803109)
              (xy 101.71 66.728004) (xy 101.752399 66.792839) (xy 101.950105 66.9945) (xy 102.183354 67.153715) (xy 102.443182 67.264367)
              (xy 102.525961 67.281904) (xy 102.748 67.159915) (xy 102.748 65.667) (xy 103.002 65.667) (xy 103.002 67.159915)
              (xy 103.224039 67.281904) (xy 103.306818 67.264367) (xy 103.566646 67.153715) (xy 103.799895 66.9945) (xy 103.997601 66.792839)
              (xy 104.152166 66.556483) (xy 104.25765 66.294514) (xy 104.31 66.017) (xy 104.31 65.667) (xy 103.002 65.667)
              (xy 102.748 65.667) (xy 102.728 65.667) (xy 102.728 65.413) (xy 102.748 65.413) (xy 102.748 63.920085)
              (xy 103.002 63.920085) (xy 103.002 65.413) (xy 104.31 65.413) (xy 104.31 65.063) (xy 104.301796 65.019508)
              (xy 104.54 65.019508) (xy 104.54 66.060491) (xy 104.560764 66.271308) (xy 104.642818 66.541807) (xy 104.776068 66.7911)
              (xy 104.955392 67.009607) (xy 105.173899 67.188932) (xy 105.423192 67.322182) (xy 105.693691 67.404236) (xy 105.975 67.431943)
              (xy 106.256308 67.404236) (xy 106.526807 67.322182) (xy 106.7761 67.188932) (xy 106.994607 67.009608) (xy 107.173932 66.791101)
              (xy 107.307182 66.541808) (xy 107.371386 66.330154) (xy 107.462988 66.551302) (xy 107.696637 66.900983) (xy 107.994017 67.198363)
              (xy 108.343698 67.432012) (xy 108.732244 67.592953) (xy 109.144721 67.675) (xy 109.565279 67.675) (xy 109.977756 67.592953)
              (xy 110.366302 67.432012) (xy 110.715983 67.198363) (xy 111.013363 66.900983) (xy 111.247012 66.551302) (xy 111.407953 66.162756)
              (xy 111.49 65.750279) (xy 111.49 65.329721) (xy 111.418838 64.971963) (xy 112.89 64.971963) (xy 112.89 66.108036)
              (xy 112.91004 66.311506) (xy 112.989236 66.57258) (xy 113.117843 66.813187) (xy 113.290919 67.02408) (xy 113.501812 67.197157)
              (xy 113.742419 67.325764) (xy 114.003493 67.40496) (xy 114.275 67.431701) (xy 114.546506 67.40496) (xy 114.80758 67.325764)
              (xy 115.048187 67.197157) (xy 115.25908 67.024081) (xy 115.432157 66.813188) (xy 115.560764 66.572581) (xy 115.63996 66.311507)
              (xy 115.66 66.108037) (xy 115.66 64.971963) (xy 115.63996 64.768493) (xy 115.560764 64.507419) (xy 115.432157 64.266812)
              (xy 115.259081 64.055919) (xy 115.048188 63.882843) (xy 114.807581 63.754236) (xy 114.546507 63.67504) (xy 114.275 63.648299)
              (xy 114.003494 63.67504) (xy 113.74242 63.754236) (xy 113.501813 63.882843) (xy 113.29092 64.055919) (xy 113.117843 64.266812)
              (xy 112.989236 64.507419) (xy 112.91004 64.768493) (xy 112.89 64.971963) (xy 111.418838 64.971963) (xy 111.407953 64.917244)
              (xy 111.247012 64.528698) (xy 111.013363 64.179017) (xy 110.715983 63.881637) (xy 110.366302 63.647988) (xy 109.977756 63.487047)
              (xy 109.565279 63.405) (xy 109.144721 63.405) (xy 108.732244 63.487047) (xy 108.343698 63.647988) (xy 107.994017 63.881637)
              (xy 107.696637 64.179017) (xy 107.462988 64.528698) (xy 107.371386 64.749846) (xy 107.307182 64.538192) (xy 107.173932 64.288899)
              (xy 106.994608 64.070392) (xy 106.776101 63.891068) (xy 106.526808 63.757818) (xy 106.256309 63.675764) (xy 105.975 63.648057)
              (xy 105.693692 63.675764) (xy 105.423193 63.757818) (xy 105.1739 63.891068) (xy 104.955393 64.070392) (xy 104.776068 64.288899)
              (xy 104.642818 64.538192) (xy 104.560764 64.808691) (xy 104.54 65.019508) (xy 104.301796 65.019508) (xy 104.25765 64.785486)
              (xy 104.152166 64.523517) (xy 103.997601 64.287161) (xy 103.799895 64.0855) (xy 103.566646 63.926285) (xy 103.306818 63.815633)
              (xy 103.224039 63.798096) (xy 103.002 63.920085) (xy 102.748 63.920085) (xy 102.525961 63.798096) (xy 102.443182 63.815633)
              (xy 102.183354 63.926285) (xy 101.950105 64.0855) (xy 101.752399 64.287161) (xy 101.71 64.351996) (xy 101.71 58.276891)
              (xy 102.198519 58.276891) (xy 102.295843 58.551252) (xy 102.444822 58.801355) (xy 102.639731 59.017588) (xy 102.87308 59.191641)
              (xy 103.135901 59.316825) (xy 103.28311 59.361476) (xy 103.513 59.240155) (xy 103.513 58.047) (xy 103.767 58.047)
              (xy 103.767 59.240155) (xy 103.99689 59.361476) (xy 104.144099 59.316825) (xy 104.40692 59.191641) (xy 104.640269 59.017588)
              (xy 104.835178 58.801355) (xy 104.91 58.675745) (xy 104.984822 58.801355) (xy 105.179731 59.017588) (xy 105.41308 59.191641)
              (xy 105.675901 59.316825) (xy 105.82311 59.361476) (xy 106.053 59.240155) (xy 106.053 58.047) (xy 106.307 58.047)
              (xy 106.307 59.240155) (xy 106.53689 59.361476) (xy 106.684099 59.316825) (xy 106.94692 59.191641) (xy 107.180269 59.017588)
              (xy 107.375178 58.801355) (xy 107.45 58.675745) (xy 107.524822 58.801355) (xy 107.719731 59.017588) (xy 107.95308 59.191641)
              (xy 108.215901 59.316825) (xy 108.36311 59.361476) (xy 108.593 59.240155) (xy 108.593 58.047) (xy 108.847 58.047)
              (xy 108.847 59.240155) (xy 109.07689 59.361476) (xy 109.224099 59.316825) (xy 109.48692 59.191641) (xy 109.720269 59.017588)
              (xy 109.915178 58.801355) (xy 109.99 58.675745) (xy 110.064822 58.801355) (xy 110.259731 59.017588) (xy 110.49308 59.191641)
              (xy 110.755901 59.316825) (xy 110.90311 59.361476) (xy 111.133 59.240155) (xy 111.133 58.047) (xy 108.847 58.047)
              (xy 108.593 58.047) (xy 106.307 58.047) (xy 106.053 58.047) (xy 103.767 58.047) (xy 103.513 58.047)
              (xy 102.319186 58.047) (xy 102.198519 58.276891) (xy 101.71 58.276891) (xy 101.71 56.71) (xy 102.790439 56.71)
            )
          )
        )
      )
      '''
      filepath = os.path.join (PATH_ARTIFACTS, 'test_generators_front_pcb_s_expression_016.kicad_pcb')
      try:
         p = s_expression.Parser ()
         root = p.parse (source, 'test')
         w = s_expression.Writer ()
         w.write (root, filepath)
      except:                                # pragma: no cover
         self.fail (traceback.format_exc ()) # pragma: no cover



if __name__ == '__main__':
   unittest.main ()
