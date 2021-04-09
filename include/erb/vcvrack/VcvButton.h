/*****************************************************************************

      VcvButton.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvParamBase.h"
#include "erb/vcvrack/VcvPins.h"
#include "erb/detail/Debounce.h"



namespace erb
{



class VcvModule;

class VcvButton
:  public VcvParamBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VcvButton (VcvModule & module, const VcvPin & pin);
   virtual        ~VcvButton () override = default;

   bool           pressed () const;
   bool           held () const;
   bool           released () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   Debounce       _state;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvButton () = delete;
                  VcvButton (const VcvButton & rhs) = delete;
                  VcvButton (VcvButton && rhs) = delete;
   VcvButton &    operator = (const VcvButton & rhs) = delete;
   VcvButton &    operator = (VcvButton && rhs) = delete;
   bool           operator == (const VcvButton & rhs) const = delete;
   bool           operator != (const VcvButton & rhs) const = delete;



}; // class VcvButton



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
