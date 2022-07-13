##############################################################################
#
#     pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import os
from . import s_expression

PATH_THIS = os.path.abspath (os.path.dirname (__file__))



# -- Root --------------------------------------------------------------------

class Root:
   def __init__ (self):
      self.version = None
      self.generator = None
      self.general = General ()
      self.paper = None
      self.layers = []
      self.setup = Setup ()
      self.nets = []
      self.footprints = []
      self.gr_shapes = []
      self.segments = []
      self.zones = []

   @staticmethod
   def read (filepath):
      with open (filepath, 'r', encoding='utf-8') as file:
         content = file.read ()
      parser = s_expression.Parser ()
      root_node = parser.parse (content, filepath)

      return Root.parse (root_node)

   @staticmethod
   def parse (node):
      if not node: return None

      root = Root ()
      root.version = node.property ('version')
      root.generator = node.property ('generator')
      root.general = General.parse (node.first_kind ('general'))
      root.paper = node.property ('paper')

      for layer_node in node.first_kind ('layers').entities [1:]:
         root.layers.append (Layer.parse (layer_node))

      root.setup = Setup.parse (node.first_kind ('setup'))

      for net_node in node.filter_kind ('net'):
         root.nets.append (Net.parse (net_node))

      for footprint_node in node.filter_kind ('footprint'):
         root.footprints.append (Footprint.parse (footprint_node))

      for gr_shape_node in node.filter_kinds (['gr_circle', 'gr_line', 'gr_text']):
         gr_shape_kind = gr_shape_node.entities [0].value
         if gr_shape_kind == 'gr_circle':
            root.gr_shapes.append (GrCircle.parse (gr_shape_node))
         elif gr_shape_kind == 'gr_line':
            root.gr_shapes.append (GrLine.parse (gr_shape_node))
         elif gr_shape_kind == 'gr_text':
            root.gr_shapes.append (GrText.parse (gr_shape_node))
         else:
            assert False

      for segment_node in node.filter_kind ('segment'):
         root.segments.append (Segment.parse (segment_node))

      for zone_node in node.filter_kind ('zone'):
         root.zones.append (Zone.parse (zone_node))

      return root

   def write (self, filepath):
      root_node = self.generate ()
      writer = s_expression.Writer ()
      writer.write (root_node, filepath)

   def generate (self):
      root_node = s_expression.List.generate ('kicad_pcb')
      root_node.add (s_expression.List.generate_property ('version', self.version))
      root_node.add (s_expression.List.generate_property ('generator', self.generator))
      root_node.add (self.general.generate ())
      root_node.add (s_expression.List.generate_property ('paper', self.paper))

      layers_node = root_node.add (s_expression.List.generate ('layers'))
      for layer in self.layers:
         layers_node.append (layer.generate ())

      root_node.add (self.setup.generate ())

      for net in self.nets:
         root_node.add (net.generate ())

      for footprint in self.footprints:
         root_node.add (footprint.generate ())

      for gr_shape in self.gr_shapes:
         root_node.add (gr_shape.generate ())

      for segment in self.segments:
         root_node.add (segment.generate ())

      for zone in self.zones:
         root_node.add (zone.generate ())

      return root_node



# -- At ----------------------------------------------------------------------

class At:
   def __init__ (self):
      self.x = None        # float
      self.y = None        # float
      self.rotation = None # float, degree

   @staticmethod
   def parse (node):
      if not node: return None

      at = At ()
      at.x = node.entities [1].value
      at.y = node.entities [2].value
      at.rotation = node.entities [3].value

      return at

   def generate (self):
      at_node = s_expression.List.generate ('at')
      at_node.add (s_expression.FloatLiteral (self.x))
      at_node.add (s_expression.FloatLiteral (self.y))
      at_node.add (s_expression.FloatLiteral (self.rotation))

      return at_node



# -- Xy ----------------------------------------------------------------------

