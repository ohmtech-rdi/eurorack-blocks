##############################################################################
#
#     project_daisy.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



# !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



{
   'includes': [
      '%PATH_ROOT%/eurorack-blocks.gypi',
   ],

   'target_defaults': {
      'defines': [ %boot.option% ],
   },

   'targets' : [
      {
         'target_name': '%module.name%',
         'type': 'executable',

         'includes': [
            '%PATH_ROOT%/include/erb/erb-daisy.gypi',
%           target_includes%
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

         'ldflags': [ '-T%module.section%' ],
      },
   ],
}
