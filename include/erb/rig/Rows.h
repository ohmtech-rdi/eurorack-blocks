/*****************************************************************************

      Rows.h
      Copyright (c) 2026 Ohm Force

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <functional>
#include <vector>



namespace erb
{
namespace rig
{



struct Row
{
   const char *   name;
   std::function <void ()>
                  run;
};

inline int     run_rows (int argc, const char * argv [], const std::vector <Row> & rows);



}  // namespace rig
}  // namespace erb



#include "erb/rig/Rows.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
