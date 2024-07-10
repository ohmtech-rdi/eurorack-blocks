/*****************************************************************************

      MidiMessage.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cstddef>
#include <type_traits>
#include <tuple>



namespace erb
{



struct MidiMessage
{
   inline         MidiMessage () = default;
   inline         ~MidiMessage () = default;

   inline explicit
                  operator bool () const;





}; // class MidiMessage



}  // namespace erb



#include "erb/MidiMessage.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
