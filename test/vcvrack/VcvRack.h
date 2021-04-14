/*****************************************************************************

      VcvRack.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

using namespace erb;

struct VcvRack
{
   Module module;

   AudioInDaisy audio_in { module, AudioInDaisyPinLeft };
   AudioInDaisy audio_in2 { module, AudioInDaisyPinRight };
   AudioOutDaisy audio_out { module, AudioOutDaisyPinLeft };
   Button button { module, Pin1 };
   CvIn cv_in { module, AdcPin0 };
   GateIn gate_in { module, Pin2 };
   GateOut gate_out { module, Pin3 };
   Led led { module, Pin4 };
   LedBi led_bi { module, Pin5, Pin6 };
   Pot pot { module, AdcPin1 };
   Switch switch_ { module, Pin7, Pin8 };
   Trim trim { module, AdcPin2, Trim::Mode::Bipolar };

   Multiplexer rogan { module, AdcPin3, Pin9, Pin10, Pin12 };
   Pot rogan_6ps { rogan, MultiplexerPin0 };
   Pot rogan_5ps { rogan, MultiplexerPin1 };
   Pot rogan_3ps { rogan, MultiplexerPin2 };
   Pot rogan_2ps { rogan, MultiplexerPin3 };
   Pot rogan_1ps { rogan, MultiplexerPin4 };

   Switch dailywell_2ms1 { module, Pin13, Pin14 };
   Switch dailywell_2ms3 { module, Pin15, Pin16 };

   Led led_3mm_red { module, Pin17 };
   Led led_3mm_green { module, Pin18 };
   Led led_3mm_yellow { module, Pin19 };

   LedBi led_3mm_green_red { module, Pin21, Pin22 };

   CvIn thonk_pj398sm_knurled { module, AdcPin4 };
   CvIn thonk_pj398sm_hex { module, AdcPin5 };

   Button tl1105 { module, Pin23 };
   Button ck_d6_black { module, Pin24 };

   Switch dailywell_2ms1_90ccw { module, Pin25, Pin26 };
   Switch dailywell_2ms1_m90cw { module, Pin27, Pin28 };

   bool first_flag = true;

   void  process ();
};
