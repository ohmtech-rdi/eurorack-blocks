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


// 'erb_MONITOR' activates the monitor: an RTT link over the debug probe
// (SWD) with cycle counting and profiling primitives, used by the
// 'erbb monitor' command for live measurement of a running module.
// Activate by adding:
//
// define erb_MONITOR=1
//
// to your erbb module definition

#if !defined (erb_MONITOR)
   #define erb_MONITOR 0
#endif


// 'erb_MONITOR_FIFO_SIZE' sizes the SDRAM fifo that buffers the monitor
// down-channel while a stream handler stalls (SD card access, display
// redraws...). The default, about one second of ST-Link throughput, suits
// handlers that never block for long; raise it when a stream handler can
// stall the idle loop for several seconds, or the debug probe drops bytes
// and streams fail their CRC check.

#if !defined (erb_MONITOR_FIFO_SIZE)
   #define erb_MONITOR_FIFO_SIZE 262144
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
