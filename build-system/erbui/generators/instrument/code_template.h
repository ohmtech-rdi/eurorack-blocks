/*****************************************************************************

      %module.name%Module.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%.h"

#include "erb/module_fnc.h"
#include "erb/instrument/ModuleBoard.h"

#include "erb/def.h"

#include <chrono>
#include <cmath>
#include <cstdef>



/*\\\ CLASSES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

class %module.name%Module
{
public:
   inline         %module.name%Module ();

   inline void    reboot ();

   inline void    run (std::chrono::duration <float> duration);

   inline void    process ();
   inline void    idle ();

   erb::Clock     clock;

private:
   static_assert (sizeof (%module.name%) < 128 * 1024 /* 128K */, "");

   erb::ModuleBoard
                  _module_board;
   std::unique_ptr <%module.name%>
                  _module_uptr;

};



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : %module.name%Module::ctor
==============================================================================
*/

%module.name%Module::%module.name%Module ()
{
   reboot ();
}



/*
==============================================================================
Name : %module.name%Module::reboot
==============================================================================
*/

%module.name%Module::reboot ()
{
   erb::ModuleBoard::Scoped scoped { _module_board };

   _module_uptr = std::make_unique <%module.name%> ();
   auto & module = *_module_uptr;

   // bind

%  module.controls.bind%

   erb::module_init (module);
}



/*
==============================================================================
Name : %module.name%Module::run
==============================================================================
*/

void  %module.name%Module::run (std::chrono::duration <float> duration)
{
   constexpr float process_period = float (erb_BUFFER_SIZE) / float (erb_SAMPLE_RATE);

   // assume the "idle thread" is running every 6ms
   const auto nbr_process_per_idle = std::size_t (std::ceil (0.006f / process_period));
   const auto nbr_process = std::size_t (std::ceil (duration.count () / process_period));

   for (std::size_t i = 0 ; i < nbr_process ; ++i)
   {
      process ();

      if (i % nbr_process_per_idle == 0) idle ();
   }
}



/*
==============================================================================
Name : %module.name%Module::process
==============================================================================
*/

void  %module.name%Module::process ()
{
   erb::ModuleBoard::Scoped scoped {module_board};

   auto & module = *module_uptr;

   check_all_inputs_specified ();

%  normalling_process%
   module.ui.board.impl_pull_audio_inputs ();

   module.ui.board.impl_preprocess ();

%  controls_preprocess%
   module.process ();

%  controls_postprocess%
   module.ui.board.impl_postprocess ();
}


/*
==============================================================================
Name : %module.name%Module::idle
==============================================================================
*/

void  %module.name%Module::idle ()
{
   erb::ModuleBoard::Scoped scoped {module_board};

   auto & module = *module_uptr;
   erb::module_idle (module);
}



/*
==============================================================================
Name : ErbModule::onAdd
==============================================================================
*/

void  ErbModule::onAdd (const rack::engine::Module::AddEvent & e)
{
   erb::ModuleBoard::Scoped scoped {module_board};

   auto & module = *module_uptr;

   erb::module_init (module);
}



/*
==============================================================================
Name : ErbModule::dataToJson
==============================================================================
*/

json_t * ErbModule::dataToJson ()
{
   erb::ModuleBoard::Scoped scoped {module_board};

   auto & module = *module_uptr;

   json_t * root_json = json_object ();
   json_t * persistent_json = json_array ();

   for (auto && item : module.ui.board.use_persistent_map ())
   {
      const auto page = item.first;
      const auto data = item.second;

      std::ostringstream sstr;
      sstr << std::hex << std::setfill ('0');

      for (auto b : data)
      {
         sstr << std::setw (2) << int (b);
      }

      auto data_str = sstr.str ();

      json_t * item_json = json_object ();
      json_object_set_new (item_json, "page", json_integer (page));
      json_object_set_new (item_json, "data", json_string (data_str.c_str ()));

      json_array_append_new (persistent_json, item_json);
   }

   json_object_set_new (root_json, "persistent", persistent_json);

   return root_json;
}



/*
==============================================================================
Name : ErbModule::dataFromJson
==============================================================================
*/

void  ErbModule::dataFromJson (json_t * root)
{
   erb::ModuleBoard::Scoped scoped {module_board};

   auto & module = *module_uptr;

   json_t * persistent_json = json_object_get (root, "persistent");

   if (persistent_json)
   {
      auto & persistent = module.ui.board.use_persistent_map ();

      json_t * item_json;
      size_t index;
      json_array_foreach (persistent_json, index, item_json)
      {
         json_t * page_json = json_object_get (item_json, "page");
         json_t * data_json = json_object_get (item_json, "data");

         auto page = size_t (json_integer_value (page_json));
         auto data_str = std::string (json_string_value (data_json));

         std::vector <uint8_t> data (data_str.size () / 2);

         for (size_t i = 0 ; i < data.size () ; ++i)
         {
            std::istringstream sstr {std::string {data_str, i * 2, 2}};
            int val;
            sstr >> std::hex >> std::setw (2) >> val;
            data [i] = uint8_t (val);
         }

         persistent [page] = data;
      }
   }
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

   if (%add_screws%)
   {
      addChild (createWidget <ScrewSilver> (Vec (RACK_GRID_WIDTH, 0)));
      addChild (createWidget <ScrewSilver> (Vec (box.size.x - 2 * RACK_GRID_WIDTH, 0)));
      addChild (createWidget <ScrewSilver> (Vec (RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
      addChild (createWidget <ScrewSilver> (Vec (box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   }

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
