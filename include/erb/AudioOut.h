/*****************************************************************************

      AudioOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"



namespace erb
{



class AudioOut
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         AudioOut (Buffer & data);
   virtual        ~AudioOut () = default;

   inline AudioOut &
                  operator = (const Buffer & buffer);

   inline std::size_t
                  size () const;
   inline float & operator [] (std::size_t index);
   inline void    fill (float val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const void *   impl_data () const { return &_data; }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   Buffer &       _data;



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
