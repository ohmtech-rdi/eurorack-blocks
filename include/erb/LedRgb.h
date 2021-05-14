/*****************************************************************************

      LedRgb.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Led.h"



namespace erb
{



using namespace std::chrono_literals;

class LedRgb
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

                  LedRgb (float & data_r, float & data_g, float & data_b, const uint64_t & clock_ms);
   virtual        ~LedRgb () = default;

   void           set_brightness (float perceptual_brightness);

   void           on (Color color);
   void           off ();
   void           pulse (Color color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
   void           pulse_twice (Color color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
   void           pulse_thrice (Color color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
   void           blink (Color color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);


   Led            r;
   Led            g;
   Led            b;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const void *   impl_data () const { return r.impl_data (); }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  LedRgb () = delete;
                  LedRgb (const LedRgb & rhs) = delete;
                  LedRgb (LedRgb && rhs) = delete;
   LedRgb &       operator = (const LedRgb & rhs) = delete;
   LedRgb &       operator = (LedRgb && rhs) = delete;
   bool           operator == (const LedRgb & rhs) const = delete;
   bool           operator != (const LedRgb & rhs) const = delete;



}; // class LedRgb



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
