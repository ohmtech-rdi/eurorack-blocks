/*****************************************************************************

      VcvGateOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvOutputBase.h"
#include "erb/vcvrack/VcvPins.h"

#include <chrono>

#include <cstdint>



namespace erb
{



using namespace std::chrono_literals;

class VcvModule;

class VcvGateOut
:  public VcvOutputBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VcvGateOut (VcvModule & module, const VcvPin & pin);
   virtual        ~VcvGateOut () override = default;

   void           on ();
   void           off ();
   void           trigger (std::chrono::milliseconds duration = 6ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum class Mode
   {
      Constant, Pulse
   };

   VcvModule &    _module;

   Mode           _mode;
   bool           _current = false;
   uint64_t       _start = 0;
   uint64_t       _duration = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvGateOut () = delete;
                  VcvGateOut (const VcvGateOut & rhs) = delete;
                  VcvGateOut (VcvGateOut && rhs) = delete;
   VcvGateOut &   operator = (const VcvGateOut & rhs) = delete;
   VcvGateOut &   operator = (VcvGateOut && rhs) = delete;
   bool           operator == (const VcvGateOut & rhs) const = delete;
   bool           operator != (const VcvGateOut & rhs) const = delete;



}; // class VcvGateOut



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
