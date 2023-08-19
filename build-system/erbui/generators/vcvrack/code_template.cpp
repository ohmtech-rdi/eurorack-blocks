/*****************************************************************************

      plugin_vcvrack.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%.h"

#include "erb/module_fnc.h"
#include "erb/vcvrack/ModuleBoard.h"
#include "erb/vcvrack/VcvWidgets.h"

#include "erb/def.h"

erb_DISABLE_WARNINGS_VCVRACK
#include <rack.hpp>
erb_RESTORE_WARNINGS

#include <memory>
#include <type_traits>



/*\\\ CLASSES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct ErbModule
:  rack::engine::Module
{
                  ErbModule ();
   void           process (const ProcessArgs & /* args */) override;

   erb::ModuleBoard
                  module_board;
   std::unique_ptr <%module.name%>
                  module_uptr;

}; // struct ErbModule



struct ErbWidget
:  rack::ModuleWidget
{
                  ErbWidget (ErbModule * module);

   void           step () override;

   ErbModule *    module_ptr = nullptr;
}; // struct ErbWidget



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

extern rack::Plugin * plugin_instance;
extern rack::Model * model;

rack::Plugin * plugin_instance = nullptr;

erb_DISABLE_WARNINGS_GLOBAL_CTOR
rack::Model * model = rack::createModel <ErbModule, ErbWidget> ("%module.name%");
erb_RESTORE_WARNINGS



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
   erb::ModuleBoard::Scoped scoped {module_board};

   module_uptr = std::make_unique <%module.name%> ();
   auto & module = *module_uptr;

   // The Daisy Seed stack, sitting on SRAM is 512K only.
   // When more memory is needed, move the big buffers like
   // delay lines or samples to the SDRAM, which is 64M.
   // Since we have some heap allocations, we keep a bit of margin
   // and complain when we reach 128K of stack space.

   static_assert (sizeof (module) < 128 * 1024 /* 128K */, "");

   // The SDRAM is compararively slow compared to the SRAM,
   // So try to keep all memory that is accessed often in SRAM.

   // Check 'erb::make_sdram_object' to put your buffers in
   // SDRAM.

   // We know this is not the Daisy target, but we complain
   // now so that you don't have a bad surprise when you build
   // for the Daisy target.

   config (
      /* nbr_params  */ %module.nbr_params%,
      /* nbr_inputs  */ %module.nbr_inputs%,
      /* nbr_outputs */ %module.nbr_outputs%,
      /* nbr_lights  */ %module.nbr_lights%
   );

   // bind

%  module.controls.bind+config%
   erb::module_init (module);
}



/*
==============================================================================
Name : ErbModule::process
==============================================================================
*/

void  ErbModule::process (const ProcessArgs & /* args */)
{
   erb::ModuleBoard::Scoped scoped {module_board};

   auto & module = *module_uptr;

   bool process_flag = module.ui.board.impl_need_process ();

%  normalling_process%
   module.ui.board.impl_pull_audio_inputs ();

   if (process_flag)
   {
      module.ui.board.impl_preprocess ();

%     controls_preprocess%
      module.process ();

%     controls_postprocess%
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
:  module_ptr (module_)
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

   // controls

%  controls_widget%
}



/*
==============================================================================
Name : ErbWidget::step
==============================================================================
*/

void  ErbWidget::step ()
{
   rack::Widget::step ();

   if (module_ptr == nullptr) return;
   if (!module_ptr->module_uptr) return;

   erb::module_idle (*module_ptr->module_uptr);
}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
