/*****************************************************************************

      BoardDefault.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #error BoardDefault does not support Daisy firmware builds
#endif

#include "erb/vcvrack/BoardGeneric.h"



namespace erb
{



class BoardDefault
:  public BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardDefault () : BoardGeneric (
      128, 128, 4,   // digital/analog/audio inputs
      128, 128, 4    // digital/analog/audio outputs
   ) {}
   virtual        ~BoardDefault () override = default;

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
                  BoardDefault (const BoardDefault & rhs) = delete;
                  BoardDefault (BoardDefault && rhs) = delete;
   BoardDefault &    operator = (const BoardDefault & rhs) = delete;
   BoardDefault &    operator = (BoardDefault && rhs) = delete;
   bool           operator == (const BoardDefault & rhs) const = delete;
   bool           operator != (const BoardDefault & rhs) const = delete;



}; // class BoardDefault



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
