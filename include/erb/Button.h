/*****************************************************************************

      Button.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Control.h"

#include "daisy_core.h"
#include "per/gpio.h"



namespace erb
{



class Module;

class Button
:  public Control
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Button (Module & module, const dsy_gpio_pin & pin);
   virtual        ~Button () override = default;

   bool           pressed () const;
   bool           held () const;
   bool           released () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // Control
   virtual void   impl_process () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   static dsy_gpio
                  to_gpio (const dsy_gpio_pin & pin);

   const dsy_gpio _gpio;

   uint8_t        _state = 0xff;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Button () = delete;
                  Button (const Button & rhs) = delete;
                  Button (Button && rhs) = delete;
   Button &       operator = (const Button & rhs) = delete;
   Button &       operator = (Button && rhs) = delete;
   bool           operator == (const Button & rhs) const = delete;
   bool           operator != (const Button & rhs) const = delete;



}; // class Button



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
