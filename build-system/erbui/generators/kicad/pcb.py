##############################################################################
#
#     pcb.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import hashlib
import math
import os
import pickle
import tempfile
from . import s_expression

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ARTIFACTS = os.path.join (PATH_THIS, 'artifacts')



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
      self.vias = []
      self.segments = []
      self.zones = []

   @staticmethod
   def read (filepath):
      assert os.path.isabs (filepath)

      if not os.path.exists (PATH_ARTIFACTS):
         os.makedirs (PATH_ARTIFACTS)

      path_cache = os.path.join (
         PATH_ARTIFACTS,
         hashlib.sha1 (filepath.encode ()).hexdigest ()
      )

      if os.path.exists (path_cache):
         use_cache = os.path.getmtime (path_cache) > os.path.getmtime (filepath) \
            and os.path.getmtime (path_cache) > os.path.getmtime (PATH_THIS)
      else:
         use_cache = False

      if use_cache:
         with open (path_cache, 'rb') as file:
            return pickle.load (file)

      else:
         with open (filepath, 'r', encoding='utf-8') as file:
            content = file.read ()

         parser = s_expression.Parser ()
         root_node = parser.parse (content, filepath)

         ret = Root.parse (root_node)
         with tempfile.NamedTemporaryFile (mode='wb', delete=False, dir=PATH_ARTIFACTS) as file:
            tmppath = file.name
            pickle.dump (ret, file)
         os.replace (tmppath, path_cache)

         return ret

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

      for via_node in node.filter_kind ('via'):
         root.vias.append (Via.parse (via_node))

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
         layers_node.add (layer.generate ())

      root_node.add (self.setup.generate ())

      for net in self.nets:
         root_node.add (net.generate ())

      for footprint in self.footprints:
         root_node.add (footprint.generate ())

      for gr_shape in self.gr_shapes:
         root_node.add (gr_shape.generate ())

      for via in self.vias:
         root_node.add (via.generate ())

      for segment in self.segments:
         root_node.add (segment.generate ())

      for zone in self.zones:
         root_node.add (zone.generate ())

      return root_node

   def rotate (self, rotation):
      for footprint in self.footprints:
         footprint.rotate (rotation)

      for gr_shape in self.gr_shapes:
         gr_shape.rotate (rotation)

      for segment in self.segments:
         segment.rotate (rotation)

      for zone in self.zones:
         zone.rotate (rotation)

   def translate (self, x, y):
      for footprint in self.footprints:
         footprint.translate (x, y)

      for gr_shape in self.gr_shapes:
         gr_shape.translate (x, y)

      for segment in self.segments:
         segment.translate (x, y)

      for zone in self.zones:
         zone.translate (x, y)

   def get_bounds (self, layer):
      bounds = Bounds (None, None, None, None)

      for footprint in self.footprints:
         bounds.union (footprint.get_bounds (layer))

      for gr_shape in self.gr_shapes:
         bounds.union (gr_shape.get_bounds (layer))

      for segment in self.segments:
         bounds.union (segment.get_bounds (layer))

      for zone in self.zones:
         bounds.union (zone.get_bounds (layer))

      return bounds


# -- Rotation ----------------------------------------------------------------

class Rotation:
   def __init__ (self, rotation_degree):
      self.degree = rotation_degree
      self.radian = float (self.degree) * 2.0 * math.pi / 360.0

      # axis is top/down in pcb coordinates: invert rotation angle
      self.cos_a = math.cos (- self.radian)
      self.sin_a = math.sin (- self.radian)

   def apply (self, x, y):
      return (
         x * self.cos_a - y * self.sin_a,
         x * self.sin_a + y * self.cos_a
      )


# -- Bounds ------------------------------------------------------------------

