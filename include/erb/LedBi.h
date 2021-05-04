/*****************************************************************************

      DaisyLedBi.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyLed.h"

#include <chrono>



namespace erb
{



using namespace std::chrono_literals;

class DaisyModule;

class DaisyLedBi
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

                  DaisyLedBi (DaisyModule & module, const Pin & pin_r, const Pin & pin_g);
   virtual        ~DaisyLedBi () = default;

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

   DaisyLed       _led_red;
   DaisyLed       _led_green;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyLedBi () = delete;
                  DaisyLedBi (const DaisyLedBi & rhs) = delete;
                  DaisyLedBi (DaisyLedBi && rhs) = delete;
   DaisyLedBi &   operator = (const DaisyLedBi & rhs) = delete;
   DaisyLedBi &   operator = (DaisyLedBi && rhs) = delete;
   bool           operator == (const DaisyLedBi & rhs) const = delete;
   bool           operator != (const DaisyLedBi & rhs) const = delete;



}; // class DaisyLedBi



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
