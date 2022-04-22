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

struct ColorRgb
{
   float r, g, b;

   inline static ColorRgb none ();
   inline static ColorRgb red ();
   inline static ColorRgb green ();
   inline static ColorRgb blue ();
};

template <PinType Pin>
class LedRgb
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = 0.f;
   static constexpr float ValueMax = 1.f;

                  LedRgb (typename Led <Pin>::BindingType data_r, typename Led <Pin>::BindingType data_g, typename Led <Pin>::BindingType data_b, const uint64_t & clock_ms);
   virtual        ~LedRgb () = default;

   void           set_brightness (float perceptual_brightness);

   void           on (ColorRgb color);
   void           off ();
   void           pulse (ColorRgb color, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
   void           pulse_twice (ColorRgb color, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
   void           pulse_thrice (ColorRgb color, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
   void           blink (ColorRgb color, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);


   Led <Pin>      r;
   Led <Pin>      g;
   Led <Pin>      b;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   void           impl_postprocess ();



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



#include "erb/LedRgb.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
