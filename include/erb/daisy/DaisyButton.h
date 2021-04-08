/*****************************************************************************

      DaisyButton.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyModuleListener.h"
#include "erb/daisy/DaisyPins.h"

#include "per/gpio.h"



namespace erb
{



class DaisyModule;

class DaisyButton
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  DaisyButton (DaisyModule & module, const Pin & pin);
   virtual        ~DaisyButton () override = default;

   bool           pressed () const;
   bool           held () const;
   bool           released () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   static dsy_gpio
                  to_gpio (const Pin & pin);

   const dsy_gpio _gpio;

   uint8_t        _state = 0xff;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyButton () = delete;
                  DaisyButton (const DaisyButton & rhs) = delete;
                  DaisyButton (DaisyButton && rhs) = delete;
   DaisyButton &       operator = (const DaisyButton & rhs) = delete;
   DaisyButton &       operator = (DaisyButton && rhs) = delete;
   bool           operator == (const DaisyButton & rhs) const = delete;
   bool           operator != (const DaisyButton & rhs) const = delete;



}; // class DaisyButton



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
