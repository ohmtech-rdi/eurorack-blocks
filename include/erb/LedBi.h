/*****************************************************************************

      LedBi.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Led.h"

#include <chrono>



namespace erb
{



using namespace std::chrono_literals;

class Module;

class LedBi
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Color
   {
      Red, Yellow, Green
   };

                  LedBi (Module & module, const dsy_gpio_pin & pin_r, const dsy_gpio_pin & pin_g);
   virtual        ~LedBi () = default;

   void           on (Color color);
   void           off ();
   void           pulse (Color color, std::chrono::milliseconds duration = 200ms);
   void           blink (Color color, std::chrono::milliseconds half_period = 500ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   struct State
   {
      bool        red;
      bool        green;
   };

   State          to_state (Color color);

   Led            _led_red;
   Led            _led_green;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  LedBi () = delete;
                  LedBi (const LedBi & rhs) = delete;
                  LedBi (LedBi && rhs) = delete;
   LedBi &        operator = (const LedBi & rhs) = delete;
   LedBi &        operator = (LedBi && rhs) = delete;
   bool           operator == (const LedBi & rhs) const = delete;
   bool           operator != (const LedBi & rhs) const = delete;



}; // class LedBi



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
