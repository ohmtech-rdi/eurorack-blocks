/*****************************************************************************

      BoardKivu12.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/BoardDaisySeed.h"

#include <array>



namespace erb
{



class BoardKivu12
:  public BoardDaisySeed
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardKivu12 ();
   virtual        ~BoardKivu12 () = default;

   // Digital Inputs
   inline const uint8_t &
                  d1 () { return _digital_inputs [0]; }
   inline const uint8_t &
                  d2 () { return _digital_inputs [1]; }
   inline const uint8_t &
                  d3 () { return _digital_inputs [2]; }
   inline const uint8_t &
                  d4 () { return _digital_inputs [3]; }
   inline const uint8_t &
                  d5 () { return _digital_inputs [4]; }
   inline const uint8_t &
                  d6 () { return _digital_inputs [5]; }
   inline const uint8_t &
                  d7 () { return _digital_inputs [6]; }
   inline const uint8_t &
                  d8 () { return _digital_inputs [7]; }
   inline const uint8_t &
                  d9 () { return _digital_inputs [8]; }
   inline const uint8_t &
                  d10 () { return _digital_inputs [9]; }
   inline const uint8_t &
                  d11 () { return _digital_inputs [10]; }
   inline const uint8_t &
                  d12 () { return _digital_inputs [11]; }
   inline const uint8_t &
                  d13 () { return _digital_inputs [12]; }
   inline const uint8_t &
                  d14 () { return _digital_inputs [13]; }
   inline const uint8_t &
                  d15 () { return _digital_inputs [14]; }
   inline const uint8_t &
                  d16 () { return _digital_inputs [15]; }
   inline const uint8_t &
                  d17 () { return _digital_inputs [16]; }
   inline const uint8_t &
                  d18 () { return _digital_inputs [17]; }
   inline const uint8_t &
                  d19 () { return _digital_inputs [18]; }
   inline const uint8_t &
                  d20 () { return _digital_inputs [19]; }

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



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_preprocess ();
   void           impl_postprocess ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum
   {
                  NBR_DIGITAL_INPUTS = 20,
                  NBR_ANALOG_INPUTS = 20,
                  NBR_AUDIO_INPUTS = 2,

                  NBR_DIGITAL_OUTPUTS = 2,
                  NBR_ANALOG_OUTPUTS = 22,
                  NBR_AUDIO_OUTPUTS = 2,

                  NBR_PCA9685_DRIVERS = 2,
   };

   using LedDriver = daisy::LedDriverPca9685 <NBR_PCA9685_DRIVERS>;

   void           init_digital_inputs ();
   void           init_analog_inputs ();

   void           init_digital_outputs ();
   void           init_analog_outputs ();

   std::array <uint8_t, NBR_DIGITAL_INPUTS>
                  _digital_inputs = {};
   std::array <float, NBR_ANALOG_INPUTS>
                  _analog_inputs = {};
   std::array <Buffer, NBR_AUDIO_INPUTS>
                  _audio_inputs = {};

   std::array <uint8_t, NBR_DIGITAL_OUTPUTS>
                  _digital_outputs = {};
   std::array <float, NBR_ANALOG_OUTPUTS>
                  _analog_outputs = {};
   std::array <Buffer, NBR_AUDIO_OUTPUTS>
                  _audio_outputs = {};

   std::array <uint16_t *, NBR_ANALOG_INPUTS>
                  _adc16_channels = {};

   LedDriver      _led_driver;



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
