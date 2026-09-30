/*****************************************************************************

      Vco.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioIn.h"
#include "erb/rig/Source.h"



namespace erb
{
namespace rig
{



class Vco
:  public Source
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Waveform
   {
      Sine,
   };

                  Vco () = default;
   virtual        ~Vco () override = default;

   inline Connection
                  bind (Bench & bench, AudioIn & input);

   inline void    set_waveform (Waveform waveform);
   inline void    set_frequency (float frequency_hz);
   inline void    set_level (float level);

   inline void    impl_process () override;

   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   Waveform       _waveform = Waveform::Sine;
   float          _frequency_hz = 440.f;
   float          _level = 0.5f;
   double         _phase = 0.0;   // turns



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Vco (const Vco & rhs) = delete;
                  Vco (Vco && rhs) = delete;
   Vco &          operator = (const Vco & rhs) = delete;
   Vco &          operator = (Vco && rhs) = delete;
   bool           operator == (const Vco & rhs) const = delete;
   bool           operator != (const Vco & rhs) const = delete;



}; // class Vco



}  // namespace rig
}  // namespace erb



#include "erb/rig/Vco.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
