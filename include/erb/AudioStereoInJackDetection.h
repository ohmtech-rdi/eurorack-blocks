/*****************************************************************************

      AudioStereoInJackDetection.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/JackDetection.h"



namespace erb
{



class AudioStereoInJackDetection
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         AudioStereoInJackDetection (const Buffer & data_left, const Buffer & data_right, const uint8_t & npr);
   virtual        ~AudioStereoInJackDetection () = default;

   inline bool    plugged () const;

   AudioIn        left;
   AudioIn        right;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const uint8_t &
                  impl_npr;
   inline void    impl_preprocess ();
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   JackDetection  _jack_detection;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AudioStereoInJackDetection () = delete;
                  AudioStereoInJackDetection (const AudioStereoInJackDetection & rhs) = delete;
                  AudioStereoInJackDetection (AudioStereoInJackDetection && rhs) = delete;
   AudioStereoInJackDetection &
                  operator = (const AudioStereoInJackDetection & rhs) = delete;
   AudioStereoInJackDetection &
                  operator = (AudioStereoInJackDetection && rhs) = delete;
   bool           operator == (const AudioStereoInJackDetection & rhs) const = delete;
   bool           operator != (const AudioStereoInJackDetection & rhs) const = delete;



}; // class AudioStereoInJackDetection



}  // namespace erb



#include "erb/AudioStereoInJackDetection.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
