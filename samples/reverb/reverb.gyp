##############################################################################
#
#     reverb.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'variables': {
      'erbb_flash_lds': '../../../../../submodules/libDaisy/core/STM32H750IB_flash.lds',
   },

   'includes': [
      '../../eurorack-blocks.gypi',
   ],

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
         'type': 'executable',

         'dependencies': [ 'reverb', 'erb-daisy' ],
      },

      {
         'target_name': 'reverb-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'reverb', 'erb-vcvrack' ],
      },
   ],
}
