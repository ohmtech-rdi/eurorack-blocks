/*****************************************************************************

      Multiplexer.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Multiplexer.h"

#include "erb/Module.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Multiplexer::Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a)
{
   module.add (*this, pin.pin, MultiplexerAddressPins { pin_a, PinNC, PinNC });
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

Multiplexer::Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b)
{
   module.add (*this, pin.pin, { pin_a, pin_b, PinNC });
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

Multiplexer::Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b, const Pin & pin_c)
{
   module.add (*this, pin.pin, { pin_a, pin_b, pin_c });
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  Multiplexer::impl_bind (AnalogControlBase & control, size_t idx)
{
   _controls [idx] = &control;
}



/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  Multiplexer::impl_bind (uint16_t * val_u16_ptr)
{
   for (size_t i = 0 ; i < _controls.size () ; ++i)
   {
      auto * control_ptr = _controls [i];

      if (control_ptr != nullptr)
      {
         control_ptr->impl_bind (&val_u16_ptr [i]);
      }
   }
}



/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  Multiplexer::impl_notify_audio_buffer_start ()
{
   for (auto * control_ptr : _controls)
   {
      if (control_ptr != nullptr)
      {
         control_ptr->impl_notify_audio_buffer_start ();
      }
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
