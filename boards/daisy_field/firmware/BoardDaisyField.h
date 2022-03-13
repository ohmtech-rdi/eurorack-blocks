/*****************************************************************************

      BoardDaisyField.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/AdcDaisy.h"
#include "erb/daisy/DacDaisy.h"
#include "erb/daisy/GpioInputDaisy.h"
#include "erb/daisy/GpioOutputDaisy.h"
#include "erb/daisy/SubmoduleDaisySeed.h"

#include <array>



namespace erb
{



class BoardDaisyField
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardDaisyField ();
   virtual        ~BoardDaisyField () = default;

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

   // Clock
   inline const uint64_t &
                  clock () { return _submodule.clock (); }

   template <typename F>
   inline void    run (F && f) { _submodule.run (std::forward <F> (f)); }

   struct GpiPin { size_t index; };
   static constexpr GpiPin GI = {0};
   static constexpr GpiPin B1 = {1};
   static constexpr GpiPin B2 = {2};

   struct GpoPin { size_t index; };
   static constexpr GpoPin GO = {0};

   struct AdcPin { size_t index; };
   static constexpr AdcPin CI1 = {0};
   static constexpr AdcPin CI2 = {1};
   static constexpr AdcPin CI3 = {2};
   static constexpr AdcPin CI4 = {3};
   static constexpr AdcPin P1 = {4};
   static constexpr AdcPin P2 = {5};
   static constexpr AdcPin P3 = {6};
   static constexpr AdcPin P4 = {7};
   static constexpr AdcPin P5 = {8};
   static constexpr AdcPin P6 = {9};
   static constexpr AdcPin P7 = {10};
   static constexpr AdcPin P8 = {11};

   struct DacPin { size_t index; };
   static constexpr DacPin CO1 = {0};
   static constexpr DacPin CO2 = {1};
   static constexpr DacPin L1 = {2};
   static constexpr DacPin L2 = {3};
   static constexpr DacPin L3 = {4};
   static constexpr DacPin L4 = {5};
   static constexpr DacPin L5 = {6};
   static constexpr DacPin L6 = {7};
   static constexpr DacPin L7 = {8};
   static constexpr DacPin L8 = {9};

   struct AudioInPin { size_t index; };
   static constexpr AudioInPin AI1 = {0};
   static constexpr AudioInPin AI2 = {1};

   struct AudioOutPin { size_t index; };
   static constexpr AudioOutPin AO1 = {0};
   static constexpr AudioOutPin AO2 = {1};


/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   inline void    impl_preprocess (GpiPin pin);
   inline void    impl_preprocess (AdcPin pin);
   inline void    impl_preprocess (AudioInPin pin);

   inline void    impl_postprocess (GpoPin pin);
   inline void    impl_postprocess (DacPin pin);
   inline void    impl_postprocess (AudioOutPin pin);
   inline void    impl_postprocess ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   SubmoduleDaisySeed
                  _submodule;

   std::array <uint8_t, 3>
                  _digital_inputs;
   std::array <float, 12>
                  _analog_inputs;
   std::array <Buffer, 2>
                  _audio_inputs;

   std::array <uint8_t, 1>
                  _digital_outputs;
   std::array <float, 10>
                  _analog_outputs;
   std::array <Buffer, 2>
                  _audio_outputs;

   std::array <GpioInputDaisy, 3>
                  _gpio_inputs = {{
                     {SubmoduleDaisySeed::Pin0},
                     {SubmoduleDaisySeed::Pin30, GpioInputDaisy::Pull::Up},
                     {SubmoduleDaisySeed::Pin29, GpioInputDaisy::Pull::Up}
                  }};
   std::array <GpioOutputDaisy, 1>
                  _gpio_outputs = {{
                     {SubmoduleDaisySeed::Pin15}
                  }};

   AdcDaisy <12>  _adc = {
                     _submodule.adc (),
                     {
                        {SubmoduleDaisySeed::AdcPin2.pin},
                        {SubmoduleDaisySeed::AdcPin3.pin},
                        {SubmoduleDaisySeed::AdcPin10.pin},
                        {SubmoduleDaisySeed::AdcPin9.pin},
                        {
                           SubmoduleDaisySeed::AdcPin1.pin, 8,
                           {
                              SubmoduleDaisySeed::Pin21,
                              SubmoduleDaisySeed::Pin20,
                              SubmoduleDaisySeed::Pin19
                           }
                        },
                     }
                  };

   DacDaisy       _dac = {_submodule.dac (), {CO1.index, CO2.index}};

   daisy::LedDriverPca9685 <1, true>
                  _led_driver;



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



#include "BoardDaisyField.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
