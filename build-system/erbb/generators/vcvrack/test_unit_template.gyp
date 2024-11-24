      {
         'target_name': '%test.name%',
         'type': 'executable',

         'defines': [
%           defines.entities%
         ],

         'include_dirs': [
            '.',
%           bases.entities%
         ],

         'sources': [
%           test.sources%
         ],
      },
