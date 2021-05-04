/*****************************************************************************

      DaisySwitch.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyModuleListener.h"
#include "erb/daisy/DaisyGateIn.h"



namespace erb
{



class DaisyModule;

class DaisySwitch
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Position
   {
      Out0, Center, Out1
   };

                  DaisySwitch (DaisyModule & module, const Pin & pin_0, const Pin & pin_1);
   virtual        ~DaisySwitch () override = default;

                  operator Position () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   DaisyGateIn    _gate_0;
   DaisyGateIn    _gate_1;
   Position       _position = Position::Center;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisySwitch () = delete;
                  DaisySwitch (const DaisySwitch & rhs) = delete;
                  DaisySwitch (DaisySwitch && rhs) = delete;
   DaisySwitch &  operator = (const DaisySwitch & rhs) = delete;
   DaisySwitch &  operator = (DaisySwitch && rhs) = delete;
   bool           operator == (const DaisySwitch & rhs) const = delete;
   bool           operator != (const DaisySwitch & rhs) const = delete;



}; // class DaisySwitch



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
