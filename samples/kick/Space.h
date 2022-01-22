/*****************************************************************************

      Space.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "ClockEstimator.h"

#include "dsp/Ramp.h"

#include <cstddef>



class Space
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Space () = default;
                  ~Space () = default;

   void           tick (uint64_t clock_ms, float space);
   void           trigger ();
   float          process (float x);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   ClockEstimator _estimator;
   size_t         _space_spl = 24000;
   size_t         _step_spl = 0;
   bool           _active = false;
   dsp::Ramp <1024>
                  _ramp = {1.f};
};
