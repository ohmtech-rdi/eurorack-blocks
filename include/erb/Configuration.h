/*****************************************************************************

      Buffer.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstddef>



namespace erb
{



struct Configuration
{
   size_t         nbr_audio_ins = 0;
   size_t         nbr_audio_outs = 0;
   size_t         nbr_buttons = 0;
   size_t         nbr_cv_ins = 0;
   size_t         nbr_cv_outs = 0;
   size_t         nbr_gate_ins = 0;
   size_t         nbr_gate_outs = 0;
   size_t         nbr_leds = 0;
   size_t         nbr_led_bis = 0;
   size_t         nbr_led_rgbs = 0;
   size_t         nbr_pots = 0;
   size_t         nbr_switches = 0;
   size_t         nbr_trims = 0;

   inline size_t  total_nbr_pots () const {
      return nbr_pots + nbr_trims;
   }

   inline size_t  total_nbr_buttons () const {
      return nbr_buttons + 2 * nbr_switches;
   }

   inline size_t  total_nbr_leds () const {
      return nbr_leds + 2 * nbr_led_bis + 3 * nbr_led_rgbs;
   }
};



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
