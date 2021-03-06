/*****************************************************************************

      VcvSwitch.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvSwitch.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvSwitch::VcvSwitch (VcvModule & module, const VcvPin & /* pin_0 */, const VcvPin & /* pin_1 */)
:  VcvParamBase (module)
{
}



/*
==============================================================================
Name : operator Position
==============================================================================
*/

VcvSwitch::operator Position () const
{
   return _position;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  VcvSwitch::impl_notify_audio_buffer_start ()
{
   VcvParamBase::impl_notify_audio_buffer_start ();

   float val = _position_mult * norm_val ();

   if (val < 0.25f)
   {
      _position = Position::Out0;
   }
   else if (val > 0.75f)
   {
      _position = Position::Out1;
   }
   else
   {
      _position = Position::Center;
   }
}



/*
==============================================================================
Name : set_3_position
==============================================================================
*/

void  VcvSwitch::set_3_position ()
{
   _position_mult = 0.5f;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
