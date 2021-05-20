/*****************************************************************************

      VcvPins.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstddef>



namespace erb
{



struct VcvPin
{
   size_t port;
   size_t pin;
};

static constexpr size_t DSY_GPIOX = 0;
static constexpr size_t DSY_GPIOA = 1;
static constexpr size_t DSY_GPIOB = 2;
static constexpr size_t DSY_GPIOC = 3;
static constexpr size_t DSY_GPIOD = 4;
static constexpr size_t DSY_GPIOE = 5;
static constexpr size_t DSY_GPIOF = 6;
static constexpr size_t DSY_GPIOG = 7;

static constexpr VcvPin Pin0 =  {DSY_GPIOB, 12};
static constexpr VcvPin Pin1 =  {DSY_GPIOC, 11};
static constexpr VcvPin Pin2 =  {DSY_GPIOC, 10};
static constexpr VcvPin Pin3 =  {DSY_GPIOC, 9};
static constexpr VcvPin Pin4 =  {DSY_GPIOC, 8};
static constexpr VcvPin Pin5 =  {DSY_GPIOD, 2};
static constexpr VcvPin Pin6 =  {DSY_GPIOC, 12};

static constexpr VcvPin Pin7 =  {DSY_GPIOG, 10};
static constexpr VcvPin Pin8 =  {DSY_GPIOG, 11};
static constexpr VcvPin Pin9 =  {DSY_GPIOB, 4};
static constexpr VcvPin Pin10 = {DSY_GPIOB, 5};
static constexpr VcvPin Pin11 = {DSY_GPIOB, 8};
static constexpr VcvPin Pin12 = {DSY_GPIOB, 9};
static constexpr VcvPin Pin13 = {DSY_GPIOB, 6};
static constexpr VcvPin Pin14 = {DSY_GPIOB, 7};

static constexpr VcvPin Pin15 = {DSY_GPIOC, 0};
static constexpr VcvPin Pin16 = {DSY_GPIOA, 3};
static constexpr VcvPin Pin17 = {DSY_GPIOB, 1};
static constexpr VcvPin Pin18 = {DSY_GPIOA, 7};
static constexpr VcvPin Pin19 = {DSY_GPIOA, 6};
static constexpr VcvPin Pin20 = {DSY_GPIOC, 1};
static constexpr VcvPin Pin21 = {DSY_GPIOC, 4};
static constexpr VcvPin Pin22 = {DSY_GPIOA, 5};

static constexpr VcvPin Pin23 = {DSY_GPIOA, 4};
static constexpr VcvPin Pin24 = {DSY_GPIOA, 1};
static constexpr VcvPin Pin25 = {DSY_GPIOA, 0};
static constexpr VcvPin Pin26 = {DSY_GPIOD, 11};
static constexpr VcvPin Pin27 = {DSY_GPIOG, 9};
static constexpr VcvPin Pin28 = {DSY_GPIOA, 2};
static constexpr VcvPin Pin29 = {DSY_GPIOB, 14};
static constexpr VcvPin Pin30 = {DSY_GPIOB, 15};

static constexpr VcvPin PinNC = {DSY_GPIOX, 0}; // internal



struct VcvAdcPin
{
   VcvPin pin;
};

static constexpr VcvAdcPin AdcPin0 =  {Pin15};
static constexpr VcvAdcPin AdcPin1 =  {Pin16};
static constexpr VcvAdcPin AdcPin2 =  {Pin17};
static constexpr VcvAdcPin AdcPin3 =  {Pin18};
static constexpr VcvAdcPin AdcPin4 =  {Pin19};
static constexpr VcvAdcPin AdcPin5 =  {Pin20};
static constexpr VcvAdcPin AdcPin6 =  {Pin21};
static constexpr VcvAdcPin AdcPin7 =  {Pin22};
static constexpr VcvAdcPin AdcPin8 =  {Pin23};
static constexpr VcvAdcPin AdcPin9 =  {Pin24};
static constexpr VcvAdcPin AdcPin10 = {Pin25};
static constexpr VcvAdcPin AdcPin11 = {Pin28};

static constexpr VcvAdcPin AdcPinNC = {PinNC}; // internal



struct VcvMultiplexerPin
{
   size_t pin;
};

static constexpr VcvMultiplexerPin MultiplexerPin0 =  {0};
static constexpr VcvMultiplexerPin MultiplexerPin1 =  {1};
static constexpr VcvMultiplexerPin MultiplexerPin2 =  {2};
static constexpr VcvMultiplexerPin MultiplexerPin3 =  {3};
static constexpr VcvMultiplexerPin MultiplexerPin4 =  {4};
static constexpr VcvMultiplexerPin MultiplexerPin5 =  {5};
static constexpr VcvMultiplexerPin MultiplexerPin6 =  {6};
static constexpr VcvMultiplexerPin MultiplexerPin7 =  {7};

static constexpr VcvMultiplexerPin MultiplexerPinNC =  {size_t (-1)};



struct VcvAudioInPin
{
   size_t pin;
};

static constexpr VcvAudioInPin AudioInPinLeft =  {0};
static constexpr VcvAudioInPin AudioInPinRight = {1};
static constexpr VcvAudioInPin AudioInPin0 =     {0};
static constexpr VcvAudioInPin AudioInPin1 =     {1};

static constexpr VcvAudioInPin AudioInPinNC =     {size_t (-1)};


struct VcvAudioOutPin
{
   size_t pin;
};

static constexpr VcvAudioOutPin AudioOutPinLeft =  {0};
static constexpr VcvAudioOutPin AudioOutPinRight = {1};
static constexpr VcvAudioOutPin AudioOutPin0 =     {0};
static constexpr VcvAudioOutPin AudioOutPin1 =     {1};

static constexpr VcvAudioOutPin AudioOutPinNC =     {size_t (-1)};



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
