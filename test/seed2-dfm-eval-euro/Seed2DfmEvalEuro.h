/*****************************************************************************

      Seed2DfmEvalEuro.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "artifacts/Seed2DfmEvalEuroUi.h"
#include "artifacts/Seed2DfmEvalEuroData.h"

#include "erb/erb.h"

#include <atomic>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct Seed2DfmEvalEuro
{
   Seed2DfmEvalEuroUi ui;

   void  process ();
   void  idle ();

   class OscSin
   {
   public:
      void  set (float freq) {
         const double phase_step = double (freq) * (2.0 * M_PI / double (erb_SAMPLE_RATE));
         _step_cos = std::cos (phase_step);
         _step_sin = std::sin (phase_step);
      }

      auto  operator () () -> float {
         const double old_cos = _pos_cos;
         const double old_sin = _pos_sin;
         _pos_cos = old_cos * _step_cos - old_sin * _step_sin;
         _pos_sin = old_cos * _step_sin + old_sin * _step_cos;

         return float (_pos_sin);
      }

   private:
      double _step_cos = 1.0;
      double _step_sin = 0.0;
      double _pos_cos = 1.0;
      double _pos_sin = 0.0;
   };

   OscSin osc1;
   OscSin osc2;
   OscSin osc3;
   OscSin osc4;

   std::atomic <int> pic = 0;
};
