/*****************************************************************************

      SramPtr.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



template <typename T>
class SramPtr
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using element_type = T;
   using pointer = T *;
   using reference = T &;

                  SramPtr () = default;
                  SramPtr (SramPtr && rhs);
   virtual        ~SramPtr ();

   SramPtr &     operator = (SramPtr && rhs);

   pointer        get () const;
   explicit       operator bool () const;

   reference      operator * () const;
   pointer        operator -> () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  SramPtr (pointer ptr);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   void           release ();

   pointer        _ptr = nullptr;

   template <typename U, class... Args>
   friend SramPtr <U> make_sram (Args &&... args);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SramPtr (const SramPtr & rhs) = delete;
   SramPtr &      operator = (const SramPtr & rhs) = delete;
   bool           operator == (const SramPtr & rhs) const = delete;
   bool           operator != (const SramPtr & rhs) const = delete;



}; // class SramPtr



template <typename T, class... Args>
SramPtr <T>   make_sram (Args &&... args);



}  // namespace erb



#include "erb/SramPtr.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
