/*****************************************************************************

      main.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/erb.h"

#include <cmath>



/*\\\ CLASSES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

constexpr double pim2 = 2.0 * M_PI;

class OscSin
{
public:
   void           set_freq (float freq)
   {
      const double phase_step = pim2 * double (freq) / double (erb::sample_rate);
      _step_cos = std::cos (phase_step);
      _step_sin = std::sin (phase_step);
   }

   float          process ()
   {
      const double old_cos = _pos_cos;
      const double old_sin = _pos_sin;
      _pos_cos = old_cos * _step_cos - old_sin * _step_sin;
      _pos_sin = old_cos * _step_sin + old_sin * _step_cos;

      return float (_pos_sin);
   }

private:
   double         _step_cos = 1.0;
   double         _step_sin = 0.0;

   double         _pos_cos = 1.0;
   double         _pos_sin = 0.0;
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
   AudioOut audio_out0 (module, AudioOutPin0);
   AudioOut audio_out1 (module, AudioOutPin1);

   Multiplexer multiplexer (module, AdcPin1, Pin23, Pin24, Pin25);

   Pot ctrl_1 (multiplexer, MultiplexerPin0); // osc1 amplitude
   Pot ctrl_2 (multiplexer, MultiplexerPin1); // osc1 frequency
   Pot ctrl_3 (multiplexer, MultiplexerPin2); // osc2 amplitude
   Pot ctrl_4 (multiplexer, MultiplexerPin3); // osc2 frequency
   Pot ctrl_5 (multiplexer, MultiplexerPin4); // osc3 amplitude
   Pot ctrl_6 (multiplexer, MultiplexerPin5); // osc3 frequency
   Pot ctrl_7 (multiplexer, MultiplexerPin6); // osc4 amplitude
   Pot ctrl_8 (multiplexer, MultiplexerPin7); // osc4 frequency

   Pot ctrl_9 (module, AdcPin0); // osc5 frequency

   OscSin osc1, osc2, osc3, osc4, osc5;

   module.run ([&](){
      for (size_t i = 0 ; i < audio_out0.size () ; ++i)
      {
         osc1.set_freq (20.f * std::pow (500.f, ctrl_2));
         auto out_val = osc1.process () * ctrl_1;

         osc2.set_freq (20.f * std::pow (500.f, ctrl_4));
         out_val += osc2.process () * ctrl_3;

         osc3.set_freq (20.f * std::pow (500.f, ctrl_6));
         out_val += osc3.process () * ctrl_5;

         osc4.set_freq (20.f * std::pow (500.f, ctrl_8));
         out_val += osc4.process () * ctrl_7;

         osc5.set_freq (20.f * std::pow (500.f, ctrl_9));
         out_val += osc5.process ();

         audio_out0 [i] = out_val;
         audio_out1 [i] = out_val;
      }
   });
}
