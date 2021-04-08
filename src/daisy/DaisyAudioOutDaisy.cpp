/*****************************************************************************

      DaisyAudioOutDaisy.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyAudioOutDaisy.h"

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

DaisyAudioOutDaisy::DaisyAudioOutDaisy (DaisyModule & module, AudioOutDaisyPin pin)
:  _module (module)
,  _channel (pin.pin)
{
   module.add (*this);
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

DaisyAudioOutDaisy &   DaisyAudioOutDaisy::operator = (const Buffer & buffer)
{
   _buffer = buffer;

   return *this;
}



/*
==============================================================================
Name : size
==============================================================================
*/

size_t   DaisyAudioOutDaisy::size () const
{
   return _buffer.size ();
}



/*
==============================================================================
Name : operator []
==============================================================================
*/

float &  DaisyAudioOutDaisy::operator [] (size_t index)
{
   return _buffer [index];
}



/*
==============================================================================
Name : fill
==============================================================================
*/

void  DaisyAudioOutDaisy::fill (float val)
{
   _buffer.fill (val);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  DaisyAudioOutDaisy::impl_notify_audio_buffer_start ()
{
   // nothing
}



/*
==============================================================================
Name : impl_notify_audio_buffer_end
==============================================================================
*/

void  DaisyAudioOutDaisy::impl_notify_audio_buffer_end ()
{
   auto & buffer = _module.impl_onboard_codec_buffer_output ();

   buffer [_channel] = _buffer;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
