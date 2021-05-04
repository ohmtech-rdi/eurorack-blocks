/*****************************************************************************

      DaisyLed.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Animation.h"
#include "erb/daisy/DaisyModuleListener.h"
#include "erb/daisy/DaisyPins.h"

#include "per/gpio.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class DaisyModule;

class DaisyLed
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  DaisyLed (DaisyModule & module, const Pin & pin);
   virtual        ~DaisyLed () = default;

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

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   static dsy_gpio
                  to_gpio (const Pin & pin);

   DaisyModule &  _module;
   const dsy_gpio _gpio;

   float          _brightness = 1.f;
   Animation <float, 8>
                  _animation;

   static constexpr size_t
                  _pwm_period = 32;
   size_t         _pwm_active = 0;
   size_t         _pwm_cur = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyLed () = delete;
                  DaisyLed (const DaisyLed & rhs) = delete;
                  DaisyLed (DaisyLed && rhs) = delete;
   DaisyLed &     operator = (const DaisyLed & rhs) = delete;
   DaisyLed &     operator = (DaisyLed && rhs) = delete;
   bool           operator == (const DaisyLed & rhs) const = delete;
   bool           operator != (const DaisyLed & rhs) const = delete;



}; // class DaisyLed



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
