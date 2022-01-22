/*****************************************************************************

      VoiceTransient.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "dsp/Ramp.h"

#include <cstddef>



class VoiceTransient
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VoiceTransient () = default;
                  ~VoiceTransient () = default;

   void           trigger ();
   void           stop ();

   void           set_speed (float step_spl);

   template <typename T>
   float          process (const T & sample_1, const T & sample_2, float mix);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           _active_flag = false;
   float          _pos = 0.f;
   float          _step_spl = 1.f;
   dsp::Ramp <256>
                  _ramp = {1.f};
};



#include "VoiceTransient.hpp"
