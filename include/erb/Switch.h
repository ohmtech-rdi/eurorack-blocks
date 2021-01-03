/*****************************************************************************

      Switch.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Control.h"
#include "erb/GateIn.h"



namespace erb
{



class Module;

class Switch
:  public Control
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Position
   {
      Out0, Center, Out1
   };

                  Switch (Module & module, const dsy_gpio_pin & pin_0, const dsy_gpio_pin & pin_1);
   virtual        ~Switch () override = default;

                  operator Position () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // Control
   virtual void   impl_process () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   GateIn         _gate_0;
   GateIn         _gate_1;
   Position       _position = Position::Center;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Switch () = delete;
                  Switch (const Switch & rhs) = delete;
                  Switch (Switch && rhs) = delete;
   Switch &       operator = (const Switch & rhs) = delete;
   Switch &       operator = (Switch && rhs) = delete;
   bool           operator == (const Switch & rhs) const = delete;
   bool           operator != (const Switch & rhs) const = delete;



}; // class Switch



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
