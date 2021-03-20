/*****************************************************************************

      AdcChannels.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Pins.h"

#include <array>



namespace daisy
{
class DaisySeed;
}



namespace erb
{



class AnalogControlBase;
class Multiplexer;

class AdcChannels
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  AdcChannels (daisy::DaisySeed & seed);
   virtual        ~AdcChannels () = default;

   void           add (AnalogControlBase & control, const Pin & pin);
   void           add (Multiplexer & multiplexer, const Pin & pin, const MultiplexerAddressPins & address_pins);

   void           init ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Channel
   {
      dsy_gpio_pin
                  pin;

      // Single
      AnalogControlBase *
                  control_ptr = nullptr;

      // Multiplexer
      Multiplexer *
                  multiplexer_ptr = nullptr;
      MultiplexerAddressPins
                  address_pins;
   };

   enum {         NBR_MAX_ADC_CHANNELS = 12 };

   daisy::DaisySeed &
                  _seed;

   std::array <Channel, NBR_MAX_ADC_CHANNELS>
                  _channels;
   size_t         _nbr_adc_channel = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AdcChannels (const AdcChannels & rhs) = delete;
                  AdcChannels (AdcChannels && rhs) = delete;
   AdcChannels &  operator = (const AdcChannels & rhs) = delete;
   AdcChannels &  operator = (AdcChannels && rhs) = delete;
   bool           operator == (const AdcChannels & rhs) const = delete;
   bool           operator != (const AdcChannels & rhs) const = delete;



}; // class AdcChannels



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
