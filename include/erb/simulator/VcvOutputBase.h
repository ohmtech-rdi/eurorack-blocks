/*****************************************************************************

      VcvOutputBase.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvModuleListener.h"

#include <cstddef>



namespace rack
{
namespace engine
{
struct Output;
}
}



namespace erb
{



class VcvModule;

class VcvOutputBase
:  public VcvModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  VcvOutputBase () = default; // audio only
                  VcvOutputBase (VcvModule & module);
   virtual        ~VcvOutputBase () override = default;

   size_t         index () const;
   void           set_norm_val (float norm_val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (size_t index, rack::engine::Output & output);

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   rack::engine::Output *
                  _output_ptr = nullptr;
   size_t         _index = size_t (-1);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvOutputBase (const VcvOutputBase & rhs) = delete;
                  VcvOutputBase (VcvOutputBase && rhs) = delete;
   VcvOutputBase &operator = (const VcvOutputBase & rhs) = delete;
   VcvOutputBase &operator = (VcvOutputBase && rhs) = delete;
   bool           operator == (const VcvOutputBase & rhs) const = delete;
   bool           operator != (const VcvOutputBase & rhs) const = delete;



}; // class VcvOutputBase



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
