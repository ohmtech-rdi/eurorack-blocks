/*****************************************************************************

      VcvGateIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvInputBase.h"
#include "erb/vcvrack/VcvPins.h"



namespace erb
{



class VcvModule;

class VcvGateIn
:  public VcvInputBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  VcvGateIn (VcvModule & module, const VcvPin & pin);
   virtual        ~VcvGateIn () override = default;

   bool           triggered () const;
                  operator bool () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   bool           _previous = false;
   bool           _current = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvGateIn () = delete;
                  VcvGateIn (const VcvGateIn & rhs) = delete;
                  VcvGateIn (VcvGateIn && rhs) = delete;
   VcvGateIn &    operator = (const VcvGateIn & rhs) = delete;
   VcvGateIn &    operator = (VcvGateIn && rhs) = delete;
   bool           operator == (const VcvGateIn & rhs) const = delete;
   bool           operator != (const VcvGateIn & rhs) const = delete;



}; // class VcvGateIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
