/*****************************************************************************

      Animation.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <algorithm>



namespace erb
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : set
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::set (T value)
{
   _value = value;
   _nbr_blocks = 0;
   _loop_flag = false;
}



/*
==============================================================================
Name : set
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
Animation <T, NbrKeyframes> & Animation <T, NbrKeyframes>::set (std::initializer_list <Keyframe> keyframes)
{
   _nbr_blocks = std::min (keyframes.size (), NbrKeyframes);

   T start = _value;
   _blocks_duration = 0ull;

   for (size_t i = 0 ; i < _nbr_blocks ; ++i)
   {
      auto & block = _blocks [i];
      const auto & keyframe = *(keyframes.begin () + i);

      block.start = start;
      block.target = keyframe.target;
      block.duration = uint64_t (keyframe.transition_duration.count ());
      block.function = keyframe.transition_function;

      start = keyframe.target;
      _blocks_duration += block.duration;
   }

   _loop_flag = false;

   return *this;
}



/*
==============================================================================
Name : loop
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
Animation <T, NbrKeyframes> & Animation <T, NbrKeyframes>::loop ()
{
   _loop_flag = true;

   if (_nbr_blocks == 0) return *this;  // abort

   _blocks [0].start = _blocks [_nbr_blocks - 1].target;

   return *this;
}



/*
==============================================================================
Name : start
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
Animation <T, NbrKeyframes> & Animation <T, NbrKeyframes>::start (TimePoint current_time)
{
   _start_time = current_time;

   return *this;
}



/*
==============================================================================
Name : stop
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
Animation <T, NbrKeyframes> & Animation <T, NbrKeyframes>::stop ()
{
   _nbr_blocks = 0;
   _loop_flag = false;

   return *this;
}



/*
==============================================================================
Name : get
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
T Animation <T, NbrKeyframes>::get (TimePoint current_time)
{
   if (_nbr_blocks > 0)
   {
      if (_loop_flag)
      {
         process_loop (current_time);
      }
      else
      {
         process_one_shot (current_time);
      }
   }

   return _value;
}



/*
==============================================================================
Name : pulse
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::pulse (TimePoint start_time, Duration duration, TransitionFunction function, T val1, T val2)
{
   set (val1);

   set ({
      {val2, duration, function}
   });

   start (start_time);
}



/*
==============================================================================
Name : pulse_twice
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::pulse_twice (TimePoint start_time, Duration duration, TransitionFunction function, T val1, T val2)
{
   set (val1);

   set ({
      {val2, duration / 3, function},
      {val1, duration / 3, function},
      {val2, duration / 3, function}
   });

   start (start_time);
}



/*
==============================================================================
Name : pulse_thrice
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::pulse_thrice (TimePoint start_time, Duration duration, TransitionFunction function, T val1, T val2)
{
   set (val1);

   set ({
      {val2, duration / 5, function},
      {val1, duration / 5, function},
      {val2, duration / 5, function},
      {val1, duration / 5, function},
      {val2, duration / 5, function}
   });

   start (start_time);
}



/*
==============================================================================
Name : blink
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::blink (TimePoint start_time, Duration period, TransitionFunction function, T val1, T val2)
{
   set ({
      {val1, period / 2, function},
      {val2, period / 2, function}
   });

   loop ();

   start (start_time);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process_one_shot
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::process_one_shot (TimePoint current_time)
{
   auto position = current_time - _start_time;

   if (position > _blocks_duration)
   {
      _nbr_blocks = 0;
      return;  // abort
   }

   process_blocks (position);
}



/*
==============================================================================
Name : process_loop
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::process_loop (TimePoint current_time)
{
   uint64_t position;

   do
   {
      position = current_time - _start_time;
      if (position > _blocks_duration)
      {
         _start_time += _blocks_duration;
      }
   }
   while (position > _blocks_duration);

   process_blocks (position);
}



/*
==============================================================================
Name : process_blocks
==============================================================================
*/

template <typename T, size_t NbrKeyframes>
void  Animation <T, NbrKeyframes>::process_blocks (uint64_t position)
{
   for (size_t i = 0 ; i < _nbr_blocks ; ++i)
   {
      auto && block = _blocks [i];

      if (position <= block.duration)
      {
         float t = float (position) / float (block.duration);
         t = block.function (t);

         _value = static_cast <T> (interpolate (block.start, block.target, t));

         break;
      }

      position -= block.duration;
   }
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
