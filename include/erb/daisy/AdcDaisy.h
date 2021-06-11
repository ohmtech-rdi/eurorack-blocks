/*****************************************************************************

      AdcDaisy.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

erb_DISABLE_WARNINGS_DAISY
#include "per/gpio.h"
erb_RESTORE_WARNINGS

#include <array>



namespace daisy
{
class AdcHandle;
}

namespace erb
{



template <size_t MaxNbrData>
class AdcDaisy
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   using Pin = dsy_gpio_pin;

   struct MuxAddress
   {
      Pin         pin_a = PinNC;
      Pin         pin_b = PinNC;
      Pin         pin_c = PinNC;
   };

   struct Channel
   {
      Pin         pin;
      size_t      nbr_channels = 1;
      MuxAddress  address = MuxAddress {};
   };

   inline         AdcDaisy (daisy::AdcHandle & adc, std::initializer_list <Channel> channels);
   virtual        ~AdcDaisy () = default;

   inline uint16_t
                  read (size_t index);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static constexpr Pin PinNC = {DSY_GPIOX, 0};



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   std::array <uint16_t *, MaxNbrData>
                  _data;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AdcDaisy (const AdcDaisy & rhs) = delete;
                  AdcDaisy (AdcDaisy && rhs) = delete;
   AdcDaisy &
                  operator = (const AdcDaisy & rhs) = delete;
   AdcDaisy &
                  operator = (AdcDaisy && rhs) = delete;
   bool           operator == (const AdcDaisy & rhs) const = delete;
   bool           operator != (const AdcDaisy & rhs) const = delete;



}; // class AdcDaisy



}  // namespace erb



#include "erb/daisy/AdcDaisy.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
