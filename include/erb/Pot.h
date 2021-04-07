/*****************************************************************************

      Pot.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AnalogControlBase.h"
#include "erb/Pins.h"

#include <cstdint>



namespace erb
{



class Module;
class Multiplexer;

class Pot
:  public AnalogControlBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Mode
   {
      Normalized, Bipolar
   };

                  Pot (Module & module, const AdcPin & pin, Mode mode = Mode::Normalized);
                  Pot (Multiplexer & multiplexer, const MultiplexerPin & pin, Mode mode = Mode::Normalized);
   virtual        ~Pot () override = default;

   void           set_mode (Mode mode);
                  operator float () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Mode           _mode;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Pot () = delete;
                  Pot (const Pot & rhs) = delete;
                  Pot (Pot && rhs) = delete;
   Pot &          operator = (const Pot & rhs) = delete;
   Pot &          operator = (Pot && rhs) = delete;
   bool           operator == (const Pot & rhs) const = delete;
   bool           operator != (const Pot & rhs) const = delete;



}; // class Pot



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
