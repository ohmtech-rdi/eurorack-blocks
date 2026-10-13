/*****************************************************************************

      Context.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <any>
#include <map>
#include <string>



namespace erb
{
namespace rig
{



using ContextMap = std::map <std::string, std::any>;

void  context_set (const ContextMap & context);

template <typename T>
T     context (const std::string & key);

ContextMap &
      impl_context_singleton ();



}  // namespace rig
}  // namespace erb



#include "erb/rig/Context.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
