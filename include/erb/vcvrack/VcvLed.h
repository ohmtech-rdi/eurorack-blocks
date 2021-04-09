/*****************************************************************************

      VcvLed.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvLightBase.h"
#include "erb/vcvrack/VcvPins.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class VcvModule;

class VcvLed
:  public VcvLightBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VcvLed (VcvModule & module, const VcvPin & pin);
   virtual        ~VcvLed () override = default;

   void           on (bool state = true);
   void           off ();
   void           pulse (std::chrono::milliseconds duration = 200ms);
   void           blink (std::chrono::milliseconds half_period = 500ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum class Mode
   {
      Constant, Pulse, Blink,
   };

   VcvModule &    _module;

   Mode           _mode;
   bool           _current = false;
   uint64_t       _start = 0;
   uint64_t       _duration = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvLed () = delete;
                  VcvLed (const VcvLed & rhs) = delete;
                  VcvLed (VcvLed && rhs) = delete;
   VcvLed &       operator = (const VcvLed & rhs) = delete;
      VcvLed &    operator = (VcvLed && rhs) = delete;
   bool           operator == (const VcvLed & rhs) const = delete;
   bool           operator != (const VcvLed & rhs) const = delete;



}; // class VcvLed



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
