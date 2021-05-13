/*****************************************************************************

      Board.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/kivu12/Board.h"

#include "erb/detail/ControlInputNormFloat.h"



namespace erb
{
namespace kivu12
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Board::Board ()
{
   init_adc_channels ();
   init_audio ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : do_notify_audio_buffer_start
==============================================================================
*/

void  Board::do_notify_audio_buffer_start ()
{
   // convert all platform inputs to control inputs

   for (size_t i = 0 ; i < _adcs.size () ; ++i)
   {
      constexpr float scale = 1.f / 65535.f;
      _adcs [i] = *_adcs_u16 [i] * scale;
   }
}



/*
==============================================================================
Name : do_notify_audio_buffer_end
==============================================================================
*/

void  Board::do_notify_audio_buffer_end ()
{
   // convert all control outputs to platform outputs 
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_adc_channels
==============================================================================
*/

void  Board::init_adc_channels ()
{
   _adcs_u16 = do_init_adc_channels <NBR_ADC_CHANNELS> ({
      // 8 CVs
      {AdcPin1}, {AdcPin2}, {AdcPin3}, {AdcPin4},
      {AdcPin5}, {AdcPin6}, {AdcPin7}, {AdcPin8},
      // 12 Pots
      {AdcPin9, 8, Pin19, Pin20, Pin21},
      {AdcPin10, 8, Pin19, Pin20, Pin21} // 4 last ones ignored
   });

   for (size_t i = 0 ; i < NBR_ADC_CHANNELS ; ++i)
   {
      map (_adcs [i], _cis [i]);
   }
}



/*
==============================================================================
Name : init_audio
==============================================================================
*/

void  Board::init_audio ()
{
   for (size_t i = 0 ; i < NBR_AUDIO_INPUTS ; ++i)
   {
   }
}



}  // namespace kivu12
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
