##############################################################################
#
#     gen_dsp.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'defines': [
      'GENLIB_USE_FLOAT32',
      'GENLIB_NO_JSON',
      'GEN_NO_STDLIB',
   ],

   'sources': [
      'genlib_common_win.h',
      'genlib_common.h',
      'genlib_exportfunctions.h',
      'genlib_ops.h',
      'genlib_platform.h',
      'genlib.cpp',
      'genlib.h',
   ],

   'include_dirs': [
      '.',
   ],
}
