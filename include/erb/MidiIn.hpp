/*****************************************************************************

      MidiIn.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

MidiIn::MidiIn (Stream <erb_MIDI_MESSAGE_SIZE> & data)
:  impl_data (data)
{
}



/*
==============================================================================
Name : reset
==============================================================================
*/

void  MidiIn::reset ()
{
   _state = State::WaitingStatusByte;
   _msg.size = 0;
}



/*
==============================================================================
Name : pop
==============================================================================
*/

std::optional <MidiIn::Message>  MidiIn::pop ()
{
   StreamState ss = StreamState::Empty;

   do
   {
      ss = feed ();
   }
   while ((ss == StreamState::Empty) || (ss == StreamState::MessageReady));

   if (ss == StreamState::MessageReady)
   {
      return {_msg};
   }
   else
   {
      return std::nullopt;
   }
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : feed
==============================================================================
*/

MidiIn::StreamState  MidiIn::feed ()
{
   const auto byte_opt = impl_data.read ();
   if (!byte_opt) return StreamState::Empty; // abort

   const auto byte = *byte_opt;

   if (_state == State::WaitingStatusByte)
   {
      _msg.size = 0;
      
      if (byte & 0x80)
      {
         _msg.data [_msg.size] = byte;
         _msg.size += 1;
         _state = State::Reading;
      }
      else
      {
         // silently drop byte
      }

      return StreamState::Fed;
   }
   else if (_state == State::Reading)
   {
      if (byte & 0x80)
      {
         // new message boundary
         impl_data.put_back ();

         _state = State::WaitingStatusByte;

         return StreamState::MessageReady;
      }
      else
      {
         if (_msg.size < _msg.data.size ())
         {
            _msg.data [_msg.size] = byte;
            _msg.size += 1;

            return StreamState::Fed;
         }
         else
         {
            reset ();

            return StreamState::Overflowed;
         }
      }
   }
}






}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
