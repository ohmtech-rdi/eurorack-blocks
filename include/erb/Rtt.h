/*****************************************************************************

      Rtt.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include <cstddef>
#include <cstdint>



namespace erb
{



class Rtt
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static Rtt &   use ();

   void           init ();
   // same as printf attributes, except we need to skip 'this'
   void           printf (const char * format_0, ...)
                     __attribute__((format (printf, 2, 3)));
   std::size_t    read (void * ptr, std::size_t max_size);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  Rtt () = default;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   static constexpr std::size_t BufferUpSize = 4096;
   static constexpr std::size_t BufferDownSize = 4096;

   struct BufferDesc
   {
      const char *   name_0;
      char *         buffer;
      std::uint32_t  size;
      volatile std::uint32_t
                     wr_off;
      volatile std::uint32_t
                     rd_off;
      std::uint32_t  flags;
   };

   struct ControlBlock
   {
      char           id [16];
      std::int32_t   max_nbr_up;
      std::int32_t   max_nbr_down;
      BufferDesc     up [1];
      BufferDesc     down [1];
   };

   void           write (const char * data, std::size_t size);

   // the probe reads this memory over SWD at fixed addresses: statically
   // placed in the non-cacheable DMA RAM region, not instance state
   static ControlBlock
                  _cb;
   static char    _buffer_up [BufferUpSize];
   static char    _buffer_down [BufferDownSize];



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  Rtt (const Rtt & rhs) = delete;
                  Rtt (Rtt && rhs) = delete;
   Rtt &          operator = (const Rtt & rhs) = delete;
   Rtt &          operator = (Rtt && rhs) = delete;
};



}  // namespace erb

#endif   // erb_MONITOR && erb_TARGET_DAISY
