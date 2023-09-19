##############################################################################
#
#     erb-daisy.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'dependencies': [ 'libdaisy' ],

   'defines': [
      'erb_TARGET_DAISY',
   ],

   'includes' : ['erb-src.gypi'],

   'sources': [
      'daisy/AdcDaisy.h',
      'daisy/AdcDaisy.hpp',
      'daisy/DacDaisy.h',
      'daisy/DacDaisy.hpp',
      'daisy/GpioInputDaisy.h',
      'daisy/GpioInputDaisy.hpp',
      'daisy/GpioOutputDaisy.h',
      'daisy/GpioOutputDaisy.hpp',
      'daisy/SubmoduleDaisyPatchSm.h',
      'daisy/SubmoduleDaisyPatchSm.hpp',
      'daisy/SubmoduleDaisySeed.h',
      'daisy/SubmoduleDaisySeed.hpp',
      'daisy/SubmoduleDaisySeed2Dfm.h',

      '../../src/daisy/SubmoduleDaisyPatchSm.cpp',
      '../../src/daisy/SubmoduleDaisySeed.cpp',
   ],

   'include_dirs': [
      '..',
   ],

   'export_dependent_settings': [
      'libdaisy',
   ],

   'direct_dependent_settings': {
      'defines': [
         'erb_TARGET_DAISY',
      ],

      'include_dirs': [
         '..',
      ],
   },
}
