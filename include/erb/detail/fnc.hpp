/*****************************************************************************

      fnc.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"
#include "erb/detail/Sram.h"
#include "erb/detail/Sdram.h"

#include <algorithm>



namespace erb
{



/*
==============================================================================
Name : allocate_bytes_auto
==============================================================================
*/

void *   allocate_bytes_auto (size_t size)
{
   void * ptr = Sram::allocate_bytes_nullptr_on_error (size);

   if (ptr == nullptr)
   {
      ptr = Sdram::allocate_bytes_nullptr_on_error (size);
   }

   if (ptr == nullptr)
   {
#if defined (erb_TARGET_DAISY)
      asm ("bkpt 255");
#elif (erb_RAM_MEM_POOL_SIZE_SIMULATOR_CHECK)
      // Either:
      // - The module is using too much memory,
      // - Multiple modules are being debugged (check erb/config.h for workaround)
      throw std::bad_alloc ();
#endif
   }

   return ptr;
}



/*
==============================================================================
Name : scale
==============================================================================
*/

template <size_t NbrChannels>
void  scale (std::array <Buffer, NbrChannels> & buffers, float * const * in, float gain)
{
   for (size_t i = 0 ; i < buffers.size () ; ++i)
   {
      auto & buffer = buffers [i];
      const auto & in_arr = in [i];

      for (size_t j = 0 ; j < erb_BUFFER_SIZE ; ++j)
      {
         buffer [j] = gain * in_arr [j];
      }
   }
}



/*
==============================================================================
Name : scale
==============================================================================
*/

template <size_t NbrChannels>
void  scale (float ** out, const std::array <Buffer, NbrChannels> & buffers, float gain)
{
   for (size_t i = 0 ; i < buffers.size () ; ++i)
   {
      auto & out_arr = out [i];
      const auto & buffer = buffers [i];

      for (size_t j = 0 ; j < erb_BUFFER_SIZE ; ++j)
      {
         out_arr [j] = gain * buffer [j];
      }
   }
}



/*
==============================================================================
Name : scale
==============================================================================
*/

void  scale (Buffer & out, const float * in, float gain)
{
   for (size_t i = 0 ; i < out.size () ; ++i)
   {
      out [i] = gain * in [i];
   }
}



/*
==============================================================================
Name : scale
==============================================================================
*/

void  scale (float * out, const Buffer & in, float gain)
{
   for (size_t i = 0 ; i < in.size () ; ++i)
   {
      out [i] = gain * in [i];
   }
}



/*
==============================================================================
Name : norm_to_u12
==============================================================================
*/

uint16_t norm_to_u12 (float norm_val)
{
   return uint16_t (std::clamp (norm_val, 0.f, 1.f) * 4095.f);
}



/*
==============================================================================
Name : norm_to_u16
==============================================================================
*/

uint16_t norm_to_u16 (float norm_val)
{
   return uint16_t (std::clamp (norm_val, 0.f, 1.f) * 65535.f);
}



/*
==============================================================================
Name : to_float_norm
==============================================================================
*/

float to_float_norm (uint16_t val)
{
   constexpr float scale = 1.f / 65535.f;
   return float (val) * scale;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
