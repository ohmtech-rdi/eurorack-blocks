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
      3, 12, 2,  // digital/analog/audio inputs
      1, 10, 2    // digital/analog/audio outputs
   ) {}
   virtual        ~BoardDaisyField () override = default;

   // Digital Inputs
   inline const uint8_t &
                  gpi (size_t i) { return _digital_inputs [i]; }

   // Analog Inputs
   inline const float &
                  adc (size_t i) { return _analog_inputs [i]; }

   // Audio Inputs
   inline const Buffer &
                  audioin (size_t i) { return _audio_inputs [i]; }

   // Digital Outputs
   inline uint8_t &
                  gpo (size_t i) { return _digital_outputs [i]; }

   // Analog Outputs
   inline float & dac (size_t i) { return _analog_outputs [i]; }

   // Audio Outputs
   inline Buffer &
                  audioout (size_t i) { return _audio_outputs [i]; }



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
