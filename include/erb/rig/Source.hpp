/*****************************************************************************

      Source.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <cassert>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : dtor
==============================================================================
*/

inline Source::~Source ()
{
   // source always outlives module
   assert (_bench_ptr == nullptr);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : bind_channel
Note :
   One 'bind_channel' per Control and then 'connect'
==============================================================================
*/

template <typename Control>
void  Source::bind_channel (Bench & bench, Control & input)
{
   constexpr auto kind = SlotKindTrait <Control>::value;

   assert ((_bench_ptr == nullptr) || (_bench_ptr == &bench));

   _bench_ptr = &bench;
   _channels.push_back ({kind, bench.impl_bind_input (kind, &input.impl_data), &input});
}



/*
==============================================================================
Name : connect
==============================================================================
*/

Connection  Source::connect ()
{
   assert (bound ());

   _bench_ptr->impl_attach (*this);

   return Connection {[this] () { unbind (); }};
}



/*
==============================================================================
Name : input_audio
==============================================================================
*/

Buffer & Source::input_audio (std::size_t channel)
{
   assert (bound ());
   assert (channel < _channels.size ());
   assert (_channels [channel].kind == SlotKind::Audio);

   return _bench_ptr->impl_input_audio (_channels [channel].slot_index);
}



/*
==============================================================================
Name : input_analog
==============================================================================
*/

float &  Source::input_analog (std::size_t channel)
{
   assert (bound ());
   assert (channel < _channels.size ());
   assert (_channels [channel].kind == SlotKind::Analog);

   return _bench_ptr->impl_input_analog (_channels [channel].slot_index);
}



/*
==============================================================================
Name : bound
==============================================================================
*/

bool  Source::bound () const
{
   return _bench_ptr != nullptr;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : unbind
==============================================================================
*/

void  Source::unbind ()
{
   assert (bound ());

   _bench_ptr->impl_detach (*this);

   _channels.clear ();
   _bench_ptr = nullptr;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
