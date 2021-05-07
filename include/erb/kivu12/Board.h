/*****************************************************************************

      Board.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyAdcChannels.h"
#include "erb/daisy/DaisyConstants.h"
#include "erb/daisy/BoardListeners.h"
#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
// going to be probably "daisy_patch_sm.h" or something
// for now let's use Daisy Seed
#include "daisy_seed.h"
erb_RESTORE_WARNINGS

#include <array>
#include <functional>



namespace erb
{




struct L1 : TagLed {};

// or BoardKivu12?
class Board
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum { NBR_AUDIO_CHANNELS = 2 };
   using Frame = std::array <float, buffer_size>;
   using Buffer = std::array <Frame, NBR_AUDIO_CHANNELS>;

                  Board ();
   virtual        ~Board () = default;

   template <typename F>
   void           run (F && f);

   template <typename Pin, Control>
   void           bind (Control & control);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   uint64_t       now_ms (); // can be a common implementation
   void           add (DaisyAnalogControlBase & control, const Pin & pin);
   void           add (DaisyMultiplexer & multiplexer, const Pin & pin, const DaisyMultiplexerAddressPins & address_pins);
   void           add (BoardListener & listener);

   const Buffer & impl_onboard_codec_buffer_input () const;
   Buffer &       impl_onboard_codec_buffer_output ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   void           enable_fz ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   static Board *
                  _this_ptr;

   daisy::DaisySeed
                  _seed;
   std::function <void ()>
                  _buffer_callback;

   uint64_t       _now_spl = 0ull;
   uint64_t       _now_ms = 0ull;

   Buffer         _onboard_codec_buffer_input;
   Buffer         _onboard_codec_buffer_output;

   DaisyAdcChannels    _adc_channels;
   BoardListeners
                  _listeners;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Board (const Board & rhs) = delete;
                  Board (Board && rhs) = delete;
   Board &  operator = (const Board & rhs) = delete;
   Board &  operator = (Board && rhs) = delete;
   bool           operator == (const Board & rhs) const = delete;
   bool           operator != (const Board & rhs) const = delete;



}; // class Board



}  // namespace erb



#include "erb/daisy/Board.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
