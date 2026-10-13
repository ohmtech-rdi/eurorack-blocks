/*****************************************************************************

      Probe.h
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



using ProbeMap = std::map <std::string, std::any>;

struct Probe
{
   std::string key;
};

template <typename T>
void  probe (const std::string & key, const T & value);

void  probe_reset ();

ProbeMap &
      impl_probe_singleton ();



}  // namespace rig
}  // namespace erb



#include "erb/rig/Probe.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
