/*****************************************************************************

      GateIn.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/GateIn.h"

#include "erb/Module.h"

#include "per/gpio.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

GateIn::GateIn (Module & module, const dsy_gpio_pin & pin, Mode mode)
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

void  GateIn::set_mode (Mode mode)
{
   _mode = mode;
}



/*
==============================================================================
Name : operator bool
==============================================================================
*/

GateIn::operator bool () const
{
   switch (_mode)
   {
   case Mode::RisingEdge:
      return _current && !_previous;

   case Mode::FallingEdge:
      return _previous && !_current;

   case Mode::Gate:
      return _current;

#if defined (__GNUC__)
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

GateIn::GateIn (const dsy_gpio_pin & pin, Mode mode)
:  _gpio (to_gpio (pin))
,  _mode (mode)
{
}



/*
==============================================================================
Name : impl_process
==============================================================================
*/

void  GateIn::impl_process ()
{
   _previous = _current;

   _current = ! dsy_gpio_read (&_gpio);
}



/*
==============================================================================
Name : to_gpio
==============================================================================
*/

dsy_gpio GateIn::to_gpio (const dsy_gpio_pin & pin)
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
