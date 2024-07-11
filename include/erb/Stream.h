/*****************************************************************************

      Stream.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <cstdint>
#include <optional>



namespace erb
{



template <std::size_t BufferSize>
class Stream
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         Stream () = default;
   virtual        ~Stream () = default;

   bool           write (uint8_t byte);
   std::optional <uint8_t>
                  read ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   std::array <uint8_t, BufferSize>
                  _buffer = {};
   std::size_t    _write_pos = 0;
   std::size_t    _read_pos = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Stream () = delete;
                  Stream (const Stream & rhs) = delete;
                  Stream (Stream && rhs) = delete;
   Stream &       operator = (const Stream & rhs) = delete;
   Stream &       operator = (Stream && rhs) = delete;
   bool           operator == (const Stream & rhs) const = delete;
   bool           operator != (const Stream & rhs) const = delete;



}; // class Stream



}  // namespace erb



#include "erb/Stream.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
