/*****************************************************************************

      CycleCounter.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"

#if (erb_MONITOR) && defined (erb_TARGET_DAISY)

#include <cstdint>



namespace erb
{



class CycleCounter
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static void    init ();
   static inline std::uint32_t
                  now ();
};



}  // namespace erb



#include "erb/CycleCounter.hpp"

#endif   // erb_MONITOR && erb_TARGET_DAISY
