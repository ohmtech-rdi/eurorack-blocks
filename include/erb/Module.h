/*****************************************************************************

      Module.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AdcChannels.h"
#include "erb/Constants.h"
#include "erb/ModuleListeners.h"
#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS

#include <array>
#include <functional>



namespace erb
{



class AnalogControlBase;
class Multiplexer;

class Module
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Frame = std::array <float, buffer_size>;
   using Buffer = std::array <Frame, onboard_codec_nbr_channel>;

                  Module ();
   virtual        ~Module () = default;

   template <typename F>
   void           run (F && f);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   uint64_t       now_ms ();
   void           add (AnalogControlBase & control, const Pin & pin);
   void           add (Multiplexer & multiplexer, const Pin & pin, const MultiplexerAddressPins & address_pins);
   void           add (ModuleListener & listener);

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

   static Module *
                  _this_ptr;

   daisy::DaisySeed
                  _seed;
   std::function <void ()>
                  _buffer_callback;

   uint64_t       _now_spl = 0ull;
   uint64_t       _now_ms = 0ull;

   Buffer         _onboard_codec_buffer_input;
   Buffer         _onboard_codec_buffer_output;

   AdcChannels    _adc_channels;
   ModuleListeners
                  _listeners;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Module (const Module & rhs) = delete;
                  Module (Module && rhs) = delete;
   Module &       operator = (const Module & rhs) = delete;
   Module &       operator = (Module && rhs) = delete;
   bool           operator == (const Module & rhs) const = delete;
   bool           operator != (const Module & rhs) const = delete;



}; // class Module



}  // namespace erb



#include "erb/Module.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
