/*****************************************************************************

      VcvPot.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvPot.h"

#include "erb/vcvrack/VcvModule.h"
#include "erb/vcvrack/VcvMultiplexer.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvPot::VcvPot (VcvModule & module, const VcvAdcPin & /* pin */, Mode mode)
:  VcvParamBase (module)
,  _mode (mode)
{
}



/*
==============================================================================
Name : ctor
==============================================================================
*/

VcvPot::VcvPot (VcvMultiplexer & multiplexer, const VcvMultiplexerPin & /* pin */, Mode mode)
:  VcvParamBase (multiplexer.module ())
,  _mode (mode)
{
}



/*
==============================================================================
Name : set_mode
==============================================================================
*/

void  VcvPot::set_mode (Mode mode)
{
   _mode = mode;
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

VcvPot::operator float () const
{
   switch (_mode)
   {
   case Mode::Normalized:
#if defined (__GNUC__) && ! defined (__clang__)
   default:
#endif
      return norm_val ();

   case Mode::Bipolar:
      return norm_val () * 2.f - 1.f;
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
