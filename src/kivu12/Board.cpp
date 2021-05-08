/*****************************************************************************

      Board.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/kivu12/Board.h"



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
   // convert all _adc_vals_u16 to _adc_vals_f
   // NO: actually let the Platform handle that
}



/*
==============================================================================
Name : do_notify_audio_buffer_end
==============================================================================
*/

void  Board::do_notify_audio_buffer_end ()
{
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_adc_channels
==============================================================================
*/

void  Board::init_adc_channels ()
{
   // 8 CVs, 2 Multiplexers = 10 ADC channels
   std::array <AdcChannelConfig, 10> configs;

   configs [0].InitSingle (AdcPin0);
   configs [7].InitSingle (AdcPin7);

   configs [8].InitMux (
      AdcPin8, 8, MuxA, MuxB, MuxC
   );

   configs [9].InitMux (
      AdcPin9, 8, MuxA, MuxB, MuxC
   );

   //_seed.adc.Init (&configs [0], _nbr_adc_channel);
   // could return the list of 20 pointers to uint16_t *?
   // NO: it returns directly the float *
   do_init_adc_channels (configs);

   // rebind CV inputs
   for (size_t i = 0 ; i < 8 ; ++i)
   {
      _adc_vals_u16 [i] = _seed.adc.GetPtr (uint8_t (i));

      auto * ci_ptr = _cv_inputs [i];
      if (ci_ptr != nullptr)
      {
         ci_ptr->impl_bind (_adc_vals_f [i]);
      }
   }

   // rebind pots 1st mux
   for (size_t i = 0 ; i < 8 ; ++i)
   {
      // that's the basic idea, but we have a specific shuffling on pins
      _adc_vals_u16 [8 + i] = _seed.adc.GetMuxPtr (8, i)

      auto * pot_ptr = _pots [i];
      if (pot_ptr != nullptr)
      {
         pot_ptr->impl_bind (_adc_vals_f [8 + i]);
      }
   }

   // rebind pots 2nd mux
   for (size_t i = 0 ; i < 4 ; ++i)
   {
      // that's the basic idea, but we have a specific shuffling on pins
      _adc_vals_u16 [16 + i] = _seed.adc.GetMuxPtr (9, i)

      auto * pot_ptr = _pots [i];
      if (pot_ptr != nullptr)
      {
         pot_ptr->impl_bind (_adc_vals_f [16 + i]);
      }
   }
}



}  // namespace kivu12
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
