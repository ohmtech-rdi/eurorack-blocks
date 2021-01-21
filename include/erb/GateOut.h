/*****************************************************************************

      GateOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/ModuleListener.h"
#include "erb/Pins.h"

#include "per/gpio.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class Module;

class GateOut
:  public ModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  GateOut (Module & module, const Pin & pin);
   virtual        ~GateOut () = default;

   void           on ();
   void           off ();
   void           trigger (std::chrono::milliseconds duration = 6ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum class Mode
   {
      Constant, Pulse
   };

   static dsy_gpio
                  to_gpio (const Pin & pin);

   Module &       _module;
   const dsy_gpio _gpio;

   Mode           _mode;
   bool           _current = false;
   uint32_t       _start = 0;
   uint32_t       _duration = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GateOut () = delete;
                  GateOut (const GateOut & rhs) = delete;
                  GateOut (GateOut && rhs) = delete;
   GateOut &      operator = (const GateOut & rhs) = delete;
   GateOut &      operator = (GateOut && rhs) = delete;
   bool           operator == (const GateOut & rhs) const = delete;
   bool           operator != (const GateOut & rhs) const = delete;



}; // class GateOut



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
