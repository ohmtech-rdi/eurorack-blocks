/*****************************************************************************

      SubmoduleDaisySeed.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/detail/Clock.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS

#include <array>
#include <functional>
#include <initializer_list>



namespace erb
{



class SubmoduleDaisySeed
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Pin = dsy_gpio_pin;

   static constexpr Pin Pin0 =  {DSY_GPIOB, 12};
   static constexpr Pin Pin1 =  {DSY_GPIOC, 11};
   static constexpr Pin Pin2 =  {DSY_GPIOC, 10};
   static constexpr Pin Pin3 =  {DSY_GPIOC, 9};
   static constexpr Pin Pin4 =  {DSY_GPIOC, 8};
   static constexpr Pin Pin5 =  {DSY_GPIOD, 2};
   static constexpr Pin Pin6 =  {DSY_GPIOC, 12};

   static constexpr Pin Pin7 =  {DSY_GPIOG, 10};
   static constexpr Pin Pin8 =  {DSY_GPIOG, 11};
   static constexpr Pin Pin9 =  {DSY_GPIOB, 4};
   static constexpr Pin Pin10 = {DSY_GPIOB, 5};
   static constexpr Pin Pin11 = {DSY_GPIOB, 8};
   static constexpr Pin Pin12 = {DSY_GPIOB, 9};
   static constexpr Pin Pin13 = {DSY_GPIOB, 6};
   static constexpr Pin Pin14 = {DSY_GPIOB, 7};

   static constexpr Pin Pin15 = {DSY_GPIOC, 0};
   static constexpr Pin Pin16 = {DSY_GPIOA, 3};
   static constexpr Pin Pin17 = {DSY_GPIOB, 1};
   static constexpr Pin Pin18 = {DSY_GPIOA, 7};
   static constexpr Pin Pin19 = {DSY_GPIOA, 6};
   static constexpr Pin Pin20 = {DSY_GPIOC, 1};
   static constexpr Pin Pin21 = {DSY_GPIOC, 4};
   static constexpr Pin Pin22 = {DSY_GPIOA, 5};

   static constexpr Pin Pin23 = {DSY_GPIOA, 4};
   static constexpr Pin Pin24 = {DSY_GPIOA, 1};
   static constexpr Pin Pin25 = {DSY_GPIOA, 0};
   static constexpr Pin Pin26 = {DSY_GPIOD, 11};
   static constexpr Pin Pin27 = {DSY_GPIOG, 9};
   static constexpr Pin Pin28 = {DSY_GPIOA, 2};
   static constexpr Pin Pin29 = {DSY_GPIOB, 14};
   static constexpr Pin Pin30 = {DSY_GPIOB, 15};

   static constexpr Pin Pins [] = {
      Pin0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6,
      Pin7, Pin8, Pin9, Pin10, Pin11, Pin12, Pin13, Pin14,
      Pin15, Pin16, Pin17, Pin18, Pin19, Pin20, Pin21, Pin22,
      Pin23, Pin24, Pin25, Pin26, Pin27, Pin28, Pin29, Pin30
   };

   struct AdcPin
   {
      Pin pin;
   };

   static constexpr AdcPin AdcPin0 =  {Pin15};
   static constexpr AdcPin AdcPin1 =  {Pin16};
   static constexpr AdcPin AdcPin2 =  {Pin17};
   static constexpr AdcPin AdcPin3 =  {Pin18};
   static constexpr AdcPin AdcPin4 =  {Pin19};
   static constexpr AdcPin AdcPin5 =  {Pin20};
   static constexpr AdcPin AdcPin6 =  {Pin21};
   static constexpr AdcPin AdcPin7 =  {Pin22};
   static constexpr AdcPin AdcPin8 =  {Pin23};
   static constexpr AdcPin AdcPin9 =  {Pin24};
   static constexpr AdcPin AdcPin10 = {Pin25};
   static constexpr AdcPin AdcPin11 = {Pin28};

   static constexpr AdcPin AdcPins [] = {
      AdcPin0, AdcPin1, AdcPin2, AdcPin3,
      AdcPin4, AdcPin5, AdcPin6, AdcPin7,
      AdcPin8, AdcPin9, AdcPin10, AdcPin11
   };

   struct DacPin
   {
      Pin pin;
   };

   static constexpr DacPin DacPin0 =  {Pin23};
   static constexpr DacPin DacPin1 =  {Pin22};

   static constexpr DacPin DacPins [] = {
      DacPin0, DacPin1
   };

   enum class Pull
   {
      Up, Down
   };

   struct MuxAddress
   {
      Pin         pin_a = PinNC;
      Pin         pin_b = PinNC;
      Pin         pin_c = PinNC;
   };

   struct AdcChannel
   {
      AdcPin      pin;
      size_t      nbr_channels = 1;
      MuxAddress  address = MuxAddress {};
   };

   enum { NBR_MAX_ADC_CHANNELS = 12 };

                  SubmoduleDaisySeed ();
   virtual        ~SubmoduleDaisySeed () = default;

   template <typename F>
   void           run (F && f);

   // Clock
   inline const uint64_t &
                  clock () { return _clock.ms (); }

   template <size_t MaxNbrChannels>
   std::array <uint16_t *, MaxNbrChannels>
                  init_adc_channels (std::initializer_list <AdcChannel> adc_channels);

   void           init_dac_channels (std::initializer_list <DacPin> dac_pins);
   void           write_dac (DacPin pin, uint16_t val);

   // Onboard Daisy Codec and associated gain stage
   // eurorack audio level (-5V, 5V) to (-1.f, 1.f)
   static constexpr float
                  gain_input_scaling = 2.3f;

   // Onboard Daisy Codec and associated gain stage
   // Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   // 10V / (0.7 x 3.3V x 10) = 0.433
   static constexpr float
                  gain_output_scaling = 0.433f;


   float * const *raw_audio_inputs = nullptr;
   float **       raw_audio_outputs = nullptr;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static constexpr Pin PinNC = {DSY_GPIOX, 0};



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   daisy::DaisySeed
                  _seed;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           enable_fz ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   static SubmoduleDaisySeed *
                  _this_ptr;

   Clock          _clock;
   std::function <void ()>
                  _run;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SubmoduleDaisySeed (const SubmoduleDaisySeed & rhs) = delete;
                  SubmoduleDaisySeed (SubmoduleDaisySeed && rhs) = delete;
   SubmoduleDaisySeed &
                  operator = (const SubmoduleDaisySeed & rhs) = delete;
   SubmoduleDaisySeed &
                  operator = (SubmoduleDaisySeed && rhs) = delete;
   bool           operator == (const SubmoduleDaisySeed & rhs) const = delete;
   bool           operator != (const SubmoduleDaisySeed & rhs) const = delete;



}; // class SubmoduleDaisySeed



}  // namespace erb



#include "erb/daisy/SubmoduleDaisySeed.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
