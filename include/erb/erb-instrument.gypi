##############################################################################
#
#     erb-instrument.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'defines': [
      'erb_TARGET_INSTRUMENT',
   ],

   'includes' : ['erb-src.gypi'],

   'sources': [
   ],

   'include_dirs': [
      '..',
   ],

   'direct_dependent_settings': {
      'defines': [
         'erb_TARGET_INSTRUMENT',
      ],

      'include_dirs': [
         '..',
      ],
   },
}
