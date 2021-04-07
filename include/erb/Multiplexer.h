/*****************************************************************************

      Multiplexer.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AnalogControlBase.h"
#include "erb/Pins.h"

#include <array>

#include <cstdint>



namespace erb
{



class AnalogControlBase;
class Module;

class Multiplexer
:  public ModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a);
                  Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b);
                  Multiplexer (Module & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b, const Pin & pin_c);
   virtual        ~Multiplexer () override = default;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (AnalogControlBase & control, size_t idx);
   void           impl_bind (uint16_t * val_u16_ptr);

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_MAX_CONTROLS = 8 };

   using Controls = std::array <AnalogControlBase *, NBR_MAX_CONTROLS>;

   Controls       _controls = {};



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Multiplexer () = delete;
                  Multiplexer (const Multiplexer & rhs) = delete;
                  Multiplexer (Multiplexer && rhs) = delete;
   Multiplexer &  operator = (const Multiplexer & rhs) = delete;
   Multiplexer &  operator = (Multiplexer && rhs) = delete;
   bool           operator == (const Multiplexer & rhs) const = delete;
   bool           operator != (const Multiplexer & rhs) const = delete;



}; // class Multiplexer



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
