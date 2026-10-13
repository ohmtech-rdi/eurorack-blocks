      {
         'target_name': '%acceptance.name%',
         'type': 'executable',

         'includes': [
            '%PATH_ROOT%/include/erb/erb-rig.gypi',
         ],

         'defines': [
%           defines.entities%
%           test.defines%
         ],

         'include_dirs': [
            '.',
%           include_dirs%
%           bases.entities%
         ],

         'sources': [
%           sources.entities%
            'artifacts/acceptance_glue.cpp',
            'artifacts/acceptance_glue.h',
%           extra_sources%
%           acceptance.sources%
         ],

         'actions': [
%           target_actions%
         ],
      },
