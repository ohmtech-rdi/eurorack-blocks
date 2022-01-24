/*****************************************************************************

      VoicesTransient.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "artifacts/KickData.h"

#include "VoiceTransient.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



class VoicesTransient
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VoicesTransient (const KickData & data) : _data (data) {}
                  ~VoicesTransient () = default;

   void           trigger ();

   void           set_transient_morph (float transient_morph);
   void           set_speed (float step_spl);

   float          process ();

   const erb::AudioSampleMono <float, 38400> &
                  get_sample (size_t index);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   const KickData &
                  _data;

   std::array <VoiceTransient, 4>
                  _voices;
   size_t         _cur_voice = 0;
   dsp::Ramp <256>
                  _transient_morph_ramp = {1.f};
};
