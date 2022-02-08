##############################################################################
#
#     project_vcvrack.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



# !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



{
   'includes': [
      '%PATH_ROOT%/eurorack-blocks.gypi',
   ],

   'targets' : [
      {
         'target_name': '%module.name%',

         'includes': [
            '%PATH_ROOT%/include/erb/erb-vcvrack.gypi',
         ],

         'defines': [
%           defines.entities%
         ],

         'include_dirs': [
            '.',
%           bases.entities%
         ],

         'sources': [
%           sources.entities%
         ],

         'actions': [
%           target_actions%
         ],

         'copies': [
            {
               'destination': '<(PRODUCT_DIR)',
               'files': [
                  '<!(echo artifacts/plugin.json)',
               ],
            },
            {
               'destination': '<(PRODUCT_DIR)/res',
               'files': [
                  '<!(echo artifacts/panel_vcvrack.svg)',
               ],
            },
         ],
      },
   ],
}
