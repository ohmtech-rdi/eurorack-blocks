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
   enum class Color
   {
      Red, Yellow, Green
   };

                  DaisyLedBi (DaisyModule & module, const Pin & pin_r, const Pin & pin_g);
   virtual        ~DaisyLedBi () = default;

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

   DaisyLed            _led_red;
   DaisyLed            _led_green;



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
