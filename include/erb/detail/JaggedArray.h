/*****************************************************************************

      JaggedArray.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <initializer_list>
#include <vector>



namespace erb
{



template <typename T>
class JaggedArray
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  JaggedArray () = default;
   virtual        ~JaggedArray () = default;

   void           resize (std::initializer_list <size_t> row_sizes, const T & value);

   size_t         size () const;
   size_t         size (size_t row) const;

   size_t         global_index (size_t row, size_t index);

   T &            operator [] (size_t global_index);
   const T &      operator [] (size_t global_index) const;

   T &            operator () (size_t row, size_t index);
   const T &      operator () (size_t row, size_t index) const;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   std::vector <size_t>
                  _row_start_indexes; // extra last row for total
   std::vector <T>
                  _data;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  JaggedArray (const JaggedArray & rhs) = delete;
                  JaggedArray (JaggedArray && rhs) = delete;
   JaggedArray &  operator = (const JaggedArray & rhs) = delete;
   JaggedArray &  operator = (JaggedArray && rhs) = delete;
   bool           operator == (const JaggedArray & rhs) const = delete;
   bool           operator != (const JaggedArray & rhs) const = delete;



}; // class JaggedArray



}  // namespace erb



#include "erb/detail/JaggedArray.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
