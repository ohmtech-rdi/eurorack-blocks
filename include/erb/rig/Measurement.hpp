/*****************************************************************************

      Measurement.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cmath>
#include <cstdio>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : scalar_distance
==============================================================================
*/

float scalar_distance (float a, float b)
{
   return std::abs (a - b);
}



/*
==============================================================================
Name : scalar_report
==============================================================================
*/

void  scalar_report (const char * name, const char * output_name, float reading, float expected, float tolerance)
{
   std::fprintf (
      stderr,
      "%s on %s reads %f, expected %f, distance %f, tolerance %f\n",
      name, output_name,
      double (reading), double (expected),
      double (scalar_distance (reading, expected)), double (tolerance)
   );
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
