/*****************************************************************************

      BoardDaisyField.hpp
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

void  BoardDaisyField::impl_preprocess (Pin pin)
{
   // Topology:
   // - GI: BJT
   // - BX: switch to ground with pull-up
   // => Both are inverted
   _digital_ios [pin.index] = _submodule.read_gpio (pin.pin) == 0;
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisyField::impl_preprocess (AdcPin pin)
{
   auto && u16_ptr = _analog_inputs_u16 [pin.index];
   _analog_inputs [pin.index] = to_float_norm (*u16_ptr);
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisyField::impl_preprocess (AudioInPin pin)
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

void  BoardDaisyField::impl_postprocess (Pin pin)
{
   _submodule.write_gpio (pin.pin, _digital_ios [pin.index]);
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyField::impl_postprocess (DacPin pin)
{
   if (pin.index <= CO2.index)
   {
      _submodule.write_dac (
         SubmoduleDaisySeed::DacPins [pin.index],
         norm_to_u12 (_analog_outputs [pin.index])
      );
   }
   else
   {
      _led_driver.SetLed (
         pin.index - L1.index, _analog_outputs [pin.index]
      );
   }
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyField::impl_postprocess (AudioOutPin pin)
{
   scale (
      _submodule.raw_audio_outputs [pin.index],
      _audio_outputs [pin.index],
      _submodule.gain_output_scaling
   );
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyField::impl_postprocess ()
{
   _led_driver.SwapBuffersAndTransmit ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
