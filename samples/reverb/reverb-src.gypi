##############################################################################
#
#     reverb-src.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'includes': [
      '../dsp/dsp.gypi',
   ],

   # See README.md for 'erb_SDRAM_MEM_POOL_*' options
   
   'defines': [
      #'erb_SDRAM_MEM_POOL_SIZE_SIMULATOR_CHECK=0',
      #'erb_SDRAM_MEM_POOL_SIZE=67098864',
   ],

   'sources': [
      'Reverb.cpp',
      'Reverb.h',
      'ReverbDsp.cpp',
      'ReverbDsp.h',
      'Reverb.erbui',
   ],
}
