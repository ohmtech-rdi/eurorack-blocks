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
                  AudioOut (Buffer & buffer);
   virtual        ~AudioOut () = default;

   AudioOut &     operator = (const Buffer & buffer);

   std::size_t    size () const;
   float &        operator [] (std::size_t index);
   void           fill (float val);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   Buffer * const _buffer_ptr;



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



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
