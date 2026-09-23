##############################################################################
#
#     erb-rig.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'defines': [
      'erb_TARGET_ACCEPTANCE_TEST',
   ],

   'includes' : ['erb-src.gypi'],

   'sources': [
      # headers
      'detail/ModuleBoard.h',

      # sources
      '../../src/detail/ModuleBoard.cpp',
   ],

   'include_dirs': [
      '..',
   ],

   'direct_dependent_settings': {
      'defines': [
         'erb_TARGET_ACCEPTANCE_TEST',
      ],

      'include_dirs': [
         '..',
      ],
   },
}
