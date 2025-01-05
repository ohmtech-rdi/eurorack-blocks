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
#include <osdialog.h>
erb_RESTORE_WARNINGS

#include <iomanip>
#include <memory>
#include <sstream>
#include <type_traits>



/*\\\ CLASSES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct ErbModule
:  rack::engine::Module
{
                  ErbModule ();
   void           process (const ProcessArgs & /* args */) override;

   void           onAdd (const rack::engine::Module::AddEvent & e) override;

   // Persistent & SdMmc support
   json_t *       dataToJson () override;
   void           dataFromJson (json_t * root) override;

   erb::ModuleBoard
                  module_board;
   std::unique_ptr <%module.name%>
                  module_uptr;

   std::string    sd_card_path;

}; // struct ErbModule



struct ErbWidget
:  rack::ModuleWidget
{
                  ErbWidget (ErbModule * module);

   template <typename T>
   void           add_child_auto (T * control_ptr)
   {
      if constexpr (T::BehindPanel)
      {
         addChildBottom (control_ptr);
      }
      else
      {
         addChild (control_ptr);
      }
   }

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   struct InsertSdCardItem : rack::ui::MenuItem
   {
      ErbWidget * parent = nullptr;

      void onAction (const ActionEvent & e) override
      {
         char * path_0 = osdialog_file (OSDIALOG_OPEN, nullptr, nullptr, nullptr);
         if (!path_0) return; // canceled

         auto & board = parent->module_ptr->module_uptr->ui.board;
         bool ok = board.set_sd (path_0);
         if (ok)
         {
            parent->sd_card_name = rack::system::getFilename (path_0);
            parent->module_ptr->sd_card_path = path_0;
         }

         std::free (path_0);
         path_0 = nullptr;
      }
   };

   struct EjectSdCardItem : rack::ui::MenuItem
   {
      ErbWidget * parent = nullptr;

      void onAction (const ActionEvent & e) override
      {
         auto & board = parent->module_ptr->module_uptr->ui.board;

         board.reset_sd ();
         parent->sd_card_name.clear ();
         parent->module_ptr->sd_card_path.clear ();
      }
   };
   void           appendContextMenu (rack::ui::Menu * menu) override;
   std::string    sd_card_name;
#endif

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

   if (!sd_card_path.empty ())
   {
      json_object_set_new (root_json, "sd_card_path", json_string (sd_card_path.c_str ()));
   }

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

   json_t * sd_card_path_json = json_object_get (root, "sd_card_path");

   if (sd_card_path_json)
   {
      sd_card_path = std::string (json_string_value ((sd_card_path_json)));

      auto & board = module_uptr->ui.board;

      bool ok = board.set_sd (sd_card_path.c_str ());
      if (!ok) sd_card_path.clear ();
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

   if (!module_ptr->sd_card_path.empty ())
   {
      sd_card_name = rack::system::getFilename (module_ptr->sd_card_path.c_str ());
   }

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



/*
==============================================================================
Name : ErbWidget::appendContextMenu
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
void  ErbWidget::appendContextMenu (rack::ui::Menu * menu)
{
   menu->addChild (new rack::ui::MenuSeparator);

   if (sd_card_name.empty ())
   {
      InsertSdCardItem * item = new InsertSdCardItem;
      item->text = "Insert SD card";
      item->parent = this;
      menu->addChild (item);
   }
   else
   {
      EjectSdCardItem * item = new EjectSdCardItem;
      item->text = std::string ("Eject SD card ") + sd_card_name;
      item->parent = this;
      menu->addChild (item);
   }
}
#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
