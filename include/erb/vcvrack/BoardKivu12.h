/*****************************************************************************

      BoardKivu12.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"

#include <array>



namespace rack
{
namespace engine
{
struct Param;
struct Input;
struct Output;
struct Light;
}
}

namespace erb
{



class BoardKivu12
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardKivu12 ();
   virtual        ~BoardKivu12 () = default;

   size_t         nbr_params () const;
   size_t         nbr_inputs () const;
   size_t         nbr_outputs () const;
   size_t         nbr_lights () const;

   void           impl_bind (size_t idx, rack::engine::Param & param);
   void           impl_bind (size_t idx, rack::engine::Input & input);
   void           impl_bind (size_t idx, rack::engine::Output & output);
   void           impl_bind (size_t idx, rack::engine::Light & light);

   template <typename F>
   void           bind_process (F && f);

   // Pots
   inline const uint16_t &
                  p1 () { return _adc16_channels [8]; }
   inline const uint16_t &
                  p2 () { return _adc16_channels [9]; }
   inline const uint16_t &
                  p3 () { return _adc16_channels [10]; }
   inline const uint16_t &
                  p4 () { return _adc16_channels [11]; }
   inline const uint16_t &
                  p5 () { return _adc16_channels [12]; }
   inline const uint16_t &
                  p6 () { return _adc16_channels [13]; }
   inline const uint16_t &
                  p7 () { return _adc16_channels [14]; }
   inline const uint16_t &
                  p8 () { return _adc16_channels [15]; }
   inline const uint16_t &
                  p9 () { return _adc16_channels [16]; }
   inline const uint16_t &
                  p10 () { return _adc16_channels [17]; }
   inline const uint16_t &
                  p11 () { return _adc16_channels [18]; }
   inline const uint16_t &
                  p12 () { return _adc16_channels [19]; }

   // CV Inputs
   inline const uint16_t &
                  ci1 () { return _adc16_channels [0]; }
   inline const uint16_t &
                  ci2 () { return _adc16_channels [1]; }
   inline const uint16_t &
                  ci3 () { return _adc16_channels [2]; }
   inline const uint16_t &
                  ci4 () { return _adc16_channels [3]; }
   inline const uint16_t &
                  ci5 () { return _adc16_channels [4]; }
   inline const uint16_t &
                  ci6 () { return _adc16_channels [5]; }
   inline const uint16_t &
                  ci7 () { return _adc16_channels [6]; }
   inline const uint16_t &
                  ci8 () { return _adc16_channels [7]; }

   // Audio Inputs
   inline const Buffer &
                  ai1 () { return _audio_buffer_inputs [0]; }
   inline const Buffer &
                  ai2 () { return _audio_buffer_inputs [1]; }

   // Audio Outputs
   inline Buffer &
                  ao1 () { return _audio_buffer_outputs [0]; }
   inline Buffer &
                  ao2 () { return _audio_buffer_outputs [1]; }



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_notify_audio_buffer_start ();
   void           impl_notify_audio_buffer_end ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum
   {
                  NBR_POTS = 12,          // Pot, Trim
                  NBR_LEDS = 20,          // Led, LedBi, LedRgb
                  NBR_BUTTONS = 20,       // Button, GateIn
                  NBR_CV_INPUTS = 8,      // CvIn
                  NBR_GATE_OUTPUTS = 2,   // GateOut
                  NBR_AUDIO_INPUTS = 2,   // AudioIn
                  NBR_AUDIO_OUTPUTS = 2,  // AudioOut

                  NBR_PARAMS = NBR_POTS + NBR_BUTTONS,
                  NBR_INPUTS = NBR_CV_INPUTS + NBR_AUDIO_INPUTS,
                  NBR_OUTPUTS = NBR_GATE_OUTPUTS + NBR_AUDIO_OUTPUTS,
                  NBR_LIGHTS = NBR_LEDS,

                  NBR_ADC_CHANNELS = NBR_POTS + NBR_CV_INPUTS,
   };

   void           convert_to_adc16_channels ();
   void           convert_to_buttons ();
   void           convert_from_gate_outputs ();
   void           convert_from_leds ();

   std::array <rack::engine::Param *, NBR_PARAMS>
                  _params;                         // Pots | Buttons
   std::array <rack::engine::Input *, NBR_INPUTS>
                  _inputs;                         // Cv | Audio Input
   std::array <rack::engine::Output *, NBR_OUTPUTS>
                  _outputs;                        // Gate | Audio Output
   std::array <rack::engine::Light *, NBR_LIGHTS>
                  _lights;                         // Led

   std::array <uint16_t, NBR_ADC_CHANNELS>
                  _adc16_channels = {};   // PX | CIX
   std::array <uint8_t, NBR_BUTTONS>
                  _buttons = {};          // BX
   std::array <uint8_t, NBR_GATE_OUTPUTS>
                  _gate_outputs = {};     // GOX
   std::array <float, NBR_LEDS>
                  _leds = {};             // LX

   std::array <Buffer, NBR_AUDIO_INPUTS>
                  _audio_buffer_inputs;
   std::array <Buffer, NBR_AUDIO_OUTPUTS>
                  _audio_buffer_outputs;



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
