/*****************************************************************************

      ModuleListeners.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/ModuleListeners.h"

#include "erb/ModuleListener.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : add
==============================================================================
*/

void  ModuleListeners::add (ModuleListener & listener)
{
   auto & listener_ptr = _listeners [_nbr_listener];
   ++_nbr_listener;

   listener_ptr = &listener;
}



/*
==============================================================================
Name : notify_audio_buffer_start
==============================================================================
*/

void  ModuleListeners::notify_audio_buffer_start ()
{
   for (size_t i = 0 ; i < _nbr_listener ; ++i)
   {
      auto listener_ptr = _listeners [i];
      listener_ptr->impl_notify_audio_buffer_start ();
   }
}



/*
==============================================================================
Name : notify_audio_buffer_end
==============================================================================
*/

void  ModuleListeners::notify_audio_buffer_end ()
{
   for (size_t i = 0 ; i < _nbr_listener ; ++i)
   {
      auto listener_ptr = _listeners [i];
      listener_ptr->impl_notify_audio_buffer_end ();
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
