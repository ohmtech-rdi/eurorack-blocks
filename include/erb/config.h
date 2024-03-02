/*****************************************************************************

      config.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ CONFIG \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

// 'erb_SDRAM_USE_FLAG' activates the use of SDRAM. If a module doesn't
// actually use SDRAM, turning this flag off allows to save costs when
// the daisy board can be ordered without the SDRAM chip.
// If not defined, it will activate the SDRAM.

#if !defined (erb_SDRAM_USE_FLAG)
   #define erb_SDRAM_USE_FLAG true
#endif


// 'erb_SDRAM_MEM_POOL_SIZE' represents the maximum amount of memory that can
// be used for all combined usages of 'SdramPtr' for an entire module.
// If not defined, it will take the entire Daisy SDRAM memory, so 64MB.

#if !defined (erb_SDRAM_MEM_POOL_SIZE)
   #define erb_SDRAM_MEM_POOL_SIZE 0x4000000
#endif


// 'erb_SRAM_MEM_POOL_SIZE' represents the maximum amount of memory that can
// be used for all combined usages of 'SramPtr' for an entire module.
// Increase by adding:
//
// define erb_SRAM_MEM_POOL_SIZE=xxx
//
// to your erbb module definition

#if !defined (erb_SRAM_MEM_POOL_SIZE)
   #define erb_SRAM_MEM_POOL_SIZE 0x10
#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
