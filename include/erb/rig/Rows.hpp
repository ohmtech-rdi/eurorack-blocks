/*****************************************************************************

      Rows.hpp
      Copyright (c) 2026 Ohm Force

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstdio>
#include <cstring>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : run_rows
Description :
   No arg: run everything
   '--list': list the row names
   Just a name: that row only
   '--continue-on-failure' uses '--list' to get the row names and then
   execute each row in its own process.
==============================================================================
*/

int   run_rows (int argc, const char * argv [], const std::vector <Row> & rows)
{
   if ((argc == 2) && (std::strcmp (argv [1], "--list") == 0))
   {
      for (const auto & row : rows)
      {
         std::printf ("%s\n", row.name);
      }
      std::fflush (stdout);

      return 0;
   }

   if (argc == 2)
   {
      for (const auto & row : rows)
      {
         if (std::strcmp (argv [1], row.name) == 0)
         {
            std::printf ("ROW %s\n", row.name);
            std::fflush (stdout);
            row.run ();

            return 0;
         }
      }

      std::fprintf (stderr, "error: no row '%s'\n", argv [1]);

      return 2;
   }

   if (argc > 2)
   {
      std::fprintf (stderr, "usage: %s [--list | <row>]\n", argv [0]);

      return 2;
   }

   for (const auto & row : rows)
   {
      std::printf ("ROW %s\n", row.name);
      std::fflush (stdout);
      row.run ();
   }

   return 0;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
