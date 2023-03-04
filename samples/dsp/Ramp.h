/*****************************************************************************

      Ramp.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstddef>



namespace dsp
{



template <std::size_t nbr_steps>
class Ramp
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Ramp () = default;
                  Ramp (float initial_value);
   virtual        ~Ramp () = default;

   void           reset (float initial_value = 0.f);

   Ramp &         operator = (float value);

   float          process ();
                  operator float () const;
   bool           active () const;
   float          target () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   float          _current = 0.f;
   float          _target = 0.f;
   float          _step = 0.f;
   size_t         _cur_step = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Ramp (const Ramp & rhs) = delete;
                  Ramp (Ramp && rhs) = delete;
   Ramp &         operator = (const Ramp & rhs) = delete;
   Ramp &         operator = (Ramp && rhs) = delete;
   bool           operator == (const Ramp & rhs) const = delete;
   bool           operator != (const Ramp & rhs) const = delete;



}; // class Ramp



}  // namespace dsp



#include "dsp/Ramp.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
