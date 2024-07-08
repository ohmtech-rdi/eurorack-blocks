/*****************************************************************************

      AudioStereoIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"



namespace erb
{



class AudioStereoIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         AudioStereoIn (const Buffer & data_left, const Buffer & data_right);
   virtual        ~AudioStereoIn () = default;

   AudioIn        left;
   AudioIn        right;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AudioStereoIn () = delete;
                  AudioStereoIn (const AudioStereoIn & rhs) = delete;
                  AudioStereoIn (AudioStereoIn && rhs) = delete;
   AudioStereoIn &
                  operator = (const AudioStereoIn & rhs) = delete;
   AudioStereoIn &
                  operator = (AudioStereoIn && rhs) = delete;
   bool           operator == (const AudioStereoIn & rhs) const = delete;
   bool           operator != (const AudioStereoIn & rhs) const = delete;



}; // class AudioStereoIn



}  // namespace erb



#include "erb/AudioStereoIn.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
