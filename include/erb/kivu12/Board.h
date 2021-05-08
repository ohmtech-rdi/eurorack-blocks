/*****************************************************************************

      Board.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardBase.h"



namespace erb
{



class ControlInputNormFloat;

namespace kivu12
{



class Board
:  daisy::BoardBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Board ();
   virtual        ~Board () = default;

   void           bind (PinCi pin, ControlInputNormFloat & control);
   void           bind (PinP pin, ControlInputNormFloat & control);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
   // daisy::BoardBase
   virtual void   do_notify_audio_buffer_start () override;
   virtual void   do_notify_audio_buffer_end () override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_ADC_CHANNELS = 20 };

   void           init_adc_channels ();

   void           map (const float & val, ControlInputNormFloat * control_ptr);

   std::array <uint16_t *, NBR_ADC_CHANNELS>
                  _adcs_u16;
   std::array <float, NBR_ADC_CHANNELS>
                  _adcs;
   std::array <ControlInputNormFloat *, NBR_ADC_CHANNELS>
                  _cifs;



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
