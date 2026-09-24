/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/BoardGeneric.h"

#include "erb/detail/ModuleBoard.h"

#include <cassert>



namespace erb
{
namespace rig
{



#if defined (__clang__)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

// process-lifetime memory pools, allocates before 'main'
static ModuleBoard module_board;

#if defined (__clang__)
   #pragma clang diagnostic pop
#endif

static struct ModuleBoardCurrent
{
   ModuleBoardCurrent () { ModuleBoard::impl_set_current (&module_board); }
} module_board_current;



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardGeneric::BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs)
:  _digital_inputs (nbr_digital_inputs, 0)
,  _analog_inputs (nbr_analog_inputs, 0.f)
,  _audio_inputs (nbr_audio_inputs, Buffer {})
,  _digital_outputs (nbr_digital_outputs, 0)
,  _analog_outputs (nbr_analog_outputs, 0.f)
,  _audio_outputs (nbr_audio_outputs, Buffer {})
{
   // board is first member, so pools are reset before anything else,
   // and the previous module is guaranteed to be already gone

   ModuleBoard::current ().impl_reset_pools ();
}



/*
==============================================================================
Name : use_persistent_map
==============================================================================
*/

BoardGeneric::PersistentMap & BoardGeneric::use_persistent_map ()
{
   return _persistent_map;
}



/*
==============================================================================
Name : start
Description :
   Ends the "Given" phase.
   Mode is deduced from there on, when no measurements are done it means
   we don't care about audio, and so UI can run fast.
==============================================================================
*/

void  BoardGeneric::start ()
{
   assert (_boot_flag);
   assert (!_start_flag);

   _start_flag = true;

   _mode = (_nbr_measurements > 0) ? Mode::Lockstep : Mode::UiFast;
}



/*
==============================================================================
Name : run
Description :
   Pumps the current mode until 'duration' of system time has passed.
==============================================================================
*/

void  BoardGeneric::run (SystemClockVirtual::duration duration)
{
   assert (_boot_flag);

   const auto target = SystemClockVirtual::now () + duration;

   while (SystemClockVirtual::now () < target)
   {
      // last step may overshoot by one, but this is deterministic
      impl_step ();
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_setup
==============================================================================
*/

void  BoardGeneric::impl_setup ()
{
   assert (!_setup_flag);
   assert (!_boot_flag);

   _persistent_map.clear ();
   SystemClockVirtual::impl_reset ();

   _setup_flag = true;
}



/*
==============================================================================
Name : impl_boot
==============================================================================
*/

void  BoardGeneric::impl_boot (Glue glue)
{
   assert (_setup_flag);
   assert (!_boot_flag);
   assert (glue.preprocess);
   assert (glue.process);
   assert (glue.postprocess);
   assert (glue.idle);

   _glue = std::move (glue);

   _boot_flag = true;
}



/*
==============================================================================
Name : impl_step
==============================================================================
*/

void  BoardGeneric::impl_step ()
{
   switch (_mode)
   {
   case Mode::UiFast:
      impl_step_pair ();
      break;

   case Mode::Lockstep:
      impl_step_frame ();
      break;
   }
}



/*
==============================================================================
Name : impl_step_pair
Description :
   For 'UiFast', one 'process' then one 'idle'. We need 'process' because
   the UI state is from 'process'.
==============================================================================
*/

void  BoardGeneric::impl_step_pair ()
{
   impl_frame ();
   impl_idle ();

   SystemClockVirtual::impl_advance (erb_BUFFER_SIZE * FramesPerIdle);
}



/*
==============================================================================
Name : impl_step_frame
Description :
   For 'Lockstep', one 'process' then many 'idle', eg. 18 for a system with
   16 buffer size @ 48kHz and around 6ms min period for UI.
==============================================================================
*/

void  BoardGeneric::impl_step_frame ()
{
   impl_frame ();

   SystemClockVirtual::impl_advance (erb_BUFFER_SIZE);

   if (_frame_count % FramesPerIdle == 0)
   {
      impl_idle ();
   }
}



/*
==============================================================================
Name : impl_frame
==============================================================================
*/

void  BoardGeneric::impl_frame ()
{
   _glue.preprocess ();
   _glue.process ();
   _glue.postprocess ();

   ++_frame_count;
}



/*
==============================================================================
Name : impl_idle
==============================================================================
*/

void  BoardGeneric::impl_idle ()
{
   _glue.idle ();

   ++_idle_count;
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardGeneric::impl_preprocess ()
{
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardGeneric::impl_postprocess ()
{
   // Linear congruential generator (same as simulator)
   _npr_rand_state = _npr_rand_state * 1103515245 + 12345;
   _npr = _npr_rand_state >> 31;

   _clock.tick ();
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
