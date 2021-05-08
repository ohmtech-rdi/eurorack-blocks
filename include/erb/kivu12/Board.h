/*****************************************************************************

      Board.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardBase.h"



namespace erb
{



class ControlInputFloat;

namespace kivu12
{



class Board
:  daisy::BoardBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Board ();
   virtual        ~Board () = default;

   template <typename Pin, Control>
   void           bind (Control & control);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
   // daisy::BoardBase
   virtual void   do_notify_audio_buffer_start () override;
   virtual void   do_notify_audio_buffer_end () override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   void           init_adc_channels ();

   void           map (float & val, ControlInputFloat * control_ptr);

   std::array <uint16_t *, 24>
                  _adcs_u16;
   std::array <float, 20>
                  _adcs;
   std::array <ControlInputFloat *, 20>
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
