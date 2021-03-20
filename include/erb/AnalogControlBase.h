/*****************************************************************************

      AnalogControlBase.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/ModuleListener.h"
#include "erb/Pins.h"

#include <cstdint>



namespace erb
{



class Module;
class Multiplexer;

class AnalogControlBase
:  public ModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  AnalogControlBase (Module & module, const AdcPin & pin);
                  AnalogControlBase (Multiplexer & multiplexer, const MultiplexerPin & pin);
   virtual        ~AnalogControlBase () override = default;

   float          norm_val () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (uint16_t * val_u16_ptr);

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   uint16_t *     _val_u16_ptr = nullptr;
   float          _norm_val = 0.f;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AnalogControlBase () = delete;
                  AnalogControlBase (const AnalogControlBase & rhs) = delete;
                  AnalogControlBase (AnalogControlBase && rhs) = delete;
   AnalogControlBase &
                  operator = (const AnalogControlBase & rhs) = delete;
   AnalogControlBase &
                  operator = (AnalogControlBase && rhs) = delete;
   bool           operator == (const AnalogControlBase & rhs) const = delete;
   bool           operator != (const AnalogControlBase & rhs) const = delete;



}; // class AnalogControlBase



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
