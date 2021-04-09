/*****************************************************************************

      DaisyAnalogControlBase.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyModuleListener.h"
#include "erb/daisy/DaisyPins.h"

#include <cstdint>



namespace erb
{



class DaisyModule;
class DaisyMultiplexer;

class DaisyAnalogControlBase
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DaisyAnalogControlBase (DaisyModule & module, const AdcPin & pin);
                  DaisyAnalogControlBase (DaisyMultiplexer & multiplexer, const MultiplexerPin & pin);
   virtual        ~DaisyAnalogControlBase () override = default;

   float          norm_val () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (uint16_t * val_u16_ptr);

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   uint16_t *     _val_u16_ptr = nullptr;
   float          _norm_val = 0.f;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyAnalogControlBase () = delete;
                  DaisyAnalogControlBase (const DaisyAnalogControlBase & rhs) = delete;
                  DaisyAnalogControlBase (DaisyAnalogControlBase && rhs) = delete;
   DaisyAnalogControlBase &
                  operator = (const DaisyAnalogControlBase & rhs) = delete;
   DaisyAnalogControlBase &
                  operator = (DaisyAnalogControlBase && rhs) = delete;
   bool           operator == (const DaisyAnalogControlBase & rhs) const = delete;
   bool           operator != (const DaisyAnalogControlBase & rhs) const = delete;



}; // class DaisyAnalogControlBase



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
