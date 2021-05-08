/*****************************************************************************

      BoardBase.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

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

   virtual void   do_notify_audio_buffer_start () = 0;
   virtual void   do_notify_audio_buffer_end () = 0;

   template <size_t MaxNbrChannels>
   std::array <uint16_t *, MaxNbrChannels>
                  do_init_adc_channels (std::initializer_list <AdcChannel> adc_channels);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum { NBR_AUDIO_CHANNELS = 2 };
   using Frame = std::array <float, erb_BUFFER_SIZE>;
   using Buffer = std::array <Frame, NBR_AUDIO_CHANNELS>;

   void           enable_fz ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   static BoardBase *
                  _this_ptr;

   daisy::DaisySeed
                  _seed;
   std::function <void ()>
                  _buffer_callback;

   uint64_t       _now_spl = 0ull;
   uint64_t       _now_ms = 0ull;

   Buffer         _onboard_codec_buffer_input;
   Buffer         _onboard_codec_buffer_output;

   DaisyAdcChannels
                  _adc_channels;



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
