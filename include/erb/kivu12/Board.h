/*****************************************************************************

      Board.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardBase.h"



namespace erb
{
namespace kivu12
{



struct L1 : TagLed {};

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