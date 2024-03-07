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
            'scripts/erbb',
            'scripts/erbb_complete.py',

            # completion
            'completion/__init__.py',
            'completion/tests/test_completion.py',

            # erbb
            'erbb/__init__.py',
            'erbb/adapter.py',
            'erbb/analyser.py',
            'erbb/ast.py',
            'erbb/error.py',
            'erbb/grammar.py',
            'erbb/parser.py',
            'erbb/visitor.py',

            # tests
            'erbb/tests/mock.py',
            'erbb/tests/test_parser.py',

            # generators/action
            'erbb/generators/action/action_daisy_template.py',
            'erbb/generators/action/action_data_template.py',
            'erbb/generators/action/action_faust_template.py',
            'erbb/generators/action/action_fuzz_template.py',
            'erbb/generators/action/action_max_template.py',
            'erbb/generators/action/action_perf_template.py',
            'erbb/generators/action/action_ui_template.py',
            'erbb/generators/action/action_vcvrack_install_template.py',
            'erbb/generators/action/action_vcvrack_template.py',
            'erbb/generators/action/action.py',

            # generators/init
            'erbb/generators/init/project_template.cpp',
            'erbb/generators/init/project_template.erbb',
            'erbb/generators/init/project_template.erbui',
            'erbb/generators/init/project_template.h',
            'erbb/generators/init/project.py',

            # generators/data
            'erbb/generators/data/code_template.cpp',
            'erbb/generators/data/code_template.h',
            'erbb/generators/data/code.py',

            # generators/max
            'erbb/generators/max/code_template.cpp',
            'erbb/generators/max/code_template.h',
            'erbb/generators/max/code.py',
            'erbb/generators/max/module_max_template.cpp',
            'erbb/generators/max/module_max_template.h',
            'erbb/generators/max/project_template.erbb',
            'erbb/generators/max/project_template.erbui',
            'erbb/generators/max/project_template.maxpat',
            'erbb/generators/max/project.py',

            # generators/faust
            'erbb/generators/faust/code_template.h',
            'erbb/generators/faust/code_template.hpp',
            'erbb/generators/faust/code.py',
            'erbb/generators/faust/project_template.erbb',
            'erbb/generators/faust/project_template.erbui',
            'erbb/generators/faust/project_template.dsp',
            'erbb/generators/faust/project.py',

            # generators/simulator
            'erbb/generators/simulator/Makefile_template',
            'erbb/generators/simulator/make.py',
            'erbb/generators/simulator/xcode.py',
            'erbb/generators/simulator/xcscheme_template',

            # generators/vcvrack
            'erbb/generators/vcvrack/project_template.gyp',
            'erbb/generators/vcvrack/project.py',

            # generators/daisy
            'erbb/generators/daisy/Makefile_template',
            'erbb/generators/daisy/make.py',

            # generators/perf
            'erbb/generators/perf/Makefile_template',
            'erbb/generators/perf/make.py',

            # generators/fuzz
            'erbb/generators/fuzz/Makefile_template',
            'erbb/generators/fuzz/make.py',

            # generators/vscode
            'erbb/generators/vscode/c_cpp_properties_template.json',
            'erbb/generators/vscode/c_cpp_properties.py',
            'erbb/generators/vscode/extensions_template.json',
            'erbb/generators/vscode/extensions.py',
            'erbb/generators/vscode/launch_template.json',
            'erbb/generators/vscode/launch.py',
            'erbb/generators/vscode/tasks_template.json',
            'erbb/generators/vscode/tasks.py',
            'erbb/generators/vscode/workspace_template.json',
            'erbb/generators/vscode/workspace.py',

            # erbui
            'erbui/__init__.py',
            'erbui/adapter.py',
            'erbui/analyser.py',
            'erbui/ast.py',
            'erbui/error.py',
            'erbui/grammar.py',
            'erbui/parser.py',
            'erbui/visitor.py',

            # erbui/analysers
            'erbui/analysers/style.py',

            # generators/daisy
            'erbui/generators/daisy/code_template.cpp',
            'erbui/generators/daisy/code.py',

            # generators/detail
            'erbui/generators/detail/panel.py',

            # generators/kicad
            'erbui/generators/kicad/pcb.py',
            'erbui/generators/kicad/s_expression.py',
            'erbui/generators/kicad/sch.py',

            # generators/front_panel
            'erbui/generators/front_panel/dxf.py',
            'erbui/generators/front_panel/pcb.py',
            'erbui/generators/front_panel/pdf.py',

            # generators/front_pcb
            'erbui/generators/front_pcb/bom.py',
            'erbui/generators/front_pcb/centroid.py',
            'erbui/generators/front_pcb/DiyManual.erbui',
            'erbui/generators/front_pcb/DiyWire.erbui',
            'erbui/generators/front_pcb/fill_zones.py',
            'erbui/generators/front_pcb/generate_gerber.py',
            'erbui/generators/front_pcb/kicad_pcb.py',

            # generators/max
            'erbui/generators/max/code_template.cpp',
            'erbui/generators/max/code.py',

            # generators/faust
            'erbui/generators/faust/code_template.hpp',
            'erbui/generators/faust/code.py',

            # generators/perf
            'erbui/generators/perf/code_template.cpp',
            'erbui/generators/perf/code.py',

            # generators/fuzz
            'erbui/generators/fuzz/code_template.cpp',
            'erbui/generators/fuzz/code.py',

            # generators/tayda
            'erbui/generators/tayda/drill.py',
            'erbui/generators/tayda/drill_template.py',

            # generators/ui
            'erbui/generators/ui/code_template.h',
            'erbui/generators/ui/code.py',

            # generators/vcvrack
            'erbui/generators/vcvrack/code_template.cpp',
            'erbui/generators/vcvrack/code.py',
            'erbui/generators/vcvrack/manifest.py',
            'erbui/generators/vcvrack/panel.py',

            # setup
            'setup/__init__.py',

            # tests
            'erbui/tests/mock.py',
            'erbui/tests/test_analyser.py',
            'erbui/tests/test_generator_kicad.py',
            'erbui/tests/test_parser.py',
            'erbui/tests/test_s_expression.py',
         ],
      },
   ],
}
