/*****************************************************************************

      DaisySwitch.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisySwitch.h"

#include "erb/daisy/DaisyModule.h"

#include "per/gpio.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisySwitch::DaisySwitch (DaisyModule & module, const Pin & pin_0, const Pin & pin_1)
:  _gate_0 (pin_0)
,  _gate_1 (pin_1)
{
   module.add (*this);
}



/*
==============================================================================
Name : operator Position
==============================================================================
*/

DaisySwitch::operator Position () const
{
   return _position;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  DaisySwitch::impl_notify_audio_buffer_start ()
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
