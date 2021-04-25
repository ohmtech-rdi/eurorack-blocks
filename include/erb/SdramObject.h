/*****************************************************************************

      SdramObject.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



template <typename T>
class SdramObject
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  SdramObject () = default;
                  SdramObject (SdramObject && rhs);
   virtual        ~SdramObject ();

   T &            operator * () const;
   T *            operator -> () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  SdramObject (T * ptr);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   T *            _ptr = nullptr;

   template <typename U, class... Args>
   friend SdramObject <U> make_sdram_object (Args &&... args);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SdramObject (const SdramObject & rhs) = delete;
   SdramObject &  operator = (const SdramObject & rhs) = delete;
   SdramObject &  operator = (SdramObject && rhs) = delete;
   bool           operator == (const SdramObject & rhs) const = delete;
   bool           operator != (const SdramObject & rhs) const = delete;



}; // class SdramObject



template <typename T, class... Args>
SdramObject <T>   make_sdram_object (Args &&... args);



}  // namespace erb



#include "erb/SdramObject.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
