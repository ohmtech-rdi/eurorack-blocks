/*****************************************************************************

      SubmoduleDaisySeed2Dfm.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy.h"
erb_RESTORE_WARNINGS



namespace erb
{



class SubmoduleDaisySeed2Dfm
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Pin = dsy_gpio_pin;

   static constexpr Pin D9 =  {DSY_GPIOB, 12};
   static constexpr Pin E11 = {DSY_GPIOC, 11};
   static constexpr Pin E9 =  {DSY_GPIOC, 10};
   static constexpr Pin E8 =  {DSY_GPIOC, 9};
   static constexpr Pin E7 =  {DSY_GPIOC, 8};
   static constexpr Pin E6 =  {DSY_GPIOD, 2};
   static constexpr Pin E5 =  {DSY_GPIOC, 12};

   static constexpr Pin B6 =  {DSY_GPIOG, 10};
   static constexpr Pin B2 =  {DSY_GPIOG, 11};
   static constexpr Pin B1 =  {DSY_GPIOB, 4};
   static constexpr Pin B4 =  {DSY_GPIOB, 5};
   static constexpr Pin B7 =  {DSY_GPIOB, 8};
   static constexpr Pin B8 =  {DSY_GPIOB, 9};
   static constexpr Pin B3 =  {DSY_GPIOB, 6};
   static constexpr Pin B5 =  {DSY_GPIOB, 7};

   static constexpr Pin C7 =  {DSY_GPIOC, 0};
   static constexpr Pin C1 =  {DSY_GPIOA, 3};
   static constexpr Pin C5 =  {DSY_GPIOB, 1};
   static constexpr Pin C4 =  {DSY_GPIOA, 7};
   static constexpr Pin C2 =  {DSY_GPIOA, 6};
   static constexpr Pin C3 =  {DSY_GPIOC, 1};
   static constexpr Pin C6 =  {DSY_GPIOC, 4};
   static constexpr Pin C9 =  {DSY_GPIOA, 5};

   static constexpr Pin C8 =  {DSY_GPIOA, 4};
   static constexpr Pin E1 =  {DSY_GPIOA, 1};
   static constexpr Pin E2 =  {DSY_GPIOA, 0};
   static constexpr Pin E3 =  {DSY_GPIOD, 11};
   static constexpr Pin D10 = {DSY_GPIOG, 9};
   static constexpr Pin E4 =  {DSY_GPIOA, 2};
   static constexpr Pin B10 = {DSY_GPIOB, 14};
   static constexpr Pin B9 =  {DSY_GPIOB, 15};

   static constexpr Pin C10 = {DSY_GPIOC, 2};
   static constexpr Pin D8 =  {DSY_GPIOC, 3};

   static constexpr Pin Pins [] = {
      D9, E11, E9, E8, E7, E6, E5,
      B6, B2, B1, B4, B7, B8, B3, B5,
      C7, C1, C5, C4, C2, C3, C6, C9,
      C8, E1, E2, E3, D10, E4, B10, B9,
      C10, D8
   };

   struct AdcPin
   {
      Pin pin;
   };

   static constexpr AdcPin AdcPin0 =  {C7};
   static constexpr AdcPin AdcPin1 =  {C1};
   static constexpr AdcPin AdcPin2 =  {C5};
   static constexpr AdcPin AdcPin3 =  {C4};
   static constexpr AdcPin AdcPin4 =  {C2};
   static constexpr AdcPin AdcPin5 =  {C3};
   static constexpr AdcPin AdcPin6 =  {C6};
   static constexpr AdcPin AdcPin7 =  {C9};
   static constexpr AdcPin AdcPin8 =  {C8};
   static constexpr AdcPin AdcPin9 =  {E1};
   static constexpr AdcPin AdcPin10 = {E2};
   static constexpr AdcPin AdcPin11 = {E4};
   static constexpr AdcPin AdcPin12 = {C10};
   static constexpr AdcPin AdcPin13 = {D8};

   static constexpr AdcPin AdcPins [] = {
      AdcPin0, AdcPin1, AdcPin2, AdcPin3,
      AdcPin4, AdcPin5, AdcPin6, AdcPin7,
      AdcPin8, AdcPin9, AdcPin10, AdcPin11,
      AdcPin12, AdcPin13
   };

   struct DacPin
   {
      Pin pin;
   };

   static constexpr DacPin DacPin0 =  {C8};
   static constexpr DacPin DacPin1 =  {C9};

   static constexpr DacPin DacPins [] = {
      DacPin0, DacPin1
   };

   static constexpr Pin PinNC = {DSY_GPIOX, 0};



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SubmoduleDaisySeed2Dfm (const SubmoduleDaisySeed2Dfm & rhs) = delete;
                  SubmoduleDaisySeed2Dfm (SubmoduleDaisySeed2Dfm && rhs) = delete;
   SubmoduleDaisySeed2Dfm &
                  operator = (const SubmoduleDaisySeed2Dfm & rhs) = delete;
   SubmoduleDaisySeed2Dfm &
                  operator = (SubmoduleDaisySeed2Dfm && rhs) = delete;
   bool           operator == (const SubmoduleDaisySeed2Dfm & rhs) const = delete;
   bool           operator != (const SubmoduleDaisySeed2Dfm & rhs) const = delete;



}; // class SubmoduleDaisySeed2Dfm



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
