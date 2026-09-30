/*****************************************************************************

      Light.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cassert>
#include <cstdio>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : ctor
==============================================================================
*/

Light::Light (Setup setup)
:  Instrument (setup)
{
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Light::bind (Bench & bench, Led <PinType::Gpio> & led)
{
   _kind = SlotKind::Digital;
   impl_bind (bench, led);

   return impl_connect ();
}



/*
==============================================================================
Name : bind
==============================================================================
*/

Connection  Light::bind (Bench & bench, Led <PinType::Pwm> & led)
{
   _kind = SlotKind::Analog;
   impl_bind (bench, led);

   return impl_connect ();
}



/*
==============================================================================
Name : read
==============================================================================
*/

Light::Reading Light::read () const
{
   Reading ret;

   if (_kind == SlotKind::Digital)
   {
      for (auto level : impl_window_digital (0))
      {
         ret.push_back (level ? 1.f : 0.f);
      }
   }
   else
   {
      const auto window = impl_window_analog (0);
      ret.assign (window.begin (), window.end ());
   }

   return ret;
}



/*
==============================================================================
Name : check_off
==============================================================================
*/

void  Light::check_off (std::source_location sloc) const
{
   const auto summary = summarize (read ());
   const bool ok = summary.nbr_lit == 0;

   if (!ok) report ("off", summary, sloc);

   assert (ok);
}



/*
==============================================================================
Name : check_on
==============================================================================
*/

void  Light::check_on (std::source_location sloc) const
{
   const auto summary = summarize (read ());
   const bool ok = summary.nbr_lit == summary.nbr_blocks;

   if (!ok) report ("on", summary, sloc);

   assert (ok);
}



/*
==============================================================================
Name : check_blinking
==============================================================================
*/

void  Light::check_blinking (std::source_location sloc) const
{
   const auto summary = summarize (read ());
   const bool ok = summary.nbr_transitions >= 3;

   if (!ok) report ("blinking", summary, sloc);

   assert (ok);
}



/*
==============================================================================
Name : name
==============================================================================
*/

const char *   Light::name () const
{
   return "Light";
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : summarize
==============================================================================
*/

Light::Summary Light::summarize (const Reading & reading)
{
   Summary ret;
   ret.nbr_blocks = reading.size ();

   bool lit = false;

   for (std::size_t i = 0 ; i < reading.size () ; ++i)
   {
      const bool now = reading [i] > 0.f;

      if (now) ++ret.nbr_lit;
      if ((i > 0) && (now != lit)) ++ret.nbr_transitions;

      lit = now;
   }

   return ret;
}



/*
==============================================================================
Name : report
==============================================================================
*/

void  Light::report (const char * expected, const Summary & summary, std::source_location sloc) const
{
   std::fprintf (
      stderr,
      "check at %s:%u: Light on %s expected %s, lit %zu of %zu blocks, %zu transitions\n",
      sloc.file_name (), unsigned (sloc.line ()), impl_channel_name (0),
      expected, summary.nbr_lit, summary.nbr_blocks, summary.nbr_transitions
   );
   std::fflush (stderr);
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
