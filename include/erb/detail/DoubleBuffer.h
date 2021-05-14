/*****************************************************************************

      DoubleBuffer.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"



namespace erb
{



class DoubleBuffer
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  DoubleBuffer () = default;
   virtual        ~DoubleBuffer () = default;

   inline         operator Buffer () const;
   inline DoubleBuffer &
                  operator = (const Buffer & buffer);

   inline size_t  size () const;
   inline float & operator [] (size_t index);
   inline const float &
                  operator [] (size_t index) const;

   inline void    push (float spl);
   inline float   pull ();

   inline void    swap ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   std::array <Buffer, 2>
                  _buffers = {};
   size_t         _cur_buf = 0;
   size_t         _cur_index = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DoubleBuffer (const DoubleBuffer & rhs) = delete;
                  DoubleBuffer (DoubleBuffer && rhs) = delete;
   DoubleBuffer & operator = (const DoubleBuffer & rhs) = delete;
   DoubleBuffer & operator = (DoubleBuffer && rhs) = delete;
   bool           operator == (const DoubleBuffer & rhs) const = delete;
   bool           operator != (const DoubleBuffer & rhs) const = delete;



}; // class DoubleBuffer



}  // namespace erb



#include "erb/detail/DoubleBuffer.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
