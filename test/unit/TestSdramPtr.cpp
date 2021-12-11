/*****************************************************************************

      TestSdramPtr.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestSdramPtr.h"

#include "test.h"

#define erb_TARGET_VCV_RACK

#include "erb/SdramPtr.h"
#include "erb/config.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <thread>
#include <tuple>
#include <vector>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestSdramPtr::run ()
{
   run_000 ();
   run_000b ();
   run_001 ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_000
Spec :
   pos' = pool.allocate (alignment, size)
   \E n : 2^n == alignment
   \E n : 2^n == size
   For any sequence of <<alignment, size>>:
   /\ size % alignment == 0
   /\ pos' % alignment == 0
   /\ pos' - pos >= size
==============================================================================
*/

void  TestSdramPtr::run_000 ()
{
   erb::MonotonicMemoryPool <std::numeric_limits <size_t>::max ()> pool;

   using AlignmentSize = std::tuple <
      size_t /* alignment */, size_t /* size */
   >;
   using AlignmentSizeArr = std::vector <AlignmentSize>;

   AlignmentSizeArr arr;
   arr.emplace_back (1, 1);
   arr.emplace_back (1, 1);
   arr.emplace_back (1, 1);
   arr.emplace_back (1, 4);
   arr.emplace_back (1, 2);
   arr.emplace_back (4, 4);
   arr.emplace_back (4, 4);
   arr.emplace_back (4, 8);
   arr.emplace_back (4, 32);
   arr.emplace_back (8, 8);
   arr.emplace_back (8, 16);

   std::sort (arr.begin (), arr.end ());

   size_t previous_pos = 0;
   size_t previous_size = 0;

   do
   {
#if 0
      for (auto && t : arr)
      {
         std::cout << std::get <0> (t) << "," << std::get <1> (t) << std::endl;
      }
      std::cout << std::endl;
#endif

      for (auto && t : arr)
      {
         size_t alignment = std::get <0> (t);
         size_t size = std::get <1> (t);
         size_t pos = pool.allocate (alignment, size);

         erb_TEST (size % alignment == 0);
         erb_TEST (pos % alignment == 0);
         if (previous_pos != 0) erb_TEST (pos > previous_pos);
         erb_TEST (pos - previous_pos >= previous_size);

         previous_pos = pos;
         previous_size = size;
      }
   }
   while (std::next_permutation (arr.begin (), arr.end ()));
}



/*
==============================================================================
Name : run_000b
Spec :
   pos' = pool.allocate (1, 1)
   All pos are unique
==============================================================================
*/

void  TestSdramPtr::run_000b ()
{
   using Pool = erb::MonotonicMemoryPool <std::numeric_limits <size_t>::max ()>;
   Pool pool;

   constexpr size_t loop_nbr = 10000000;

   using Result = std::vector <size_t>;

   struct Process {
      Process () {
         r.reserve (loop_nbr);
      }
      void  run (Pool & pool) {
         for (size_t i = 0 ; i < loop_nbr ; ++i)
         {
            size_t pos = pool.allocate (1, 1);
            r.push_back (pos);
         }

         check_result_sorted ();
      }
      void check_result_sorted () const {
         Result rp {r};
         std::sort (rp.begin (), rp.end ());
         erb_TEST (rp == r);
      }
      Result r;
   };

   Process p1;
   Process p2;

   std::thread t1 {[&](){p1.run (pool);}};
   std::thread t2 {[&](){p2.run (pool);}};

   t1.join ();
   t2.join ();

   Result intersection;
   std::set_intersection (
      p1.r.begin (), p1.r.end (),
      p2.r.begin (), p2.r.end (),
      std::back_inserter (intersection)
   );

   erb_TEST (intersection.empty ());

   Result union_;
   std::set_union (
      p1.r.begin (), p1.r.end (),
      p2.r.begin (), p2.r.end (),
      std::back_inserter (union_)
   );

   erb_TEST (union_.size () == 2 * loop_nbr);
   erb_TEST (union_.front () == 0);
   erb_TEST (union_.back () == 2 * loop_nbr - 1);
}



/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestSdramPtr::run_001 ()
{
   struct A {
      std::array <uint8_t, erb_SDRAM_MEM_POOL_SIZE> data;
   };

   auto a_sptr = erb::make_sdram <A> ();

   bool ok_flag = false;

   try
   {
      auto b_sptr = erb::make_sdram <uint8_t> ();
   }
   catch (std::bad_alloc &)
   {
      ok_flag = true;
   }

   erb_TEST (ok_flag);
}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
