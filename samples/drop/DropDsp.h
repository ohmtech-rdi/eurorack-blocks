/*****************************************************************************

      DropDsp.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "dsp/Filter2Poles.h"
#include "dsp/GainRamp.h"

#include <array>
#include <cstddef>



class DropDsp
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Mode
   {
      HighPass, Mute
   };

   enum class State
   {
      None,
      Off, Armed, Active
   };

                  DropDsp (float sample_freq);
   /*virtual*/    ~DropDsp () = default;

   void           toggle_arm ();
   void           sync ();
   void           set_mode (Mode mode);
   void           set_highpass_freq (float freq);

   void           process (float * const out [], const float * const in [], std::size_t size);

   State          state ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum {         NBR_CHANNELS = 2 };

   using Filters = std::array <dsp::Filter2Poles, NBR_CHANNELS>;

   bool           _arm_active = false;
   dsp::GainRamp  _active;
   dsp::GainRamp  _mode;
   Filters        _filters;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DropDsp () = delete;
                  DropDsp (const DropDsp & rhs) = delete;
                  DropDsp (DropDsp && rhs) = delete;
   DropDsp &      operator = (const DropDsp & rhs) = delete;
   DropDsp &      operator = (DropDsp && rhs) = delete;
   bool           operator == (const DropDsp & rhs) const = delete;
   bool           operator != (const DropDsp & rhs) const = delete;



}; // class DropDsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
