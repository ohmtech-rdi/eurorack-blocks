##############################################################################
#
#     erb-daisy.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'type': 'executable',

   'dependencies': [ 'libdaisy' ],

   'defines': [
      'erb_TARGET_DAISY',
   ],

   'includes' : ['erb-src.gypi'],

   'sources': [
      'daisy/AdcDaisy.h',
      'daisy/AdcDaisy.hpp',
      'daisy/BoardDaisyField.h',
      'daisy/BoardDaisyField.hpp',
      'daisy/BoardDaisyMicropatch.h',
      'daisy/BoardDaisyMicropatch.hpp',
      'daisy/BoardDaisySeed.h',
      'daisy/BoardDaisySeed.hpp',
      'daisy/BoardKivu12.h',
      'daisy/BoardKivu12.hpp',
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

      '../../src/daisy/BoardDaisyField.cpp',
      '../../src/daisy/BoardDaisyMicropatch.cpp',
      '../../src/daisy/BoardDaisySeed.cpp',
      '../../src/daisy/BoardKivu12.cpp',
      '../../src/daisy/SubmoduleDaisyPatchSm.cpp',
      '../../src/daisy/SubmoduleDaisySeed.cpp',

      '<!(echo artifacts/main_daisy.cpp)',
      '<!(echo artifacts/plugin_generated_data.cpp)',
   ],

   'include_dirs': [
      '..',
   ],

   'export_dependent_settings': [
      'libdaisy',
   ],
}
