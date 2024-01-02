// BoardFirmware.h

#pragma once

#include "erb/daisy/AdcDaisy.h"
#include "erb/daisy/DacDaisy.h"
#include "erb/daisy/GpioInputDaisy.h"
#include "erb/daisy/GpioOutputDaisy.h"
#include "erb/daisy/SubmoduleDaisyPatchSm.h"

#include <array>


class Board
{
public:
   inline         Board () = default;
   virtual        ~Board () = default;

   // Analog Inputs
   inline const float &
                  p (size_t i) { return _analog_inputs [i]; }

   // Audio Inputs
   inline const erb::Buffer &
                  ai (size_t i) { return _audio_inputs [i]; }

   // Digital Outputs
   inline uint8_t &
                  ld (size_t i) { return _digital_outputs [i]; }

   // Audio Outputs
   inline erb::Buffer &
                  ao (size_t i) { return _audio_outputs [i]; }

   // Clock
   inline const uint64_t &
                  clock () { return _submodule.clock (); }

   template <typename F>
   inline void    run (F && f) { _submodule.run (std::forward <F> (f)); }

   struct AdcPin { size_t index; };
   static constexpr AdcPin P1 = {0};

   struct AudioInPin { size_t index; };
   static constexpr AudioInPin AI1 = {0};

   struct GpoPin { size_t index; };
   static constexpr GpoPin LD1 = {0};

   struct AudioOutPin { size_t index; };
   static constexpr AudioOutPin AO1 = {0};

   // internal
   inline void    impl_preprocess () {}
   inline void    impl_preprocess (AdcPin pin);
   inline void    impl_preprocess (AudioInPin pin);

   inline void    impl_postprocess (GpoPin pin);
   inline void    impl_postprocess (AudioOutPin pin);
   inline void    impl_postprocess () {}

   inline void    impl_idle () {}


private:

   inline void    set_b_mux_addr ();

   erb::SubmoduleDaisyPatchSm
                  _submodule;

   std::array <float, 1>
                  _analog_inputs;
   std::array <erb::Buffer, 1>
                  _audio_inputs;

   std::array <uint8_t, 1>
                  _digital_outputs;
   std::array <erb::Buffer, 1>
                  _audio_outputs;

   // hardware configuration

   erb::AdcDaisy <1>
                  _adc = {
                     _submodule.adc (),
                     {
                        {erb::SubmoduleDaisyPatchSm::D9}
                     }
                  };

   std::array <erb::GpioOutputDaisy, 1>
                  _gpio_outputs = {{
                     {erb::SubmoduleDaisyPatchSm::B5}, // LD1
                  }};
};


#include "BoardFirmware.hpp"
