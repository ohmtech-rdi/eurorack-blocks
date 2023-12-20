/*****************************************************************************

      BoardSeed2DfmEvalEuro.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"



namespace erb
{



class BoardSeed2DfmEvalEuro
:  public BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardSeed2DfmEvalEuro () : BoardGeneric (
      7, 7, 4, // digital/analog/audio inputs
      0, 2, 4  // digital/analog/audio outputs
   ) {}
   virtual        ~BoardSeed2DfmEvalEuro () override = default;

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

   // Display
   inline typename erb::FormatSsd130x <128, 64>::Storage &
                  oled () { return _oled; }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   erb::FormatSsd130x <128, 64>::Storage
                  _oled;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardSeed2DfmEvalEuro (const BoardSeed2DfmEvalEuro & rhs) = delete;
                  BoardSeed2DfmEvalEuro (BoardSeed2DfmEvalEuro && rhs) = delete;
   BoardSeed2DfmEvalEuro &
                  operator = (const BoardSeed2DfmEvalEuro & rhs) = delete;
   BoardSeed2DfmEvalEuro &
                  operator = (BoardSeed2DfmEvalEuro && rhs) = delete;
   bool           operator == (const BoardSeed2DfmEvalEuro & rhs) const = delete;
   bool           operator != (const BoardSeed2DfmEvalEuro & rhs) const = delete;



}; // class BoardSeed2DfmEvalEuro



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
