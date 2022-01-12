/*****************************************************************************

      %module.name%.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"
#include "erb/detail/fnc.h"

erb_DISABLE_WARNINGS_FAUST_GEN



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : addButton
==============================================================================
*/

void  Adapter::addButton (const char * /* label_0 */, float * zone)
{
   push_parameter (zone);
}



/*
==============================================================================
Name : addCheckButton
==============================================================================
*/

void  Adapter::addCheckButton (const char * /* label_0 */, float * zone)
{
   push_parameter (zone);
}



/*
==============================================================================
Name : addVerticalSlider
==============================================================================
*/

void  Adapter::addVerticalSlider (const char * /* label_0 */, float * zone, float /* init */, float /* min */, float /* max */, float /* step */)
{
   push_parameter (zone);
}



/*
==============================================================================
Name : addHorizontalSlider
==============================================================================
*/

void  Adapter::addHorizontalSlider (const char * /* label_0 */, float * zone, float /* init */, float /* min */, float /* max */, float /* step */)
{
   push_parameter (zone);
}



/*
==============================================================================
Name : addHorizontalBargraph
==============================================================================
*/

void  Adapter::addHorizontalBargraph (const char * /* label_0 */, float * zone, float /* min */, float /* max */)
{
   push_parameter (zone);
}



/*
==============================================================================
Name : addVerticalBargraph
==============================================================================
*/

void  Adapter::addVerticalBargraph (const char * /* label_0 */, float * zone, float /* min */, float /* max */)
{
   push_parameter (zone);
}



/*
==============================================================================
Name : addNumEntry
==============================================================================
*/

void  Adapter::addNumEntry (const char * /* label_0 */, float * zone, float /* init */, float /* min */, float /* max */, float /* step */)
{
   push_parameter (zone);
}



/*
==============================================================================
Name : addSoundfile
==============================================================================
*/

void  Adapter::addSoundfile (const char * /* label_0 */ , const char * /* filename_0 */, Soundfile ** sf_zone)
{
   *sf_zone = &samples [spl_index];
   ++spl_index;
}



/*
==============================================================================
Name : push_parameter
==============================================================================
*/

void  Adapter::push_parameter (float * zone)
{
   parameters [decl_index] = zone;
   ++decl_index;
}



/*
==============================================================================
Name : preprocess
==============================================================================
*/

void  Adapter::preprocess ()
{
%  module.ui_input_entities%
}



/*
==============================================================================
Name : postprocess
==============================================================================
*/

void  Adapter::postprocess ()
{
%  module.ui_output_entities%
}



/*
==============================================================================
Name : allocate
==============================================================================
*/

void *   dsp_memory_manager::allocate (size_t size)
{
   return erb::allocate_bytes_auto (size);
}



/*
==============================================================================
Name : destroy
==============================================================================
*/

void  dsp_memory_manager::destroy (void * ptr)
{
#if defined (erb_TARGET_VCV_RACK)
   std::cout << "Warning: dsp_memory_manager::destroy: Potential memory leak.\n";
   std::cout << "         Set a breakpoint to debug.\n";

   // only for simulator, see 'allocate_bytes_auto' for allocation system.
   std::free (ptr);
#endif
}



/*
==============================================================================
Name : init
==============================================================================
*/

void  %module.name%::init ()
{
   mydsp::fManager = &mem;

   mydsp::classInit (erb_SAMPLE_RATE);
   dsp.instanceInit (erb_SAMPLE_RATE);
   dsp.buildUserInterface (&adapter);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  %module.name%::process ()
{
   adapter.preprocess ();

   const float * const in [] = {
%  module.audio_inputs%
   };

   float * const out [] = {
%  module.audio_outputs%
   };

   auto in_faust = const_cast <float **> (in);
   auto out_faust = const_cast <float **> (out);

   dsp.compute (erb_BUFFER_SIZE, in_faust, out_faust);

   adapter.postprocess ();
}



erb_RESTORE_WARNINGS
