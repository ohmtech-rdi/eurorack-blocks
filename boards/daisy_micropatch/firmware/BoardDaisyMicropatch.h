/*****************************************************************************

      BoardDaisyMicropatch.h
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



class BoardDaisyMicropatch
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardDaisyMicropatch () = default;
   virtual        ~BoardDaisyMicropatch () = default;

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
   static constexpr GpiPin GI1 = {0};  // GATE IN 1
   static constexpr GpiPin GI2 = {1};  // GATE IN 2
   static constexpr GpiPin B1 = {2};   // SW1
   static constexpr GpiPin B2 = {3};   // SW2 pos0
   static constexpr GpiPin B3 = {4};   // SW2 pos1

   struct GpoPin { size_t index; };
   static constexpr GpoPin GO1 = {0};  // GATE OUT 1
   static constexpr GpoPin GO2 = {1};  // GATE OUT 2

   struct AdcPin { size_t index; };
   static constexpr AdcPin P1 = {0};
   static constexpr AdcPin P2 = {1};
   static constexpr AdcPin P3 = {2};
   static constexpr AdcPin P4 = {3};
   static constexpr AdcPin CI1 = {4};
   static constexpr AdcPin CI2 = {5};
   static constexpr AdcPin CI3 = {6};
   static constexpr AdcPin CI4 = {7};

   struct DacPin { size_t index; };
   static constexpr DacPin CO = {0};
   static constexpr DacPin L = {1};

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
   inline void    impl_postprocess () {}

   inline void    impl_idle () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   SubmoduleDaisyPatchSm
                  _submodule;

   std::array <uint8_t, 5>
                  _digital_inputs;
   std::array <float, 8>
                  _analog_inputs;
   std::array <Buffer, 2>
                  _audio_inputs;

   std::array <uint8_t, 2>
                  _digital_outputs;
   std::array <float, 2>
                  _analog_outputs;
   std::array <Buffer, 2>
                  _audio_outputs;

   std::array <GpioInputDaisy, 4>
                  _gpio_inputs = {{
                     {SubmoduleDaisyPatchSm::B10},
                     {SubmoduleDaisyPatchSm::B9},
                     {SubmoduleDaisyPatchSm::B7, GpioInputDaisy::Pull::Up},
                     {SubmoduleDaisyPatchSm::B8},
                  }};
   std::array <GpioOutputDaisy, 2>
                  _gpio_outputs = {{
                     {SubmoduleDaisyPatchSm::B5},
                     {SubmoduleDaisyPatchSm::B6},
                  }};

   AdcDaisy <8>   _adc = {
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
                     }
                  };

   DacDaisy       _dac = {
                     _submodule.dac (),
                     {
                        CO.index,
                        L.index,
                     }
                  };



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardDaisyMicropatch (const BoardDaisyMicropatch & rhs) = delete;
                  BoardDaisyMicropatch (BoardDaisyMicropatch && rhs) = delete;
   BoardDaisyMicropatch &
                  operator = (const BoardDaisyMicropatch & rhs) = delete;
   BoardDaisyMicropatch &
                  operator = (BoardDaisyMicropatch && rhs) = delete;
   bool           operator == (const BoardDaisyMicropatch & rhs) const = delete;
   bool           operator != (const BoardDaisyMicropatch & rhs) const = delete;



}; // class BoardDaisyMicropatch



}  // namespace erb



#include "BoardDaisyMicropatch.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
