/*****************************************************************************

      BoardDaisySeed.h
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



class BoardDaisySeed
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardDaisySeed ();
   virtual        ~BoardDaisySeed () = default;

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

   using AudioBufferInputs = std::array <Buffer, NBR_AUDIO_CHANNELS>;
   using AudioBufferOutputs = std::array <Buffer, NBR_AUDIO_CHANNELS>;

   virtual void   do_notify_audio_buffer_start () = 0;
   virtual void   do_notify_audio_buffer_end () = 0;

   template <size_t MaxNbrChannels>
   std::array <uint16_t *, MaxNbrChannels>
                  init_adc_channels (std::initializer_list <AdcChannel> adc_channels);

   AudioBufferInputs
                  _audio_buffer_inputs;
   AudioBufferOutputs
                  _audio_buffer_outputs;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           enable_fz ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   void           process_inputs (BufferInputs & buffer_inputs, float ** in);
   void           process_outputs (float ** out, BufferOutputs & buffer_outputs);

   static BoardDaisySeed *
                  _this_ptr;

   daisy::DaisySeed
                  _seed;
   std::function <void ()>
                  _buffer_callback;

   uint64_t       _clock_spl = 0ull;
   uint64_t       _clock_ms = 0ull;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardDaisySeed (const BoardDaisySeed & rhs) = delete;
                  BoardDaisySeed (BoardDaisySeed && rhs) = delete;
   BoardDaisySeed &
                  operator = (const BoardDaisySeed & rhs) = delete;
   BoardDaisySeed &
                  operator = (BoardDaisySeed && rhs) = delete;
   bool           operator == (const BoardDaisySeed & rhs) const = delete;
   bool           operator != (const BoardDaisySeed & rhs) const = delete;



}; // class BoardDaisySeed



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
