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
      20, 20, 2,  // digital/analog/audio inputs
      2, 22, 2    // digital/analog/audio outputs
   ) {}
   virtual        ~BoardKivu12 () = default;

   // Digital Inputs
   inline const uint8_t &
                  di1 () { return _digital_inputs [0]; }
   inline const uint8_t &
                  di2 () { return _digital_inputs [1]; }
   inline const uint8_t &
                  di3 () { return _digital_inputs [2]; }
   inline const uint8_t &
                  di4 () { return _digital_inputs [3]; }
   inline const uint8_t &
                  di5 () { return _digital_inputs [4]; }
   inline const uint8_t &
                  di6 () { return _digital_inputs [5]; }
   inline const uint8_t &
                  di7 () { return _digital_inputs [6]; }
   inline const uint8_t &
                  di8 () { return _digital_inputs [7]; }
   inline const uint8_t &
                  di9 () { return _digital_inputs [8]; }
   inline const uint8_t &
                  di10 () { return _digital_inputs [9]; }
   inline const uint8_t &
                  di11 () { return _digital_inputs [10]; }
   inline const uint8_t &
                  di12 () { return _digital_inputs [11]; }
   inline const uint8_t &
                  di13 () { return _digital_inputs [12]; }
   inline const uint8_t &
                  di14 () { return _digital_inputs [13]; }
   inline const uint8_t &
                  di15 () { return _digital_inputs [14]; }
   inline const uint8_t &
                  di16 () { return _digital_inputs [15]; }
   inline const uint8_t &
                  di17 () { return _digital_inputs [16]; }
   inline const uint8_t &
                  di18 () { return _digital_inputs [17]; }
   inline const uint8_t &
                  di19 () { return _digital_inputs [18]; }
   inline const uint8_t &
                  di20 () { return _digital_inputs [19]; }

   // Pots
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
                  p9 () { return _analog_inputs [8]; }
   inline const float &
                  p10 () { return _analog_inputs [9]; }
   inline const float &
                  p11 () { return _analog_inputs [10]; }
   inline const float &
                  p12 () { return _analog_inputs [11]; }

   // Gate Outputs
   inline uint8_t &
                  go1 () { return _digital_outputs [0]; }
   inline uint8_t &
                  go2 () { return _digital_outputs [1]; }

   // CV Inputs
   inline const float &
                  ci1 () { return _analog_inputs [12]; }
   inline const float &
                  ci2 () { return _analog_inputs [13]; }
   inline const float &
                  ci3 () { return _analog_inputs [14]; }
   inline const float &
                  ci4 () { return _analog_inputs [15]; }
   inline const float &
                  ci5 () { return _analog_inputs [16]; }
   inline const float &
                  ci6 () { return _analog_inputs [17]; }
   inline const float &
                  ci7 () { return _analog_inputs [18]; }
   inline const float &
                  ci8 () { return _analog_inputs [19]; }

   // CV Outputs
   inline float & co1 () { return _analog_outputs [0]; }
   inline float & co2 () { return _analog_outputs [1]; }

   // LEDs
   inline float & l1 () { return _analog_outputs [2]; }
   inline float & l2 () { return _analog_outputs [3]; }
   inline float & l3 () { return _analog_outputs [4]; }
   inline float & l4 () { return _analog_outputs [5]; }
   inline float & l5 () { return _analog_outputs [6]; }
   inline float & l6 () { return _analog_outputs [7]; }
   inline float & l7 () { return _analog_outputs [8]; }
   inline float & l8 () { return _analog_outputs [9]; }
   inline float & l9 () { return _analog_outputs [10]; }
   inline float & l10 () { return _analog_outputs [11]; }
   inline float & l11 () { return _analog_outputs [12]; }
   inline float & l12 () { return _analog_outputs [13]; }
   inline float & l13 () { return _analog_outputs [14]; }
   inline float & l14 () { return _analog_outputs [15]; }
   inline float & l15 () { return _analog_outputs [16]; }
   inline float & l16 () { return _analog_outputs [17]; }
   inline float & l17 () { return _analog_outputs [18]; }
   inline float & l18 () { return _analog_outputs [19]; }
   inline float & l19 () { return _analog_outputs [20]; }
   inline float & l20 () { return _analog_outputs [21]; }

   // Audio Inputs
   inline const Buffer &
                  ai1 () { return _audio_inputs [0]; }
   inline const Buffer &
                  ai2 () { return _audio_inputs [1]; }

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
                  BoardKivu12 (const BoardKivu12 & rhs) = delete;
                  BoardKivu12 (BoardKivu12 && rhs) = delete;
   BoardKivu12 &  operator = (const BoardKivu12 & rhs) = delete;
   BoardKivu12 &  operator = (BoardKivu12 && rhs) = delete;
   bool           operator == (const BoardKivu12 & rhs) const = delete;
   bool           operator != (const BoardKivu12 & rhs) const = delete;



}; // class BoardKivu12



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
