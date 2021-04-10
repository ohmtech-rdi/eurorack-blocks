/*****************************************************************************

      DropPluginVcv.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DropModule.h"

#include <rack.hpp>



/*\\\ CLASSES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct DropVcv
:  rack::engine::Module
{
                  DropVcv ();
   void           process (const ProcessArgs & /* args */) override;

   DropModule     module;

}; // struct DropDsp



struct DropWidgetVcv
:  rack::ModuleWidget
{
                  DropWidgetVcv (DropVcv * module);

}; // struct DropDsp



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

extern rack::Plugin * plugin_instance;
extern rack::Model * model_drop;

rack::Plugin * plugin_instance = nullptr;
rack::Model * model_drop = rack::createModel <DropVcv, DropWidgetVcv> ("Drop");



/*
==============================================================================
Name : init
==============================================================================
*/

void  init (rack::Plugin * p)
{
   plugin_instance = p;
   p->addModel (model_drop);
}



/*
==============================================================================
Name : DropVcv::ctor
==============================================================================
*/

DropVcv::DropVcv ()
{
   config (
      module.module.nbr_params (),
      module.module.nbr_inputs (),
      module.module.nbr_outputs (),
      module.module.nbr_lights ()
   );

   for (int i = 0 ; i < int (module.module.nbr_params ()) ; ++i)
   {
      configParam (i, 0.f, 1.f, 0.f);
   }

   // bind

   for (size_t i = 0 ; i < module.module.nbr_params () ; ++i)
   {
      module.module.impl_bind (i, params [i]);
   }

   for (size_t i = 0 ; i < module.module.nbr_inputs () ; ++i)
   {
      module.module.impl_bind (i, inputs [i]);
   }

   for (size_t i = 0 ; i < module.module.nbr_outputs () ; ++i)
   {
      module.module.impl_bind (i, outputs [i]);
   }

   for (size_t i = 0 ; i < module.module.nbr_lights () ; ++i)
   {
      module.module.impl_bind (i, lights [i]);
   }

   module.module.bind_process ([&](){
      module.process ();
   });
}



/*
==============================================================================
Name : DropVcv::process
==============================================================================
*/

void  DropVcv::process (const ProcessArgs & /* args */)
{
   module.module.impl_process ();
}



/*
==============================================================================
Name : DropWidgetVcv::ctor
==============================================================================
*/

DropWidgetVcv::DropWidgetVcv (DropVcv * module_)
{
   using namespace rack;

   setModule (module_);

   // panel

   setPanel (APP->window->loadSvg (
      asset::plugin (plugin_instance, "res/DropGuiVcv.svg"))
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

   // freq
   addParam (createParamCentered <Rogan5PSGray> (
      mm2px (Vec (20.32, 21.8)), module_, module_->module.freq.index ())
   );

   // HP/mute
   addParam (createParamCentered <CKSS> (
      mm2px (Vec (20.32, 46.7)), module_, module_->module.mute_hp.index ())
   );

   // State LED
   addChild (createLightCentered <MediumLight <GreenRedLight>> (
      mm2px (Vec (12.7, 63.1)), module_, module_->module.state_led.index ())
   );

   // Arm button
   addParam (createParamCentered <CKD6> (
      mm2px (Vec (27.94, 63.1)), module_, module_->module.arm_button.index ())
   );

   // Sync LED
   addChild (createLightCentered <MediumLight <RedLight>> (
      mm2px (Vec (12.7, 73.7)), module_, module_->module.sync_led.index ())
   );

   // Arm LED
   addChild (createLightCentered <MediumLight <RedLight>> (
      mm2px (Vec (27.94, 73.7)), module_, module_->module.arm_led.index ())
   );

   // Sync input
   addInput (createInputCentered <PJ301MPort> (
      mm2px (Vec (12.7, 84.25)), module_, module_->module.sync_gate.index ())
   );

   // Arm input
   addInput (createInputCentered <PJ301MPort> (
      mm2px (Vec (27.94, 84.25)), module_, module_->module.arm_gate.index ())
   );

   // Left input
   addInput (createInputCentered <PJ301MPort> (
      mm2px (Vec (12.7, 100.125)), module_, module_->module.audio_in_left.index ())
   );

   // Right input
   addInput (createInputCentered <PJ301MPort> (
      mm2px (Vec (27.94, 100.125)), module_, module_->module.audio_in_right.index ())
   );

   // Left output
   addOutput (createOutputCentered <PJ301MPort> (
      mm2px (Vec (12.7, 116)), module_, module_->module.audio_out_left.index ())
   );

   // Right output
   addOutput (createOutputCentered <PJ301MPort> (
      mm2px (Vec (27.94, 116)), module_, module_->module.audio_out_right.index ())
   );
}



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
