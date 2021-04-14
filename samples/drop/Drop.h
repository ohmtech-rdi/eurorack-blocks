/*****************************************************************************

      Drop.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DropDsp.h"

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

using namespace erb;

struct Drop
{
   DropDsp drop_dsp { sample_rate };

   Module module;

   AudioInDaisy audio_in_left { module, AudioInDaisyPinLeft };
   AudioInDaisy audio_in_right { module, AudioInDaisyPinRight };

   AudioOutDaisy audio_out_left { module, AudioOutDaisyPinLeft };
   AudioOutDaisy audio_out_right { module, AudioOutDaisyPinRight };

   Button sync_button { module, Pin5 };
   GateIn sync_gate { module, Pin14 };
   Led sync_led { module, Pin13 };
   Switch mute_hp { module, Pin12, Pin11 };
   Pot freq_pot { module, AdcPin0 };
   CvIn freq_cv { module, AdcPin1 };
   Trim freq_trim { module, AdcPin2, Trim::Mode::Bipolar };
   Button arm_button { module, Pin10 };
   GateIn arm_gate { module, Pin9 };
   Led arm_led { module, Pin8 };
   GateOut state_gate { module, Pin4 };
   LedBi state_led { module, Pin7, Pin6 };

   DropDsp::State _old_state = DropDsp::State::None;

   void  process ();
};
