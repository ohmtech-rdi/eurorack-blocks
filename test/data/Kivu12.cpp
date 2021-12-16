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
#if 0
   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      auto val = data.sample_mono.channels [0].samples [pos];
      pos = (pos + 1) % data.sample_mono.channels [0].samples.size ();

      ui.audio_out1 [i] = val;
      ui.audio_out2 [i] = val;
   }

#elif 1
   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out1 [i] = data.sample_stereo.channels [0].samples [pos];
      ui.audio_out2 [i] = data.sample_stereo.channels [1].samples [pos];
      pos = (pos + 1) % data.sample_mono.channels [0].samples.size ();
   }
#endif
}
