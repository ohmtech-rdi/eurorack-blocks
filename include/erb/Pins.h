/*****************************************************************************

      Pins.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "daisy_core.h"



namespace erb
{



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

static constexpr Pin PinNC = {DSY_GPIOX, 0}; // internal

inline bool      operator == (const Pin & lhs, const Pin & rhs)
{
   return lhs.port == rhs.port && lhs.pin == rhs.pin;
}



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



struct MultiplexerPin
{
   size_t pin;
};

static constexpr MultiplexerPin MultiplexerPin0 =  {0};
static constexpr MultiplexerPin MultiplexerPin1 =  {1};
static constexpr MultiplexerPin MultiplexerPin2 =  {2};
static constexpr MultiplexerPin MultiplexerPin3 =  {3};
static constexpr MultiplexerPin MultiplexerPin4 =  {4};
static constexpr MultiplexerPin MultiplexerPin5 =  {5};
static constexpr MultiplexerPin MultiplexerPin6 =  {6};
static constexpr MultiplexerPin MultiplexerPin7 =  {7};



struct MultiplexerAddressPins
{
   dsy_gpio_pin pin_a;
   dsy_gpio_pin pin_b;
   dsy_gpio_pin pin_c;
};



struct AudioInDaisyPin
{
   size_t pin;
};

static constexpr AudioInDaisyPin AudioInDaisyPinLeft =  {0};
static constexpr AudioInDaisyPin AudioInDaisyPinRight = {1};
static constexpr AudioInDaisyPin AudioInDaisyPin0 =     {0};
static constexpr AudioInDaisyPin AudioInDaisyPin1 =     {1};



struct AudioOutDaisyPin
{
   size_t pin;
};

static constexpr AudioOutDaisyPin AudioOutDaisyPinLeft =  {0};
static constexpr AudioOutDaisyPin AudioOutDaisyPinRight = {1};
static constexpr AudioOutDaisyPin AudioOutDaisyPin0 =     {0};
static constexpr AudioOutDaisyPin AudioOutDaisyPin1 =     {1};



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
