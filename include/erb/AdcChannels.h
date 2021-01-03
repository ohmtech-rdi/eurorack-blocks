/*****************************************************************************

      AdcChannels.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "per/adc.h"

#include <array>



namespace daisy
{
class DaisySeed;
}



namespace erb
{



class CvIn;

class AdcChannels
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  AdcChannels (daisy::DaisySeed & seed);
   virtual        ~AdcChannels () = default;

   void           add (CvIn & cv_in, const dsy_gpio_pin & pin);

   void           init ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Channel
   {
      CvIn *      cv_in_ptr = nullptr;
      dsy_gpio_pin
                  pin;
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