class Xy:
   def __init__ (self):
      self.x = None        # float
      self.y = None        # float

   @staticmethod
   def parse (node):
      if not node: return None

      xy = Xy ()
      xy.x = node.entities [1].value
      xy.y = node.entities [2].value

      return xy

   def generate (self):
      xy_node = s_expression.List.generate ('xy')
      xy_node.add (s_expression.FloatLiteral (self.x))
      xy_node.add (s_expression.FloatLiteral (self.y))

      return xy_node

   def generate_with_alternate_name (self, name):
      xy_node = s_expression.List.generate (name)
      xy_node.add (s_expression.FloatLiteral (self.x))
      xy_node.add (s_expression.FloatLiteral (self.y))

      return xy_node


# -- Pts ----------------------------------------------------------------------

class Pts:
   def __init__ (self):
      self.items = [] # list of Xy

   @staticmethod
   def parse (node):
      if not node: return None

      pts = Pts ()
      for xy_node in node.filter_kind ('xy'):
         pts.items.append (Xy.parse (xy_node))

      return pts

   def generate (self):
      pts_node = s_expression.List.generate ('pts')
      for xy in self.items:
         pts_node.add (xy.generate ())

      return pts_node


# -- Effects -----------------------------------------------------------------

class Effects:
   def __init__ (self):
      self.font = Effects.Font ()
      self.justify = Effects.Justify ()

   @staticmethod
   def parse (node):
      if not node: return None

      effects = Effects ()
      effects.font = Effects.Font.parse (node.first_kind ('font'))
      effects.justify = Effects.Justify.parse (node.first_kind ('justify'))

      return effects

   def generate (self):
      effects_node = s_expression.List.generate ('effects')
      effects_node.add (self.font.generate ())
      effects_node.add (self.justify.generate ())
      return effects_node


   class Font:
      def __init__ (self):
         self.size = Size ()
         self.thickness = None   # float
         self.italic = None      # boolean

      @staticmethod
      def parse (node):
         if not node: return None

         font = Effects.Font ()
         font.size = Size.parse (node.first_kind ('size'))
         font.thickness = node.property ('thickness')
         font.italic = any (e.is_symbol and e.value == 'italic' for e in node.entities)

         return font

      def generate (self):
         font_node = s_expression.List.generate ('font')
         font_node.add (self.size.generate ())
         font_node.add (s_expression.List.generate_property ('thickness', self.thickness))
         if self.italic:
            font_node.add (s_expression.Symbol ('italic'))
         return font_node

   class Justify:
      def __init__ (self):
         self.type = None     # symbol eg. left, right. None is center
         self.mirror = None   # boolean

      @staticmethod
      def parse (node):
         if not node: return None

         justify = Effects.Justify ()
         justify.type = node.entities [1].value
         justify.mirror = any (e.is_symbol and e.value == 'italic' for e in node.entities)

         return justify

      def generate (self):
         justify_node = s_expression.List.generate ('justify')
         if self.type:
            justify_node.add (s_expression.Symbol (self.type))
         if self.mirror:
            justify_node.add (s_expression.Symbol ('mirror'))
         return justify_node


# -- Layer -------------------------------------------------------------------

class Layer:
   def __init__ (self):
      self.index = None # int eg. 0
      self.name = None  # str eg. "F.Cu"
      self.type = None  # symbol eg. signal, user
      self.user_name = None   # optional str eg. "B.Adhesive"

   @staticmethod
   def parse (node):
      if not node: return None

      layer = Layer ()
      layer.index = node.entities [0].value
      layer.name = node.entities [1].value
      layer.type = node.entities [2].value
      if len (node.entities) >= 4:
         layer.user_name = node.entities [3].value
      return layer

   def generate (self):
      layer_node = s_expression.List ()
      layer_node.add (s_expression.IntegerLiteral (self.index))
      layer_node.add (s_expression.StringLiteral (self.name))
      layer_node.add (s_expression.Symbol (self.type))
      if self.user_name:
         layer_node.add (s_expression.StringLiteral (self.user_name))
      return layer_node


# -- Setup -------------------------------------------------------------------

