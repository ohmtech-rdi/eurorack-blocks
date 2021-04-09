/*****************************************************************************

      DaisyAdcChannels.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyPins.h"

#include <array>



namespace daisy
{
class DaisySeed;
}



namespace erb
{



class DaisyAnalogControlBase;
class DaisyMultiplexer;

class DaisyAdcChannels
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  DaisyAdcChannels (daisy::DaisySeed & seed);
   virtual        ~DaisyAdcChannels () = default;

   void           add (DaisyAnalogControlBase & control, const Pin & pin);
   void           add (DaisyMultiplexer & multiplexer, const Pin & pin, const DaisyMultiplexerAddressPins & address_pins);

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
      DaisyAnalogControlBase *
                  control_ptr = nullptr;

      // DaisyMultiplexer
      DaisyMultiplexer *
                  multiplexer_ptr = nullptr;
      DaisyMultiplexerAddressPins
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
                  DaisyAdcChannels (const DaisyAdcChannels & rhs) = delete;
                  DaisyAdcChannels (DaisyAdcChannels && rhs) = delete;
   DaisyAdcChannels &  operator = (const DaisyAdcChannels & rhs) = delete;
   DaisyAdcChannels &  operator = (DaisyAdcChannels && rhs) = delete;
   bool           operator == (const DaisyAdcChannels & rhs) const = delete;
   bool           operator != (const DaisyAdcChannels & rhs) const = delete;



}; // class DaisyAdcChannels



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
