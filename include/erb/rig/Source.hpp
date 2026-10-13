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
Name : impl_bind
Note :
   One 'impl_bind' per Control and then 'impl_connect'
==============================================================================
*/

template <typename Control>
void  Source::impl_bind (Bench & bench, Control & input)
{
   constexpr auto kind = SlotKindTrait <Control>::value;

   assert ((_bench_ptr == nullptr) || (_bench_ptr == &bench));

   _bench_ptr = &bench;
   _channels.push_back ({kind, bench.impl_bind_input (kind, &input.impl_data), &input});
}



/*
==============================================================================
Name : impl_connect
==============================================================================
*/

Connection  Source::impl_connect ()
{
   assert (impl_bound ());

   _bench_ptr->impl_attach (*this);

   return Connection {[this] () { impl_unbind (); }};
}



/*
==============================================================================
Name : impl_input_audio
==============================================================================
*/

Buffer & Source::impl_input_audio (std::size_t channel)
{
   assert (impl_bound ());
   assert (channel < _channels.size ());
   assert (_channels [channel].kind == SlotKind::Audio);

   return _bench_ptr->impl_input_audio (_channels [channel].slot_index);
}



/*
==============================================================================
Name : impl_bound
==============================================================================
*/

bool  Source::impl_bound () const
{
   return _bench_ptr != nullptr;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_unbind
==============================================================================
*/

void  Source::impl_unbind ()
{
   assert (impl_bound ());

   _bench_ptr->impl_detach (*this);

   _channels.clear ();
   _bench_ptr = nullptr;
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
