/*****************************************************************************

      BoardDaisySeed.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/SubmoduleDaisySeed.h"

#include <array>



namespace erb
{



class BoardDaisySeed
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardDaisySeed ();
   virtual        ~BoardDaisySeed () = default;

   // Digital Inputs
   inline const uint8_t &
                  gpi (size_t i) { return _digital_ios [i]; }

   // Analog Inputs
   inline const float &
                  adc (size_t i) { return _analog_inputs [i]; }

   // Audio Inputs
   inline const Buffer &
                  audioin (size_t i) { return _audio_inputs [i]; }

   // Digital Outputs
   inline uint8_t &
                  gpo (size_t i) { return _digital_ios [i]; }

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

   struct Pin { size_t index; };
   static constexpr Pin Pin0 = {0};
   static constexpr Pin Pin1 = {1};
   static constexpr Pin Pin2 = {2};
   static constexpr Pin Pin3 = {3};
   static constexpr Pin Pin4 = {4};
   static constexpr Pin Pin5 = {5};
   static constexpr Pin Pin6 = {6};
   static constexpr Pin Pin7 = {7};
   static constexpr Pin Pin8 = {8};
   static constexpr Pin Pin9 = {9};
   static constexpr Pin Pin10 = {10};
   static constexpr Pin Pin11 = {11};
   static constexpr Pin Pin12 = {12};
   static constexpr Pin Pin13 = {13};
   static constexpr Pin Pin14 = {14};
   static constexpr Pin Pin26 = {26};
   static constexpr Pin Pin27 = {27};
   static constexpr Pin Pin29 = {29};
   static constexpr Pin Pin30 = {30};

   struct AdcPin { size_t index; };
   static constexpr AdcPin AdcPin0 = {0};
   static constexpr AdcPin AdcPin1 = {1};
   static constexpr AdcPin AdcPin2 = {2};
   static constexpr AdcPin AdcPin3 = {3};
   static constexpr AdcPin AdcPin4 = {4};
   static constexpr AdcPin AdcPin5 = {5};
   static constexpr AdcPin AdcPin6 = {6};
   static constexpr AdcPin AdcPin9 = {9};
   static constexpr AdcPin AdcPin10 = {10};
   static constexpr AdcPin AdcPin11 = {11};

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
   inline void    impl_preprocess (Pin pin);
   inline void    impl_preprocess (AdcPin pin);
   inline void    impl_preprocess (AudioInPin pin);

   inline void    impl_postprocess (Pin pin);
   inline void    impl_postprocess (DacPin pin);
   inline void    impl_postprocess (AudioOutPin pin);
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   SubmoduleDaisySeed
                  _submodule;

   std::array <uint8_t, 31>
                  _digital_ios;

   std::array <float, 12>
                  _analog_inputs;
   std::array <Buffer, 2>
                  _audio_inputs;

   std::array <float, 2>
                  _analog_outputs;
   std::array <Buffer, 2>
                  _audio_outputs;

   std::array <uint16_t *, 10>
                  _analog_inputs_u16;



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



#include "erb/daisy/BoardDaisySeed.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
