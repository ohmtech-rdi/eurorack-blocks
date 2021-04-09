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
   enum class Color
   {
      Red, Yellow, Green
   };

                  VcvLedBi (VcvModule & module, const VcvPin & pin_r, const VcvPin & pin_g);
   virtual        ~VcvLedBi () = default;

   size_t         index () const;

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
