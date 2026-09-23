      {
         'target_name': '%test.name%',
         'type': 'executable',

         'defines': [
%           defines.entities%
%           test.defines%
         ],

         'include_dirs': [
            '.',
%           bases.entities%
         ],

         'sources': [
%           test.sources%
         ],
      },
