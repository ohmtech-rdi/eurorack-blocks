/*****************************************************************************

      BoardKivu12.hpp
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

void  BoardKivu12::impl_preprocess ()
{
   // address was already set 1ms or so, read from gpios

   // GI: BJT => inverted
   _digital_inputs [_b_mux_addr] = !_gpio_inputs [0].read ();
   _digital_inputs [8 + _b_mux_addr] = !_gpio_inputs [1].read ();
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardKivu12::impl_preprocess (GpiPin /* pin */)
{
   // nothing
   // BX are preprocessed in the board level preprocess above
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardKivu12::impl_preprocess (AdcPin pin)
{
   if ((pin.index >= CI1.index) && (pin.index <= CI8.index))
   {
      const auto norm_val = to_float_norm (_adc.read (pin.index));
      // OpAmp in inverter adder with voltage reference
      _analog_inputs [pin.index] = 1.f - norm_val;
   }
   else if ((pin.index >= P1.index) && (pin.index <= P12.index))
   {
      // IN1-X4, IN2-X6, IN3-X7, IN4-X5
      // IN5-X2, IN6-X1, IN7-X0, IN8-X3
      // IN9-X2, IN10-X1, IN11-X0, IN12-X3

      constexpr size_t pot_order [] = {
         8+4, 8+6, 8+7, 8+5, 8+2, 8+1, 8+0, 8+3, // P1..8
         16+2, 16+1, 16+0, 16+3                  // P9..12
      };

      const auto norm_val = to_float_norm (
         _adc.read (pot_order [pin.index - 8])
      );

      _analog_inputs [pin.index] = norm_val;
   }
}



/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

void  BoardKivu12::impl_preprocess (AudioInPin pin)
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

void  BoardKivu12::impl_postprocess (GpoPin pin)
{
   _gpio_outputs [pin.index].write (_digital_outputs [pin.index]);
}



/*
==============================================================================
Name : impl_postprocess
==============================================================================
*/

void  BoardKivu12::impl_postprocess (DacPin pin)
{
   if (pin.index <= CO2.index)
   {
      _dac.write (pin.index, norm_to_u12 (_analog_outputs [pin.index]));
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

void  BoardKivu12::impl_postprocess (AudioOutPin pin)
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

void  BoardKivu12::impl_postprocess ()
{
   _led_driver.SwapBuffersAndTransmit ();

   // set address for next read in next preprocess
   _b_mux_addr = (_b_mux_addr + 1) % 8;
   set_b_mux_addr ();

   // a full cycle has a length of 8, which represent at worst a 8ms latency
   // with the default 48 sample buffer and 48kHz sample rate.
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : set_b_mux_addr
==============================================================================
*/

void  BoardKivu12::set_b_mux_addr ()
{
   _gpio_b_mux [0].write ((_b_mux_addr & 1) != 0);
   _gpio_b_mux [1].write ((_b_mux_addr & 2) != 0);
   _gpio_b_mux [2].write ((_b_mux_addr & 4) != 0);
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
