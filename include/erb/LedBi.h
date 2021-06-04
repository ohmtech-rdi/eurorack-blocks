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

struct ColorBi
{
   float r, g;

   inline static ColorBi none ();
   inline static ColorBi red ();
   inline static ColorBi green ();
   inline static ColorBi yellow ();
};

template <PinType Pin, CurrentMode Current>
class LedBi
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  LedBi (typename Led <Pin, Current>::BindingType data_r, typename Led <Pin, Current>::BindingType data_g, const uint64_t & clock_ms);
   virtual        ~LedBi () = default;

   void           set_brightness (float perceptual_brightness);

   void           on (ColorBi color);
   void           off ();
   void           pulse (ColorBi color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
   void           pulse_twice (ColorBi color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
   void           pulse_thrice (ColorBi color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
   void           blink (ColorBi color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);


   Led <Pin, Current>
                  r;
   Led <Pin, Current>
                  g;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   void           impl_postprocess ();



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



#include "erb/LedBi.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
