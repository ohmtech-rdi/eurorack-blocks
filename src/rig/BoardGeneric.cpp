/*****************************************************************************

      BoardGeneric.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/BoardGeneric.h"

#include "erb/detail/ModuleBoard.h"

#include <cassert>
#include <functional>



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

   for (auto & c : _digital_measurements) c.measurement->impl_start ();
   for (auto & c : _analog_measurements) c.measurement->impl_start ();
   for (auto & c : _audio_measurements) c.measurement->impl_start ();
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



/*
==============================================================================
Name : press
Note :
   Firmware sees 'pressed' and 'held', button stays pressed
==============================================================================
*/

void  BoardGeneric::press (Button & button)
{
   assert (_boot_flag);

   impl_digital_slot (button.impl_data) = 1;
   impl_steps (DebounceFrames);
}



/*
==============================================================================
Name : release
==============================================================================
*/

void  BoardGeneric::release (Button & button)
{
   assert (_boot_flag);

   impl_digital_slot (button.impl_data) = 0;
   impl_steps (DebounceFrames);
}



/*
==============================================================================
Name : click
==============================================================================
*/

void  BoardGeneric::click (Button & button)
{
   press (button);
   release (button);
}



/*
==============================================================================
Name : long_press
==============================================================================
*/

void  BoardGeneric::long_press (Button & button, SystemClockVirtual::duration duration)
{
   press (button);
   run (duration);
   release (button);
}



/*
==============================================================================
Name : trigger
==============================================================================
*/

void  BoardGeneric::trigger (GateIn & gate)
{
   assert (_boot_flag);

   auto & data = impl_digital_slot (gate.impl_data);

   data = 1;
   impl_steps (TriggerFrames);
   data = 0;
   impl_steps (1);
}



/*
==============================================================================
Name : set
==============================================================================
*/

void  BoardGeneric::set (GateIn & gate, bool state)
{
   assert (_boot_flag);

   impl_digital_slot (gate.impl_data) = state ? 1 : 0;
}



/*
==============================================================================
Name : control_name
Description :
   Returns erbui name of a control mostly for logs
==============================================================================
*/

const char *  BoardGeneric::control_name (const void * control_ptr) const
{
   assert (_boot_flag);

   return _glue.control_name (control_ptr);
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
   assert (glue.control_name);

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
Name : impl_steps
==============================================================================
*/

void  BoardGeneric::impl_steps (std::size_t nbr_steps)
{
   for (std::size_t i = 0 ; i < nbr_steps ; ++i)
   {
      impl_step ();
   }
}



/*
==============================================================================
Name : impl_digital_slot
Description :
   'data' is the 'impl_data' of the control that is const, and in the
   vector.
==============================================================================
*/

uint8_t &   BoardGeneric::impl_digital_slot (const uint8_t & data)
{
   return _digital_inputs [impl_slot_index (_digital_inputs, data)];
}



/*
==============================================================================
Name : impl_analog_slot
==============================================================================
*/

float &  BoardGeneric::impl_analog_slot (const float & data)
{
   return _analog_inputs [impl_slot_index (_analog_inputs, data)];
}



/*
==============================================================================
Name : impl_measurement_output_name
Description :
   The erbui name of the output a measurement is connected to
   or nullptr when it is not connected.
==============================================================================
*/

const char *  BoardGeneric::impl_measurement_output_name (const MeasurementBase & measurement) const
{
   const void * control_ptr = nullptr;

   for (const auto & c : _digital_measurements)
      if (c.measurement == &measurement) control_ptr = c.control_ptr;

   for (const auto & c : _analog_measurements)
      if (c.measurement == &measurement) control_ptr = c.control_ptr;

   for (const auto & c : _audio_measurements)
      if (c.measurement == &measurement) control_ptr = c.control_ptr;

   if (control_ptr == nullptr) return nullptr;

   return _boot_flag ? _glue.control_name (control_ptr) : "";
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

   if (_start_flag)
   {
      for (auto & c : _digital_measurements)
         c.measurement->impl_feed (_digital_outputs [c.index]);

      for (auto & c : _analog_measurements)
         c.measurement->impl_feed (_analog_outputs [c.index]);

      for (auto & c : _audio_measurements)
         c.measurement->impl_feed (_audio_outputs [c.index]);
   }
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
