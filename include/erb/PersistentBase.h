/*****************************************************************************

      PersistentBase.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

#include <cstddef>
#include <cstdint>



namespace erb
{



template <typename Type, uint64_t Magic>
class PersistentBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         PersistentBase () = default;
   virtual        ~PersistentBase () = default;

   template <typename Board>
   Type           load (Board & board, size_t page);

   template <typename Board>
   void           save (Board & board, size_t page, Type value);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  PersistentBase (const PersistentBase & rhs) = delete;
                  PersistentBase (PersistentBase && rhs) = delete;
   PersistentBase &
                  operator = (const PersistentBase & rhs) = delete;
   PersistentBase &
                  operator = (PersistentBase && rhs) = delete;
   bool           operator == (const PersistentBase & rhs) const = delete;
   bool           operator != (const PersistentBase & rhs) const = delete;



}; // class PersistentBase



}  // namespace erb



#include "erb/PersistentBase.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
