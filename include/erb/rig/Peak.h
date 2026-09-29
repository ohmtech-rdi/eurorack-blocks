/*****************************************************************************

      Peak.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AudioOut.h"
#include "erb/rig/Instrument.h"

#include <source_location>



namespace erb
{
namespace rig
{



class Peak
:  public Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Reading = float;

   inline explicit
                  Peak (Setup setup);
   virtual        ~Peak () override = default;

   inline Connection
                  bind (Bench & bench, AudioOut & output);

   inline Reading read () const;
   inline void    check (Reading expected, float tolerance, std::source_location sloc = std::source_location::current ()) const;

   inline const char *
                  name () const override;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Peak () = delete;
                  Peak (const Peak & rhs) = delete;
                  Peak (Peak && rhs) = delete;
   Peak &         operator = (const Peak & rhs) = delete;
   Peak &         operator = (Peak && rhs) = delete;
   bool           operator == (const Peak & rhs) const = delete;
   bool           operator != (const Peak & rhs) const = delete;



}; // class Peak



}  // namespace rig
}  // namespace erb



#include "erb/rig/Peak.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
