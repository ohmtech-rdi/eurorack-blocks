/*****************************************************************************

      VoicesBody.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "VoiceBody.h"

#include <array>
#include <cstddef>



class VoicesBody
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VoicesBody () = default;
                  ~VoicesBody () = default;

   void           trigger ();

   void           set_speed (float step_spl);

   template <typename T>
   float          process (const T & sample);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   std::array <VoiceBody, 4>
                  _voices;
   size_t         _cur_voice = 0;
};



#include "VoicesBody.hpp"
