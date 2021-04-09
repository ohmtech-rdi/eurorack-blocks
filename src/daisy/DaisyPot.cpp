/*****************************************************************************

      DaisyPot.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyPot.h"

#include "erb/daisy/DaisyModule.h"
#include "erb/def.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

DaisyPot::DaisyPot (DaisyModule & module, const AdcPin & pin, Mode mode)
:  DaisyAnalogControlBase (module, pin)
,  _mode (mode)
{
}



/*
==============================================================================
Name : ctor
Note : DaisyMultiplexer version
==============================================================================
*/

DaisyPot::DaisyPot (DaisyMultiplexer & multiplexer, const MultiplexerPin & pin, Mode mode)
:  DaisyAnalogControlBase (multiplexer, pin)
,  _mode (mode)
{
}



/*
==============================================================================
Name : set_mode
==============================================================================
*/

void  DaisyPot::set_mode (Mode mode)
{
   _mode = mode;
}



/*
==============================================================================
Name : operator float
==============================================================================
*/

DaisyPot::operator float () const
{
   switch (_mode)
   {
   case Mode::Normalized:
#if erb_GNUC_SWITCH_COVERAGE_FIX
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
