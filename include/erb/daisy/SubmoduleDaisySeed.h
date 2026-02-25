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

#include <functional>



namespace erb
{



class SubmoduleDaisySeed
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Pin = daisy::Pin;

   static constexpr Pin Pin0 =  {daisy::PORTB, 12};
   static constexpr Pin Pin1 =  {daisy::PORTC, 11};
   static constexpr Pin Pin2 =  {daisy::PORTC, 10};
   static constexpr Pin Pin3 =  {daisy::PORTC, 9};
   static constexpr Pin Pin4 =  {daisy::PORTC, 8};
   static constexpr Pin Pin5 =  {daisy::PORTD, 2};
   static constexpr Pin Pin6 =  {daisy::PORTC, 12};

   static constexpr Pin Pin7 =  {daisy::PORTG, 10};
   static constexpr Pin Pin8 =  {daisy::PORTG, 11};
   static constexpr Pin Pin9 =  {daisy::PORTB, 4};
   static constexpr Pin Pin10 = {daisy::PORTB, 5};
   static constexpr Pin Pin11 = {daisy::PORTB, 8};
   static constexpr Pin Pin12 = {daisy::PORTB, 9};
   static constexpr Pin Pin13 = {daisy::PORTB, 6};
   static constexpr Pin Pin14 = {daisy::PORTB, 7};

   static constexpr Pin Pin15 = {daisy::PORTC, 0};
   static constexpr Pin Pin16 = {daisy::PORTA, 3};
   static constexpr Pin Pin17 = {daisy::PORTB, 1};
   static constexpr Pin Pin18 = {daisy::PORTA, 7};
   static constexpr Pin Pin19 = {daisy::PORTA, 6};
   static constexpr Pin Pin20 = {daisy::PORTC, 1};
   static constexpr Pin Pin21 = {daisy::PORTC, 4};
   static constexpr Pin Pin22 = {daisy::PORTA, 5};

   static constexpr Pin Pin23 = {daisy::PORTA, 4};
   static constexpr Pin Pin24 = {daisy::PORTA, 1};
   static constexpr Pin Pin25 = {daisy::PORTA, 0};
   static constexpr Pin Pin26 = {daisy::PORTD, 11};
   static constexpr Pin Pin27 = {daisy::PORTG, 9};
   static constexpr Pin Pin28 = {daisy::PORTA, 2};
   static constexpr Pin Pin29 = {daisy::PORTB, 14};
   static constexpr Pin Pin30 = {daisy::PORTB, 15};

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

                  SubmoduleDaisySeed ();
   virtual        ~SubmoduleDaisySeed () = default;

   template <typename F>
   void           run (F && f);

   template <std::size_t N>
   inline std::array <uint8_t, N>
                  load (size_t page);

   template <typename Data>
   inline void    save (size_t page, const Data & data);

   // Clock
   inline const uint64_t &
                  clock ();
   inline void    clock_tick ();

   inline daisy::AdcHandle &
                  adc ();
   inline daisy::DacHandle &
                  dac ();

   // Onboard Daisy Codec and associated gain stage
   // eurorack audio level (-5V, 5V) to (-1.f, 1.f)
   static constexpr float
                  gain_input_scaling = 2.3f;

   // Onboard Daisy Codec and associated gain stage
   // Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   // 10V / (0.7 x 3.3V x 10) = 0.433
   static constexpr float
                  gain_output_scaling = 0.433f;


   const float * const *
                  raw_audio_inputs = nullptr;
   float **       raw_audio_outputs = nullptr;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static constexpr Pin PinNC = {daisy::PORTX, 0};



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   daisy::DaisySeed
                  _seed;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           init_qspi ();
   void           init_audio ();

   void           do_run ();

   static void    audio_callback_proc (const float * const * in, float ** out, size_t size);
   void           audio_callback (const float * const * in, float ** out, size_t size);

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
