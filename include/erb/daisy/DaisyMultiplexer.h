/*****************************************************************************

      DaisyMultiplexer.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyAnalogControlBase.h"
#include "erb/daisy/DaisyPins.h"

#include <array>

#include <cstdint>



namespace erb
{



class DaisyAnalogControlBase;
class DaisyModule;

class DaisyMultiplexer
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DaisyMultiplexer (DaisyModule & module, const AdcPin & pin, const Pin & pin_a);
                  DaisyMultiplexer (DaisyModule & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b);
                  DaisyMultiplexer (DaisyModule & module, const AdcPin & pin, const Pin & pin_a, const Pin & pin_b, const Pin & pin_c);
   virtual        ~DaisyMultiplexer () override = default;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (DaisyAnalogControlBase & control, size_t idx);
   void           impl_bind (uint16_t * val_u16_ptr);

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_MAX_CONTROLS = 8 };

   using Controls = std::array <DaisyAnalogControlBase *, NBR_MAX_CONTROLS>;

   Controls       _controls = {};



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyMultiplexer () = delete;
                  DaisyMultiplexer (const DaisyMultiplexer & rhs) = delete;
                  DaisyMultiplexer (DaisyMultiplexer && rhs) = delete;
   DaisyMultiplexer &  operator = (const DaisyMultiplexer & rhs) = delete;
   DaisyMultiplexer &  operator = (DaisyMultiplexer && rhs) = delete;
   bool           operator == (const DaisyMultiplexer & rhs) const = delete;
   bool           operator != (const DaisyMultiplexer & rhs) const = delete;



}; // class DaisyMultiplexer



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
