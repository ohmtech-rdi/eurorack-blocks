/*****************************************************************************

      Switch.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

template <size_t NbrPosition>
Switch <NbrPosition>::Switch (const uint8_t & data_0, const uint8_t & data_1)
:  _0 (data_0)
,  _1 (data_1)
{
}



/*
==============================================================================
Name : position_first
==============================================================================
*/

template <size_t NbrPosition>
bool  Switch <NbrPosition>::position_first () const
{
   return _0.held ();
}



/*
==============================================================================
Name : position_center
==============================================================================
*/

template <size_t NbrPosition>
bool  Switch <NbrPosition>::position_center () const
{
   return !_0.held () && !_1.held ();
}



/*
==============================================================================
Name : position_last
==============================================================================
*/

template <size_t NbrPosition>
bool  Switch <NbrPosition>::position_last () const
{
   return _1.held ();
}



/*
==============================================================================
Name : operator SwitchPosition
==============================================================================
*/

template <size_t NbrPosition>
Switch <NbrPosition>::operator SwitchPosition () const
{
   if (position_first ())
   {
      return SwitchPosition::First;
   }
   else if (position_last ())
   {
      return SwitchPosition::Last;
   }
   else
   {
      return SwitchPosition::Center;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_preprocess
==============================================================================
*/

template <size_t NbrPosition>
void  Switch <NbrPosition>::impl_preprocess ()
{
   _0.impl_preprocess ();
   _1.impl_preprocess ();
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