class Bounds:
   def __init__ (self, left, top, right, bottom):
      self.left = left
      self.top = top
      self.right = right
      self.bottom = bottom

   def union (self, bounds):
      def min_opt (x, y):
         if x is None:
            return y
         elif y is None:
            return x
         else:
            return min (x, y)

      def max_opt (x, y):
         if x is None:
            return y
         elif y is None:
            return x
         else:
            return max (x, y)

      self.left = min_opt (bounds.left, self.left)
      self.top = min_opt (bounds.top, self.top)
      self.right = max_opt (bounds.right, self.right)
      self.bottom = max_opt (bounds.bottom, self.bottom)


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
      if len (node.entities) >= 4:
         at.rotation = node.entities [3].value

      return at

   def generate (self):
      at_node = s_expression.List.generate ('at')
      at_node.add (s_expression.FloatLiteral (self.x))
      at_node.add (s_expression.FloatLiteral (self.y))
      if self.rotation:
         at_node.add (s_expression.FloatLiteral (self.rotation))

      return at_node

   def rotate (self, rotation):
      self.x, self.y = rotation.apply (self.x, self.y)

      if not self.rotation:
         self.rotation = 0
      self.rotation = (self.rotation + rotation.degree + 360) % 360

   def translate (self, x, y):
      self.x += x
      self.y += y


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

   def rotate (self, rotation):
      self.x, self.y = rotation.apply (self.x, self.y)

   def translate (self, x, y):
      self.x += x
      self.y += y


# -- Xyz ---------------------------------------------------------------------

class Xyz:
   def __init__ (self):
      self.x = None        # float
      self.y = None        # float
      self.z = None        # float

   @staticmethod
   def parse (node):
      if not node: return None

      xyz = Xyz ()
      xyz.x = node.entities [1].value
      xyz.y = node.entities [2].value
      xyz.z = node.entities [3].value

      return xyz

   def generate (self):
      xyz_node = s_expression.List.generate ('xyz')
      xyz_node.add (s_expression.FloatLiteral (self.x))
      xyz_node.add (s_expression.FloatLiteral (self.y))
      xyz_node.add (s_expression.FloatLiteral (self.z))

      return xyz_node

   def generate_with_alternate_name (self, name):
      xyz_node = s_expression.List.generate (name)
      xyz_node.add (s_expression.FloatLiteral (self.x))
      xyz_node.add (s_expression.FloatLiteral (self.y))
      xyz_node.add (s_expression.FloatLiteral (self.z))

      return xyz_node


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

   def rotate (self, rotation):
      for item in self.items:
         item.x, item.y = rotation.apply (item.x, item.y)

   def translate (self, x, y):
      for item in self.items:
         item.x += x
         item.y += y

   @property
   def bounds (self):
      xs = [item.x for item in self.items]
      ys = [item.y for item in self.items]
      return Bounds (min (xs), min (ys), max (xs), max (ys))


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
      if self.justify:
         effects_node.add (self.justify.generate ())
      return effects_node


   class Font:
      def __init__ (self):
         self.size = Xy ()
         self.thickness = None   # float
         self.italic = None      # boolean

      @staticmethod
      def parse (node):
         if not node: return None

         font = Effects.Font ()
         font.size = Xy.parse (node.first_kind ('size'))
         font.thickness = node.property ('thickness')
         font.italic = any (e.is_symbol and e.value == 'italic' for e in node.entities)

         return font

      def generate (self):
         font_node = s_expression.List.generate ('font')
         font_node.add (self.size.generate_with_alternate_name ('size'))
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
         justify.mirror = any (e.is_symbol and e.value == 'mirror' for e in node.entities)

         return justify

      def generate (self):
         justify_node = s_expression.List.generate ('justify')
         if self.type:
            justify_node.add (s_expression.Symbol (self.type))
         if self.mirror:
            justify_node.add (s_expression.Symbol ('mirror'))
         return justify_node


# -- General -----------------------------------------------------------------

