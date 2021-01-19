/*****************************************************************************

      GateIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/ModuleListener.h"

#include "daisy_core.h"
#include "per/gpio.h"



namespace erb
{



class Module;

class GateIn
:  public ModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Mode
   {
      Trigger, Gate
   };

                  GateIn (Module & module, const dsy_gpio_pin & pin, Mode mode = Mode::Trigger);
   virtual        ~GateIn () override = default;

   void           set_mode (Mode mode);
                  operator bool () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  GateIn (const dsy_gpio_pin & pin, Mode mode);

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   static dsy_gpio
                  to_gpio (const dsy_gpio_pin & pin);

   const dsy_gpio _gpio;

   Mode           _mode;
   bool           _previous = false;
   bool           _current = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GateIn () = delete;
                  GateIn (const GateIn & rhs) = delete;
                  GateIn (GateIn && rhs) = delete;
   GateIn &       operator = (const GateIn & rhs) = delete;
   GateIn &       operator = (GateIn && rhs) = delete;
   bool           operator == (const GateIn & rhs) const = delete;
   bool           operator != (const GateIn & rhs) const = delete;



}; // class GateIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
