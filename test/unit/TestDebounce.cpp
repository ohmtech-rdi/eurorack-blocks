/*****************************************************************************

      TestDebounce.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestDebounce.h"

#include "test.h"

#include "erb/detail/Debounce.h"



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestDebounce::run ()
{
   run_001 ();
   run_002 ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestDebounce::run_001 ()
{
   erb::Debounce debounce;

   erb_TEST (debounce.idle ());
   erb_TEST (!debounce.pressed ());
   erb_TEST (!debounce.held ());
   erb_TEST (!debounce.released ());

   for (int i = 0 ; i < 6 ; ++i)
   {
      debounce.process (true);

      erb_TEST (!debounce.idle ());
      erb_TEST (!debounce.pressed ());
      erb_TEST (!debounce.held ());
      erb_TEST (!debounce.released ());
   }

   debounce.process (true);

   erb_TEST (!debounce.idle ());
   erb_TEST (debounce.pressed ());
   erb_TEST (!debounce.held ());
   erb_TEST (!debounce.released ());

   debounce.process (true);

   erb_TEST (!debounce.idle ());
   erb_TEST (!debounce.pressed ());
   erb_TEST (debounce.held ());
   erb_TEST (!debounce.released ());

   debounce.process (true);

   erb_TEST (!debounce.idle ());
   erb_TEST (!debounce.pressed ());
   erb_TEST (debounce.held ());
   erb_TEST (!debounce.released ());

   for (int i = 0 ; i < 6 ; ++i)
   {
      debounce.process (false);

      erb_TEST (!debounce.idle ());
      erb_TEST (!debounce.pressed ());
      erb_TEST (!debounce.held ());
      erb_TEST (!debounce.released ());
   }

   debounce.process (false);

   erb_TEST (!debounce.idle ());
   erb_TEST (!debounce.pressed ());
   erb_TEST (!debounce.held ());
   erb_TEST (debounce.released ());

   debounce.process (false);

   erb_TEST (debounce.idle ());
   erb_TEST (!debounce.pressed ());
   erb_TEST (!debounce.held ());
   erb_TEST (!debounce.released ());
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestDebounce::run_002 ()
{
   erb::Debounce debounce;

   erb_TEST (debounce.idle ());
   erb_TEST (!debounce.pressed ());
   erb_TEST (!debounce.held ());
   erb_TEST (!debounce.released ());

   for (int i = 0 ; i < 20 ; ++i)
   {
      debounce.process (true);

      erb_TEST (!debounce.idle ());
      erb_TEST (!debounce.pressed ());
      erb_TEST (!debounce.held ());
      erb_TEST (!debounce.released ());

      debounce.process (false);

      erb_TEST (!debounce.idle ());
      erb_TEST (!debounce.pressed ());
      erb_TEST (!debounce.held ());
      erb_TEST (!debounce.released ());
   }

   for (int i = 0 ; i < 6 ; ++i)
   {
      debounce.process (true);

      erb_TEST (!debounce.idle ());
      erb_TEST (!debounce.pressed ());
      erb_TEST (!debounce.held ());
      erb_TEST (!debounce.released ());
   }

   debounce.process (true);

   erb_TEST (!debounce.idle ());
   erb_TEST (debounce.pressed ());
   erb_TEST (!debounce.held ());
   erb_TEST (!debounce.released ());
}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