class General:
   def __init__ (self):
      self.thickness = None # float

   @staticmethod
   def parse (node):
      if not node: return None

      general = General ()
      general.thickness = node.property ('thickness')
      return general

   def generate (self):
      general_node = s_expression.List.generate ('general')
      general_node.add (s_expression.List.generate_property ('thickness', self.thickness))
      return general_node


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
      self.pcbplotparams = Setup.Pcbplotparams ()

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
      if self.solder_mask_min_width:
         setup_node.add (s_expression.List.generate_property ('solder_mask_min_width', self.solder_mask_min_width))
      if self.grid_origin:
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

         pcbplotparams = Setup.Pcbplotparams ()
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
         pcbplotparams_node.add (s_expression.List.generate_property_symbol ('usegerberadvancedattributes', self.usegerberadvancedattributes))
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
      self.attr = Footprint.Attr ()
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
      footprint.attr = Footprint.Attr.parse (node.first_kind ('attr'))

      for fp_shape_node in node.filter_kinds (['fp_text', 'fp_line', 'fp_arc', 'fp_circle', 'fp_poly']):
         fp_shape_kind = fp_shape_node.entities [0].value
         if fp_shape_kind == 'fp_text':
            footprint.fp_shapes.append (Footprint.FpText.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_line':
            footprint.fp_shapes.append (Footprint.FpLine.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_arc':
            footprint.fp_shapes.append (Footprint.FpArc.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_circle':
            footprint.fp_shapes.append (Footprint.FpCircle.parse (fp_shape_node))
         elif fp_shape_kind == 'fp_poly':
            footprint.fp_shapes.append (Footprint.FpPoly.parse (fp_shape_node))
         else:
            assert False

      for pad_node in node.filter_kind ('pad'):
         footprint.pads.append (Footprint.Pad.parse (pad_node))

      for model_node in node.filter_kind ('model'):
         footprint.models.append (Footprint.Model.parse (model_node))

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
      footprint_node.add (self.attr.generate ())
      for fp_shape in self.fp_shapes:
         footprint_node.add (fp_shape.generate ())
      for pad in self.pads:
         footprint_node.add (pad.generate ())
      for model in self.models:
         footprint_node.add (model.generate ())
      return footprint_node

   @property
   def reference (self):
      matches = [e for e in self.fp_shapes if isinstance (e, Footprint.FpText) and e.name == 'reference']
      match = next (iter (matches), None)
      return match.value

   def set_reference (self, value):
      matches = [e for e in self.fp_shapes if isinstance (e, Footprint.FpText) and e.name == 'reference']
      match = next (iter (matches), None)
      match.value = value

   def rotate (self, rotation):
      self.at.rotate (rotation)
      # pads need to be rotated as well for some reason
      for pad in self.pads:
         if not pad.at.rotation:
            pad.at.rotation = 0
         pad.at.rotation = (pad.at.rotation + rotation.degree + 360) % 360

   def translate (self, x, y):
      self.at.translate (x, y)

   def get_bounds (self, layer):
      bounds = Bounds (None, None, None, None)

      for fp_shape in self.fp_shapes:
         bounds.union (fp_shape.get_bounds (layer))

      if bounds.left is not None:
         bounds.left += self.at.x

      if bounds.top is not None:
         bounds.top += self.at.y

      if bounds.right is not None:
         bounds.right += self.at.x

      if bounds.bottom is not None:
         bounds.bottom += self.at.y

      return bounds

   class Attr:
      def __init__ (self):
         self.attributes = [] # list of symbols, eg. exclude_from_pos_files exclude_from_bom

      @staticmethod
      def parse (node):
         if not node: return None

         attr = Footprint.Attr ()
         for attribute in node.entities [1:]:
            attr.attributes.append (attribute.value)
         return attr

      def generate (self):
         attr_node = s_expression.List.generate ('attr')
         for attribute in self.attributes:
            attr_node.add (s_expression.Symbol (attribute))
         return attr_node

   class FpText:
      def __init__ (self):
         self.name = None  # symbol, eg. reference
         self.value = None # str, eg. R1
         self.at = At ()
         self.layer = None # str, eg. "F.SilkS"
         self.hide = None # boolean
         self.effects = Effects ()
         self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         fp_text = Footprint.FpText ()
         fp_text.name = node.entities [1].value
         fp_text.value = node.entities [2].value
         fp_text.at = At.parse (node.first_kind ('at'))
         fp_text.layer = node.property ('layer')
         fp_text.hide = any (e.is_symbol and e.value == 'hide' for e in node.entities)
         fp_text.effects = Effects.parse (node.first_kind ('effects'))
         fp_text.tstamp = node.property ('tstamp')

         return fp_text

      def generate (self):
         fp_text_node = s_expression.List.generate ('fp_text')
         fp_text_node.add (s_expression.Symbol (self.name))
         fp_text_node.add (s_expression.StringLiteral (self.value))
         fp_text_node.add (self.at.generate ())
         fp_text_node.add (s_expression.List.generate_property ('layer', self.layer))
         if self.hide:
            fp_text_node.add (s_expression.Symbol ('hide'))
         fp_text_node.add (self.effects.generate ())
         fp_text_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_text_node

      def get_bounds (self, layer):
         if self.layer != layer:
            return Bounds (None, None, None, None)

         # best effort
         return Bounds (self.at.x, self.at.y, self.at.x, self.at.y)


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

      def get_bounds (self, layer):
         if self.layer != layer:
            return Bounds (None, None, None, None)

         return Bounds (
            min (self.start.x, self.end.x),
            min (self.start.y, self.end.y),
            max (self.start.x, self.end.x),
            max (self.start.y, self.end.y)
         )


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
         fp_arc_node.add (self.mid.generate_with_alternate_name ('mid'))
         fp_arc_node.add (self.end.generate_with_alternate_name ('end'))
         fp_arc_node.add (s_expression.List.generate_property ('layer', self.layer))
         fp_arc_node.add (s_expression.List.generate_property ('width', self.width))
         fp_arc_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_arc_node

      def get_bounds (self, layer):
         if self.layer != layer:
            return Bounds (None, None, None, None)

         # not accurate but should be fine
         return Bounds (
            min (self.start.x, self.mid.x, self.end.x),
            min (self.start.y, self.mid.y, self.end.y),
            max (self.start.x, self.mid.x, self.end.x),
            max (self.start.y, self.mid.y, self.end.y)
         )


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
         fp_circle_node.add (self.center.generate_with_alternate_name ('center'))
         fp_circle_node.add (self.end.generate_with_alternate_name ('end'))
         fp_circle_node.add (s_expression.List.generate_property ('layer', self.layer))
         fp_circle_node.add (s_expression.List.generate_property ('width', self.width))
         fp_circle_node.add (s_expression.List.generate_property_symbol ('fill', self.fill))
         fp_circle_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return fp_circle_node

      @property
      def radius (self):
         vec_x = self.center.x - self.end.x
         vec_y = self.center.y - self.end.y
         return math.sqrt (vec_x * vec_x + vec_y * vec_y)

      def get_bounds (self, layer):
         if self.layer != layer:
            return Bounds (None, None, None, None)

         r = self.radius
         return Bounds (
            self.center.x - r, self.center.y - r,
            self.center.x + r, self.center.y + r
         )


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
         fp_poly.pts = Pts.parse (node.first_kind ('pts'))
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

      def get_bounds (self, layer):
         if self.layer != layer:
            return Bounds (None, None, None, None)

         return self.pts.bounds


   class Pad:
      def __init__ (self):
         self.name = None     # str eg. "1"
         self.type = None     # symbol eg. smd, thru_hole, np_thru_hole
         self.shape = None    # symbol eg. oval
         self.locked = None   # boolean
         self.at = At ()
         self.size = Xy ()
         self.drill = Footprint.Pad.Drill ()
         self.layers = Footprint.Pad.Layers ()   # multiple symbols eg. *.Cu *.Mask
         self.net = Net ()
         self.tstamp = None            # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

      @staticmethod
      def parse (node):
         if not node: return None

         pad = Footprint.Pad ()
         pad.name = node.entities [1].value
         pad.type = node.entities [2].value
         pad.shape = node.entities [3].value
         pad.locked = any (e.is_symbol and e.value == 'locked' for e in node.entities)
         pad.at = At.parse (node.first_kind ('at'))
         pad.size = Xy.parse (node.first_kind ('size'))
         pad.drill = Footprint.Pad.Drill.parse (node.first_kind ('drill'))
         pad.layers = Footprint.Pad.Layers.parse (node.first_kind ('layers'))
         pad.net = Net.parse (node.first_kind ('net'))
         pad.tstamp = node.property ('tstamp')

         return pad

      def generate (self):
         pad_node = s_expression.List.generate ('pad')
         pad_node.add (s_expression.StringLiteral (self.name))
         pad_node.add (s_expression.Symbol (self.type))
         pad_node.add (s_expression.Symbol (self.shape))
         if self.locked:
            pad_node.add (s_expression.Symbol ('locked'))
         pad_node.add (self.at.generate ())
         pad_node.add (self.size.generate_with_alternate_name ('size'))
         if self.drill:
            pad_node.add (self.drill.generate ())
         pad_node.add (self.layers.generate ())
         if self.net:
            pad_node.add (self.net.generate ())
         pad_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
         return pad_node

      class Drill:
         def __init__ (self):
            self.type = None     # None (circular) or symbol oval
            self.size_x = None   # float
            self.size_y = None   # float, only relevant when oval

         @staticmethod
         def parse (node):
            if not node: return None

            drill = Footprint.Pad.Drill ()
            if node.entities [1].is_symbol:
               drill.type = node.entities [1].value
               drill.size_x = node.entities [2].value
               drill.size_y = node.entities [3].value
            elif node.entities [1].is_float_literal or node.entities [1].is_integer_literal:
               drill.size_x = node.entities [1].value
            else:
               assert False

            return drill

         def generate (self):
            drill_node = s_expression.List.generate ('drill')
            if self.type:
               drill_node.add (s_expression.Symbol (self.type))
               drill_node.add (s_expression.FloatLiteral (self.size_x))
               drill_node.add (s_expression.FloatLiteral (self.size_y))
            else:
               drill_node.add (s_expression.FloatLiteral (self.size_x))
            return drill_node

      class Layers:
         def __init__ (self):
            self.names = []

         @staticmethod
         def parse (node):
            if not node: return None

            layers = Footprint.Pad.Layers ()
            for layer in node.entities [1:]:
               layers.names.append (layer.value)
            return layers

         def generate (self):
            layers_node = s_expression.List.generate ('layers')
            for name in self.names:
               layers_node.add (s_expression.Symbol (name))
            return layers_node

   class Model:
      def __init__ (self):
         self.name = None  # str, eg. "${KISYS3DMOD}/Diode_SMD.3dshapes/D_SOD-123.wrl"
         self.offset = Xyz ()
         self.scale = Xyz ()
         self.rotate = Xyz ()

      @staticmethod
      def parse (node):
         if not node: return None

         model = Footprint.Model ()
         model.name = node.entities [1].value
         model.offset = Xyz.parse (node.first_kind ('offset').entities [1])
         model.scale = Xyz.parse (node.first_kind ('scale').entities [1])
         model.rotate = Xyz.parse (node.first_kind ('rotate').entities [1])

         return model

      def generate (self):
         model_node = s_expression.List.generate ('model')
         model_node.add (s_expression.StringLiteral (self.name))

         offset_node = model_node.add (s_expression.List.generate ('offset'))
         offset_node.add (self.offset.generate ())

         scale_node = model_node.add (s_expression.List.generate ('scale'))
         scale_node.add (self.scale.generate ())

         rotate_node = model_node.add (s_expression.List.generate ('rotate'))
         rotate_node.add (self.rotate.generate ())

         return model_node


class GrCircle:
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

      gr_circle = GrCircle ()
      gr_circle.center = Xy.parse (node.first_kind ('center'))
      gr_circle.end = Xy.parse (node.first_kind ('end'))
      gr_circle.layer = node.property ('layer')
      gr_circle.width = node.property ('width')
      gr_circle.fill = node.property ('fill')
      gr_circle.tstamp = node.property ('tstamp')

      return gr_circle

   def generate (self):
      gr_circle_node = s_expression.List.generate ('gr_circle')
      gr_circle_node.add (self.center.generate_with_alternate_name ('center'))
      gr_circle_node.add (self.end.generate_with_alternate_name ('end'))
      gr_circle_node.add (s_expression.List.generate_property ('layer', self.layer))
      gr_circle_node.add (s_expression.List.generate_property ('width', self.width))
      gr_circle_node.add (s_expression.List.generate_property_symbol ('fill', self.fill))
      gr_circle_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
      return gr_circle_node

   def rotate (self, rotation):
      self.center.rotate (rotation)
      self.end.rotate (rotation)

   def translate (self, x, y):
      self.center.translate (x, y)
      self.end.translate (x, y)

   @property
   def radius (self):
      vec_x = self.center.x - self.end.x
      vec_y = self.center.y - self.end.y
      return math.sqrt (vec_x * vec_x + vec_y * vec_y)

   def get_bounds (self, layer):
      if self.layer != layer:
         return Bounds (None, None, None, None)

      r = self.radius
      return Bounds (
         self.center.x - r, self.center.y - r,
         self.center.x + r, self.center.y + r
      )


class GrLine:
   def __init__ (self):
      self.start = Xy ()
      self.end = Xy ()
      self.layer = None  # str, eg. "F.SilkS"
      self.width = None  # float
      self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

   @staticmethod
   def parse (node):
      if not node: return None

      gr_line = GrLine ()
      gr_line.start = Xy.parse (node.first_kind ('start'))
      gr_line.end = Xy.parse (node.first_kind ('end'))
      gr_line.layer = node.property ('layer')
      gr_line.width = node.property ('width')
      gr_line.tstamp = node.property ('tstamp')

      return gr_line

   def generate (self):
      gr_line_node = s_expression.List.generate ('gr_line')
      gr_line_node.add (self.start.generate_with_alternate_name ('start'))
      gr_line_node.add (self.end.generate_with_alternate_name ('end'))
      gr_line_node.add (s_expression.List.generate_property ('layer', self.layer))
      gr_line_node.add (s_expression.List.generate_property ('width', self.width))
      gr_line_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
      return gr_line_node

   def rotate (self, rotation):
      self.start.rotate (rotation)
      self.end.rotate (rotation)

   def translate (self, x, y):
      self.start.translate (x, y)
      self.end.translate (x, y)

   def get_bounds (self, layer):
      if self.layer != layer:
         return Bounds (None, None, None, None)

      return Bounds (
         min (self.start.x, self.end.x),
         min (self.start.y, self.end.y),
         max (self.start.x, self.end.x),
         max (self.start.y, self.end.y)
      )


class GrText:
   def __init__ (self):
      self.value = None # str, eg. "github.com/ohmtech-rdi/eurorack-blocks"
      self.at = At ()
      self.layer = None # str, eg. "F.SilkS"
      self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6
      self.effects = Effects ()

   @staticmethod
   def parse (node):
      if not node: return None

      gr_text = GrText ()
      gr_text.value = node.entities [1].value
      gr_text.at = At.parse (node.first_kind ('at'))
      gr_text.layer = node.property ('layer')
      gr_text.tstamp = node.property ('tstamp')
      gr_text.effects = Effects.parse (node.first_kind ('effects'))

      return gr_text

   def generate (self):
      gr_text_node = s_expression.List.generate ('gr_text')
      gr_text_node.add (s_expression.StringLiteral (self.value))
      gr_text_node.add (self.at.generate ())
      gr_text_node.add (s_expression.List.generate_property ('layer', self.layer))
      gr_text_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
      gr_text_node.add (self.effects.generate ())
      return gr_text_node

   def rotate (self, rotation):
      self.at.rotate (rotation)

   def translate (self, x, y):
      self.at.translate (x, y)

   def get_bounds (self, layer):
      if self.layer != layer:
         return Bounds (None, None, None, None)

      # best effort
      return Bounds (self.at.x, self.at.y, self.at.x, self.at.y)


class Via:
   def __init__ (self):
      self.locked = None   # boolean
      self.at = Xy ()
      self.size = None     # float
      self.drill = None    # float
      self.layers = []     # [str], eg. "F.Cu" "B.Cu"
      self.free = None     # boolean
      self.net = None      # int, eg. 9
      self.tstamp = None   # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

   @staticmethod
   def parse (node):
      if not node: return None

      via = Via ()
      via.locked = any (e.is_symbol and e.value == 'locked' for e in node.entities)
      via.at = At.parse (node.first_kind ('at'))
      via.size = node.property ('size')
      via.drill = node.property ('drill')
      via.layers = [e.value for e in node.first_kind ('layers').entities [1:]]
      via.free = node.first_kind ('free') != None
      via.net = node.property ('net')
      via.tstamp = node.property ('tstamp')

      return via

   def generate (self):
      via_node = s_expression.List.generate ('via')
      if self.locked:
         via_node.add (s_expression.Symbol ('locked'))
      via_node.add (self.at.generate ())
      via_node.add (s_expression.List.generate_property ('size', self.size))
      via_node.add (s_expression.List.generate_property ('drill', self.drill))
      layers_node = s_expression.List.generate ('layers')
      for layer in self.layers:
         layers_node.add (s_expression.StringLiteral (layer))
      via_node.add (layers_node)
      if self.free:
         via_node.add (s_expression.List.generate ('free'))
      via_node.add (s_expression.List.generate_property ('net', self.net))
      via_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
      return via_node

   def rotate (self, rotation):
      pass # nothing

   def translate (self, x, y):
      self.at.translate (x, y)

   def get_bounds (self, layer):
      if self.layer != layer:
         return Bounds (None, None, None, None)

      return Bounds (
         self.at.x - self.size * 0.5,
         self.at.y - self.size * 0.5,
         self.at.x + self.size * 0.5,
         self.at.y + self.size * 0.5
      )


class Segment:
   def __init__ (self):
      self.start = Xy ()
      self.end = Xy ()
      self.width = None  # float
      self.layer = None  # str, eg. "F.Cu"
      self.net = None    # int, eg. 9
      self.tstamp = None # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6

   @staticmethod
   def parse (node):
      if not node: return None

      segment = Segment ()
      segment.start = Xy.parse (node.first_kind ('start'))
      segment.end = Xy.parse (node.first_kind ('end'))
      segment.width = node.property ('width')
      segment.layer = node.property ('layer')
      segment.net = node.property ('net')
      segment.tstamp = node.property ('tstamp')

      return segment

   def generate (self):
      segment_node = s_expression.List.generate ('segment')
      segment_node.add (self.start.generate_with_alternate_name ('start'))
      segment_node.add (self.end.generate_with_alternate_name ('end'))
      segment_node.add (s_expression.List.generate_property ('width', self.width))
      segment_node.add (s_expression.List.generate_property ('layer', self.layer))
      segment_node.add (s_expression.List.generate_property ('net', self.net))
      segment_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
      return segment_node

   def rotate (self, rotation):
      self.start.rotate (rotation)
      self.end.rotate (rotation)

   def translate (self, x, y):
      self.start.translate (x, y)
      self.end.translate (x, y)

   def get_bounds (self, layer):
      if self.layer != layer:
         return Bounds (None, None, None, None)

      return Bounds (
         min (self.start.x, self.end.x),
         min (self.start.y, self.end.y),
         max (self.start.x, self.end.x),
         max (self.start.y, self.end.y)
      )


class Zone:
   def __init__ (self):
      self.net = None      # int, eg. 1
      self.net_name = None # str, eg. "GND"
      self.layer = None    # str, eg. "F.Cu"
      self.tstamp = None   # str, eg. 839a72a1-b92d-4d34-94b8-fd1a057ff2d6
      self.hatch = Zone.Hatch ()
      self.connect_pads = Zone.ConnectPads ()
      self.min_thickness = None  # float
      self.fill = Zone.Fill ()
      self.polygon = Zone.Polygon ()
      self.filled_polygon = Zone.FilledPolygon ()

   @staticmethod
   def parse (node):
      if not node: return None

      zone = Zone ()
      zone.net = node.property ('net')
      zone.net_name = node.property ('net_name')
      zone.layer = node.property ('layer')
      zone.tstamp = node.property ('tstamp')
      zone.hatch = Zone.Hatch.parse (node.first_kind ('hatch'))
      zone.connect_pads = Zone.ConnectPads.parse (node.first_kind ('connect_pads'))
      zone.min_thickness = node.property ('min_thickness')
      zone.fill = Zone.Fill.parse (node.first_kind ('fill'))
      zone.polygon = Zone.Polygon.parse (node.first_kind ('polygon'))
      zone.filled_polygon = Zone.FilledPolygon.parse (node.first_kind ('filled_polygon'))
      return zone

   def generate (self):
      zone_node = s_expression.List.generate ('zone')
      zone_node.add (s_expression.List.generate_property ('net', self.net))
      zone_node.add (s_expression.List.generate_property ('net_name', self.net_name))
      zone_node.add (s_expression.List.generate_property ('layer', self.layer))
      zone_node.add (s_expression.List.generate_property ('tstamp', self.tstamp))
      zone_node.add (self.hatch.generate ())
      zone_node.add (self.connect_pads.generate ())
      zone_node.add (s_expression.List.generate_property ('min_thickness', self.min_thickness))
      zone_node.add (self.fill.generate ())
      zone_node.add (self.polygon.generate ())
      if self.filled_polygon:
         zone_node.add (self.filled_polygon.generate ())
      return zone_node

   def rotate (self, rotation):
      self.polygon.rotate (rotation)
      self.filled_polygon.rotate (rotation)

   def translate (self, x, y):
      self.polygon.translate (x, y)
      self.filled_polygon.translate (x, y)

   def get_bounds (self, layer):
      if self.layer != layer:
         return Bounds (None, None, None, None)

      return self.polygon.pts.bounds.union (self.filled_polygon.pts.bounds)

   class Hatch:
      def __init__ (self):
         self.display = None  # symbol, eg. edge, full
         self.distance = None # float, not available in KiCad UI

      @staticmethod
      def parse (node):
         if not node: return None

         hatch = Zone.Hatch ()
         hatch.display = node.entities [1].value
         hatch.distance = node.entities [2].value
         return hatch

      def generate (self):
         hatch_node = s_expression.List.generate ('hatch')
         hatch_node.add (s_expression.Symbol (self.display))
         hatch_node.add (s_expression.FloatLiteral (self.distance))
         return hatch_node

   class ConnectPads:
      def __init__ (self):
         self.clearance = None # float

      @staticmethod
      def parse (node):
         if not node: return None

         connect_pads = Zone.ConnectPads ()
         connect_pads.clearance = node.property ('clearance')
         return connect_pads

      def generate (self):
         connect_pads_node = s_expression.List.generate ('connect_pads')
         connect_pads_node.add (s_expression.List.generate_property ('clearance', self.clearance))
         return connect_pads_node

   class Fill:
      def __init__ (self):
         self.active = None               # symbol eg. yes
         self.thermal_gap = None          # float, eg.
         self.thermal_bridge_width = None # float, eg. 0.508

      @staticmethod
      def parse (node):
         if not node: return None

         fill = Zone.Fill ()
         fill.active = any (e.is_symbol and e.value == 'yes' for e in node.entities)
         fill.thermal_gap = node.property ('thermal_gap')
         fill.thermal_bridge_width = node.property ('thermal_bridge_width')
         return fill

      def generate (self):
         fill_node = s_expression.List.generate ('fill')
         if self.active:
            fill_node.add (s_expression.Symbol ('yes'))
         fill_node.add (s_expression.List.generate_property ('thermal_gap', self.thermal_gap))
         fill_node.add (s_expression.List.generate_property ('thermal_bridge_width', self.thermal_bridge_width))
         return fill_node

   class Polygon:
      def __init__ (self):
         self.pts = Pts ()

      @staticmethod
      def parse (node):
         if not node: return None

         polygon = Zone.Polygon ()
         polygon.pts = Pts.parse (node.first_kind ('pts'))
         return polygon

      def generate (self):
         polygon_node = s_expression.List.generate ('polygon')
         polygon_node.add (self.pts.generate ())
         return polygon_node

      def rotate (self, rotation):
         self.pts.rotate (rotation)

      def translate (self, x, y):
         self.pts.translate (x, y)

   class FilledPolygon:
      def __init__ (self):
         self.layer = None # str, eg. "F.Cu"
         self.pts = Pts ()

      @staticmethod
      def parse (node):
         if not node: return None

         filled_polygon = Zone.FilledPolygon ()
         filled_polygon.layer = node.property ('layer')
         filled_polygon.pts = Pts.parse (node.first_kind ('pts'))
         return filled_polygon

      def generate (self):
         filled_polygon_node = s_expression.List.generate ('filled_polygon')
         filled_polygon_node.add (s_expression.List.generate_property ('layer', self.layer))
         filled_polygon_node.add (self.pts.generate ())
         return filled_polygon_node

      def rotate (self, rotation):
         self.pts.rotate (rotation)

      def translate (self, x, y):
         self.pts.translate (x, y)
