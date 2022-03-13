/*****************************************************************************

      BoardKivu12.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"



namespace erb
{



class BoardKivu12
:  public BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardKivu12 () : BoardGeneric (
      16, 20, 2,  // digital/analog/audio inputs
      2, 22, 2    // digital/analog/audio outputs
   ) {}
   virtual        ~BoardKivu12 () override = default;

   // Digital Inputs
   inline const uint8_t &
                  b (size_t i) { return _digital_inputs [i]; }

   // Analog Inputs
   inline const float &
                  ci (size_t i) { return _analog_inputs [i]; }
   inline const float &
                  p (size_t i) { return _analog_inputs [i + 8]; }

   // Audio Inputs
   inline const Buffer &
                  ai (size_t i) { return _audio_inputs [i]; }

   // Digital Outputs
   inline uint8_t &
                  go (size_t i) { return _digital_outputs [i]; }

   // Analog Outputs
   inline float & co (size_t i) { return _analog_outputs [i]; }
   inline float & l (size_t i) { return _analog_outputs [i + 2]; }

   // Audio Outputs
   inline Buffer &
                  ao (size_t i) { return _audio_outputs [i]; }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardKivu12 (const BoardKivu12 & rhs) = delete;
                  BoardKivu12 (BoardKivu12 && rhs) = delete;
   BoardKivu12 &  operator = (const BoardKivu12 & rhs) = delete;
   BoardKivu12 &  operator = (BoardKivu12 && rhs) = delete;
   bool           operator == (const BoardKivu12 & rhs) const = delete;
   bool           operator != (const BoardKivu12 & rhs) const = delete;



}; // class BoardKivu12



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
