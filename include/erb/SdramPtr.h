/*****************************************************************************

      SdramPtr.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



template <typename T>
class SdramPtr
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using element_type = T;
   using pointer = T *;
   using reference = T &;

                  SdramPtr () = default;
                  SdramPtr (SdramPtr && rhs);
   virtual        ~SdramPtr ();

   SdramPtr &     operator = (SdramPtr && rhs);

   pointer        get () const;
   explicit       operator bool () const;

   reference      operator * () const;
   pointer        operator -> () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  SdramPtr (pointer ptr);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   void           release ();

   pointer        _ptr = nullptr;

   template <typename U, class... Args>
   friend SdramPtr <U> make_sdram (Args &&... args);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SdramPtr (const SdramPtr & rhs) = delete;
   SdramPtr &     operator = (const SdramPtr & rhs) = delete;
   bool           operator == (const SdramPtr & rhs) const = delete;
   bool           operator != (const SdramPtr & rhs) const = delete;



}; // class SdramPtr



template <typename T, class... Args>
SdramPtr <T>   make_sdram (Args &&... args);



}  // namespace erb



#include "erb/SdramPtr.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
