/*****************************************************************************

      AudioIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"

#include <cstddef>
#include <type_traits>
#include <tuple>



namespace erb
{



class AudioIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = -1.f;
   static constexpr float ValueMax = 1.f;

   inline         AudioIn (const Buffer & data);
   virtual        ~AudioIn () = default;

   inline         operator const Buffer & () const;

   inline std::size_t
                  size () const;
   inline const float &
                  operator [] (std::size_t index) const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const Buffer & impl_data;
   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AudioIn () = delete;
                  AudioIn (const AudioIn & rhs) = delete;
                  AudioIn (AudioIn && rhs) = delete;
   AudioIn &      operator = (const AudioIn & rhs) = delete;
   AudioIn &      operator = (AudioIn && rhs) = delete;
   bool           operator == (const AudioIn & rhs) const = delete;
   bool           operator != (const AudioIn & rhs) const = delete;



}; // class AudioIn



}  // namespace erb



template <>
struct std::tuple_size <erb::AudioIn>
: public integral_constant <std::size_t, erb_BUFFER_SIZE> {};



#include "erb/AudioIn.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
