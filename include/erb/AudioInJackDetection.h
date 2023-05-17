/*****************************************************************************

      AudioInJackDetection.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/JackDetection.h"

#include <type_traits>
#include <cstddef>



namespace erb
{



class AudioInJackDetection
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = -1.f;
   static constexpr float ValueMax = 1.f;

   inline         AudioInJackDetection (const Buffer & data, const uint8_t & npr);
   virtual        ~AudioInJackDetection () = default;

   inline bool    plugged () const;

   inline         operator const Buffer & () const;

   inline std::size_t
                  size () const;
   inline const float &
                  operator [] (std::size_t index);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const Buffer & impl_data;
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
                  AudioInJackDetection () = delete;
                  AudioInJackDetection (const AudioInJackDetection & rhs) = delete;
                  AudioInJackDetection (AudioInJackDetection && rhs) = delete;
   AudioInJackDetection &
                  operator = (const AudioInJackDetection & rhs) = delete;
   AudioInJackDetection &
                  operator = (AudioInJackDetection && rhs) = delete;
   bool           operator == (const AudioInJackDetection & rhs) const = delete;
   bool           operator != (const AudioInJackDetection & rhs) const = delete;



}; // class AudioInJackDetection



}  // namespace erb



#include "erb/AudioInJackDetection.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
