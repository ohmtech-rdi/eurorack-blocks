/*****************************************************************************

      DropPluginVcv.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DropModule.h"

#include <rack.hpp>

extern rack::Plugin * pluginInstance;
extern rack::Model * modelDrop;



struct DropVcv
:  rack::engine::Module
{
                  DropVcv ();
   void           process (const ProcessArgs & /* args */) override;

   DropModule     module;

}; // class DropDsp



struct DropWidgetVcv
:  rack::ModuleWidget
{
                  DropWidgetVcv (DropVcv * module);

}; // class DropDsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
