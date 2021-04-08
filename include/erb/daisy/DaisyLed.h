/*****************************************************************************

      DaisyLed.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyModuleListener.h"
#include "erb/daisy/DaisyPins.h"

#include "per/gpio.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class DaisyModule;

class DaisyLed
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  DaisyLed (DaisyModule & module, const Pin & pin);
   virtual        ~DaisyLed () = default;

   void           on (bool state = true);
   void           off ();
   void           pulse (std::chrono::milliseconds duration = 200ms);
   void           blink (std::chrono::milliseconds half_period = 500ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // DaisyModuleListener
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
                  to_gpio (const Pin & pin);

   DaisyModule &       _module;
   const dsy_gpio _gpio;

   Mode           _mode;
   bool           _current = false;
   uint64_t       _start = 0;
   uint64_t       _duration = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyLed () = delete;
                  DaisyLed (const DaisyLed & rhs) = delete;
                  DaisyLed (DaisyLed && rhs) = delete;
   DaisyLed &     operator = (const DaisyLed & rhs) = delete;
   DaisyLed &     operator = (DaisyLed && rhs) = delete;
   bool           operator == (const DaisyLed & rhs) const = delete;
   bool           operator != (const DaisyLed & rhs) const = delete;



}; // class DaisyLed



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
