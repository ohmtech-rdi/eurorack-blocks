/*****************************************************************************

      GpioInputDaisy.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

GpioInputDaisy::GpioInputDaisy (const daisy::Pin & pin, Pull pull)
{
   _impl.Init (pin, daisy::GPIO::Mode::INPUT, to_daisy_GPIO_Pull (pull));
}



/*
==============================================================================
Name : read
==============================================================================
*/

bool  GpioInputDaisy::read ()
{
   return _impl.Read ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : to_daisy_GPIO_Pull
==============================================================================
*/

daisy::GPIO::Pull  GpioInputDaisy::to_daisy_GPIO_Pull (Pull pull)
{
   switch (pull)
   {
   case Pull::None:
      return daisy::GPIO::Pull::NOPULL;
      //break;

   case Pull::Up:
      return daisy::GPIO::Pull::PULLUP;
      //break;

   case Pull::Down:
      return daisy::GPIO::Pull::PULLDOWN;
      //break;
   }

   return daisy::GPIO::Pull::NOPULL;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
