/*****************************************************************************

      Ramp.hpp
      Copyright (c) 2021 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace dsp
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <size_t nbr_steps>
Ramp <nbr_steps>::Ramp (float initial_value)
{
   reset (initial_value);
}



/*
==============================================================================
Name : reset
==============================================================================
*/

template <size_t nbr_steps>
void  Ramp <nbr_steps>::reset (float initial_value)
{
   _current = initial_value;
   _target = initial_value;
   _step = 0.f;
   _cur_step = 0;
}



/*
==============================================================================
Name : operator =
==============================================================================
*/

template <size_t nbr_steps>
Ramp <nbr_steps> &   Ramp <nbr_steps>::operator = (float value)
{
   constexpr float scale = 1.f / float (nbr_steps);

   _target = value;
   _step = (_target - _current) * scale;
   _cur_step = nbr_steps;

   return *this;
}



/*
==============================================================================
Name : process
==============================================================================
*/

template <size_t nbr_steps>
float  Ramp <nbr_steps>::process ()
{
   if (!active ()) return _current; // abort

   _current += _step;
   --_cur_step;

   return _current;
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

template <size_t nbr_steps>
Ramp <nbr_steps>::operator float () const
{
   return _current;
}



/*
==============================================================================
Name : active
==============================================================================
*/

template <size_t nbr_steps>
bool  Ramp <nbr_steps>::active () const
{
   return _cur_step > 0;
}



/*
==============================================================================
Name : target
==============================================================================
*/

template <size_t nbr_steps>
float Ramp <nbr_steps>::target () const
{
   return _target;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace dsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
