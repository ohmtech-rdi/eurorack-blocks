/*****************************************************************************

      BoardKivu12.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardDaisySeed.h"



namespace erb
{



class BoardKivu12
:  BoardDaisySeed
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardKivu12 ();
   virtual        ~BoardKivu12 () = default;

   // Pots
   inline const uint16_t &
                  p1 () { return *_adc_channels [8]; }
   inline const uint16_t &
                  p2 () { return *_adc_channels [9]; }
   inline const uint16_t &
                  p2 () { return *_adc_channels [9]; }
   inline const uint16_t &
                  p3 () { return *_adc_channels [10]; }
   inline const uint16_t &
                  p4 () { return *_adc_channels [11]; }
   inline const uint16_t &
                  p5 () { return *_adc_channels [12]; }
   inline const uint16_t &
                  p6 () { return *_adc_channels [13]; }
   inline const uint16_t &
                  p7 () { return *_adc_channels [14]; }
   inline const uint16_t &
                  p8 () { return *_adc_channels [15]; }
   inline const uint16_t &
                  p9 () { return *_adc_channels [16]; }
   inline const uint16_t &
                  p10 () { return *_adc_channels [17]; }
   inline const uint16_t &
                  p11 () { return *_adc_channels [18]; }
   inline const uint16_t &
                  p12 () { return *_adc_channels [19]; }

   // CV Inputs
   inline const uint16_t &
                  ci1 () { return *_adc_channels [0]; }
   inline const uint16_t &
                  ci2 () { return *_adc_channels [1]; }
   inline const uint16_t &
                  ci3 () { return *_adc_channels [2]; }
   inline const uint16_t &
                  ci4 () { return *_adc_channels [3]; }
   inline const uint16_t &
                  ci5 () { return *_adc_channels [4]; }
   inline const uint16_t &
                  ci6 () { return *_adc_channels [5]; }
   inline const uint16_t &
                  ci7 () { return *_adc_channels [6]; }
   inline const uint16_t &
                  ci8 () { return *_adc_channels [7]; }

   // Audio Inputs
   inline const Buffer &
                  ai1 () { return *_audio_buffer_inputs [0]; }
   inline const Buffer &
                  ai2 () { return *_audio_buffer_inputs [1]; }

   // Audio Outputs
   inline Buffer &
                  ao1 () { return *_audio_buffer_ouputs [0]; }
   inline Buffer &
                  ao2 () { return *_audio_buffer_outputs [1]; }



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_notify_audio_buffer_start ();
   void           impl_notify_audio_buffer_end ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_ADC_CHANNELS = 20 };
   enum {         NBR_AUDIO_INPUTS = 2 };
   enum {         NBR_AUDIO_OUTPUTS = 2 };

   void           init_adc_channels ();
   void           init_audio ();

   // ADCs
   std::array <uint16_t *, NBR_ADC_CHANNELS>
                  _adc_channels = {};



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardKivu12 (const BoardKivu12 & rhs) = delete;
                  BoardKivu12 (BoardKivu12 && rhs) = delete;
   BoardKivu12 &        operator = (const BoardKivu12 & rhs) = delete;
   BoardKivu12 &        operator = (BoardKivu12 && rhs) = delete;
   bool           operator == (const BoardKivu12 & rhs) const = delete;
   bool           operator != (const BoardKivu12 & rhs) const = delete;



}; // class BoardKivu12



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
