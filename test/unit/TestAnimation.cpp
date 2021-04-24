/*****************************************************************************

      TestAnimation.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestAnimation.h"

#include "test.h"

#include "erb/detail/Animation.h"

#include <chrono>



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestAnimation::run ()
{
   run_001 ();
   run_002 ();
   run_002b ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_008 ();
   run_009 ();
   run_010 ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestAnimation::run_001 ()
{
   erb::Animation <float, 2> animation;

   erb_TEST (animation.get (0) == 0.f);

   animation.set (1.f);

   erb_TEST (animation.get (0) == 1.f);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestAnimation::run_002 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 2> animation;

   erb_TEST (animation.get (0) == 0.f);

   animation.set ({
      {1.f, 10ms},
      {0.f, 10ms}
   });

   animation.start (0);

   for (uint64_t i = 0 ; i < 10 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }

   for (uint64_t i = 10 ; i < 20 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 20 ; i < 100 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }
}



/*
==============================================================================
Name : run_002b
==============================================================================
*/

void  TestAnimation::run_002b ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 2> animation;

   erb_TEST (animation.get (0) == 0.f);

   animation.set ({
      {1.f, 10ms},
      {0.f, 10ms}
   });

   animation.start (3);

   for (uint64_t i = 0 ; i < 10 ; ++i)
   {
      erb_TEST (animation.get (i + 3) == 0.f);
   }

   for (uint64_t i = 10 ; i < 20 ; ++i)
   {
      erb_TEST (animation.get (i + 3) == 1.f);
   }

   for (uint64_t i = 20 ; i < 100 ; ++i)
   {
      erb_TEST (animation.get (i + 3) == 0.f);
   }
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestAnimation::run_003 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 2> animation;

   erb_TEST (animation.get (0) == 0.f);

   animation.set ({
      {1.f, 10ms},
      {0.f, 10ms}
   }).loop ();

   animation.start (0);

   for (uint64_t j = 0 ; j < 5 ; ++j)
   {
      for (uint64_t i = 0 ; i < 10 ; ++i)
      {
         erb_TEST (animation.get (i + j * 20) == 0.f);
      }

      for (uint64_t i = 10 ; i < 20 ; ++i)
      {
         erb_TEST (animation.get (i + j * 20) == 1.f);
      }
   }
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestAnimation::run_004 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 2> animation;

   erb_TEST (animation.get (0) == 0.f);

   animation.set ({
      {1.f, 4ms, erb::linear},
      {0.f, 4ms, erb::linear}
   }).loop ();

   animation.start (0);

   erb_TEST (animation.get (0) == 0.f);
   erb_TEST (animation.get (1) == 0.25f);
   erb_TEST (animation.get (2) == 0.5f);
   erb_TEST (animation.get (3) == 0.75f);
   erb_TEST (animation.get (4) == 1.f);
   erb_TEST (animation.get (5) == 0.75f);
   erb_TEST (animation.get (6) == 0.5f);
   erb_TEST (animation.get (7) == 0.25f);
   erb_TEST (animation.get (8) == 0.f);
   erb_TEST (animation.get (9) == 0.25f);

   animation.stop ();

   erb_TEST (animation.get (10) == 0.25f);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestAnimation::run_005 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 2> animation;

   erb_TEST (animation.get (0) == 0.f);

   animation.set (0.5f);

   animation.set ({
      {1.f, 4ms, erb::linear},
      {0.f, 4ms, erb::linear}
   }).loop ();

   animation.start (0);

   erb_TEST (animation.get (0) == 0.f);
   erb_TEST (animation.get (1) == 0.25f);
   erb_TEST (animation.get (2) == 0.5f);
   erb_TEST (animation.get (3) == 0.75f);
   erb_TEST (animation.get (4) == 1.f);
   erb_TEST (animation.get (5) == 0.75f);
   erb_TEST (animation.get (6) == 0.5f);
   erb_TEST (animation.get (7) == 0.25f);
   erb_TEST (animation.get (8) == 0.f);
   erb_TEST (animation.get (9) == 0.25f);

   animation.stop ();

   erb_TEST (animation.get (10) == 0.25f);
}



