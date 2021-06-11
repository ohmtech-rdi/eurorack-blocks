/*****************************************************************************

      GpioOutputDaisy.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "daisy_core.h"
erb_RESTORE_WARNINGS



namespace erb
{



class GpioOutputDaisy
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   inline         GpioOutputDaisy (const dsy_gpio_pin & pin);
   virtual        ~GpioOutputDaisy () = default;

   inline void    write (bool val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   dsy_gpio       _impl;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GpioOutputDaisy (const GpioOutputDaisy & rhs) = delete;
                  GpioOutputDaisy (GpioOutputDaisy && rhs) = delete;
   GpioOutputDaisy &
                  operator = (const GpioOutputDaisy & rhs) = delete;
   GpioOutputDaisy &
                  operator = (GpioOutputDaisy && rhs) = delete;
   bool           operator == (const GpioOutputDaisy & rhs) const = delete;
   bool           operator != (const GpioOutputDaisy & rhs) const = delete;



}; // class GpioOutputDaisy



}  // namespace erb



#include "erb/daisy/GpioOutputDaisy.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
