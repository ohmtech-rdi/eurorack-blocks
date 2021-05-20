/*****************************************************************************

      BoardDaisySeed.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/AudioOut.h"
#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/CvOut.h"
#include "erb/GateIn.h"
#include "erb/GateOut.h"
#include "erb/Led.h"
#include "erb/LedBi.h"
#include "erb/LedRgb.h"
#include "erb/Pot.h"
#include "erb/Switch.h"
#include "erb/detail/fnc.h"

#include <algorithm>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisySeed::impl_preprocess (Pin pin)
{
   _digital_ios [pin.index] = _submodule.read_gpio (
      SubmoduleDaisySeed::Pins [pin.index]
   );
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisySeed::impl_preprocess (AdcPin pin)
{
   auto pin_u16 = (pin.index < 7) ? pin.index : pin.index - 2;

   auto && u16_ptr = _analog_inputs_u16 [pin_u16];
   _analog_inputs [pin.index] = to_float_norm (*u16_ptr);
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisySeed::impl_preprocess (AudioInPin pin)
{
   scale (
      _audio_inputs [pin.index],
      _submodule.raw_audio_inputs [pin.index],
      _submodule.gain_input_scaling
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisySeed::impl_postprocess (Pin pin)
{
   _submodule.write_gpio (
      SubmoduleDaisySeed::Pins [pin.index],
      _digital_ios [pin.index]
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisySeed::impl_postprocess (DacPin pin)
{
   _submodule.write_dac (
      SubmoduleDaisySeed::DacPins [pin.index],
      norm_to_u16 (_analog_outputs [pin.index])
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisySeed::impl_postprocess (AudioOutPin pin)
{
   scale (
      _submodule.raw_audio_outputs [pin.index],
      _audio_outputs [pin.index],
      _submodule.gain_input_scaling
   );
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
