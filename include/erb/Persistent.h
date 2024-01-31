/*****************************************************************************

      Persistent.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

#if defined (erb_TARGET_DAISY)
   #include "erb/daisy/ClockHal.h"
#endif

#include <chrono>

#include <cstddef>
#include <cstdint>



namespace erb
{



template <typename Type, size_t Page, uint64_t Magic, size_t RateLimitMs = 1000>
class Persistent
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         Persistent () = default;
   virtual        ~Persistent () = default;

   template <typename Board>
   Type           load (Board & board);

   template <typename Board>
   void           save (Board & board, Type value);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

#if defined (erb_TARGET_DAISY)
      using Clock = ClockHal;

#elif defined (erb_TARGET_VCV_RACK) || defined (erb_TARGET_UNIT_TEST)
      using Clock = std::chrono::steady_clock;

#endif

   Type           _value = {};

   bool           _need_commit_flag = false;
   std::chrono::time_point <Clock>
                  _earliest_commit_tp;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Persistent (const Persistent & rhs) = delete;
                  Persistent (Persistent && rhs) = delete;
   Persistent &   operator = (const Persistent & rhs) = delete;
   Persistent &   operator = (Persistent && rhs) = delete;
   bool           operator == (const Persistent & rhs) const = delete;
   bool           operator != (const Persistent & rhs) const = delete;



}; // class Persistent



}  // namespace erb



#include "erb/Persistent.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
