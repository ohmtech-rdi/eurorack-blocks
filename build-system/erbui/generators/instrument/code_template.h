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

   inline void    run (std::chrono::duration <double> duration);

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

void  %module.name%Module::run (std::chrono::duration <double> duration)
{
   constexpr double process_period = double (erb_BUFFER_SIZE) / double (erb_SAMPLE_RATE);

   // assume the "idle thread" is running every 6ms
   const auto nbr_process_per_idle = std::size_t (std::ceil (0.006 / process_period));
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



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
