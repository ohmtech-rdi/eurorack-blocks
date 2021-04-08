/*****************************************************************************

      GateOut.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/GateOut.h"

#include "erb/Module.h"
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

GateOut::GateOut (Module & module, const Pin & pin)
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

void  GateOut::on ()
{
   _mode = Mode::Constant;

   _current = true;
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  GateOut::off ()
{
   _mode = Mode::Constant;

   _current = false;
}



/*
==============================================================================
Name : trigger
==============================================================================
*/

void  GateOut::trigger (std::chrono::milliseconds duration)
{
   _mode = Mode::Pulse;
   _start = _module.now_ms ();
   _duration = uint32_t (duration.count ());

   _current = true;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  GateOut::impl_notify_audio_buffer_start ()
{
   if (_mode == Mode::Pulse)
   {
      auto now = _module.now_ms ();
      auto elapsed = now - _start;
      _current = elapsed < _duration;
   }

   dsy_gpio_write (&_gpio, _current);
}



/*
==============================================================================
Name : to_gpio
==============================================================================
*/

dsy_gpio GateOut::to_gpio (const Pin & pin)
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
