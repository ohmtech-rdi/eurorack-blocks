/*****************************************************************************

      Led.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/ModuleListener.h"

#include "daisy_core.h"
#include "per/gpio.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class Module;

class Led
:  public ModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Led (Module & module, const dsy_gpio_pin & pin);
   virtual        ~Led () = default;

   void           on (bool state = true);
   void           off ();
   void           pulse (std::chrono::milliseconds duration = 200ms);
   void           blink (std::chrono::milliseconds half_period = 500ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum class Mode
   {
      Constant, Pulse, Blink,
   };

   static dsy_gpio
                  to_gpio (const dsy_gpio_pin & pin);

   Module &       _module;
   const dsy_gpio _gpio;

   Mode           _mode;
   bool           _current = false;
   uint32_t       _start = 0;
   uint32_t       _duration = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Led () = delete;
                  Led (const Led & rhs) = delete;
                  Led (Led && rhs) = delete;
   Led &          operator = (const Led & rhs) = delete;
   Led &          operator = (Led && rhs) = delete;
   bool           operator == (const Led & rhs) const = delete;
   bool           operator != (const Led & rhs) const = delete;



}; // class Led



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
