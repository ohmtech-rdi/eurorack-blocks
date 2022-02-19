/*****************************************************************************

      Kivu12.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "artifacts/Kivu12Ui.h"

#include "erb/erb.h"

#include <array>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

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



struct Kivu12
{
   Kivu12Ui ui;
   OscSin osc;

   void  process ();
};