class Setup:
   def __init__ (self):
      self.pad_to_mask_clearance = None # float
      self.solder_mask_min_width = None  # float
      self.grid_origin = Xy ()
      self.pcbplotparams = Pcbplotparams ()

   @staticmethod
   def parse (node):
      if not node: return None

      setup = Setup ()
      setup.pad_to_mask_clearance = node.property ('pad_to_mask_clearance')
      setup.solder_mask_min_width = node.property ('solder_mask_min_width')
      setup.grid_origin = Xy.parse (node.first_kind ('grid_origin'))
      setup.pcbplotparams = Setup.Pcbplotparams.parse (node.first_kind ('pcbplotparams'))
      return setup

   def generate (self):
      setup_node = s_expression.List.generate ('setup')
      setup_node.add (s_expression.List.generate_property ('pad_to_mask_clearance', self.pad_to_mask_clearance))
      setup_node.add (s_expression.List.generate_property ('solder_mask_min_width', self.solder_mask_min_width))
      setup_node.add (self.grid_origin.generate_with_alternate_name ('grid_origin'))
      setup_node.add (self.pcbplotparams.generate ())

      return setup_node

   class Pcbplotparams:
      def __init__ (self):
         self.layerselection = None                # hex integer, captured as symbol
         self.disableapertmacros = None            # boolean
         self.usegerberextensions = None           # boolean
         self.usegerberattributes = None           # boolean
         self.usegerberadvancedattributes = None   # boolean
         self.creategerberjobfile = None           # boolean
         self.svguseinch = None                    # boolean
         self.svgprecision = None                  # int
         self.excludeedgelayer = None              # boolean
         self.plotframeref = None                  # boolean
         self.viasonmask = None                    # boolean
         self.mode = None                          # int
         self.useauxorigin = None                  # boolean
         self.hpglpennumber = None                 # int
         self.hpglpenspeed = None                  # int
         self.hpglpendiameter = None               # float
         self.dxfpolygonmode = None                # boolean
         self.dxfimperialunits = None              # boolean
         self.dxfusepcbnewfont = None              # boolean
         self.psnegative = None                    # boolean
         self.psa4output = None                    # boolean
         self.plotreference = None                 # boolean
         self.plotvalue = None                     # boolean
         self.plotinvisibletext = None             # boolean
         self.sketchpadsonfab = None               # boolean
         self.subtractmaskfromsilk = None          # boolean
         self.outputformat = None                  # int
         self.mirror = None                        # boolean
         self.drillshape = None                    # int
         self.scaleselection = None                # int
         self.outputdirectory = None               # str

      @staticmethod
      def parse (node):
         if not node: return None

         pcbplotparams = Pcbplotparams ()
         pcbplotparams.layerselection = node.property ('layerselection')
         pcbplotparams.disableapertmacros = node.property ('disableapertmacros')
         pcbplotparams.usegerberextensions = node.property ('usegerberextensions')
         pcbplotparams.usegerberattributes = node.property ('usegerberattributes')
         pcbplotparams.usegerberadvancedattributes = node.property ('usegerberadvancedattributes')
         pcbplotparams.creategerberjobfile = node.property ('creategerberjobfile')
         pcbplotparams.svguseinch = node.property ('svguseinch')
         pcbplotparams.svgprecision = node.property ('svgprecision')
         pcbplotparams.excludeedgelayer = node.property ('excludeedgelayer')
         pcbplotparams.plotframeref = node.property ('plotframeref')
         pcbplotparams.viasonmask = node.property ('viasonmask')
         pcbplotparams.mode = node.property ('mode')
         pcbplotparams.useauxorigin = node.property ('useauxorigin')
         pcbplotparams.hpglpennumber = node.property ('hpglpennumber')
         pcbplotparams.hpglpenspeed = node.property ('hpglpenspeed')
         pcbplotparams.hpglpendiameter = node.property ('hpglpendiameter')
         pcbplotparams.dxfpolygonmode = node.property ('dxfpolygonmode')
         pcbplotparams.dxfimperialunits = node.property ('dxfimperialunits')
         pcbplotparams.dxfusepcbnewfont = node.property ('dxfusepcbnewfont')
         pcbplotparams.psnegative = node.property ('psnegative')
         pcbplotparams.psa4output = node.property ('psa4output')
         pcbplotparams.plotreference = node.property ('plotreference')
         pcbplotparams.plotvalue = node.property ('plotvalue')
         pcbplotparams.plotinvisibletext = node.property ('plotinvisibletext')
         pcbplotparams.sketchpadsonfab = node.property ('sketchpadsonfab')
         pcbplotparams.subtractmaskfromsilk = node.property ('subtractmaskfromsilk')
         pcbplotparams.outputformat = node.property ('outputformat')
         pcbplotparams.mirror = node.property ('mirror')
         pcbplotparams.drillshape = node.property ('drillshape')
         pcbplotparams.scaleselection = node.property ('scaleselection')
         pcbplotparams.outputdirectory = node.property ('outputdirectory')
         return pcbplotparams

      def generate (self):
         pcbplotparams_node = s_expression.List.generate ('pcbplotparams')
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('layerselection', self.layerselection))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('disableapertmacros', self.disableapertmacros))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('usegerberextensions', self.usegerberextensions))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('usegerberattributes', self.usegerberattributes))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('(usegerberadvancedattributes false)', self.(usegerberadvancedattributes false)))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('creategerberjobfile', self.creategerberjobfile))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('svguseinch', self.svguseinch))
         pcbplotparams_node.add (s_expression.List.generate_property ('svgprecision', self.svgprecision))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('excludeedgelayer', self.excludeedgelayer))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('plotframeref', self.plotframeref))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('viasonmask', self.viasonmask))
         pcbplotparams_node.add (s_expression.List.generate_property ('mode', self.mode))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('useauxorigin', self.useauxorigin))
         pcbplotparams_node.add (s_expression.List.generate_property ('hpglpennumber', self.hpglpennumber))
         pcbplotparams_node.add (s_expression.List.generate_property ('hpglpenspeed', self.hpglpenspeed))
         pcbplotparams_node.add (s_expression.List.generate_property ('hpglpendiameter', self.hpglpendiameter))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('dxfpolygonmode', self.dxfpolygonmode))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('dxfimperialunits', self.dxfimperialunits))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('dxfusepcbnewfont', self.dxfusepcbnewfont))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('psnegative', self.psnegative))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('psa4output', self.psa4output))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('plotreference', self.plotreference))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('plotvalue', self.plotvalue))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('plotinvisibletext', self.plotinvisibletext))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('sketchpadsonfab', self.sketchpadsonfab))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('subtractmaskfromsilk', self.subtractmaskfromsilk))
         pcbplotparams_node.add (s_expression.List.generate_property ('outputformat', self.outputformat))
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('mirror', self.mirror))
         pcbplotparams_node.add (s_expression.List.generate_property ('drillshape', self.drillshape))
         pcbplotparams_node.add (s_expression.List.generate_property ('scaleselection', self.scaleselection))
         pcbplotparams_node.add (s_expression.List.generate_property ('outputdirectory', self.outputdirectory))
         return pcbplotparams_node


