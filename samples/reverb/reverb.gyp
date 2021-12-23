##############################################################################
#
#     reverb.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'includes': [
      '../../eurorack-blocks.gypi',
   ],

   # See README.md for 'erb_SDRAM_MEM_POOL_*' options
   'target_defaults': {
      'defines': [
         #'erb_SDRAM_MEM_POOL_SIZE_SIMULATOR_CHECK=0',
         #'erb_SDRAM_MEM_POOL_SIZE=67098864',
      ],
   },

   'targets' : [
      {
         'target_name': 'reverb',
         'type': 'none',

         'direct_dependent_settings': {
            'sources': [
               'Reverb.cpp',
               'Reverb.h',
               'ReverbDsp.cpp',
               'ReverbDsp.h',
               'Reverb.erbui',

               '../dsp/Filter2Poles.cpp',
               '../dsp/Filter2Poles.h',
               '../dsp/Filter2Poles.hpp',
               '../dsp/GainRamp.cpp',
               '../dsp/GainRamp.h',
               '../dsp/GainRamp.hpp',
               '../dsp/ReverbSc.cpp',
               '../dsp/ReverbSc.h',
            ],

            'include_dirs': [
               '..',
            ],
         },
      },

      {
         'target_name': 'reverb-daisy',

         'dependencies': [ 'reverb', 'erb-daisy' ],
      },

      {
         'target_name': 'reverb-vcvrack',

         'dependencies': [ 'reverb', 'erb-vcvrack' ],
      },
   ],
}
