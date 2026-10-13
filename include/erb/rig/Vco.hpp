/*****************************************************************************

      Vco.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cassert>
#include <cmath>
#include <numbers>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Vco::bind (Bench & bench, AudioIn & input)
{
   impl_bind (bench, input);

   return impl_connect ();
}



/*
==============================================================================
Name : set_waveform
==============================================================================
*/

void  Vco::set_waveform (Waveform waveform)
{
   _waveform = waveform;
}



/*
==============================================================================
Name : set_frequency
==============================================================================
*/

void  Vco::set_frequency (float frequency_hz)
{
   assert (frequency_hz > 0.f);

   _frequency_hz = frequency_hz;
}



/*
==============================================================================
Name : set_level
==============================================================================
*/

void  Vco::set_level (float level)
{
   assert (level >= 0.f);

   _level = level;
}



/*
==============================================================================
Name : impl_process
==============================================================================
*/

void  Vco::impl_process ()
{
   auto & buffer = impl_input_audio (0);

   const double increment = double (_frequency_hz) / double (erb_SAMPLE_RATE);

   for (auto & sample : buffer)
   {
      switch (_waveform)
      {
      case Waveform::Sine:
         sample = _level * float (std::sin (_phase * 2.0 * std::numbers::pi));
         break;
      }

      _phase += increment;
      if (_phase >= 1.0) _phase -= 1.0;
   }
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Vco::name () const
{
   return "Vco";
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
