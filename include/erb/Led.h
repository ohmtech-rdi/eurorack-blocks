/*****************************************************************************

      Led.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Animation.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class Led
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Led () = default;
   virtual        ~Led () = default;

   void           set_brightness (float perceptual_brightness);

   void           on (bool state = true);
   void           off ();
   void           pulse (float brightness = 1.f, std::chrono::milliseconds duration = 100ms, TransitionFunction transition_function = step);
   void           pulse_twice (float brightness = 1.f, std::chrono::milliseconds duration = 400ms, TransitionFunction transition_function = step);
   void           pulse_thrice (float brightness = 1.f, std::chrono::milliseconds duration = 700ms, TransitionFunction transition_function = step);
   void           blink (float brightness = 1.f, std::chrono::milliseconds period = 800ms, TransitionFunction transition_function = step);

   Animation <float, 8> &
                  animation ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (float & val, uint64_t & now_ms);
   void           impl_notify_audio_buffer_start ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   float          _brightness = 1.f;
   Animation <float, 8>
                  _animation;
   float *        _val_ptr = nullptr;
   uint64_t *     _now_ms_ptr = nullptr;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Led (const Led & rhs) = delete;
                  Led (Led && rhs) = delete;
   Led &          operator = (const Led & rhs) = delete;
   Led &          operator = (Led && rhs) = delete;
   bool           operator == (const Led & rhs) const = delete;
   bool           operator != (const Led & rhs) const = delete;



}; // class Led



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
