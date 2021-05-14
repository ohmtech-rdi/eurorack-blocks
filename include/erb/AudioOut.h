/*****************************************************************************

      AudioOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/DoubleBuffer.h"



namespace erb
{



class AudioOut
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         AudioOut (DoubleBuffer & data);
   virtual        ~AudioOut () = default;

   inline AudioOut &
                  operator = (const Buffer & buffer);

   inline std::size_t
                  size () const;
   inline float & operator [] (std::size_t index);
   inline void    fill (float val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const void *   impl_data () const { return &_data; }
   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   DoubleBuffer & _data;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AudioOut () = delete;
                  AudioOut (const AudioOut & rhs) = delete;
                  AudioOut (AudioOut && rhs) = delete;
   AudioOut &     operator = (const AudioOut & rhs) = delete;
   AudioOut &     operator = (AudioOut && rhs) = delete;
   bool           operator == (const AudioOut & rhs) const = delete;
   bool           operator != (const AudioOut & rhs) const = delete;



}; // class AudioOut



}  // namespace erb



#include "erb/AudioOut.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
