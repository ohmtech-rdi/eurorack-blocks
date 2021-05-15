/*****************************************************************************

      plugin_vcvrack.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "../%module.name%.h"

#include "erb/module_init.h"
#include "erb/vcvrack/VcvWidgets.h"

#include <rack.hpp>

#include <type_traits>



/*\\\ CLASSES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct ErbModule
:  rack::engine::Module
{
                  ErbModule ();
   void           process (const ProcessArgs & /* args */) override;

   %module.name% module;

}; // struct ErbModule



struct ErbWidget
:  rack::ModuleWidget
{
                  ErbWidget (ErbModule * module);

}; // struct ErbWidget



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

extern rack::Plugin * plugin_instance;
extern rack::Model * model;

rack::Plugin * plugin_instance = nullptr;
rack::Model * model = rack::createModel <ErbModule, ErbWidget> ("%module.name%");



/*
==============================================================================
Name : init
==============================================================================
*/

void  init (rack::Plugin * p)
{
   plugin_instance = p;
   p->addModel (model);
}



/*
==============================================================================
Name : ErbModule::ctor
==============================================================================
*/

ErbModule::ErbModule ()
{
   // The Daisy Seed stack, sitting on SRAM is 512K only.
   // When more memory is needed, move the big buffers like
   // delay lines or samples to the SDRAM, which is 64M.
   // Since we have some heap allocations, we keep a bit of margin
   // and complain when we reach 384K of stack space.

   static_assert (sizeof (module) < 384 * 1024 /* 384K */, "");

   // The SDRAM is compararively slow compared to the SRAM,
   // So try to keep all memory that is accessed often in SRAM.

   // Check 'erb::make_sdram_object' to put your buffers in
   // SDRAM.

   // We know this is not the Daisy target, but we complain
   // now so that you don't have a bad surprise when you build
   // for the Daisy target.

   config (
      module.ui.board.nbr_params (),
      module.ui.board.nbr_inputs (),
      module.ui.board.nbr_outputs (),
      module.ui.board.nbr_lights ()
   );

   // bind

   for (size_t i = 0 ; i < module.ui.board.nbr_params () ; ++i)
   {
      module.ui.board.impl_bind (i, params [i]);
   }

   for (size_t i = 0 ; i < module.ui.board.nbr_inputs () ; ++i)
   {
      module.ui.board.impl_bind (i, inputs [i]);
   }

   for (size_t i = 0 ; i < module.ui.board.nbr_outputs () ; ++i)
   {
      module.ui.board.impl_bind (i, outputs [i]);
   }

   for (size_t i = 0 ; i < module.ui.board.nbr_lights () ; ++i)
   {
      module.ui.board.impl_bind (i, lights [i]);
   }

   // configure params values

   for (size_t i = 0 ; i < module.ui.board.nbr_params () ; ++i)
   {
      float max_value = 1.f;

%controls_config%
      configParam (int (i), 0.f, max_value, 0.f);
   }

   erb::module_init (module);

   module.ui.board.bind_process ([&](){
      module.process ();
   });
}



/*
==============================================================================
Name : ErbModule::process
==============================================================================
*/

void  ErbModule::process (const ProcessArgs & /* args */)
{
   bool process_flag = module.ui.board.impl_need_process ();

   module.ui.board.impl_pull_audio_inputs ();

   if (process_flag)
   {
      module.ui.board.impl_preprocess ();

%controls_preprocess%

      module.ui.board.impl_process ();

%controls_postprocess%

      module.ui.board.impl_postprocess ();
   }

   module.ui.board.impl_push_audio_outputs ();
}



/*
==============================================================================
Name : ErbWidget::ctor
==============================================================================
*/

ErbWidget::ErbWidget (ErbModule * module_)
{
   using namespace rack;

   setModule (module_);

   // panel

   setPanel (APP->window->loadSvg (
      asset::plugin (plugin_instance, "res/panel_vcvrack.svg"))
   );

   // screws

   addChild (createWidget <ScrewSilver> (Vec (RACK_GRID_WIDTH, 0)));
   addChild (createWidget <ScrewSilver> (Vec (box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild (createWidget <ScrewSilver> (Vec (RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild (createWidget <ScrewSilver> (Vec (box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   // VcvRack is expecting static enumeration of parameters, etc.
   // But since we deduce them dynamically, we are just going to ignore
   // this.
   // In practice, when the module is loaded through the module browser
   // the constructor is called with a `nullptr` module.
   // We just skip this, so that the plug-in appears with only its
   // back panel.
   // This is probably fine for prototyping.

   if (module == nullptr) return;

   // controls

%controls%
}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
