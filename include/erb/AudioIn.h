/*****************************************************************************

      AudioIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"



namespace erb
{



class AudioIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  AudioIn (const Buffer & buffer);
   virtual        ~AudioIn () = default;

                  operator Buffer () const;

   std::size_t    size () const;
   const float &  operator [] (std::size_t index);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   const Buffer * const
                  _buffer_ptr;



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



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
