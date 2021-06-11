/*****************************************************************************

      DacDaisy.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

erb_DISABLE_WARNINGS_DAISY
#include "per/dac.h"
erb_RESTORE_WARNINGS



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DacDaisy::DacDaisy (daisy::DacHandle & dac, std::initializer_list <Channel> channels)
:  _dac (dac)
{
   daisy::DacHandle::Channel channel = daisy::DacHandle::Channel::BOTH;

   if (channels.size () == 1)
   {
      auto index = *channels.begin ();
      channel
         = (index == 0)
         ? daisy::DacHandle::Channel::ONE
         : daisy::DacHandle::Channel::TWO;
   }

   daisy::DacHandle::Config cfg;
   cfg.bitdepth = daisy::DacHandle::BitDepth::BITS_12;
   cfg.buff_state = daisy::DacHandle::BufferState::ENABLED;
   cfg.mode = daisy::DacHandle::Mode::POLLING;
   cfg.chn = channel;

   _dac.Init (cfg);
}



/*
==============================================================================
Name : write
==============================================================================
*/

void  DacDaisy::write (size_t index, uint16_t val)
{
   auto channel
      = (index == 0)
      ? daisy::DacHandle::Channel::ONE
      : daisy::DacHandle::Channel::TWO;

   _dac.WriteValue (channel, val);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
