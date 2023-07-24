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
// Increase by adding:
//
// define erb_SRAM_MEM_POOL_SIZE=xxx
//
// to your erbb module definition

#if !defined (erb_SRAM_MEM_POOL_SIZE)
   #define erb_SRAM_MEM_POOL_SIZE 0x10
#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
