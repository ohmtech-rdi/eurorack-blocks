/*****************************************************************************

      VcvAudioInDaisy.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvAudioInDaisy.h"

#include "erb/vcvrack/VcvModule.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvAudioInDaisy::VcvAudioInDaisy (VcvModule & module, VcvAudioInDaisyPin /* pin */)
:  VcvInputBase ()
{
   module.add (*this);

   for (auto & buffer : _buffers) buffer.fill (0.f);
}



/*
==============================================================================
Name : size
==============================================================================
*/

VcvAudioInDaisy::operator Buffer () const
{
   return _buffers [_cur_buf];
}



/*
==============================================================================
Name : size
==============================================================================
*/

size_t   VcvAudioInDaisy::size () const
{
   return _buffers [_cur_buf].size ();
}



/*
==============================================================================
Name : operator []
==============================================================================
*/

const float &  VcvAudioInDaisy::operator [] (size_t index)
{
   return _buffers [_cur_buf][index];
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_pull_sample
==============================================================================
*/

void  VcvAudioInDaisy::impl_pull_sample ()
{
   VcvInputBase::impl_notify_audio_buffer_start ();

   float sample = norm_val ();

   _buffers [1 - _cur_buf][_cur_index] = sample;
   ++_cur_index;
}



/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  VcvAudioInDaisy::impl_notify_audio_buffer_start ()
{
   // we don't need to call-in the base class method

   // switch buffer
   _cur_buf = 1 - _cur_buf;
   _cur_index = 0;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
