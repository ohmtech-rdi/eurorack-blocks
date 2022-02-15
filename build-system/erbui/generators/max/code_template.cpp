/*****************************************************************************

      %module.name%_erbui.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : preprocess_params
==============================================================================
*/

void  %module.name%::preprocess_params ()
{
%  state.set_param%
}



/*
==============================================================================
Name : perform
==============================================================================
*/

void  %module.name%::perform ()
{
   const float * const in [] = {
%  module.audio_inputs%
   };

   float * const out [] = {
%  module.audio_outputs%
   };

   auto ins = const_cast <float **> (in);
   auto outs = const_cast <float **> (out);

   state.perform (ins, outs, erb_BUFFER_SIZE);
}


/*
==============================================================================
Name : perform
==============================================================================
*/

void  %module.name%::postprocess_params ()
{
%  ui.param = state.m_param%
}
