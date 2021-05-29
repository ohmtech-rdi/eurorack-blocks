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
      const double phase_step = pim2 * double (freq) / erb_SAMPLE_RATE;
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

   BoardDaisySeed board;

   AudioOut audio_out_left { board.audioout (0) };
   AudioOut audio_out_right { board.audioout (1) };

   // Pins are the same as the CTRL 1..4 on Daisy Patch
   CvIn <FloatRange::Normalized> ctrl_1 { board.adc (0) }; // osc1 amplitude
   CvIn <FloatRange::Normalized> ctrl_2 { board.adc (1) }; // osc1 frequency
   CvIn <FloatRange::Normalized> ctrl_3 { board.adc (6) }; // osc2 amplitude
   CvIn <FloatRange::Normalized> ctrl_4 { board.adc (3) }; // osc2 frequency

   OscSin osc1, osc2;

   board.run ([&](){
      for (size_t i = 0 ; i < audio_out_left.size () ; ++i)
      {
         osc1.set_freq (20.f * std::pow (500.f, std::abs (ctrl_2)));
         auto out_val = osc1.process () * ctrl_1;

         osc2.set_freq (20.f * std::pow (500.f, std::abs (ctrl_4)));
         out_val += osc2.process () * ctrl_3;

         audio_out_left [i] = out_val;
         audio_out_right [i] = out_val;
      }
   });
}
