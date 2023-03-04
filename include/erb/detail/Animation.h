/*****************************************************************************

      Animation.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <chrono>
#include <initializer_list>

#include <cstddef>
#include <cstdint>



namespace erb
{



float             interpolate (float val0, float val1, float t);

using TransitionFunction = float (*)(float);

float             step (float t);
float             inverse_step (float t);
float             linear (float t);
float             ease_in (float t);
float             ease_out (float t);
float             ease_in_out (float t);



template <typename T, std::size_t NbrKeyframes>
class Animation
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   using TimePoint = uint64_t /* ms */;
   using Duration = std::chrono::milliseconds;

   struct Keyframe
   {
      T           target;
      Duration    transition_duration;
      TransitionFunction
                  transition_function = step;
   };

                  Animation () = default;
   virtual        ~Animation () = default;

   void           set (T value);
   Animation &    set (std::initializer_list <Keyframe> keyframes);
   Animation &    loop ();

   Animation &    start (TimePoint current_time);
   Animation &    stop ();

   T              get (TimePoint current_time);

   void           pulse (TimePoint start_time, Duration duration, TransitionFunction function, T val1, T val2);
   void           pulse_twice (TimePoint start_time, Duration duration, TransitionFunction function, T val1, T val2);
   void           pulse_thrice (TimePoint start_time, Duration duration, TransitionFunction function, T val1, T val2);
   void           blink (TimePoint start_time, Duration period, TransitionFunction function, T val1, T val2);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   struct Block
   {
      T           start;
      T           target;
      uint64_t    duration;
      TransitionFunction
                  function;
   };

   using Blocks = std::array <Block, NbrKeyframes>;

   void           process_one_shot (TimePoint current_time);
   void           process_loop (TimePoint current_time);
   void           process_blocks (uint64_t position);

   Blocks         _blocks;
   size_t         _nbr_blocks = 0ull;
   uint64_t       _blocks_duration = 0ull;
   T              _value = {};
   TimePoint      _start_time = 0ull;
   bool           _loop_flag = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Animation (const Animation & rhs) = delete;
                  Animation (Animation && rhs) = delete;
   Animation &    operator = (const Animation & rhs) = delete;
   Animation &    operator = (Animation && rhs) = delete;
   bool           operator == (const Animation & rhs) const = delete;
   bool           operator != (const Animation & rhs) const = delete;



}; // class Animation



}  // namespace erb



#include "erb/detail/Animation.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
