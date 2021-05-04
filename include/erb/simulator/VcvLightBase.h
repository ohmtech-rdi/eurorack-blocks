/*****************************************************************************

      VcvLightBase.h
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
struct Light;
}
}



namespace erb
{



class VcvModule;

class VcvLightBase
:  public VcvModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  VcvLightBase (VcvModule & module);
   virtual        ~VcvLightBase () override = default;

   size_t         index () const;
   void           set_norm_val (float norm_val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_bind (size_t index, rack::engine::Light & light);

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   rack::engine::Light *
                  _light_ptr = nullptr;
   size_t         _index = size_t (-1);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvLightBase () = delete;
                  VcvLightBase (const VcvLightBase & rhs) = delete;
                  VcvLightBase (VcvLightBase && rhs) = delete;
   VcvLightBase & operator = (const VcvLightBase & rhs) = delete;
   VcvLightBase & operator = (VcvLightBase && rhs) = delete;
   bool           operator == (const VcvLightBase & rhs) const = delete;
   bool           operator != (const VcvLightBase & rhs) const = delete;



}; // class VcvLightBase



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
