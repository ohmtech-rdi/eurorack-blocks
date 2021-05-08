/*****************************************************************************

      BoardBase.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/daisy/DaisyPins.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS

#include <array>
#include <functional>
#include <initializer_list>



namespace erb
{
namespace daisy
{



class BoardBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardBase ();
   virtual        ~BoardBase () = default;

   template <typename F>
   void           run (F && f);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   struct AdcChannel
   {
      AdcPin      pin;
      size_t      nbr_channels = 1;
      Pin         pin_a = PinNC;
      Pin         pin_b = PinNC;
      Pin         pin_c = PinNC;
   };

   enum { NBR_AUDIO_CHANNELS = 2 };

   virtual void   do_notify_audio_buffer_start () = 0;
   virtual void   do_notify_audio_buffer_end () = 0;

   template <size_t MaxNbrChannels>
   std::array <uint16_t *, MaxNbrChannels>
                  do_init_adc_channels (std::initializer_list <AdcChannel> adc_channels);

   std::array <const Buffer *, NBR_AUDIO_CHANNELS>
                  do_init_audio_in ();
   std::array <Buffer *, NBR_AUDIO_CHANNELS>
                  do_init_audio_out ();



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   using BufferInputs = std::array <Buffer, NBR_AUDIO_CHANNELS>;
   using BufferOutputs = std::array <Buffer, NBR_AUDIO_CHANNELS>;

   void           enable_fz ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   void           process_inputs (BufferInputs & buffer_inputs, float ** in);
   void           process_outputs (float ** out, BufferOutputs & buffer_outputs);

   static BoardBase *
                  _this_ptr;

   daisy::DaisySeed
                  _seed;
   std::function <void ()>
                  _buffer_callback;

   uint64_t       _clock_spl = 0ull;
   uint64_t       _clock_ms = 0ull;

   BufferInputs   _buffer_inputs;
   BufferOutputs  _buffer_outputs;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardBase (const BoardBase & rhs) = delete;
                  BoardBase (BoardBase && rhs) = delete;
   BoardBase &    operator = (const BoardBase & rhs) = delete;
   BoardBase &    operator = (BoardBase && rhs) = delete;
   bool           operator == (const BoardBase & rhs) const = delete;
   bool           operator != (const BoardBase & rhs) const = delete;



}; // class BoardBase



}  // namespace daisy
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
