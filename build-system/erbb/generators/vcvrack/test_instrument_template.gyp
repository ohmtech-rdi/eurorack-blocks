      {
         'target_name': '%test.name%',
         'type': 'executable',

         'includes': [
            '%PATH_ROOT%/include/erb/erb-instrument.gypi',
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
%           test.sources%
         ],

         'actions': [
%           target_actions%
         ],
      },
