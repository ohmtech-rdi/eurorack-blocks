/*****************************************************************************

      BoardDaisySeed.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardDaisySeed.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
Description :

   !!! This board is not meant to be used !!!
   !!! it is for development testing only !!!

   Setup a predefined configuration for Daisy Seed submodule:
   - 12 digital inputs
   - 10 analog inputs
   - 2 audio inputs
   - 7 digital outputs
   - 2 analog outputs
   - 2 audio outputs
==============================================================================
*/

BoardDaisySeed::BoardDaisySeed ()
{
   // no init needed for audio inputs

   _submodule.init_dac_channels ({
      SubmoduleDaisySeed::DacPin0,
      SubmoduleDaisySeed::DacPin1,
   });

   // no init needed for audio outputs
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
