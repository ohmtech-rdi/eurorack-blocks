/*****************************************************************************

      BoardSeed2DfmEvalEuro.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/detail/Clock.h"

#include "erb/daisy/AdcDaisy.h"
#include "erb/daisy/DacDaisy.h"
#include "erb/daisy/GpioInputDaisy.h"
#include "erb/daisy/GpioOutputDaisy.h"
#include "erb/daisy/OledSsd130x.h"
#include "erb/daisy/SubmoduleDaisySeed2Dfm.h"

erb_DISABLE_WARNINGS_DAISY
#include "dev/oled_ssd130x.h"
erb_RESTORE_WARNINGS


#include <array>



namespace erb
{



class BoardSeed2DfmEvalEuro
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardSeed2DfmEvalEuro ();
   virtual        ~BoardSeed2DfmEvalEuro () = default;

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
                  oled () { return _oled_buffer; }

   // Clock
   inline const uint64_t &
                  clock () { return _clock.ms (); }

   template <typename F>
   inline void    run (F && f);

   struct GpiPin { size_t index; };
   static constexpr GpiPin GI1 = {0};  // Gate In
   static constexpr GpiPin B1 = {1};   // Tactile Switch
   static constexpr GpiPin B2 = {2};   // Toggle Switch pos0
   static constexpr GpiPin B3 = {3};   // Toggle Switch pos1
   static constexpr GpiPin B4 = {4};   // Encoder A
   static constexpr GpiPin B5 = {5};   // Encoder B

   struct GpoPin { size_t index; };

   struct AdcPin { size_t index; };
   static constexpr AdcPin CI1 = {0};
   static constexpr AdcPin CI2 = {1};
   static constexpr AdcPin CI3 = {2};
   static constexpr AdcPin P1 = {3};
   static constexpr AdcPin P2 = {4};
   static constexpr AdcPin P3 = {5};
   static constexpr AdcPin P4 = {6};

   struct DacPin { size_t index; };
   static constexpr DacPin CO1 = {0};
   static constexpr DacPin CO2 = {1};

   struct AudioInPin { size_t index; };
   static constexpr AudioInPin AI1 = {0};
   static constexpr AudioInPin AI2 = {1};
   static constexpr AudioInPin AI3 = {2};
   static constexpr AudioInPin AI4 = {3};

   struct AudioOutPin { size_t index; };
   static constexpr AudioOutPin AO1 = {0};
   static constexpr AudioOutPin AO2 = {1};
   static constexpr AudioOutPin AO3 = {2};
   static constexpr AudioOutPin AO4 = {3};

   struct OledBus {};
   static constexpr OledBus OLED1 = {};



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   inline void    impl_preprocess (GpiPin pin);
   inline void    impl_preprocess (AdcPin pin);
   inline void    impl_preprocess (AudioInPin pin);

   inline void    impl_postprocess (GpoPin pin);
   inline void    impl_postprocess (DacPin pin);
   inline void    impl_postprocess (AudioOutPin pin);
   inline void    impl_postprocess (OledBus);
   inline void    impl_postprocess () {}

   inline void    impl_idle ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   inline void    init_audio ();
   inline void    init_display ();

   inline static void
                  audio_callback_proc (const float * const * in, float ** out, size_t size);
   inline void    audio_callback (const float * const * in, float ** out, size_t size);

   inline static BoardSeed2DfmEvalEuro *
                  _this_ptr = nullptr;

   const float * const *
                  raw_audio_inputs = nullptr;
   float **       raw_audio_outputs = nullptr;

   daisy::AudioHandle
                  _audio;
   daisy::AdcHandle
                  _adc_hnd;
   daisy::DacHandle
                  _dac_hnd;

   Clock          _clock;
   std::function <void ()>
                  _run;

   std::array <uint8_t, 6>
                  _digital_inputs;
   std::array <float, 7>
                  _analog_inputs;
   std::array <Buffer, 4>
                  _audio_inputs;

   std::array <uint8_t, 0>
                  _digital_outputs;
   std::array <float, 2>
                  _analog_outputs;
   std::array <Buffer, 4>
                  _audio_outputs;

   std::array <GpioInputDaisy, 6>
                  _gpio_inputs = {{
                     {SubmoduleDaisySeed2Dfm::B7},    // Gate In
                     {SubmoduleDaisySeed2Dfm::B1, GpioInputDaisy::Pull::Up},  // Tactile Switch
                     {SubmoduleDaisySeed2Dfm::B10, GpioInputDaisy::Pull::Up}, // Toggle Switch pos0
                     {SubmoduleDaisySeed2Dfm::B9, GpioInputDaisy::Pull::Up},  // Toggle Switch pos1
                     {SubmoduleDaisySeed2Dfm::C1, GpioInputDaisy::Pull::Up},  // Encoder A
                     {SubmoduleDaisySeed2Dfm::C3, GpioInputDaisy::Pull::Up},  // Encoder B
                  }};

   AdcDaisy <7>   _adc = {
                     _adc_hnd,
                     {
                        {SubmoduleDaisySeed2Dfm::C7}, // CI1
                        {SubmoduleDaisySeed2Dfm::C6}, // CI2
                        {SubmoduleDaisySeed2Dfm::C5}, // CI3
                        {
                           SubmoduleDaisySeed2Dfm::C4, 4, // P1-4
                           {
                              SubmoduleDaisySeed2Dfm::B8,
                              SubmoduleDaisySeed2Dfm::C10,
                           }
                        },
                     }
                  };

   DacDaisy       _dac = {
                     _dac_hnd,
                     {
                        CO1.index,
                        CO2.index,
                     }
                  };

   daisy::SSD130x4WireSpiTransport
                  _display_transport;
   FormatSsd130x <128, 64>::Storage
                  _oled_buffer;
   OledSsd130x <128, 64, 0, 0, daisy::SSD130x4WireSpiTransport>
                  _display;



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



#include "BoardSeed2DfmEvalEuro.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
