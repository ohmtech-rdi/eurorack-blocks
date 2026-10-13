/*****************************************************************************

      Source.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/rig/Bench.h"
#include "erb/rig/Connection.h"
#include "erb/rig/SlotKindTrait.h"

#include <vector>

#include <cstddef>



namespace erb
{
namespace rig
{



// lab source device abstraction (function generator, etc.)

class Source
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Source () = default;
   virtual        ~Source ();

   virtual const char *
                  name () const = 0;

   virtual void   impl_process () = 0;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
   template <typename Control>
   void           impl_bind (Bench & bench, Control & input);
   inline Connection
                  impl_connect ();

   inline Buffer &
                  impl_input_audio (std::size_t channel);
   inline bool    impl_bound () const;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Channel
   {
      SlotKind    kind;
      std::size_t slot_index;
      const void *
                  control_ptr;   // for logs
   };

   inline void    impl_unbind ();

   Bench *        _bench_ptr = nullptr;
   std::vector <Channel>
                  _channels;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Source (const Source & rhs) = delete;
                  Source (Source && rhs) = delete;
   Source &       operator = (const Source & rhs) = delete;
   Source &       operator = (Source && rhs) = delete;
   bool           operator == (const Source & rhs) const = delete;
   bool           operator != (const Source & rhs) const = delete;



}; // class Source



}  // namespace rig
}  // namespace erb



#include "erb/rig/Source.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
