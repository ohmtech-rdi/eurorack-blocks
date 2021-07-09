##############################################################################
#
#     sampler.gyp
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
         'target_name': 'sampler',
         'type': 'none',

         'direct_dependent_settings': {
            'sources': [
               'Sampler.cpp',
               'Sampler.h',
               'SamplerDsp.cpp',
               'SamplerDsp.h',
               'Sampler.erbui',
            ],

            'include_dirs': [
               '..',
            ],
         },
      },

      {
         'target_name': 'sampler-daisy',
         'type': 'executable',

         'dependencies': [ 'sampler', 'erb-daisy' ],
      },

      {
         'target_name': 'sampler-vcvrack',
         'type': 'shared_library',

         'dependencies': [ 'sampler', 'erb-vcvrack' ],
      },
   ],
}
