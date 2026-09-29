/*****************************************************************************

      Connection.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <functional>
#include <utility>



namespace erb
{
namespace rig
{



class [[nodiscard]] Connection
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline explicit
                  Connection (std::function <void ()> release);
   inline         Connection (Connection && rhs);
   inline         ~Connection ();



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   std::function <void ()>
                  _release;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Connection () = delete;
                  Connection (const Connection & rhs) = delete;
   Connection &   operator = (const Connection & rhs) = delete;
   Connection &   operator = (Connection && rhs) = delete;
   bool           operator == (const Connection & rhs) const = delete;
   bool           operator != (const Connection & rhs) const = delete;



}; // class Connection



}  // namespace rig
}  // namespace erb



#include "erb/rig/Connection.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
