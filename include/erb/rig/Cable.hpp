/*****************************************************************************

      Cable.hpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>

#include <cassert>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : bind
==============================================================================
*/

template <FloatRange OutputRange, FloatRange InputRange>
Connection  Cable::bind (Bench & bench, CvOut <OutputRange> & output, CvIn <InputRange> & input)
{
   bind_channel (bench, input);
   unplug_channel (0);

   _output_data_ptr = &output.impl_data;
   _input_min = CvIn <InputRange>::ValueMin;
   _input_max = CvIn <InputRange>::ValueMax;

   return connect ();
}



/*
==============================================================================
Name : plug
==============================================================================
*/

void  Cable::plug ()
{
   assert (bound ());

   _plugged = true;
   plug_channel (0);
}



/*
==============================================================================
Name : unplug
==============================================================================
*/

void  Cable::unplug ()
{
   assert (bound ());

   _plugged = false;
   unplug_channel (0);
}



/*
==============================================================================
Name : impl_process
Note :
   This introduces a buffer size latency
==============================================================================
*/

void  Cable::impl_process ()
{
   if (!_plugged) return;

   input_analog (0) = std::clamp (*_output_data_ptr, _input_min, _input_max);
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Cable::name () const
{
   return "Cable";
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
