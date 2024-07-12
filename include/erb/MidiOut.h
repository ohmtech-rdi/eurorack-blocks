/*****************************************************************************

      MidiOut.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Stream.h"

#include <array>
#include <cstdint>
#include <optional>



namespace erb
{



template <typename T>
concept midi_out_msg = requires (T a, std::size_t i)
{
   a [i];
   a.size ();
};


class MidiOut
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         MidiOut (Stream <erb_MIDI_MESSAGE_SIZE> & data);
   virtual        ~MidiOut () = default;

   inline void    send (const midi_out_msg auto & data);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   Stream <erb_MIDI_MESSAGE_SIZE> &
                  impl_data;
   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  MidiOut () = delete;
                  MidiOut (const MidiOut & rhs) = delete;
                  MidiOut (MidiOut && rhs) = delete;
   MidiOut &       operator = (const MidiOut & rhs) = delete;
   MidiOut &       operator = (MidiOut && rhs) = delete;
   bool           operator == (const MidiOut & rhs) const = delete;
   bool           operator != (const MidiOut & rhs) const = delete;



}; // class MidiOut



}  // namespace erb



#include "erb/MidiOut.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
