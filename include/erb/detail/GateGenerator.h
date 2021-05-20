/*****************************************************************************

      GateGenerator.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <chrono>

#include <cstdint>



namespace erb
{



class GateGenerator
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  GateGenerator () = default;
   virtual        ~GateGenerator () = default;

   inline void    set (bool val);
   inline void    pulse (uint64_t clock_ms, std::chrono::milliseconds duration);

   inline bool    process (uint64_t clock_ms);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum class Mode
   {
      Constant, Pulse
   };

   Mode           _mode = Mode::Constant;

   union
   {
      bool        constant;
      uint64_t    pulse_falling_edge_ms;
   } _val = {};



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GateGenerator (const GateGenerator & rhs) = delete;
                  GateGenerator (GateGenerator && rhs) = delete;
   GateGenerator &     operator = (const GateGenerator & rhs) = delete;
   GateGenerator &     operator = (GateGenerator && rhs) = delete;
   bool           operator == (const GateGenerator & rhs) const = delete;
   bool           operator != (const GateGenerator & rhs) const = delete;



}; // class GateGenerator



}  // namespace erb



#include "erb/detail/GateGenerator.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
