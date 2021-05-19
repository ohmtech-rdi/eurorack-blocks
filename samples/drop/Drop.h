/*****************************************************************************

      Drop.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DropDsp.h"
#include "artifacts/DropUi.h"

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct Drop
{
   DropDsp dsp { erb_SAMPLE_RATE };
   DropUi ui;

   DropDsp::State _old_state = DropDsp::State::None;

   void  process ();
};
