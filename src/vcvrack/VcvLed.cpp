/*****************************************************************************

      VcvLed.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvLed.h"

#include "erb/vcvrack/VcvModule.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvLed::VcvLed (VcvModule & module, const VcvPin & /* pin */)
:  VcvLightBase (module)
,  _module (module)
{
}



/*
==============================================================================
Name : on
==============================================================================
*/

void  VcvLed::on (bool state)
{
   _mode = Mode::Constant;

   _current = state;
}



/*
==============================================================================
Name : off
==============================================================================
*/

void  VcvLed::off ()
{
   _mode = Mode::Constant;

   _current = false;
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

void  VcvLed::pulse (std::chrono::milliseconds duration)
{
   _mode = Mode::Pulse;
   _start = _module.now_ms ();
   _duration = uint64_t (duration.count ());

   _current = true;
}



/*
==============================================================================
Name : blink
==============================================================================
*/

void  VcvLed::blink (std::chrono::milliseconds half_period)
{
   _mode = Mode::Blink;
   _start = _module.now_ms ();
   _duration = uint64_t (half_period.count ());

   _current = true;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_notify_audio_buffer_start
==============================================================================
*/

void  VcvLed::impl_notify_audio_buffer_start ()
{
   if (_mode == Mode::Pulse)
   {
      auto now = _module.now_ms ();
      auto elapsed = now - _start;
      _current = elapsed < _duration;
   }
   else if (_mode == Mode::Blink)
   {
      auto now = _module.now_ms ();
      auto elapsed = now - _start;
      _current = ((elapsed / _duration) % 2) == 1;
   }

   set_norm_val (float (_current));
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
