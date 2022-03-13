/*****************************************************************************

      BoardDaisySeed.h
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



class BoardDaisySeed
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardDaisySeed () = default;
   virtual        ~BoardDaisySeed () = default;

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
   static constexpr GpiPin Pin0 = {0};
   static constexpr GpiPin Pin1 = {1};
   static constexpr GpiPin Pin2 = {2};
   static constexpr GpiPin Pin3 = {3};
   static constexpr GpiPin Pin4 = {4};
   static constexpr GpiPin Pin5 = {5};
   static constexpr GpiPin Pin6 = {6};
   static constexpr GpiPin Pin7 = {7};
   static constexpr GpiPin Pin8 = {8};
   static constexpr GpiPin Pin9 = {9};
   static constexpr GpiPin Pin10 = {10};
   static constexpr GpiPin Pin11 = {11};

   struct AdcPin { size_t index; };
   static constexpr AdcPin AdcPin0 = {0};
   static constexpr AdcPin AdcPin1 = {1};
   static constexpr AdcPin AdcPin2 = {2};
   static constexpr AdcPin AdcPin3 = {3};
   static constexpr AdcPin AdcPin4 = {4};
   static constexpr AdcPin AdcPin5 = {5};
   static constexpr AdcPin AdcPin6 = {6};
   static constexpr AdcPin AdcPin9 = {7};
   static constexpr AdcPin AdcPin10 = {8};
   static constexpr AdcPin AdcPin11 = {9};

   struct GpoPin { size_t index; };
   static constexpr GpoPin Pin12 = {0};
   static constexpr GpoPin Pin13 = {1};
   static constexpr GpoPin Pin14 = {2};
   static constexpr GpoPin Pin26 = {3};
   static constexpr GpoPin Pin27 = {4};
   static constexpr GpoPin Pin29 = {5};
   static constexpr GpoPin Pin30 = {6};

   struct DacPin { size_t index; };
   static constexpr DacPin DacPin0 = {0};
   static constexpr DacPin DacPin1 = {1};

   struct AudioInPin { size_t index; };
   static constexpr AudioInPin AudioInPin0 = {0};
   static constexpr AudioInPin AudioInPinLeft = {0};
   static constexpr AudioInPin AudioInPin1 = {1};
   static constexpr AudioInPin AudioInPinRight = {1};

   struct AudioOutPin { size_t index; };
   static constexpr AudioOutPin AudioOutPin0 = {0};
   static constexpr AudioOutPin AudioOutPinLeft = {0};
   static constexpr AudioOutPin AudioOutPin1 = {1};
   static constexpr AudioOutPin AudioOutPinRight = {1};


/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   inline void    impl_preprocess (GpiPin pin);
   inline void    impl_preprocess (AdcPin pin);
   inline void    impl_preprocess (AudioInPin pin);

   inline void    impl_postprocess (GpoPin pin);
   inline void    impl_postprocess (DacPin pin);
   inline void    impl_postprocess (AudioOutPin pin);
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   SubmoduleDaisySeed
                  _submodule;

   std::array <uint8_t, 12>
                  _digital_inputs;
   std::array <float, 12>
                  _analog_inputs;
   std::array <Buffer, 2>
                  _audio_inputs;

   std::array <uint8_t, 7>
                  _digital_outputs;
   std::array <float, 2>
                  _analog_outputs;
   std::array <Buffer, 2>
                  _audio_outputs;

   std::array <GpioInputDaisy, 12>
                  _gpio_inputs = {{
                     {SubmoduleDaisySeed::Pin0},
                     {SubmoduleDaisySeed::Pin1},
                     {SubmoduleDaisySeed::Pin2},
                     {SubmoduleDaisySeed::Pin3},
                     {SubmoduleDaisySeed::Pin4},
                     {SubmoduleDaisySeed::Pin5},
                     {SubmoduleDaisySeed::Pin6},
                     {SubmoduleDaisySeed::Pin7},
                     {SubmoduleDaisySeed::Pin8},
                     {SubmoduleDaisySeed::Pin9},
                     {SubmoduleDaisySeed::Pin10},
                     {SubmoduleDaisySeed::Pin11},
                  }};
   std::array <GpioOutputDaisy, 7>
                  _gpio_outputs = {{
                     {SubmoduleDaisySeed::Pin12},
                     {SubmoduleDaisySeed::Pin13},
                     {SubmoduleDaisySeed::Pin14},
                     {SubmoduleDaisySeed::Pin26},
                     {SubmoduleDaisySeed::Pin27},
                     {SubmoduleDaisySeed::Pin29},
                     {SubmoduleDaisySeed::Pin30},
                  }};

   AdcDaisy <10>  _adc = {
                     _submodule.adc (),
                     {
                        {SubmoduleDaisySeed::AdcPin0.pin},
                        {SubmoduleDaisySeed::AdcPin1.pin},
                        {SubmoduleDaisySeed::AdcPin2.pin},
                        {SubmoduleDaisySeed::AdcPin3.pin},
                        {SubmoduleDaisySeed::AdcPin4.pin},
                        {SubmoduleDaisySeed::AdcPin5.pin},
                        {SubmoduleDaisySeed::AdcPin6.pin},
                        {SubmoduleDaisySeed::AdcPin9.pin},
                        {SubmoduleDaisySeed::AdcPin10.pin},
                        {SubmoduleDaisySeed::AdcPin11.pin}
                     }
                  };
   DacDaisy       _dac = {_submodule.dac (), {DacPin0.index, DacPin1.index}};



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardDaisySeed (const BoardDaisySeed & rhs) = delete;
                  BoardDaisySeed (BoardDaisySeed && rhs) = delete;
   BoardDaisySeed &
                  operator = (const BoardDaisySeed & rhs) = delete;
   BoardDaisySeed &
                  operator = (BoardDaisySeed && rhs) = delete;
   bool           operator == (const BoardDaisySeed & rhs) const = delete;
   bool           operator != (const BoardDaisySeed & rhs) const = delete;



}; // class BoardDaisySeed



}  // namespace erb



#include "BoardDaisySeed.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
