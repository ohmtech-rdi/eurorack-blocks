/*****************************************************************************

      RttProtocol.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include <atomic>
#include <span>

#include <cstddef>
#include <cstdint>



namespace erb
{



class RttProtocol
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using CommandHandler = void (*) (void * ctx, std::span <const std::uint8_t> payload);
   using StreamHandler = void (*) (void * ctx, std::size_t payload_size);

   static constexpr std::size_t MaxPayloadSize = 128;

   static RttProtocol &
                  use ();

   static inline constexpr std::uint32_t
                  fourcc (const char str_0 [5]);

   void           init ();
   bool           register_command (std::uint32_t cmd, void * ctx, CommandHandler handler);
   bool           register_stream (std::uint32_t cmd, void * ctx, StreamHandler handler);

   void           idle ();
   void           isr_pump ();

   // valid inside a StreamHandler only
   std::size_t    stream_read (void * ptr, std::size_t size);
   std::size_t    stream_read_raw (void * ptr, std::size_t size);
   std::size_t    stream_consumed () const;
   void           stream_crc_reset ();
   std::uint32_t  stream_crc ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  RttProtocol () = default;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   static constexpr std::size_t MaxNbrEntries = 24;

   // sized so the fifo absorbs stream handler stalls without the debug
   // probe ever finding the 4 KB RTT ring full, which would silently drop
   // bytes (see erb_MONITOR_FIFO_SIZE in config.h)
   static constexpr std::size_t FifoSize = erb_MONITOR_FIFO_SIZE;

   enum class Kind { None, Command, Stream };

   struct Entry
   {
      std::uint32_t  cmd = 0;
      Kind           kind = Kind::None;
      CommandHandler command_handler = nullptr;
      StreamHandler  stream_handler = nullptr;
      void *         ctx = nullptr;
   };

   struct Header
   {
      std::uint32_t  payload_size;
      std::uint32_t  cmd;
   };

   static void    command_ping (void * ctx, std::span <const std::uint8_t> payload);
   static void    stream_sink (void * ctx, std::size_t payload_size);

   void           check_stall ();
   void           process_chunk (const std::uint8_t * data, std::size_t size);
   std::size_t    process_header (const std::uint8_t * data, std::size_t size, std::size_t pos);
   std::size_t    process_payload (const std::uint8_t * data, std::size_t size, std::size_t pos);
   std::size_t    dispatch (const std::uint8_t * data, std::size_t size, std::size_t pos);
   std::size_t    process_stream (Entry & entry, const std::uint8_t * data, std::size_t size, std::size_t pos);

   Entry *        find (std::uint32_t cmd);
   void           finish ();
   std::size_t    pull_raw (void * ptr, std::size_t size);
   std::size_t    read_source (void * ptr, std::size_t size);
   void           crc_update (const std::uint8_t * data, std::size_t size);

   Entry          _entries [MaxNbrEntries];

   Header         _header = {};
   std::size_t    _header_pos = 0;
   std::size_t    _payload_pos = 0;
   std::uint32_t  _last_rx_tick = 0;

   std::uint8_t   _payload [MaxPayloadSize] = {};

   // bytes of the current chunk not yet consumed by the box state machine,
   // handed to the synchronous stream ahead of the ring
   const std::uint8_t *
                  _pending_ptr = nullptr;
   std::size_t    _pending_len = 0;

   std::uint32_t  _crc = 0;

   std::atomic <bool>
                  _stream_active = false;
   std::uint8_t * _fifo = nullptr;
   std::atomic <std::uint32_t>
                  _fifo_wr = 0;
   std::atomic <std::uint32_t>
                  _fifo_rd = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  RttProtocol (const RttProtocol & rhs) = delete;
                  RttProtocol (RttProtocol && rhs) = delete;
   RttProtocol &  operator = (const RttProtocol & rhs) = delete;
   RttProtocol &  operator = (RttProtocol && rhs) = delete;
};



}  // namespace erb



#include "erb/RttProtocol.hpp"

#endif   // erb_MONITOR && erb_TARGET_DAISY
