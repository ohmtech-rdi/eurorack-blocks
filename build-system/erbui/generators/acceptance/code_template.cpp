/*****************************************************************************

      acceptance_glue.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "acceptance_glue.h"

#include "%module.name%.h"

#include "erb/module_fnc.h"

#include <cassert>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : glue_init
==============================================================================
*/

void  glue_init (%module.name% & module)
{
   erb::module_init (module);
}



/*
==============================================================================
Name : glue_preprocess
==============================================================================
*/

void  glue_preprocess (%module.name% & module)
{
   module.ui.board.impl_preprocess ();

%  controls_preprocess%
}



/*
==============================================================================
Name : glue_process
==============================================================================
*/

void  glue_process (%module.name% & module)
{
   module.process ();
}



/*
==============================================================================
Name : glue_postprocess
==============================================================================
*/

void  glue_postprocess (%module.name% & module)
{
%  controls_postprocess%

   module.ui.board.impl_postprocess ();
}



/*
==============================================================================
Name : glue_idle
==============================================================================
*/

void  glue_idle (%module.name% & module)
{
   erb::module_idle (module);
}



/*
==============================================================================
Name : glue_control_name
Description :
   Returns the erbui name of a control.
==============================================================================
*/

const char *  glue_control_name (const %module.name% & module, const void * control_ptr)
{
%  controls_name%
   assert (false);
   return nullptr;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
