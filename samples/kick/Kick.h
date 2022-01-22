/*****************************************************************************

      Kick.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "artifacts/KickUi.h"
#include "artifacts/KickData.h"

#include "Presence.h"
#include "Space.h"
#include "VoicesBody.h"
#include "VoicesTransient.h"

#include "dsp/Filter2Poles.h"
#include "dsp/Ramp.h"

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct Kick
{
   KickUi ui;
   KickData data;

   void  init ();
   void  process ();

   VoicesBody body;
   VoicesTransient transient {data};
   dsp::Filter2Poles filter;
   Space space;
   Presence presence;
   bool active = true;
   dsp::Ramp <256> active_ramp;
};
