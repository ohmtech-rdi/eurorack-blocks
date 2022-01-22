/*****************************************************************************

      config.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ CONFIG \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

// 'erb_SDRAM_MEM_POOL_SIZE' represents the maximum amount of memory that can
// be used for all combined usages of 'SdramPtr' for an entire module.
// If not defined, it will take the entire Daisy SDRAM memory, so 64MB.

#if !defined (erb_SDRAM_MEM_POOL_SIZE)
   #define erb_SDRAM_MEM_POOL_SIZE 0x4000000
#endif


// 'erb_SRAM_MEM_POOL_SIZE' represents the maximum amount of memory that can
// be used for all combined usages of 'SramPtr' for an entire module.
// If not defined, it will take the entire Daisy AXI SRAM memory, so 512KB.

#if !defined (erb_SRAM_MEM_POOL_SIZE)
   #define erb_SRAM_MEM_POOL_SIZE 0x80000
#endif


// 'erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK' will break into the debugger when
// a module consumes more than the available pool size for the choosen memory
// section in the simulator.
// However, this only works when debugging one module, as instantiating
// 2 or more modules will count the used pool size for all modules.
// To workaround this, one might want to disable explicitly this flag to be
// able to test more than one module in the simulator.

#if !defined (erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK)
   #define erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK 1
#endif








/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
