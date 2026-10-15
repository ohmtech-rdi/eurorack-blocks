/*****************************************************************************

      Scope.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"
#include "erb/CvOut.h"
#include "erb/rig/Instrument.h"

#include <source_location>
#include <vector>



namespace erb
{
namespace rig
{



class Scope
:  public Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Reading = std::vector <float>;

   inline explicit
                  Scope (Setup setup);
   virtual        ~Scope () override = default;

   inline Connection
                  bind (Bench & bench, AudioOut & output);
   template <FloatRange Range>
   Connection     bind (Bench & bench, CvOut <Range> & output);

   inline Reading read () const;
   inline void    check (const Reading & expected, float tolerance, std::source_location sloc = std::source_location::current ()) const;

   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   SlotKind       _kind = SlotKind::Audio;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Scope () = delete;
                  Scope (const Scope & rhs) = delete;
                  Scope (Scope && rhs) = delete;
   Scope &        operator = (const Scope & rhs) = delete;
   Scope &        operator = (Scope && rhs) = delete;
   bool           operator == (const Scope & rhs) const = delete;
   bool           operator != (const Scope & rhs) const = delete;



}; // class Scope



}  // namespace rig
}  // namespace erb



#include "erb/rig/Scope.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
