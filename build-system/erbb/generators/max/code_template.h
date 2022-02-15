/*****************************************************************************

      %module.name%.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%Ui.h"
%include module.nameData.h%

#include "erb/erb.h"

#include "module_max_alt.h"

#include <array>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct %module.name%
{
   %module.name%Ui ui;
%  module.nameData data;%

   void  init ();
   void  process ();

   void  preprocess_params ();
   void  perform ();
   void  postprocess_params ();

   module_max::State state;
   std::array <float, erb_BUFFER_SIZE> silence = {};
};
