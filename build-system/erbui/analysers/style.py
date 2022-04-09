##############################################################################
#
#     style.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from .. import adapter
from .. import ast
from .. import error

import os
from difflib import get_close_matches

PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_ROOT = os.path.abspath (os.path.dirname (os.path.dirname (os.path.dirname (PATH_THIS))))



class AnalyserStyle:

   class Library:
      def __init__ (self):
         self.catalogs = []
         self.keywords = set ()

      def add (self, catalog):
         self.catalogs.append (catalog)
         self.keywords = self.keywords.union (catalog.keywords)

   class Catalog:
      class Entry:
         def __init__ (self, keywords, parts):
            self.keywords = keywords
            self.parts = parts

      def __init__ (self, manufacturer):
         self.manufacturer = manufacturer
         self.entries = []

      def add (self, keywords, parts):
         assert isinstance (keywords, set)
         assert isinstance (parts, list)
         self.entries.append (AnalyserStyle.Catalog.Entry (keywords, parts))

      @property
      def keywords (self):
         ret = set ()
         for entry in self.entries:
            ret = ret.union (entry.keywords)
         return ret

   def __init__ (self):
      self.libraries = {}
      self.init_jack ()
      self.init_pot ()
      self.init_switch ()
      self.init_trim ()
      self.init_button ()
      self.init_led ()
      self.init_led_bi ()
      self.init_led_rgb ()

   def init_jack (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add ({'hex'}, ['thonk.pj398sm', 'thonk.pj398sm.nut.hex'])
      catalog.add ({'knurled'}, ['thonk.pj398sm', 'thonk.pj398sm.nut.knurled'])
      catalog.add (
         {'befaco', 'bananuts', 'black'}, ['thonk.pj398sm', 'befaco.bananuts.black']
      )
      catalog.add (
         {'befaco', 'bananuts', 'red'}, ['thonk.pj398sm', 'befaco.bananuts.red']
      )
      library.add (catalog)

      kinds = ['AudioIn', 'AudioOut', 'CvIn', 'CvOut', 'GateIn', 'GateOut']
      for kind in kinds:
         self.libraries [kind] = library

   def init_pot (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add (
         {'rogan', '3ps','size3', 'large', 'skirt', 'd_shaft'}, ['alpha.9mm.dshaft', 'rogan.3ps.dshaft']
      )
      catalog.add (
         {'rogan', '2ps','size2', 'medium', 'skirt', 'd_shaft'}, ['alpha.9mm.dshaft', 'rogan.2ps.dshaft']
      )
      catalog.add (
         {'rogan', '1ps','size1', 'small', 'skirt', 'd_shaft'}, ['alpha.9mm.dshaft', 'rogan.1ps.dshaft']
      )
      catalog.add (
         {'rogan', '2p','size2', 'medium', 'unskirted', 'd_shaft'}, ['alpha.9mm.dshaft', 'rogan.2p.dshaft']
      )
      catalog.add (
         {'rogan', '1p','size1', 'small', 'unskirted', 'd_shaft'}, ['alpha.9mm.dshaft', 'rogan.1p.dshaft']
      )
      catalog.add (
         {'rogan', '6ps','size6', 'xlarge', 'skirt', 'd_shaft'}, ['alpha.9mm.dshaft', 'rogan.6ps.dshaft']
      )
      catalog.add (
         {'rogan', '5ps','size5', 'larger', 'skirt', 'd_shaft'}, ['alpha.9mm.dshaft', 'rogan.5ps.dshaft']
      )
      catalog.add (
         {'sifam', 'selco', 'dbn150', 'large', 'skirt', 'd_shaft', 'white'},
         ['alpha.9mm.dshaft', 'sifam.dbn150.white.dshaft', 'sifam.c150.white']
      )
      catalog.add (
         {'sifam', 'selco', 'dbn151', 'large', 'skirt', 'd_shaft', 'white', 'line'},
         ['alpha.9mm.dshaft', 'sifam.dbn151.white.dshaft', 'sifam.c151.white']
      )
      catalog.add (
         {'sifam', 'selco', 'drn110', 'small', 'skirt', 'd_shaft', 'white'},
         ['alpha.9mm.dshaft', 'sifam.drn110.white.dshaft', 'sifam.c110.white']
      )
      catalog.add (
         {'sifam', 'selco', 'drn111', 'small', 'skirt', 'd_shaft', 'white', 'line'},
         ['alpha.9mm.dshaft', 'sifam.drn111.white.dshaft', 'sifam.c111.white']
      )
      catalog.add (
         {'sifam', 'selco', 'db150', 'large', 'unskirted', 'd_shaft', 'white'},
         ['alpha.9mm.dshaft', 'sifam.db150.white.dshaft', 'sifam.c150.white']
      )
      catalog.add (
         {'sifam', 'selco', 'db151', 'large', 'unskirted', 'd_shaft', 'white', 'line'},
         ['alpha.9mm.dshaft', 'sifam.db151.white.dshaft', 'sifam.c151.white']
      )
      catalog.add (
         {'sifam', 'selco', 'dr110', 'small', 'unskirted', 'd_shaft', 'white'},
         ['alpha.9mm.dshaft', 'sifam.dr110.white.dshaft', 'sifam.c110.white']
      )
      catalog.add (
         {'sifam', 'selco', 'dr111', 'small', 'unskirted', 'd_shaft', 'white', 'line'},
         ['alpha.9mm.dshaft', 'sifam.dr111.white.dshaft', 'sifam.c111.white']
      )
      library.add (catalog)

      self.libraries ['Pot'] = library

   def init_switch (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add (
         {'dailywell', '2ms3', 'on_off_on'}, ['dailywell.2ms3']
      )
      catalog.add (
         {'dailywell', '2ms1', 'on_on'}, ['dailywell.2ms1']
      )
      library.add (catalog)

      self.libraries ['Switch'] = library

   def init_trim (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add (
         {'songhuei', '9mm', 'tall'}, ['songhuei.9mm.tall']
      )
      catalog.add (
         {'songhuei', '9mm', 'tall', 'center_detent'}, ['songhuei.9mm.tall.center_detent']
      )
      catalog.add (
         {'songhuei', '9mm', 'short'}, ['songhuei.9mm.short']
      )
      catalog.add (
         {'songhuei', '9mm', 'short', 'center_detent'}, ['songhuei.9mm.short.center_detent']
      )
      library.add (catalog)

      self.libraries ['Trim'] = library

   def init_button (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add (
         {'tl1105', 'black'}, ['tl1105', '1rblk']
      )
      catalog.add (
         {'ck', 'd6r', 'black'}, ['ck.d6r.black']
      )
      catalog.add (
         {'ck', 'd6r', 'white'}, ['ck.d6r.white']
      )
      catalog.add (
         {'ck', 'd6r', 'red'}, ['ck.d6r.red']
      )
      library.add (catalog)

      self.libraries ['Button'] = library

   def init_led (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add (
         {'tht', '3mm', 'red'}, ['led.tht.3mm.red']
      )
      catalog.add (
         {'tht', '3mm', 'green'}, ['led.tht.3mm.green']
      )
      catalog.add (
         {'tht', '3mm', 'yellow'}, ['led.tht.3mm.yellow']
      )
      catalog.add (
         {'tht', '3mm', 'orange'}, ['led.tht.3mm.orange']
      )
      library.add (catalog)

      self.libraries ['Led'] = library

   def init_led_bi (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add (
         {'tht', '3mm', 'green_red'}, ['led.tht.3mm.green_red']
      )
      library.add (catalog)

      self.libraries ['LedBi'] = library

   def init_led_rgb (self):
      library = AnalyserStyle.Library ()
      catalog = AnalyserStyle.Catalog ('diy')
      catalog.add (
         {'smt', '3mm', 'rgb'}, ['led.smt.3mm.rgb']
      )
      library.add (catalog)

      self.libraries ['LedRgb'] = library


   #--------------------------------------------------------------------------

   def analyse (self, global_namespace):
      for module in global_namespace.modules:
         self.analyse_module (module)


   #--------------------------------------------------------------------------

   def analyse_module (self, module):
      for control in module.controls:
         self.analyse_select (control, self.libraries [control.kind])


   #--------------------------------------------------------------------------

   def analyse_select (self, control, library):
      catalogs = library.catalogs
      keywords = library.keywords

      styles = set ()
      if control.style is not None:
         for keyword in control.style.keyword_names:
            if keyword.value not in keywords:
               raise error.unknown_style (keyword, keywords)
            styles.add (keyword.value.casefold ())

      cur_common_nbr = -1
      cur_element = None

      for catalog in catalogs:
         for element in catalog.entries:
            common_nbr = len (styles.intersection (element.keywords))
            if common_nbr > cur_common_nbr:
               cur_common_nbr = common_nbr
               cur_element = element

      for unknown in styles.difference (cur_element.keywords):
         for keyword in control.style.keyword_names:
            if keyword.value.casefold () == unknown:
               raise error.incompatible_style (keyword, cur_element.keywords)

      control.parts = cur_element.parts

