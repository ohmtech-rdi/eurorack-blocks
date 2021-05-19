/*****************************************************************************

      BoardDaisyField.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"



namespace erb
{



class BoardDaisyField
:  public BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardDaisyField () : BoardGeneric (
      3, 12, 2,   // digital/analog/audio inputs
      1, 10, 2    // digital/analog/audio outputs
   ) {}
   virtual        ~BoardDaisyField () = default;

   // Digital Inputs
   inline const uint8_t &
                  b1 () { return _digital_inputs [0]; }
   inline const uint8_t &
                  b2 () { return _digital_inputs [1]; }
   inline const uint8_t &
                  gi () { return _digital_inputs [2]; }

   // Analog Inputs
   inline const float &
                  p1 () { return _analog_inputs [0]; }
   inline const float &
                  p2 () { return _analog_inputs [1]; }
   inline const float &
                  p3 () { return _analog_inputs [2]; }
   inline const float &
                  p4 () { return _analog_inputs [3]; }
   inline const float &
                  p5 () { return _analog_inputs [4]; }
   inline const float &
                  p6 () { return _analog_inputs [5]; }
   inline const float &
                  p7 () { return _analog_inputs [6]; }
   inline const float &
                  p8 () { return _analog_inputs [7]; }
   inline const float &
                  ci1 () { return _analog_inputs [8]; }
   inline const float &
                  ci2 () { return _analog_inputs [9]; }
   inline const float &
                  ci3 () { return _analog_inputs [10]; }
   inline const float &
                  ci4 () { return _analog_inputs [11]; }

   // Audio Inputs
   inline const Buffer &
                  ai1 () { return _audio_inputs [0]; }
   inline const Buffer &
                  ai2 () { return _audio_inputs [1]; }

   // Digital Outputs
   inline uint8_t &
                  go () { return _digital_outputs [0]; }

   // Analog Outputs
   inline float & co1 () { return _analog_outputs [0]; }
   inline float & co2 () { return _analog_outputs [1]; }
   inline float & l1 () { return _analog_outputs [2]; }
   inline float & l2 () { return _analog_outputs [3]; }
   inline float & l3 () { return _analog_outputs [4]; }
   inline float & l4 () { return _analog_outputs [5]; }
   inline float & l5 () { return _analog_outputs [6]; }
   inline float & l6 () { return _analog_outputs [7]; }
   inline float & l7 () { return _analog_outputs [8]; }
   inline float & l8 () { return _analog_outputs [9]; }

   // Audio Outputs
   inline Buffer &
                  ao1 () { return _audio_outputs [0]; }
   inline Buffer &
                  ao2 () { return _audio_outputs [1]; }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardDaisyField (const BoardDaisyField & rhs) = delete;
                  BoardDaisyField (BoardDaisyField && rhs) = delete;
   BoardDaisyField &
                  operator = (const BoardDaisyField & rhs) = delete;
   BoardDaisyField &
                  operator = (BoardDaisyField && rhs) = delete;
   bool           operator == (const BoardDaisyField & rhs) const = delete;
   bool           operator != (const BoardDaisyField & rhs) const = delete;



}; // class BoardDaisyField



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
