// BoardFirmware.hpp

#pragma once


void  Board::impl_preprocess (AdcPin pin)
{
   const auto norm_val = erb::to_float_norm (
      _adc.read (pin.index)
   );

   _analog_inputs [pin.index] = norm_val;
}


void  Board::impl_preprocess (AudioInPin pin)
{
   erb::scale (
      _audio_inputs [pin.index],
      _submodule.raw_audio_inputs [pin.index],
      _submodule.gain_input_scaling
   );
}


void  Board::impl_postprocess (AudioOutPin pin)
{
   erb::scale (
      _submodule.raw_audio_outputs [pin.index],
      _audio_outputs [pin.index],
      _submodule.gain_output_scaling
   );
}