# -- Net ---------------------------------------------------------------------

class Net:
   def __init__ (self):
      self.index = None # int eg. 0
      self.name = None  # str eg. "GND"

   @staticmethod
   def parse (node):
      if not node: return None

      net = Net ()
      net.index = node.entities [1].value
      net.name = node.entities [2].value
      return net

   def generate (self):
      net_node = s_expression.List.generate ('net')
      net_node.add (s_expression.IntegerLiteral (self.index))
      net_node.add (s_expression.StringLiteral (self.name))
      return net_node


# -- Footprint ---------------------------------------------------------------

class Footprint:
   def __init__ (self):
      self.name = None     # str eg. "Potentiometer_Thonk:AlphaPot9ShaftD"
      self.locked = None   # boolean
      self.layer = None    # str eg. "F.Cu"
      self.tedit = None    # str eg. 60CF9975
      self.tstamp = None   # str eg. 00000000-0000-0000-0000-00006089d0fa
      self.at = At ()
      self.descr = None    # optional str eg. "SOD-123"
      self.tags = None     # optional str eg. "SOD-123"
      self.path = None     # str eg. "/00000000-0000-0000-0000-00005fcae65b"
      self.attr = None     # symbol eg. through_hole
      self.fp_shapes = []
      self.pads = []
      self.models = []

   @staticmethod
   def parse (node):
      if not node: return None

      footprint = Footprint ()
      footprint.name = node.entities [1].value
      footprint.locked = any (e.is_symbol and e.value == 'locked' for e in node.entities)
      footprint.layer = node.property ('layer')
      footprint.tedit = node.property ('tedit')
      footprint.tstamp = node.property ('tstamp')
      footprint.at = At.parse (node.first_kind ('at'))
      footprint.descr = node.property ('descr')
      footprint.tags = node.property ('tags')
      footprint.path = node.property ('path')
      footprint.attr = node.property ('attr')

      for fp_shape_node in node.filter_kinds (['fp_text', 'fp_line', 'fp_arc', 'fp_circle', 'fp_poly']):
         fp_shape_kind = fp_shape_node.entities [0].value
         if fp_shape_kind == 'fp_text':
            root.fp_shapes.append (FpText.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_line':
            root.fp_shapes.append (FpLine.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_arc':
            root.fp_shapes.append (FpArc.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_circle':
            root.fp_shapes.append (FpCircle.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_poly':
            root.fp_shapes.append (FpPoly.parse (fp_shape_node))
         else:
            assert False

      for pad_node in node.filter_kind ('pad'):
         root.pads.append (Pad.parse (pad_node))

      for model_node in node.filter_kind ('model'):
         root.models.append (Model.parse (model_node))

      return footprint

   def generate (self):
      footprint_node = s_expression.List.generate ('footprint')
      footprint_node.add (s_expression.StringLiteral (self.name))
      if self.locked:
         footprint_node.add (s_expression.Symbol ('locked'))
      footprint_node.add (s_expression.List.generate_property ('layer', self.layer))
      footprint_node.add (s_expression.List.generate_property ('tedit', self.tedit))
      footprint_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
      footprint_node.add (self.at.generate ())
      if self.descr:
         footprint_node.add (s_expression.List.generate_property ('descr', self.descr))
      if self.tags:
         footprint_node.add (s_expression.List.generate_property ('tags', self.tags))
      footprint_node.add (s_expression.List.generate_property ('path', self.path))
      footprint_node.add (s_expression.List.generate_property_symbol ('attr', self.attr))
      for fp_shape in self.fp_shapes:
         footprint_node.add (fp_shape.generate ())
      for pad in self.pads:
         footprint_node.add (pad.generate ())
      for model in self.models:
         footprint_node.add (model.generate ())
      return footprint_node

   class FpText:
      def __init__ (self):
         self.name = None  # symbol, eg. reference
         self.value = None # str, eg. R1
         self.at = At ()
         self.layer = None # str, eg. "F.SilkS"
         self.effects = Effects ()
         self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         fp_text = Footprint.FpText ()
         fp_text.name = node.entities [1].value
         fp_text.value = node.entities [2].value
         fp_text.at = Pts.parse (node.first_kind ('at'))
         fp_text.layer = node.property ('layer')
         fp_text.effects = Effects.parse (node.first_kind ('effects'))
         fp_text.tstamp = node.property ('tstamp')

         return fp_text

      def generate (self):
         fp_text_node = s_expression.List.generate ('fp_text')
         fp_text_node.add (s_expression.Symbol (self.name))
         fp_text_node.add (s_expression.StringLiteral (self.value))
         fp_text_node.add (self.at.generate ())
         fp_text_node.add (s_expression.List.generate_property ('layer', self.layer))
         fp_text_node.add (self.at.effects ())
         fp_text_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_text_node


   class FpLine:
      def __init__ (self):
         self.start = Xy ()
         self.end = Xy ()
         self.layer = None  # str, eg. "F.SilkS"
         self.width = None  # float
         self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         fp_line = Footprint.FpLine ()
         fp_line.start = Xy.parse (node.first_kind ('start'))
         fp_line.end = Xy.parse (node.first_kind ('end'))
         fp_line.layer = node.property ('layer')
         fp_line.width = node.property ('width')
         fp_line.tstamp = node.property ('tstamp')

         return fp_line

      def generate (self):
         fp_line_node = s_expression.List.generate ('fp_line')
         fp_line_node.add (self.start.generate_with_alternate_name ('start'))
         fp_line_node.add (self.end.generate_with_alternate_name ('end'))
         fp_line_node.add (s_expression.List.generate_property ('layer', self.layer))
         fp_line_node.add (s_expression.List.generate_property ('width', self.width))
         fp_line_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_line_node


   class FpArc:
      def __init__ (self):
         self.start = Xy ()
         self.mid = Xy ()
         self.end = Xy ()
         self.layer = None  # str, eg. "F.SilkS"
         self.width = None  # float
         self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         fp_arc = Footprint.FpArc ()
         fp_arc.start = Xy.parse (node.first_kind ('start'))
         fp_arc.mid = Xy.parse (node.first_kind ('mid'))
         fp_arc.end = Xy.parse (node.first_kind ('end'))
         fp_arc.layer = node.property ('layer')
         fp_arc.width = node.property ('width')
         fp_arc.tstamp = node.property ('tstamp')

         return fp_arc

      def generate (self):
         fp_arc_node = s_expression.List.generate ('fp_arc')
         fp_arc_node.add (self.start.generate_with_alternate_name ('start'))
         fp_arc_node.add (self.start.generate_with_alternate_name ('mid'))
         fp_arc_node.add (self.end.generate_with_alternate_name ('end'))
         fp_arc_node.add (s_expression.List.generate_property ('layer', self.layer))
         fp_arc_node.add (s_expression.List.generate_property ('width', self.width))
         fp_arc_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_arc_node


   class FpCircle:
      def __init__ (self):
         self.center = Xy ()
         self.end = Xy ()
         self.layer = None  # str, eg. "F.SilkS"
         self.width = None  # float
         self.fill = None   # symbol, eg. none
         self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         fp_circle = Footprint.FpCircle ()
         fp_circle.center = Xy.parse (node.first_kind ('center'))
         fp_circle.end = Xy.parse (node.first_kind ('end'))
         fp_circle.layer = node.property ('layer')
         fp_circle.width = node.property ('width')
         fp_circle.fill = node.property ('fill')
         fp_circle.tstamp = node.property ('tstamp')

         return fp_circle

      def generate (self):
         fp_circle_node = s_expression.List.generate ('fp_circle')
         fp_circle_node.add (self.start.generate_with_alternate_name ('center'))
         fp_circle_node.add (self.end.generate_with_alternate_name ('end'))
         fp_circle_node.add (s_expression.List.generate_property ('layer', self.layer))
         fp_circle_node.add (s_expression.List.generate_property ('width', self.width))
         fp_circle_node.add (s_expression.List.generate_property_symbol ('fill', self.fill))
         fp_circle_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_circle_node


   class FpPoly:
      def __init__ (self):
         self.pts = Pts ()
         self.layer = None  # str, eg. "F.SilkS"
         self.width = None  # float
         self.fill = None   # symbol, eg. solid
         self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         fp_poly = Footprint.FpPoly ()
         fp_polypts = Pts.parse (node.first_kind ('pts'))
         fp_poly.layer = node.property ('layer')
         fp_poly.width = node.property ('width')
         fp_poly.fill = node.property ('fill')
         fp_poly.tstamp = node.property ('tstamp')

         return fp_poly

      def generate (self):
         fp_poly_node = s_expression.List.generate ('fp_poly')
         fp_poly_node.add (self.pts.generate ())
         fp_poly_node.add (s_expression.List.generate_property ('layer', self.layer))
         fp_poly_node.add (s_expression.List.generate_property ('width', self.width))
         fp_poly_node.add (s_expression.List.generate_property_symbol ('fill', self.fill))
         fp_poly_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_poly_node


   class Pad:
      def __init__ (self):
         self.name = None  # str eg. "1"
         self.type = None  # symbol eg. smd, thru_hole, np_thru_hole
         self.locked = None   # boolean
         self.at = At ()
         self.size = Size ()
         self.drill = Drill ()
         self.layers = None   # multiple symbols eg. *.Cu *.Mask
         self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         circle = Footprint.Circle ()
         circle.center = Xy.parse (node.first_kind ('center'))
         circle.radius = node.property ('radius')
         circle.stroke = Stroke.parse (node.first_kind ('stroke'))
         circle.fill = Fill.parse (node.first_kind ('fill'))

         return circle

      def generate (self):
         circle_node = s_expression.List.generate ('circle')
         circle_node.add (self.center.generate_with_alternate_name ('center'))
         circle_node.add (s_expression.List.generate_property ('radius', self.radius))
         circle_node.add (self.stroke.generate ())
         circle_node.add (self.fill.generate ())
         return circle_node


