/*****************************************************************************

      SubmoduleDaisySeed.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

template <typename F>
void  SubmoduleDaisySeed::run (F && f)
{
   _run = std::forward <F> (f);

   do_run ();
}



/*
==============================================================================
Name : load
==============================================================================
*/

template <std::size_t N>
std::array <uint8_t, N> SubmoduleDaisySeed::load (size_t page)
{
   auto address_offset = uint32_t { page * 256 };
   void * data_ptr = _seed.qspi.GetData (address_offset);

   if (daisy::System::GetProgramMemoryRegion () != daisy::System::MemoryRegion::INTERNAL_FLASH)
   {
      dsy_dma_invalidate_cache_for_buffer (reinterpret_cast <uint8_t *> (data_ptr), N);
   }

   std::array <uint8_t, N> ret;
   std::memcpy (&ret [0], data_ptr, N);

   return ret;
}



/*
==============================================================================
Name : save
==============================================================================
*/

template <typename Data>
void  SubmoduleDaisySeed::save (size_t page, const Data & data)
{
   auto address_offset = uint32_t { page * 256 };

   _seed.qspi.Erase (address_offset, address_offset + uint32_t (data.size ()));
   _seed.qspi.Write (address_offset, uint32_t (data.size ()), const_cast <uint8_t *> (data.data ()));
}



/*
==============================================================================
Name : clock
==============================================================================
*/

const uint64_t &  SubmoduleDaisySeed::clock ()
{
   return _clock.ms ();
}



/*
==============================================================================
Name : clock_tick
==============================================================================
*/

void  SubmoduleDaisySeed::clock_tick ()
{
   return _clock.tick ();
}



/*
==============================================================================
Name : adc
==============================================================================
*/

daisy::AdcHandle &   SubmoduleDaisySeed::adc ()
{
   return _seed.adc;
}



/*
==============================================================================
Name : dac
==============================================================================
*/

daisy::DacHandle &   SubmoduleDaisySeed::dac ()
{
   return _seed.dac;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
