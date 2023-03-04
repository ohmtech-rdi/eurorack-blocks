/*****************************************************************************

      DropDsp.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DropDsp.h"



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DropDsp::DropDsp (float sample_freq)
{
   for (auto & filter : _filters)
   {
      filter.set_sample_freq (sample_freq);
      filter.set_type_high_pass ();
   }
}



/*
==============================================================================
Name : toggle_arm
==============================================================================
*/

void  DropDsp::toggle_arm ()
{
   _arm_active = !_arm_active;
}



/*
==============================================================================
Name : tick
==============================================================================
*/

void  DropDsp::sync ()
{
   _active.target = float (_arm_active);
}



/*
==============================================================================
Name : set_mode
==============================================================================
*/

void  DropDsp::set_mode (Mode mode)
{
   _mode.target = float (mode == Mode::Mute);
}



/*
==============================================================================
Name : set_highpass_freq
==============================================================================
*/

void  DropDsp::set_highpass_freq (float freq)
{
   for (auto & filter : _filters) filter.set_freq (freq);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  DropDsp::process (float * const out [], const float * const in [], std::size_t size)
{
   for (auto & filter : _filters) filter.update ();

   for (std::size_t i = 0 ; i < size ; ++i)
   {
      _active.process ();
      _mode.process ();

      for (std::size_t c = 0 ; c < NBR_CHANNELS ; ++c)
      {
         auto & filter = _filters [c];
         auto in_chn = in [c];
         auto out_chn = out [c];

         float in_spl = in_chn [i];
         float & out_spl = out_chn [i];

         auto hp = filter.process (in_spl);
         auto mix = hp * (1.f - _mode);

         out_spl = in_spl + (mix - in_spl) * _active;
      }
   }
}



/*
==============================================================================
Name : state
==============================================================================
*/

DropDsp::State DropDsp::state ()
{
   if (_active.target == float (_arm_active))
   {
      if (_active.target == 0.f)
      {
         return State::Off;
      }
      else
      {
         return State::Active;
      }
   }
   else
   {
      return State::Armed;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
