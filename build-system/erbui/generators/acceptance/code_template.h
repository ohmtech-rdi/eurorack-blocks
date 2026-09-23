/*****************************************************************************

      acceptance_glue.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstddef>

struct %module.name%;



namespace erb
{
namespace rig
{



void  glue_init (%module.name% & module);
void  glue_preprocess (%module.name% & module);
void  glue_process (%module.name% & module);
void  glue_postprocess (%module.name% & module);
void  glue_idle (%module.name% & module);

const char *
      glue_control_name (const %module.name% & module, const void * control_ptr);



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
