/*****************************************************************************

      DaisyPot.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyAnalogControlBase.h"
#include "erb/daisy/DaisyPins.h"

#include <cstdint>



namespace erb
{



class DaisyModule;
class DaisyMultiplexer;

class DaisyPot
:  public DaisyAnalogControlBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Mode
   {
      Normalized, Bipolar
   };

                  DaisyPot (DaisyModule & module, const AdcPin & pin, Mode mode = Mode::Normalized);
                  DaisyPot (DaisyMultiplexer & multiplexer, const MultiplexerPin & pin, Mode mode = Mode::Normalized);
   virtual        ~DaisyPot () override = default;

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
                  DaisyPot () = delete;
                  DaisyPot (const DaisyPot & rhs) = delete;
                  DaisyPot (DaisyPot && rhs) = delete;
   DaisyPot &     operator = (const DaisyPot & rhs) = delete;
   DaisyPot &     operator = (DaisyPot && rhs) = delete;
   bool           operator == (const DaisyPot & rhs) const = delete;
   bool           operator != (const DaisyPot & rhs) const = delete;



}; // class DaisyPot



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
