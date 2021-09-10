/*****************************************************************************

      BoardKivu12.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/AdcDaisy.h"
#include "erb/daisy/DacDaisy.h"
#include "erb/daisy/GpioInputDaisy.h"
#include "erb/daisy/GpioOutputDaisy.h"
#include "erb/daisy/SubmoduleDaisyPatchSm.h"

#include <array>



namespace erb
{



class BoardKivu12
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardKivu12 ();
   virtual        ~BoardKivu12 () = default;

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

   // Clock
   inline const uint64_t &
                  clock () { return _submodule.clock (); }

   template <typename F>
   inline void    run (F && f) { _submodule.run (std::forward <F> (f)); }

   struct GpiPin { size_t index; };
   static constexpr GpiPin B1 = {0};
   static constexpr GpiPin B2 = {1};
   static constexpr GpiPin B3 = {2};
   static constexpr GpiPin B4 = {3};
   static constexpr GpiPin B5 = {4};
   static constexpr GpiPin B6 = {5};
   static constexpr GpiPin B7 = {6};
   static constexpr GpiPin B8 = {7};
   static constexpr GpiPin B9 = {8};
   static constexpr GpiPin B10 = {9};
   static constexpr GpiPin B11 = {10};
   static constexpr GpiPin B12 = {11};
   static constexpr GpiPin B13 = {12};
   static constexpr GpiPin B14 = {13};
   static constexpr GpiPin B15 = {14};
   static constexpr GpiPin B16 = {15};

   struct GpoPin { size_t index; };
   static constexpr GpoPin GO1 = {0};
   static constexpr GpoPin GO2 = {1};

   struct AdcPin { size_t index; };
   static constexpr AdcPin CI1 = {0};
   static constexpr AdcPin CI2 = {1};
   static constexpr AdcPin CI3 = {2};
   static constexpr AdcPin CI4 = {3};
   static constexpr AdcPin CI5 = {4};
   static constexpr AdcPin CI6 = {5};
   static constexpr AdcPin CI7 = {6};
   static constexpr AdcPin CI8 = {7};
   static constexpr AdcPin P1 = {8};
   static constexpr AdcPin P2 = {9};
   static constexpr AdcPin P3 = {10};
   static constexpr AdcPin P4 = {11};
   static constexpr AdcPin P5 = {12};
   static constexpr AdcPin P6 = {13};
   static constexpr AdcPin P7 = {14};
   static constexpr AdcPin P8 = {15};
   static constexpr AdcPin P9 = {16};
   static constexpr AdcPin P10 = {17};
   static constexpr AdcPin P11 = {18};
   static constexpr AdcPin P12 = {19};

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
   static constexpr DacPin L9 = {10};
   static constexpr DacPin L10 = {11};
   static constexpr DacPin L11 = {12};
   static constexpr DacPin L12 = {13};
   static constexpr DacPin L13 = {14};
   static constexpr DacPin L14 = {15};
   static constexpr DacPin L15 = {16};
   static constexpr DacPin L16 = {17};
   static constexpr DacPin L17 = {18};
   static constexpr DacPin L18 = {19};
   static constexpr DacPin L19 = {20};
   static constexpr DacPin L20 = {21};

   struct AudioInPin { size_t index; };
   static constexpr AudioInPin AI1 = {0};
   static constexpr AudioInPin AI2 = {1};

   struct AudioOutPin { size_t index; };
   static constexpr AudioOutPin AO1 = {0};
   static constexpr AudioOutPin AO2 = {1};


/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess ();
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

   inline void    set_b_mux_addr ();

   SubmoduleDaisyPatchSm
                  _submodule;

   std::array <uint8_t, 16>
                  _digital_inputs;
   std::array <float, 20>
                  _analog_inputs;
   std::array <Buffer, 2>
                  _audio_inputs;

   std::array <uint8_t, 2>
                  _digital_outputs;
   std::array <float, 22>
                  _analog_outputs;
   std::array <Buffer, 2>
                  _audio_outputs;

   std::array <GpioInputDaisy, 2>
                  _gpio_inputs = {{
                     {SubmoduleDaisyPatchSm::B10}, // GATE IN 1
                     {SubmoduleDaisyPatchSm::B9},  // GATE IN 2
                  }};

   std::array <GpioOutputDaisy, 3>
                  _gpio_b_mux = {{        // B Gate mux address
                     {SubmoduleDaisyPatchSm::A3},
                     {SubmoduleDaisyPatchSm::A2},
                     {SubmoduleDaisyPatchSm::A9},
                  }};

   std::array <GpioOutputDaisy, 2>
                  _gpio_outputs = {{
                     {SubmoduleDaisyPatchSm::B6},  // GATE OUT 1
                     {SubmoduleDaisyPatchSm::B5},  // GATE OUT 2
                  }};

   AdcDaisy <20>  _adc = {
                     _submodule.adc (),
                     {
                        {SubmoduleDaisyPatchSm::AdcPin0.pin},
                        {SubmoduleDaisyPatchSm::AdcPin1.pin},
                        {SubmoduleDaisyPatchSm::AdcPin2.pin},
                        {SubmoduleDaisyPatchSm::AdcPin3.pin},
                        {SubmoduleDaisyPatchSm::AdcPin4.pin},
                        {SubmoduleDaisyPatchSm::AdcPin5.pin},
                        {SubmoduleDaisyPatchSm::AdcPin6.pin},
                        {SubmoduleDaisyPatchSm::AdcPin7.pin},
                        {
                           SubmoduleDaisyPatchSm::D9, 8,
                           {
                              SubmoduleDaisyPatchSm::D1,
                              SubmoduleDaisyPatchSm::D10,
                              SubmoduleDaisyPatchSm::A8
                           }
                        },
                        {
                           // first 4 are relevant only
                           SubmoduleDaisyPatchSm::D8, 8,
                           {
                              SubmoduleDaisyPatchSm::D1,
                              SubmoduleDaisyPatchSm::D10,
                              SubmoduleDaisyPatchSm::A8
                           }
                        },
                     }
                  };

   DacDaisy       _dac = {
                     _submodule.dac (),
                     {
                        CO1.index,
                        CO2.index,
                     }
                  };

   daisy::LedDriverPca9685 <2, true>
                  _led_driver;

   uint8_t        _b_mux_addr = 0;



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



#include "erb/daisy/BoardKivu12.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
