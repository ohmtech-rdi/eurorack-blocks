/*****************************************************************************

      Cable.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/Bench.h"
#include "erb/rig/Connection.h"
#include "erb/rig/Source.h"

#include "erb/CvIn.h"
#include "erb/CvOut.h"
#include "erb/FloatRange.h"

#include <cstddef>



namespace erb
{
namespace rig
{



class Cable
:  public Source
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Cable () = default;
   virtual        ~Cable () override = default;

   template <FloatRange OutputRange, FloatRange InputRange>
   inline Connection
                  bind (Bench & bench, CvOut <OutputRange> & output, CvIn <InputRange> & input);

   inline void    plug ();
   inline void    unplug ();

   inline void    impl_process () override;
   inline const char *
                  name () const override;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   const float *  _output_data_ptr = nullptr;
   float          _input_min = 0.f;
   float          _input_max = 0.f;
   bool           _plugged = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Cable (const Cable & rhs) = delete;
                  Cable (Cable && rhs) = delete;
   Cable &        operator = (const Cable & rhs) = delete;
   Cable &        operator = (Cable && rhs) = delete;
   bool           operator == (const Cable & rhs) const = delete;
   bool           operator != (const Cable & rhs) const = delete;



}; // class Cable



}  // namespace rig
}  // namespace erb



#include "erb/rig/Cable.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
