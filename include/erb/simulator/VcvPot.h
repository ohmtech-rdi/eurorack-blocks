/*****************************************************************************

      VcvPot.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvParamBase.h"
#include "erb/vcvrack/VcvPins.h"



namespace erb
{



class VcvModule;
class VcvMultiplexer;

class VcvPot
:  public VcvParamBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Mode
   {
      Normalized, Bipolar
   };

                  VcvPot (VcvModule & module, const VcvAdcPin & pin, Mode mode = Mode::Normalized);
                  VcvPot (VcvMultiplexer & multiplexer, const VcvMultiplexerPin & pin, Mode mode = Mode::Normalized);
   virtual        ~VcvPot () override = default;

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
                  VcvPot () = delete;
                  VcvPot (const VcvPot & rhs) = delete;
                  VcvPot (VcvPot && rhs) = delete;
   VcvPot &       operator = (const VcvPot & rhs) = delete;
   VcvPot &       operator = (VcvPot && rhs) = delete;
   bool           operator == (const VcvPot & rhs) const = delete;
   bool           operator != (const VcvPot & rhs) const = delete;



}; // class VcvPot



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
