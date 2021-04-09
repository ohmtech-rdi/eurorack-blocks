/*****************************************************************************

      DaisyGateOut.h
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

class DaisyGateOut
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  DaisyGateOut (DaisyModule & module, const Pin & pin);
   virtual        ~DaisyGateOut () = default;

   void           on ();
   void           off ();
   void           trigger (std::chrono::milliseconds duration = 6ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // DaisyModuleListener
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

   DaisyModule &       _module;
   const dsy_gpio _gpio;

   Mode           _mode;
   bool           _current = false;
   uint64_t       _start = 0;
   uint64_t       _duration = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyGateOut () = delete;
                  DaisyGateOut (const DaisyGateOut & rhs) = delete;
                  DaisyGateOut (DaisyGateOut && rhs) = delete;
   DaisyGateOut & operator = (const DaisyGateOut & rhs) = delete;
   DaisyGateOut & operator = (DaisyGateOut && rhs) = delete;
   bool           operator == (const DaisyGateOut & rhs) const = delete;
   bool           operator != (const DaisyGateOut & rhs) const = delete;



}; // class DaisyGateOut



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
