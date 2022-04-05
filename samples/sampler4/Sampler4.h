// Sampler4.h

#pragma once

#include "artifacts/Sampler4Ui.h"
#include "artifacts/Sampler4Data.h"
#include "erb/erb.h"


struct Sampler4
{
   Sampler4Ui ui;
   Sampler4Data data;

   struct Track
   {
      Track (erb::Encoder & select_, erb::Button & trigger_button_, erb::Led <erb::PinType::Pwm> & trigger_led_, erb::GateIn & trigger_gate_);

      erb::Encoder & select;
      erb::Button & trigger_button;
      erb::Led <erb::PinType::Pwm> & trigger_led;
      erb::GateIn & trigger_gate;
   };

   using Tracks = std::array <Track, 1>;

   Tracks tracks = {{
      {
         ui.track1_select,
         ui.track1_trigger_button,
         ui.track1_trigger_led,
         ui.track1_trigger_gate
      }
   }};

   void  init ();
   void  process ();
};
