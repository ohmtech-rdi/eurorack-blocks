/*****************************************************************************

      AudioStereoOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"



namespace erb
{



class AudioStereoOut
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         AudioStereoOut (Buffer & data_left, Buffer & data_right);
   virtual        ~AudioStereoOut () = default;

   AudioOut       left;
   AudioOut       right;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AudioStereoOut () = delete;
                  AudioStereoOut (const AudioStereoOut & rhs) = delete;
                  AudioStereoOut (AudioStereoOut && rhs) = delete;
   AudioStereoOut &
                  operator = (const AudioStereoOut & rhs) = delete;
   AudioStereoOut &
                  operator = (AudioStereoOut && rhs) = delete;
   bool           operator == (const AudioStereoOut & rhs) const = delete;
   bool           operator != (const AudioStereoOut & rhs) const = delete;



}; // class AudioStereoOut



}  // namespace erb



#include "erb/AudioStereoOut.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
