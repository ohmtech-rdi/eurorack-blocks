/*****************************************************************************

      BoardMega.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #error Board mega doesn't support Daisy firmware builds
#endif

#include "erb/vcvrack/BoardGeneric.h"



namespace erb
{



class BoardMega
:  public BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardMega () : BoardGeneric (
      128, 128, 4,   // digital/analog/audio inputs
      128, 128, 4    // digital/analog/audio outputs
   ) {}
   virtual        ~BoardMega () override = default;

   // Digital Inputs
   inline const uint8_t &
                  dii (size_t i) { return _digital_inputs [i]; }

   // Analog Inputs
   inline const float &
                  ani (size_t i) { return _analog_inputs [i]; }

   // Audio Inputs
   inline const Buffer &
                  aui (size_t i) { return _audio_inputs [i]; }

   // Digital Outputs
   inline uint8_t &
                  dio (size_t i) { return _digital_outputs [i]; }

   // Analog Outputs
   inline float & ano (size_t i) { return _analog_outputs [i]; }

   // Audio Outputs
   inline Buffer &
                  auo (size_t i) { return _audio_outputs [i]; }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardMega (const BoardMega & rhs) = delete;
                  BoardMega (BoardMega && rhs) = delete;
   BoardMega &    operator = (const BoardMega & rhs) = delete;
   BoardMega &    operator = (BoardMega && rhs) = delete;
   bool           operator == (const BoardMega & rhs) const = delete;
   bool           operator != (const BoardMega & rhs) const = delete;



}; // class BoardMega



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
