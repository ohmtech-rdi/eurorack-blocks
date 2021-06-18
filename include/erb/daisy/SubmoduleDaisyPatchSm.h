/*****************************************************************************

      SubmoduleDaisyPatchSm.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/detail/Clock.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy.h"
erb_RESTORE_WARNINGS

#include <functional>



namespace erb
{



class SubmoduleDaisyPatchSm
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Pin = dsy_gpio_pin;

   static constexpr Pin A2 = {DSY_GPIOB, 7};    // UART1 Rx
   static constexpr Pin A3 = {DSY_GPIOB, 6};    // UART1 Tx
   static constexpr Pin A8 = {DSY_GPIOA, 11};   // USB DM
   static constexpr Pin A9 = {DSY_GPIOA, 12};   // USB DP

   static constexpr Pin B5 = {DSY_GPIOC, 13};   // GATE OUT 1
   static constexpr Pin B6 = {DSY_GPIOC, 14};   // GATE OUT 2
   static constexpr Pin B7 = {DSY_GPIOB, 8};    // I2C1 SCL
   static constexpr Pin B8 = {DSY_GPIOB, 9};    // I2C1 SDA
   static constexpr Pin B9 = {DSY_GPIOG, 14};   // GATE IN 2
   static constexpr Pin B10 = {DSY_GPIOG, 13};  // GATE IN 1

   static constexpr Pin D1 = {DSY_GPIOG, 10};   // SPI1 CS
   static constexpr Pin D2 = {DSY_GPIOC, 11};   // SDMMC D3
   static constexpr Pin D3 = {DSY_GPIOC, 10};   // SDMMC D2
   static constexpr Pin D4 = {DSY_GPIOC, 9};    // SDMMC D1
   static constexpr Pin D5 = {DSY_GPIOC, 8};    // SDMMC D0
   static constexpr Pin D6 = {DSY_GPIOC, 12};   // SDMMC CK
   static constexpr Pin D7 = {DSY_GPIOD, 2};    // SDMMC CMD
   static constexpr Pin D8 = {DSY_GPIOB, 4};    // SPI1 MISO
   static constexpr Pin D9 = {DSY_GPIOB, 5};    // SPI1 MOSI
   static constexpr Pin D10 = {DSY_GPIOG, 11};  // SPI1 SCK

   static constexpr Pin Pins [] = {
      A2, A3, A8, A9,
      B5, B6, B7, B8, B9, B10,
      D1, D2, D3, D4, D5, D6, D7, D8, D9, D10
   };

   struct AdcPin
   {
      Pin pin;
   };

   static constexpr AdcPin AdcPin0 =  {{DSY_GPIOA, 3}};  // C5 CV IN 1
   static constexpr AdcPin AdcPin1 =  {{DSY_GPIOA, 6}};  // C4 CV IN 2
   static constexpr AdcPin AdcPin2 =  {{DSY_GPIOA, 2}};  // C3 CV IN 3
   static constexpr AdcPin AdcPin3 =  {{DSY_GPIOA, 7}};  // C2 CV IN 4
   static constexpr AdcPin AdcPin4 =  {{DSY_GPIOB, 1}};  // C6 CV IN 5
   static constexpr AdcPin AdcPin5 =  {{DSY_GPIOC, 4}};  // C7 CV IN 6
   static constexpr AdcPin AdcPin6 =  {{DSY_GPIOC, 0}};  // C8 CV IN 7
   static constexpr AdcPin AdcPin7 =  {{DSY_GPIOC, 1}};  // C9 CV IN 8

   static constexpr AdcPin AdcPins [] = {
      AdcPin0, AdcPin1, AdcPin2, AdcPin3,
      AdcPin4, AdcPin5, AdcPin6, AdcPin7,
   };

   struct DacPin
   {
      Pin pin;
   };

   static constexpr DacPin DacPin0 =  {{DSY_GPIOA, 4}};  // C10 CV OUT 1
   static constexpr DacPin DacPin1 =  {{DSY_GPIOA, 5}};  // C1 CV OUT 2

   static constexpr DacPin DacPins [] = {
      DacPin0, DacPin1
   };

   enum { NBR_MAX_ADC_CHANNELS = 8 };

                  SubmoduleDaisyPatchSm ();
   virtual        ~SubmoduleDaisyPatchSm () = default;

   template <typename F>
   void           run (F && f);

   // Clock
   inline const uint64_t &
                  clock ();

   inline daisy::AdcHandle &
                  adc ();
   inline daisy::DacHandle &
                  dac ();

   // Onboard Daisy Codec and associated gain stage
   // eurorack audio level (-5V, 5V) to (-1.f, 1.f)
   static constexpr float
                  gain_input_scaling = 1.52f;

   // Onboard Daisy Codec and associated gain stage
   // Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   static constexpr float
                  gain_output_scaling = 0.576f;


   float * const *raw_audio_inputs = nullptr;
   float **       raw_audio_outputs = nullptr;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static constexpr Pin PinNC = {DSY_GPIOX, 0};



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           enable_fz ();
   void           init ();
   void           init_system ();
   void           init_sdram ();
   void           init_qspi ();
   void           init_audio ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   static SubmoduleDaisyPatchSm *
                  _this_ptr;

   daisy::System  _system;
   dsy_sdram_handle
                  _sdram;
   dsy_qspi_handle
                  _qspi;
   daisy::AudioHandle
                  _audio;
   daisy::AdcHandle
                  _adc;
   daisy::DacHandle
                  _dac;
   daisy::UsbHandle
                  _usb;
   daisy::Pcm3060 _codec;

   Clock          _clock;
   std::function <void ()>
                  _run;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SubmoduleDaisyPatchSm (const SubmoduleDaisyPatchSm & rhs) = delete;
                  SubmoduleDaisyPatchSm (SubmoduleDaisyPatchSm && rhs) = delete;
   SubmoduleDaisyPatchSm &
                  operator = (const SubmoduleDaisyPatchSm & rhs) = delete;
   SubmoduleDaisyPatchSm &
                  operator = (SubmoduleDaisyPatchSm && rhs) = delete;
   bool           operator == (const SubmoduleDaisyPatchSm & rhs) const = delete;
   bool           operator != (const SubmoduleDaisyPatchSm & rhs) const = delete;



}; // class SubmoduleDaisyPatchSm



}  // namespace erb



#include "erb/daisy/SubmoduleDaisyPatchSm.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
