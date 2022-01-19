/*****************************************************************************

      ClockEstimator.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstddef>
#include <cstdint>



class ClockEstimator
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  ClockEstimator () = default;
                  ~ClockEstimator () = default;

   size_t         process (uint64_t ms);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   uint64_t       _last_ms = 0;
   size_t         _diff_ms = 0;
   bool           _running = false;
};
