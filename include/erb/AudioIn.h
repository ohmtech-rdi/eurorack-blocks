/*****************************************************************************

      AudioIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/DoubleBuffer.h"



namespace erb
{



class AudioIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         AudioIn (const DoubleBuffer & data);
   virtual        ~AudioIn () = default;

   inline         operator Buffer () const;

   inline std::size_t
                  size () const;
   inline const float &
                  operator [] (std::size_t index);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const void *   impl_data () const { return &_data; }
   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   const DoubleBuffer &
                  _data;



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



#include "erb/AudioIn.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
