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
      'rig/BoardGeneric.h',
      'rig/BoardGeneric.hpp',

      # sources
      '../../src/detail/ModuleBoard.cpp',
      '../../src/rig/BoardGeneric.cpp',
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
