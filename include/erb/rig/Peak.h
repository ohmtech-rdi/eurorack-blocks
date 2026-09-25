/*****************************************************************************

      Peak.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/Measurement.h"
#include "erb/rig/SystemClockVirtual.h"

#include <vector>

#include <cstddef>



namespace erb
{
namespace rig
{



class Peak
:  public Measurement <SlotKind::Audio>
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Reading = float;

   inline explicit
                  Peak (SystemClockVirtual::duration window);
   virtual        ~Peak () override = default;

   inline Reading reading () const;

   static inline float
                  distance (Reading a, Reading b);
   static inline void
                  report (const char * name, const char * output_name, Reading reading, Reading expected, float tolerance);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline const char *
                  name () const override;
   inline void    impl_start () override;
   inline void    impl_feed (const Buffer & buffer) override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   std::vector <float>
                  _frame_peaks; // window, ring
   std::size_t    _pos = 0;
   std::size_t    _count = 0;



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
