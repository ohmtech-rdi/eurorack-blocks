/*****************************************************************************

      MidiIn.h
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



class MidiIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   struct Message
   {
      std::array <uint8_t, erb_MIDI_MESSAGE_SIZE>
                  data = {};
      std::size_t size = 0;
   };

   inline         MidiIn (Stream <erb_MIDI_MESSAGE_SIZE> & data);
   virtual        ~MidiIn () = default;

   void           reset ();

   std::optional <Message>
                  pop ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   Stream <erb_MIDI_MESSAGE_SIZE> &
                  impl_data;
   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum class State
   {
      WaitingStatusByte, Reading
   };

   enum class StreamState
   {
      Empty,         // no byte in steam
      Fed,           // byte was fed but no message yet
      MessageReady,  // new message is available
      Overflowed     // byte was available, but would overflow
   };

   StreamState    feed ();

   State          _state = State::WaitingStatusByte;
   Message        _msg;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  MidiIn () = delete;
                  MidiIn (const MidiIn & rhs) = delete;
                  MidiIn (MidiIn && rhs) = delete;
   MidiIn &       operator = (const MidiIn & rhs) = delete;
   MidiIn &       operator = (MidiIn && rhs) = delete;
   bool           operator == (const MidiIn & rhs) const = delete;
   bool           operator != (const MidiIn & rhs) const = delete;



}; // class MidiIn



}  // namespace erb



#include "erb/MidiIn.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
