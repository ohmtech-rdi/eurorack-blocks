/*****************************************************************************

      DaisyAnalogControlBase.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyAnalogControlBase.h"

#include "erb/daisy/DaisyModule.h"
#include "erb/daisy/DaisyMultiplexer.h"

namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyAnalogControlBase::DaisyAnalogControlBase (DaisyModule & module, const AdcPin & pin)
{
   module.add (*this, pin.pin);
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyAnalogControlBase::DaisyAnalogControlBase (DaisyMultiplexer & multiplexer, const MultiplexerPin & pin)
{
   multiplexer.impl_bind (*this, pin.pin);
}



/*
==============================================================================
Name : norm_val
==============================================================================
*/

float DaisyAnalogControlBase::norm_val () const
{
   return _norm_val;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_bind
==============================================================================
*/

void  DaisyAnalogControlBase::impl_bind (uint16_t * val_u16_ptr)
{
   _val_u16_ptr = val_u16_ptr;
}



/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  DaisyAnalogControlBase::impl_notify_audio_buffer_start ()
{
   constexpr float u16_to_norm = 1.f / 65535.f;
   _norm_val = 1.f - float (*_val_u16_ptr) * u16_to_norm;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
