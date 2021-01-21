/*****************************************************************************

      main.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/erb.h"

#include <cmath>



/*\\\ CLASSES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

constexpr float pim2 = 2.f * float (M_PI);

class OscSin
{
public:
   void           set_freq (float freq)
   {
      const float phase_step = pim2 * freq / erb::sample_rate;
      _step_cos = std::cos (phase_step);
      _step_sin = std::sin (phase_step);
   }

   float          process ()
   {
      const float old_cos = _pos_cos;
      const float old_sin = _pos_sin;
      _pos_cos = old_cos * _step_cos - old_sin * _step_sin;
      _pos_sin = old_cos * _step_sin + old_sin * _step_cos;

      return _pos_sin;
   }

private:
   float          _step_cos = 1.f;
   float          _step_sin = 0.f;

   float          _pos_cos = 1.f;
   float          _pos_sin = 0.f;
};



/*\\\ FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : main
==============================================================================
*/

int main ()
{
   using namespace erb;

   Module module;
   AudioOutDaisy audio_out0 (module, AudioOutDaisyPin0);
   AudioOutDaisy audio_out1 (module, AudioOutDaisyPin1);

   // Pins are the same as the CTRL 1..4 on Daisy Patch
   Pot ctrl_1 (module, AdcPin0); // osc1 amplitude
   Pot ctrl_2 (module, AdcPin1); // osc1 frequency
   Pot ctrl_3 (module, AdcPin6); // osc2 amplitude
   Pot ctrl_4 (module, AdcPin3); // osc2 frequency

   OscSin osc1, osc2;

   module.run ([&](){
      for (size_t i = 0 ; i < audio_out0.size () ; ++i)
      {
         osc1.set_freq (20.f * std::pow (500.f, ctrl_2));
         auto out_val = osc1.process () * ctrl_1;

         osc2.set_freq (20.f * std::pow (500.f, ctrl_4));
         out_val += osc2.process () * ctrl_3;

         audio_out0 [i] = out_val;
         audio_out1 [i] = out_val;
      }
   });
}
