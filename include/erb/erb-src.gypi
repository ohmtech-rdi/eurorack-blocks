##############################################################################
#
#     erb-src.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'defines': [
      'erb_BUFFER_SIZE=48',
      'erb_SAMPLE_RATE=48014',
   ],

   'all_dependent_settings': {
      'defines': [
         'erb_BUFFER_SIZE=48',
         'erb_SAMPLE_RATE=48014',
      ],
   },

   'sources': [
      'AudioIn.h',
      'AudioIn.hpp',
      'AudioOut.h',
      'AudioOut.hpp',
      'AudioSample.h',
      'Buffer.h',
      'Button.h',
      'Button.hpp',
      'CvIn.h',
      'CvIn.hpp',
      'CvOut.h',
      'CvOut.hpp',
      'Encoder.h',
      'FloatRange.h',
      'GateIn.h',
      'GateIn.hpp',
      'GateOut.h',
      'Led.h',
      'Led.hpp',
      'LedBi.h',
      'LedBi.hpp',
      'LedRgb.h',
      'LedRgb.hpp',
      'PinType.h',
      'Pot.h',
      'Pot.hpp',
      'SdramPtr.h',
      'SdramPtr.hpp',
      'SramPtr.h',
      'SramPtr.hpp',
      'Switch.h',
      'Switch.hpp',
      'config.h',
      'def.h',
      'erb.h',
      'module_init.h',

      'detail/Animation.h',
      'detail/Animation.hpp',
      'detail/Clock.h',
      'detail/Clock.hpp',
      'detail/Debounce.h',
      'detail/DoubleBuffer.h',
      'detail/DoubleBuffer.hpp',
      'detail/GateGenerator.h',
      'detail/GateGenerator.hpp',
      'detail/MonotonicMemoryPool.h',
      'detail/MonotonicMemoryPool.hpp',
      'detail/Sdram.h',
      'detail/Sdram.hpp',
      'detail/Sram.h',
      'detail/Sram.hpp',
      'detail/fnc.h',
      'detail/fnc.hpp',

      '../../src/Button.cpp',
      '../../src/Encoder.cpp',
      '../../src/GateOut.cpp',

      '../../src/detail/Animation.cpp',
      '../../src/detail/Debounce.cpp',
      '../../src/detail/Sdram.cpp',
      '../../src/detail/Sram.cpp',
   ],

   'include_dirs': [
      '..',
   ],
}
