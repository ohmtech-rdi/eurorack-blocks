/*****************************************************************************

      VcvParamBase.h
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
struct Param;
}
}



namespace erb
{



class VcvModule;

class VcvParamBase
:  public VcvModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  VcvParamBase (VcvModule & module);
   virtual        ~VcvParamBase () override = default;

   size_t         index () const;
   float          norm_val () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (size_t index, rack::engine::Param & param);

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   rack::engine::Param *
                  _param_ptr = nullptr;
   float          _norm_val = 0.f;
   size_t         _index = size_t (-1);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvParamBase () = delete;
                  VcvParamBase (const VcvParamBase & rhs) = delete;
                  VcvParamBase (VcvParamBase && rhs) = delete;
   VcvParamBase & operator = (const VcvParamBase & rhs) = delete;
   VcvParamBase & operator = (VcvParamBase && rhs) = delete;
   bool           operator == (const VcvParamBase & rhs) const = delete;
   bool           operator != (const VcvParamBase & rhs) const = delete;



}; // class VcvParamBase



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
