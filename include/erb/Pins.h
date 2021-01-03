/*****************************************************************************

      Pins.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "daisy_core.h"



namespace erb
{



static constexpr dsy_gpio_pin Pin0 =  {DSY_GPIOB, 12};
static constexpr dsy_gpio_pin Pin1 =  {DSY_GPIOC, 11};
static constexpr dsy_gpio_pin Pin2 =  {DSY_GPIOC, 10};
static constexpr dsy_gpio_pin Pin3 =  {DSY_GPIOC, 9};
static constexpr dsy_gpio_pin Pin4 =  {DSY_GPIOC, 8};
static constexpr dsy_gpio_pin Pin5 =  {DSY_GPIOD, 2};
static constexpr dsy_gpio_pin Pin6 =  {DSY_GPIOC, 12};

static constexpr dsy_gpio_pin Pin7 =  {DSY_GPIOG, 10};
static constexpr dsy_gpio_pin Pin8 =  {DSY_GPIOG, 11};
static constexpr dsy_gpio_pin Pin9 =  {DSY_GPIOB, 4};
static constexpr dsy_gpio_pin Pin10 = {DSY_GPIOB, 5};
static constexpr dsy_gpio_pin Pin11 = {DSY_GPIOB, 8};
static constexpr dsy_gpio_pin Pin12 = {DSY_GPIOB, 9};
static constexpr dsy_gpio_pin Pin13 = {DSY_GPIOB, 6};
static constexpr dsy_gpio_pin Pin14 = {DSY_GPIOB, 7};

static constexpr dsy_gpio_pin Pin15 = {DSY_GPIOC, 0};
static constexpr dsy_gpio_pin Pin16 = {DSY_GPIOA, 3};
static constexpr dsy_gpio_pin Pin17 = {DSY_GPIOB, 1};
static constexpr dsy_gpio_pin Pin18 = {DSY_GPIOA, 7};
static constexpr dsy_gpio_pin Pin19 = {DSY_GPIOA, 6};
static constexpr dsy_gpio_pin Pin20 = {DSY_GPIOC, 1};
static constexpr dsy_gpio_pin Pin21 = {DSY_GPIOC, 4};
static constexpr dsy_gpio_pin Pin22 = {DSY_GPIOA, 5};

static constexpr dsy_gpio_pin Pin23 = {DSY_GPIOA, 4};
static constexpr dsy_gpio_pin Pin24 = {DSY_GPIOA, 1};
static constexpr dsy_gpio_pin Pin25 = {DSY_GPIOA, 0};
static constexpr dsy_gpio_pin Pin26 = {DSY_GPIOD, 11};
static constexpr dsy_gpio_pin Pin27 = {DSY_GPIOG, 9};
static constexpr dsy_gpio_pin Pin28 = {DSY_GPIOA, 2};
static constexpr dsy_gpio_pin Pin29 = {DSY_GPIOB, 14};
static constexpr dsy_gpio_pin Pin30 = {DSY_GPIOB, 15};



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



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
