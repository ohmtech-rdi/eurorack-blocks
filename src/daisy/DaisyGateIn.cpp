/*****************************************************************************

      DaisyGateIn.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyGateIn.h"

#include "erb/daisy/DaisyModule.h"
#include "erb/def.h"

#include "per/gpio.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyGateIn::DaisyGateIn (DaisyModule & module, const Pin & pin, Mode mode)
:  _gpio (to_gpio (pin))
,  _mode (mode)
{
   module.add (*this);
}



/*
==============================================================================
Name : set_mode
==============================================================================
*/

void  DaisyGateIn::set_mode (Mode mode)
{
   _mode = mode;
}



/*
==============================================================================
Name : operator bool
==============================================================================
*/

DaisyGateIn::operator bool () const
{
   switch (_mode)
   {
   case Mode::Trigger:
      return _current && !_previous;

   case Mode::Gate:
      return _current;

#if erb_GNUC_SWITCH_COVERAGE_FIX
   default:
      return false;
#endif
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyGateIn::DaisyGateIn (const Pin & pin, Mode mode)
:  _gpio (to_gpio (pin))
,  _mode (mode)
{
}



/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  DaisyGateIn::impl_notify_audio_buffer_start ()
{
   _previous = _current;

   _current = ! dsy_gpio_read (&_gpio);
}



/*
==============================================================================
Name : to_gpio
==============================================================================
*/

dsy_gpio DaisyGateIn::to_gpio (const Pin & pin)
{
   dsy_gpio gpio;
   gpio.pin = pin;
   gpio.mode = DSY_GPIO_MODE_INPUT;
   gpio.pull = DSY_GPIO_NOPULL;

   dsy_gpio_init (&gpio);

   return gpio;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
