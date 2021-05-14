/*****************************************************************************

      LedBi.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Led.h"



namespace erb
{



using namespace std::chrono_literals;

class LedBi
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

                  LedBi (float & data_r, float & data_g, const uint64_t & clock_ms);
   virtual        ~LedBi () = default;

   void           set_brightness (float perceptual_brightness);

   void           on (Color color);
   void           off ();
   void           pulse (Color color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
   void           pulse_twice (Color color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
   void           pulse_thrice (Color color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
   void           blink (Color color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);


   Led            r;
   Led            g;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const void *   impl_data () const { return r.impl_data (); }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



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
