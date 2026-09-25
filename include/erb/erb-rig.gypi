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
      'rig/Context.h',
      'rig/Context.hpp',
      'rig/Measurement.h',
      'rig/Measurement.hpp',
      'rig/Peak.h',
      'rig/Peak.hpp',
      'rig/Probe.h',
      'rig/Probe.hpp',
      'rig/Screen.h',
      'rig/Screen.hpp',
      'rig/SdCard.h',
      'rig/SdCard.hpp',
      'rig/SystemClockVirtual.h',
      'rig/SystemClockVirtual.hpp',

      # sources
      '../../src/detail/ModuleBoard.cpp',
      '../../src/rig/BoardGeneric.cpp',
      '../../src/rig/Context.cpp',
      '../../src/rig/Probe.cpp',
      '../../src/rig/Screen.cpp',
      '../../src/rig/ScreenWrite.cpp',
      '../../src/rig/SdCard.cpp',
   ],

   'include_dirs': [
      '..',
      '../../submodules/vcv-rack-sdk/dep/include', # stb
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
