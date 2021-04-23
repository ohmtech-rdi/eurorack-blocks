##############################################################################
#
#     build-system.gyp
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'targets' : [
      {
         'target_name': 'build-system',
         'type': 'none',

         'sources': [
            'cover.py',
            'erbuic.py',
            'test.py',

            # erbb
            'erbb/__init__.py',
            'erbb/generate_vcvrack.py',

            # erbui
            'erbui/__init__.py',
            'erbui/adapter.py',
            'erbui/analyser.py',
            'erbui/ast.py',
            'erbui/error.py',
            'erbui/grammar.py',
            'erbui/parser.py',
            'erbui/visitor.py',

            # generators/daisy
            'erbui/generators/daisy/code_template.cpp',
            'erbui/generators/daisy/code.py',

            # generators/detail
            'erbui/generators/detail/panel.py',

            # generators/front_panel
            'erbui/generators/front_panel/milling.py',
            'erbui/generators/front_panel/printing.py',

            # generators/vcvrack
            'erbui/generators/vcvrack/code_template.cpp',
            'erbui/generators/vcvrack/code.py',
            'erbui/generators/vcvrack/deploy_template.py',
            'erbui/generators/vcvrack/deploy.py',
            'erbui/generators/vcvrack/manifest.py',
            'erbui/generators/vcvrack/panel.py',

            # tests
            'erbui/tests/mock.py',
            'erbui/tests/test_generators.py',
            'erbui/tests/test_parser.py',
         ],
      },
   ],
}
