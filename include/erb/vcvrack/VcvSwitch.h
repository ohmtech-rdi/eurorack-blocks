/*****************************************************************************

      VcvSwitch.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvParamBase.h"
#include "erb/vcvrack/VcvPins.h"



namespace erb
{



class VcvModule;

class VcvSwitch
:  public VcvParamBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Position
   {
      Out0, Center, Out1
   };

                  VcvSwitch (VcvModule & module, const VcvPin & pin_0, const VcvPin & pin_1);
   virtual        ~VcvSwitch () override = default;

                  operator Position () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Position       _position = Position::Center;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvSwitch () = delete;
                  VcvSwitch (const VcvSwitch & rhs) = delete;
                  VcvSwitch (VcvSwitch && rhs) = delete;
   VcvSwitch &    operator = (const VcvSwitch & rhs) = delete;
   VcvSwitch &    operator = (VcvSwitch && rhs) = delete;
   bool           operator == (const VcvSwitch & rhs) const = delete;
   bool           operator != (const VcvSwitch & rhs) const = delete;



}; // class VcvSwitch



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
