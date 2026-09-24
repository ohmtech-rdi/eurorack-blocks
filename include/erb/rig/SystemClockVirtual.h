/*****************************************************************************

      SystemClockVirtual.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <chrono>
#include <ratio>

#include <cstdint>



namespace erb
{
namespace rig
{



class SystemClockVirtual
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   using rep = std::int64_t;
   using period = std::nano;
   using duration = std::chrono::duration <rep, period>;
   using time_point = std::chrono::time_point <SystemClockVirtual>;

   static constexpr bool
                  is_steady = true;

   static inline time_point
                  now ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static inline void
                  impl_reset ();
   static inline void
                  impl_advance (std::uint64_t nbr_samples);
   static inline std::uint64_t
                  impl_samples ();



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   static inline std::uint64_t
                  _samples = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SystemClockVirtual () = delete;
                  ~SystemClockVirtual () = delete;



}; // class SystemClockVirtual



}  // namespace rig
}  // namespace erb



#include "erb/rig/SystemClockVirtual.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
