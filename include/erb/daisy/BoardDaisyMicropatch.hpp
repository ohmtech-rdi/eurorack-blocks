/*****************************************************************************

      BoardDaisyMicropatch.hpp
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

void  BoardDaisyMicropatch::impl_preprocess (GpiPin pin)
{
   if (pin.index == B1.index)
   {
       // Pull-up when NO => inverted
      _digital_inputs [pin.index] = !_gpio_inputs [pin.index].read ();
   }
   else if (pin.index == B2.index)
   {
      bool val = _gpio_inputs [B2.index].read ();
      _digital_inputs [B2.index] = !val;
      _digital_inputs [B3.index] = val;
   }
   else if (pin.index == GI1.index || pin.index == GI2.index)
   {
       // BJT => inverted
      _digital_inputs [pin.index] = !_gpio_inputs [pin.index].read ();
   }
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisyMicropatch::impl_preprocess (AdcPin pin)
{
   const auto norm_val = to_float_norm (_adc.read (pin.index));

   // OpAmp in inverter adder with voltage reference
   const auto inverted = 1.f - norm_val;

   if ((pin.index >= P1.index) && (pin.index <= P4.index))
   {
      // in the pot case, value covers only 0.5 to 1.
      // renormalize it

      _analog_inputs [pin.index] = 2.f * inverted - 1.f;
   }
   else
   {
      _analog_inputs [pin.index] = inverted;
   }
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardDaisyMicropatch::impl_preprocess (AudioInPin pin)
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

void  BoardDaisyMicropatch::impl_postprocess (GpoPin pin)
{
   _gpio_outputs [pin.index].write (_digital_outputs [pin.index]);
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyMicropatch::impl_postprocess (DacPin pin)
{
   _dac.write (pin.index, norm_to_u12 (_analog_outputs [pin.index]));
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardDaisyMicropatch::impl_postprocess (AudioOutPin pin)
{
   scale (
      _submodule.raw_audio_outputs [pin.index],
      _audio_outputs [pin.index],
      _submodule.gain_output_scaling
   );
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
