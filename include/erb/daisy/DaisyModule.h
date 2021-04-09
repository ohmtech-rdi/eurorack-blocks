/*****************************************************************************

      DaisyModule.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyAdcChannels.h"
#include "erb/daisy/DaisyConstants.h"
#include "erb/daisy/DaisyModuleListeners.h"
#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS

#include <array>
#include <functional>



namespace erb
{



class DaisyAnalogControlBase;
class DaisyMultiplexer;

class DaisyModule
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Frame = std::array <float, buffer_size>;
   using Buffer = std::array <Frame, onboard_codec_nbr_channel>;

                  DaisyModule ();
   virtual        ~DaisyModule () = default;

   template <typename F>
   void           run (F && f);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   uint64_t       now_ms ();
   void           add (DaisyAnalogControlBase & control, const Pin & pin);
   void           add (DaisyMultiplexer & multiplexer, const Pin & pin, const DaisyMultiplexerAddressPins & address_pins);
   void           add (DaisyModuleListener & listener);

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

   static DaisyModule *
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
   DaisyModuleListeners
                  _listeners;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyModule (const DaisyModule & rhs) = delete;
                  DaisyModule (DaisyModule && rhs) = delete;
   DaisyModule &  operator = (const DaisyModule & rhs) = delete;
   DaisyModule &  operator = (DaisyModule && rhs) = delete;
   bool           operator == (const DaisyModule & rhs) const = delete;
   bool           operator != (const DaisyModule & rhs) const = delete;



}; // class DaisyModule



}  // namespace erb



#include "erb/daisy/DaisyModule.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
