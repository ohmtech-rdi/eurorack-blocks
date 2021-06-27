/*****************************************************************************

      BoardDaisyMicropatch.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"



namespace erb
{



class BoardDaisyMicropatch
:  public BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardDaisyMicropatch () : BoardGeneric (
      5, 8, 2, // digital/analog/audio inputs
      2, 2, 2  // digital/analog/audio outputs
   ) {}
   virtual        ~BoardDaisyMicropatch () override = default;

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

   // SD
   inline Filesystem &
                  sd () { return _sd; }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardDaisyMicropatch (const BoardDaisyMicropatch & rhs) = delete;
                  BoardDaisyMicropatch (BoardDaisyMicropatch && rhs) = delete;
   BoardDaisyMicropatch &
                  operator = (const BoardDaisyMicropatch & rhs) = delete;
   BoardDaisyMicropatch &
                  operator = (BoardDaisyMicropatch && rhs) = delete;
   bool           operator == (const BoardDaisyMicropatch & rhs) const = delete;
   bool           operator != (const BoardDaisyMicropatch & rhs) const = delete;



}; // class BoardDaisyMicropatch



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