struct Rgb
{
   float r, g, b;
};

Rgb  interpolate (Rgb val0, Rgb val1, float t);
Rgb  interpolate (Rgb val0, Rgb val1, float t)
{
   return {
      erb::interpolate (val0.r, val1.r, t),
      erb::interpolate (val0.g, val1.g, t),
      erb::interpolate (val0.b, val1.b, t)
   };
}

bool operator == (Rgb lhs, Rgb rhs);
bool operator == (Rgb lhs, Rgb rhs)
{
   return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestAnimation::run_006 ()
{

   using namespace std::chrono_literals;

   erb::Animation <Rgb, 2> animation;

   erb_TEST (animation.get (0) == Rgb ({0.f, 0.f, 0.f}));

   animation.set ({0.5f, 0.5f, 0.5f});

   animation.set ({
      {{1.f, 1.f, 1.f}, 4ms, erb::linear},
      {{0.f, 0.f, 0.f}, 4ms, erb::linear}
   }).loop ();

   animation.start (0);

   erb_TEST (animation.get (0) == Rgb ({0.f, 0.f, 0.f}));
   erb_TEST (animation.get (1) == Rgb ({0.25f, 0.25f, 0.25f}));
   erb_TEST (animation.get (2) == Rgb ({0.5f, 0.5f, 0.5f}));
   erb_TEST (animation.get (3) == Rgb ({0.75f, 0.75f, 0.75f}));
   erb_TEST (animation.get (4) == Rgb ({1.f, 1.f, 1.f}));
   erb_TEST (animation.get (5) == Rgb ({0.75f, 0.75f, 0.75f}));
   erb_TEST (animation.get (6) == Rgb ({0.5f, 0.5f, 0.5f}));
   erb_TEST (animation.get (7) == Rgb ({0.25f, 0.25f, 0.25f}));
   erb_TEST (animation.get (8) == Rgb ({0.f, 0.f, 0.f}));
   erb_TEST (animation.get (9) == Rgb ({0.25f, 0.25f, 0.25f}));

   animation.stop ();

   erb_TEST (animation.get (10) == Rgb ({0.25f, 0.25f, 0.25f}));
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestAnimation::run_007 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 8> animation;

   animation.pulse (0ull, 20ms, erb::step, 1.f, 0.f);

   for (uint64_t i = 0 ; i < 20 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 20 ; i < 100 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestAnimation::run_008 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 8> animation;

   animation.pulse_twice (0ull, 30ms, erb::step, 1.f, 0.f);

   for (uint64_t i = 0 ; i < 10 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 10 ; i < 20 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }

   for (uint64_t i = 20 ; i < 30 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 30 ; i < 100 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestAnimation::run_009 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 8> animation;

   animation.pulse_thrice (0ull, 50ms, erb::step, 1.f, 0.f);

   for (uint64_t i = 0 ; i < 10 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 10 ; i < 20 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }

   for (uint64_t i = 20 ; i < 30 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 30 ; i < 40 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }

   for (uint64_t i = 40 ; i < 50 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 50 ; i < 100 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestAnimation::run_010 ()
{
   using namespace std::chrono_literals;

   erb::Animation <float, 8> animation;

   animation.blink (0ull, 20ms, erb::step, 1.f, 0.f);

   for (uint64_t i = 0 ; i < 10 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }

   for (uint64_t i = 10 ; i < 20 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 20 ; i < 30 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }

   for (uint64_t i = 30 ; i < 40 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }

   for (uint64_t i = 40 ; i < 50 ; ++i)
   {
      erb_TEST (animation.get (i) == 0.f);
   }

   for (uint64_t i = 50 ; i < 60 ; ++i)
   {
      erb_TEST (animation.get (i) == 1.f);
   }
}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
