/*****************************************************************************

      VcvInputBase.h
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
struct Input;
}
}



namespace erb
{



class VcvModule;

class VcvInputBase
:  public VcvModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  VcvInputBase () = default; // audio only
                  VcvInputBase (VcvModule & module);
   virtual        ~VcvInputBase () override = default;

   size_t         index () const;
   float          norm_val () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (size_t index, rack::engine::Input & input);

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   rack::engine::Input *
                  _input_ptr = nullptr;
   float          _norm_val = 0.f;
   size_t         _index = size_t (-1);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvInputBase (const VcvInputBase & rhs) = delete;
                  VcvInputBase (VcvInputBase && rhs) = delete;
   VcvInputBase & operator = (const VcvInputBase & rhs) = delete;
   VcvInputBase & operator = (VcvInputBase && rhs) = delete;
   bool           operator == (const VcvInputBase & rhs) const = delete;
   bool           operator != (const VcvInputBase & rhs) const = delete;



}; // class VcvInputBase



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
