/*****************************************************************************

      VcvLedBi.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvLed.h"

#include <chrono>



namespace erb
{



using namespace std::chrono_literals;

class VcvModule;

class VcvLedBi
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   struct Color
   {
      float r, g;

      static Color none ();
      static Color red ();
      static Color green ();
      static Color yellow ();
   };

                  VcvLedBi (VcvModule & module, const VcvPin & pin_r, const VcvPin & pin_g);
   virtual        ~VcvLedBi () = default;

   size_t         index () const;

   void           set_brightness (float perceptual_brightness);

   void           on (Color color);
   void           off ();
   void           pulse (Color color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
   void           pulse_twice (Color color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
   void           pulse_thrice (Color color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
   void           blink (Color color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   VcvLed         _led_green;
   VcvLed         _led_red;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvLedBi () = delete;
                  VcvLedBi (const VcvLedBi & rhs) = delete;
                  VcvLedBi (VcvLedBi && rhs) = delete;
   VcvLedBi &     operator = (const VcvLedBi & rhs) = delete;
   VcvLedBi &     operator = (VcvLedBi && rhs) = delete;
   bool           operator == (const VcvLedBi & rhs) const = delete;
   bool           operator != (const VcvLedBi & rhs) const = delete;



}; // class VcvLedBi



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
