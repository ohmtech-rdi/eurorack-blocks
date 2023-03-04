/*****************************************************************************

      %module.name%_erbb.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%.h"

#include <cstddef>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init
==============================================================================
*/

void  %module.name%::init ()
{
   state.reset (erb_SAMPLE_RATE, erb_BUFFER_SIZE);

   struct MaxErbDataAdapter
   {
      // as in genlib.cpp t_erb_sample_data
      std::size_t frames;
      std::size_t channels;
      const void * data; // interleaved 32-bit floats
   };

%  state.set_data%
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  %module.name%::process ()
{
   preprocess_params ();
   perform ();
   postprocess_params ();
}
