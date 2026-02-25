/*****************************************************************************

      GpioInputDaisy.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "per/gpio.h"
erb_RESTORE_WARNINGS



namespace erb
{



class GpioInputDaisy
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Pull
   {
      None, Up, Down
   };

   inline         GpioInputDaisy (const daisy::Pin & pin, Pull pull = Pull::None);
   virtual        ~GpioInputDaisy () = default;

   inline bool    read ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   inline daisy::GPIO::Pull
                  to_daisy_GPIO_Pull (Pull pull);

   daisy::GPIO    _impl;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GpioInputDaisy (const GpioInputDaisy & rhs) = delete;
                  GpioInputDaisy (GpioInputDaisy && rhs) = delete;
   GpioInputDaisy &
                  operator = (const GpioInputDaisy & rhs) = delete;
   GpioInputDaisy &
                  operator = (GpioInputDaisy && rhs) = delete;
   bool           operator == (const GpioInputDaisy & rhs) const = delete;
   bool           operator != (const GpioInputDaisy & rhs) const = delete;



}; // class GpioInputDaisy



}  // namespace erb



#include "erb/daisy/GpioInputDaisy.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
