/*****************************************************************************

      Board.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/Board.h"



namespace erb
{



namespace kivu12
{



class Board
:  daisy::Board
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Board ();
   virtual        ~Board () = default;

   // Pots
   inline uint16_t &
                  p1 () { return *_adc_channels [8]; }
   inline uint16_t &
                  p2 () { return *_adc_channels [9]; }
   inline uint16_t &
                  p2 () { return *_adc_channels [9]; }
   inline uint16_t &
                  p3 () { return *_adc_channels [10]; }
   inline uint16_t &
                  p4 () { return *_adc_channels [11]; }
   inline uint16_t &
                  p5 () { return *_adc_channels [12]; }
   inline uint16_t &
                  p6 () { return *_adc_channels [13]; }
   inline uint16_t &
                  p7 () { return *_adc_channels [14]; }
   inline uint16_t &
                  p8 () { return *_adc_channels [15]; }
   inline uint16_t &
                  p9 () { return *_adc_channels [16]; }
   inline uint16_t &
                  p10 () { return *_adc_channels [17]; }
   inline uint16_t &
                  p11 () { return *_adc_channels [18]; }
   inline uint16_t &
                  p12 () { return *_adc_channels [19]; }

   // CV Inputs
   inline uint16_t &
                  ci1 () { return *_adc_channels [0]; }
   inline uint16_t &
                  ci2 () { return *_adc_channels [1]; }
   inline uint16_t &
                  ci3 () { return *_adc_channels [2]; }
   inline uint16_t &
                  ci4 () { return *_adc_channels [3]; }
   inline uint16_t &
                  ci5 () { return *_adc_channels [4]; }
   inline uint16_t &
                  ci6 () { return *_adc_channels [5]; }
   inline uint16_t &
                  ci7 () { return *_adc_channels [6]; }
   inline uint16_t &
                  ci8 () { return *_adc_channels [7]; }



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
                  Board (const Board & rhs) = delete;
                  Board (Board && rhs) = delete;
   Board &        operator = (const Board & rhs) = delete;
   Board &        operator = (Board && rhs) = delete;
   bool           operator == (const Board & rhs) const = delete;
   bool           operator != (const Board & rhs) const = delete;



}; // class Board



}  // namespace kivu12
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
