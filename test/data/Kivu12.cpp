/*****************************************************************************

      Kivu12.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Kivu12.h"

#include <cmath>



/*
==============================================================================
Name : process
==============================================================================
*/

void  Kivu12::process ()
{
   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      auto val = data.sample_mono.samples [pos];
      pos = (pos + 1) % data.sample_mono.samples.size ();

      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = data.sample_stereo.frames [pos].channels [0];
      ui.audio_out2 [i] = data.sample_stereo.frames [pos].channels [1];
      pos = (pos + 1) % data.sample_stereo.frames.size ();
   }

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      auto val = data.sample_mono_mono.samples [pos];
      pos = (pos + 1) % data.sample_mono_mono.samples.size ();

      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = data.sample_stereo_interleaved.frames [pos].channels [0];
      ui.audio_out2 [i] = data.sample_stereo_interleaved.frames [pos].channels [1];
      pos = (pos + 1) % data.sample_stereo_interleaved.frames.size ();
   }

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = data.sample_stereo_planar.channels [0].samples [pos];
      ui.audio_out2 [i] = data.sample_stereo_planar.channels [1].samples [pos];
      pos = (pos + 1) % data.sample_stereo_planar.channels [0].samples.size ();
   }
}
