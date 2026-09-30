/*****************************************************************************

      Light.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Led.h"
#include "erb/rig/Instrument.h"

#include <source_location>
#include <vector>

#include <cstddef>



namespace erb
{
namespace rig
{



class Light
:  public Instrument
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Reading = std::vector <float>;   // one level per block, 0 or 1 on a gpio

   inline explicit
                  Light (Setup setup);
   virtual        ~Light () override = default;

   inline Connection
                  bind (Bench & bench, Led <PinType::Gpio> & led);
   inline Connection
                  bind (Bench & bench, Led <PinType::Pwm> & led);

   inline Reading read () const;
   inline void    check_off (std::source_location sloc = std::source_location::current ()) const;
   inline void    check_on (std::source_location sloc = std::source_location::current ()) const;
   inline void    check_blinking (std::source_location sloc = std::source_location::current ()) const;

   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Summary
   {
      std::size_t nbr_blocks = 0;
      std::size_t nbr_lit = 0;
      std::size_t nbr_transitions = 0;
   };

   static inline Summary
                  summarize (const Reading & reading);
   inline void    report (const char * expected, const Summary & summary, std::source_location sloc) const;

   SlotKind       _kind = SlotKind::Digital;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Light () = delete;
                  Light (const Light & rhs) = delete;
                  Light (Light && rhs) = delete;
   Light &        operator = (const Light & rhs) = delete;
   Light &        operator = (Light && rhs) = delete;
   bool           operator == (const Light & rhs) const = delete;
   bool           operator != (const Light & rhs) const = delete;



}; // class Light



}  // namespace rig
}  // namespace erb



#include "erb/rig/Light.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
