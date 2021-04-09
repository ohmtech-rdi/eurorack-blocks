/*****************************************************************************

      VcvAudioOutDaisy.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvAudioOutDaisy.h"

#include "erb/vcvrack/VcvModule.h"

#include <rack.hpp>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvAudioOutDaisy::VcvAudioOutDaisy (VcvModule & module, VcvAudioOutDaisyPin /* pin */)
:  VcvOutputBase ()
{
   module.add (*this);

   for (auto & buffer : _buffers) buffer.fill (0.f);
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

VcvAudioOutDaisy &   VcvAudioOutDaisy::operator = (const Buffer & buffer)
{
   _buffers [_cur_buf] = buffer;

   return *this;
}



/*
==============================================================================
Name : size
==============================================================================
*/

size_t   VcvAudioOutDaisy::size () const
{
   return _buffers [_cur_buf].size ();
}



/*
==============================================================================
Name : operator []
==============================================================================
*/

float &  VcvAudioOutDaisy::operator [] (size_t index)
{
   return _buffers [_cur_buf][index];
}



/*
==============================================================================
Name : fill
==============================================================================
*/

void  VcvAudioOutDaisy::fill (float val)
{
   _buffers [_cur_buf].fill (val);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_pull_sample
==============================================================================
*/

void  VcvAudioOutDaisy::impl_push_sample ()
{
   float sample = _buffers [1 - _cur_buf][_cur_index];
   ++_cur_index;

   set_norm_val (sample);
}



/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  VcvAudioOutDaisy::impl_notify_audio_buffer_start ()
{
   // nothing
}



/*
==============================================================================
Name : impl_notify_audio_buffer_end
==============================================================================
*/

void  VcvAudioOutDaisy::impl_notify_audio_buffer_end ()
{
   // switch buffer
   _cur_buf = 1 - _cur_buf;
   _cur_index = 0;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
