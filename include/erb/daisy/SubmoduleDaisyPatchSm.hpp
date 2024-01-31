/*****************************************************************************

      SubmoduleDaisyPatchSm.hpp
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
void  SubmoduleDaisyPatchSm::run (F && f)
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
std::array <uint8_t, N> SubmoduleDaisyPatchSm::load (size_t page)
{
   auto address_offset = uint32_t { page * 256 };
   void * data_ptr = _qspi.GetData (address_offset);

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
void  SubmoduleDaisyPatchSm::save (size_t page, const Data & data)
{
   auto address_offset = uint32_t { page * 256 };

   _qspi.Erase (address_offset, address_offset + uint32_t (data.size ()));
   _qspi.Write (address_offset, uint32_t (data.size ()), const_cast <uint8_t *> (data.data ()));
}



/*
==============================================================================
Name : clock
==============================================================================
*/

const uint64_t &  SubmoduleDaisyPatchSm::clock ()
{
   return _clock.ms ();
}



/*
==============================================================================
Name : clock_tick
==============================================================================
*/

void  SubmoduleDaisyPatchSm::clock_tick ()
{
   return _clock.tick ();
}



/*
==============================================================================
Name : adc
==============================================================================
*/

daisy::AdcHandle &   SubmoduleDaisyPatchSm::adc ()
{
   return _adc;
}



/*
==============================================================================
Name : dac
==============================================================================
*/

daisy::DacHandle &   SubmoduleDaisyPatchSm::dac ()
{
   return _dac;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
