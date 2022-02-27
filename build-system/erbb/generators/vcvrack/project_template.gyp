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
         'type': 'loadable_module',

         'includes': [
            '%PATH_ROOT%/include/erb/erb-vcvrack.gypi',
%           target_includes%
         ],

%        xcode_settings%

         'cflags': [
%           cflags%
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
            'artifacts/plugin_vcvrack.cpp',
         ],

         'actions': [
%           target_actions%
         ],

         'copies': [
            {
               'destination': '<(PRODUCT_DIR)',
               'files': [
                  'artifacts/plugin.json',
               ],
            },
            {
               'destination': '<(PRODUCT_DIR)/res',
               'files': [
                  'artifacts/panel_vcvrack.svg',
               ],
            },
         ],
      },
   ],
}
