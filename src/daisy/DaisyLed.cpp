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
Name : on
==============================================================================
*/

void  DaisyLed::on (bool state)
{
   _mode = Mode::Constant;

   _current = state;
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  DaisyLed::off ()
{
   _mode = Mode::Constant;

   _current = false;
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  DaisyLed::pulse (std::chrono::milliseconds duration)
{
   _mode = Mode::Pulse;
   _start = _module.now_ms ();
   _duration = uint64_t (duration.count ());

   _current = true;
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  DaisyLed::blink (std::chrono::milliseconds half_period)
{
   _mode = Mode::Blink;
   _start = _module.now_ms ();
   _duration = uint64_t (half_period.count ());

   _current = true;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  DaisyLed::impl_notify_audio_buffer_start ()
{
   if (_mode == Mode::Pulse)
   {
      auto now = _module.now_ms ();
      auto elapsed = now - _start;
      _current = elapsed < _duration;
   }
   else if (_mode == Mode::Blink)
   {
      auto now = _module.now_ms ();
      auto elapsed = now - _start;
      _current = ((elapsed / _duration) % 2) == 1;
   }

   dsy_gpio_write (&_gpio, _current);
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
