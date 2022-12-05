/*****************************************************************************

      %module.name%_erbb.hpp
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
Name : call_faust_mydsp_memoryCreate_if_exists
Description :
   Patch Faust introduction of 'memoryCreate' which introduces a breaking
   change: the function must be called if it exists.
==============================================================================
*/

template <typename T>
auto  call_faust_mydsp_memoryCreate_if_exists (T & dsp, int) -> decltype (dsp.memoryCreate ())
{
   dsp.memoryCreate ();
}

template <typename T>
auto  call_faust_mydsp_memoryCreate_if_exists (T & dsp, long) -> void {}



/*
==============================================================================
Name : init
==============================================================================
*/

void  %module.name%::init ()
{
   mydsp::fManager = &mem;

   mydsp::classInit (erb_SAMPLE_RATE);
   call_faust_mydsp_memoryCreate_if_exists (dsp, 0);
   dsp.instanceInit (erb_SAMPLE_RATE);
   dsp.buildUserInterface (&adapter);
}



erb_RESTORE_WARNINGS
