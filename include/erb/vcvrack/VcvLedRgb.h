/*****************************************************************************

      VcvLedRgb.h
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

class VcvLedRgb
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   struct Color
   {
      float r, g, b;

      static Color none ();
      static Color red ();
      static Color green ();
      static Color blue ();
   };

                  VcvLedRgb (VcvModule & module, const VcvPin & pin_r, const VcvPin & pin_g, const VcvPin & pin_b);
   virtual        ~VcvLedRgb () = default;

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

   VcvLed         _led_red;
   VcvLed         _led_green;
   VcvLed         _led_blue;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvLedRgb () = delete;
                  VcvLedRgb (const VcvLedRgb & rhs) = delete;
                  VcvLedRgb (VcvLedRgb && rhs) = delete;
   VcvLedRgb &    operator = (const VcvLedRgb & rhs) = delete;
   VcvLedRgb &    operator = (VcvLedRgb && rhs) = delete;
   bool           operator == (const VcvLedRgb & rhs) const = delete;
   bool           operator != (const VcvLedRgb & rhs) const = delete;



}; // class VcvLedRgb



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
