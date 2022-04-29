// BoardSimulator.h

#pragma once

#include "erb/vcvrack/BoardGeneric.h"


struct Board
:  public erb::BoardGeneric
{
   inline         Board () : erb::BoardGeneric (
      0, 1, 1,  // digital/analog/audio inputs
      0, 0, 1    // digital/analog/audio outputs
   ) {}
   virtual        ~Board () override = default;

   // Analog Inputs
   inline const float &
                  p (size_t i) { return _analog_inputs [i]; }

   // Audio Inputs
   inline const erb::Buffer &
                  ai (size_t i) { return _audio_inputs [i]; }

   // Audio Outputs
   inline erb::Buffer &
                  ao (size_t i) { return _audio_outputs [i]; }
};
