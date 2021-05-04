/*****************************************************************************

      VcvLed.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Animation.h"
#include "erb/vcvrack/VcvLightBase.h"
#include "erb/vcvrack/VcvPins.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class VcvModule;

class VcvLed
:  public VcvLightBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VcvLed (VcvModule & module, const VcvPin & pin);
   virtual        ~VcvLed () override = default;

   void           set_brightness (float perceptual_brightness);

   void           on (bool state = true);
   void           off ();
   void           pulse (float brightness = 1.f, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
   void           pulse_twice (float brightness = 1.f, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
   void           pulse_thrice (float brightness = 1.f, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
   void           blink (float brightness = 1.f, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);

   Animation <float, 8> &
                  animation ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   VcvModule &    _module;

   float          _brightness = 1.f;
   Animation <float, 8>
                  _animation;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvLed () = delete;
                  VcvLed (const VcvLed & rhs) = delete;
                  VcvLed (VcvLed && rhs) = delete;
   VcvLed &       operator = (const VcvLed & rhs) = delete;
      VcvLed &    operator = (VcvLed && rhs) = delete;
   bool           operator == (const VcvLed & rhs) const = delete;
   bool           operator != (const VcvLed & rhs) const = delete;



}; // class VcvLed



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
