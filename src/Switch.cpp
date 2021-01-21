/*****************************************************************************

      Switch.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Switch.h"

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

Switch::Switch (Module & module, const Pin & pin_0, const Pin & pin_1)
:  _gate_0 (pin_0, GateIn::Mode::Gate)
,  _gate_1 (pin_1, GateIn::Mode::Gate)
{
   module.add (*this);
}



/*
==============================================================================
Name : operator Position
==============================================================================
*/

Switch::operator Position () const
{
   return _position;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  Switch::impl_notify_audio_buffer_start ()
{
   _gate_0.impl_notify_audio_buffer_start ();
   _gate_1.impl_notify_audio_buffer_start ();

   if (_gate_0)
   {
      _position = Position::Out0;
   }
   else if (_gate_1)
   {
      _position = Position::Out1;
   }
   else
   {
      _position = Position::Center;
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
