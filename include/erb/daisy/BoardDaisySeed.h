/*****************************************************************************

      BoardDaisySeed.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_seed.h"
erb_RESTORE_WARNINGS

#include <array>
#include <functional>
#include <initializer_list>



namespace erb
{



class BoardDaisySeed
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

   struct AdcPin
   {
      dsy_gpio_pin pin;
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

                  BoardDaisySeed ();
   virtual        ~BoardDaisySeed () = default;

   template <typename F>
   void           run (F && f);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static constexpr Pin PinNC = {DSY_GPIOX, 0};



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   struct Adc16Channel
   {
      AdcPin      pin;
      size_t      nbr_channels = 1;
      Pin         pin_a = PinNC;
      Pin         pin_b = PinNC;
      Pin         pin_c = PinNC;
   };

   enum { NBR_AUDIO_CHANNELS = 2 };

   using AudioBufferInputs = std::array <Buffer, NBR_AUDIO_CHANNELS>;
   using AudioBufferOutputs = std::array <Buffer, NBR_AUDIO_CHANNELS>;

   virtual void   do_notify_audio_buffer_start () = 0;
   virtual void   do_notify_audio_buffer_end () = 0;

   template <size_t MaxNbrChannels>
   std::array <uint16_t *, MaxNbrChannels>
                  init_adc16_channels (std::initializer_list <AdcChannel> adc_channels);

   AudioBufferInputs
                  _audio_buffer_inputs;
   AudioBufferOutputs
                  _audio_buffer_outputs;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           enable_fz ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   void           process_inputs (BufferInputs & buffer_inputs, float ** in);
   void           process_outputs (float ** out, BufferOutputs & buffer_outputs);

   static BoardDaisySeed *
                  _this_ptr;

   daisy::DaisySeed
                  _seed;
   std::function <void ()>
                  _buffer_callback;

   uint64_t       _clock_spl = 0ull;
   uint64_t       _clock_ms = 0ull;



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



inline bool      operator == (const BoardDaisySeed::Pin & lhs, const BoardDaisySeed::Pin & rhs)
{
   return lhs.port == rhs.port && lhs.pin == rhs.pin;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
