/*****************************************************************************

      DaisyLed.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyLed.h"

#include "erb/daisy/DaisyModule.h"
#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyLed::DaisyLed (DaisyModule & module, const Pin & pin)
:  _module (module)
,  _gpio (to_gpio (pin))
{
   _module.add (*this);
}



/*
==============================================================================
Name : set_brightness
==============================================================================
*/

void  DaisyLed::set_brightness (float perceptual_brightness)
{
   _brightness = perceptual_brightness;
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  DaisyLed::on (bool state)
{
   _animation.set (state ? 1.f : 0.f);
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  DaisyLed::off ()
{
   _animation.set (0.f);
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  DaisyLed::pulse (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse (
      _module.now_ms (), duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

void  DaisyLed::pulse_twice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_twice (
      _module.now_ms (), duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

void  DaisyLed::pulse_thrice (float brightness, std::chrono::milliseconds duration, TransitionFunction transition_function)
{
   _animation.pulse_thrice (
      _module.now_ms (), duration, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  DaisyLed::blink (float brightness, std::chrono::milliseconds period, TransitionFunction transition_function)
{
   _animation.blink (
      _module.now_ms (), period, transition_function,
      brightness, 0.f
   );
}



/*
==============================================================================
Name : animation
==============================================================================
*/

Animation <float, 8> &  DaisyLed::animation ()
{
   return _animation;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  DaisyLed::impl_notify_audio_buffer_start ()
{
   float value_per = _animation.get (_module.now_ms ()) * _brightness;
   float value_lin = value_per * value_per * value_per;

   _pwm_active = size_t (std::lround (value_lin * float (_pwm_period)));

   uint8_t bit = _pwm_cur < _pwm_active;

   dsy_gpio_write (&_gpio, bit);

   ++_pwm_cur;
   if (_pwm_cur >= _pwm_period) _pwm_cur = 0;
}



/*
==============================================================================
Name : to_gpio
==============================================================================
*/

dsy_gpio DaisyLed::to_gpio (const Pin & pin)
{
   dsy_gpio gpio;
   gpio.pin = pin;
   gpio.mode = DSY_GPIO_MODE_OUTPUT_PP;

   dsy_gpio_init (&gpio);

   return gpio;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
