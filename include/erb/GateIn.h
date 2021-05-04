/*****************************************************************************

      DaisyGateIn.h
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

class DaisyGateIn
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DaisyGateIn (DaisyModule & module, const Pin & pin);
   virtual        ~DaisyGateIn () override = default;

   bool           triggered () const;
                  operator bool () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  DaisyGateIn (const Pin & pin);

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   static dsy_gpio
                  to_gpio (const Pin & pin);

   const dsy_gpio _gpio;

   bool           _previous = false;
   bool           _current = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyGateIn () = delete;
                  DaisyGateIn (const DaisyGateIn & rhs) = delete;
                  DaisyGateIn (DaisyGateIn && rhs) = delete;
   DaisyGateIn &  operator = (const DaisyGateIn & rhs) = delete;
   DaisyGateIn &  operator = (DaisyGateIn && rhs) = delete;
   bool           operator == (const DaisyGateIn & rhs) const = delete;
   bool           operator != (const DaisyGateIn & rhs) const = delete;



}; // class DaisyGateIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
