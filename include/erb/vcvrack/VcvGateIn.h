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

   enum class Mode
   {
      Trigger, Gate
   };

                  VcvGateIn (VcvModule & module, const VcvPin & pin, Mode mode = Mode::Trigger);
   virtual        ~VcvGateIn () override = default;

   void           set_mode (Mode mode);
                  operator bool () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   /*               VcvGateIn (const VcvPin & pin, Mode mode);*/

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Mode           _mode;
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
