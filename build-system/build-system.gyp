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
            'erbb/adapter.py',
            'erbb/analyser.py',
            'erbb/ast.py',
            'erbb/error.py',
            'erbb/generate_vcvrack_template.py',
            'erbb/grammar.py',
            'erbb/parser.py',
            'erbb/visitor.py',
            'erbb/vscode/launch.json',
            'erbb/vscode/tasks.json',

            # tests
            'erbb/tests/mock.py',
            'erbb/tests/test_parser.py',

            # generators/vcvrack
            'erbb/generators/vcvrack/project_template.gyp',
            'erbb/generators/vcvrack/project.py',

            # generators/daisy
            'erbb/generators/daisy/project_template.gyp',
            'erbb/generators/daisy/project.py',

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

            # generators/data
            'erbui/generators/data/code_template.cpp',
            'erbui/generators/data/code_template.h',
            'erbui/generators/data/code.py',

            # generators/detail
            'erbui/generators/detail/panel.py',

            # generators/front_panel
            'erbui/generators/front_panel/milling.py',
            'erbui/generators/front_panel/printing.py',

            # generators/front_pcb
            'erbui/generators/front_pcb/fill_zones.py',
            'erbui/generators/front_pcb/generate_gerber.py',
            'erbui/generators/front_pcb/kicad_pcb.py',
            'erbui/generators/front_pcb/s_expression.py',
            'erbui/generators/front_pcb/alpha.9mm/alpha.9mm.kicad_pcb',
            'erbui/generators/front_pcb/board.null/board.null.kicad_pcb',
            'erbui/generators/front_pcb/dailywell.2ms/dailywell.2ms.kicad_pcb',
            'erbui/generators/front_pcb/kivu12/kivu12.kicad_pcb',
            'erbui/generators/front_pcb/led.3mm/led.3mm.kicad_pcb',
            'erbui/generators/front_pcb/led.3mm.bi/led.3mm.bi.kicad_pcb',
            'erbui/generators/front_pcb/thonk.pj398sm/thonk.pj398sm.kicad_pcb',
            'erbui/generators/front_pcb/tl1105/tl1105.kicad_pcb',
            'erbui/generators/front_pcb/songhuei.9mm/songhuei.9mm.kicad_pcb',

            # generators/ui
            'erbui/generators/ui/code_template.h',
            'erbui/generators/ui/code.py',

            # generators/vcvrack
            'erbui/generators/vcvrack/code_template.cpp',
            'erbui/generators/vcvrack/code.py',
            'erbui/generators/vcvrack/deploy_template.py',
            'erbui/generators/vcvrack/deploy.py',
            'erbui/generators/vcvrack/manifest.py',
            'erbui/generators/vcvrack/panel.py',

            # tests
            'erbui/tests/mock.py',
            'erbui/tests/test_analyser.py',
            'erbui/tests/test_generator_front_pcb.py',
            'erbui/tests/test_generators.py',
            'erbui/tests/test_parser.py',
            'erbui/tests/test_s_expression.py',
         ],
      },
   ],
}
