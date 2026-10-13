/*****************************************************************************

      SdCardDriver.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS

#include "erb/rig/SdCardDriver.h"

#include "erb/rig/SdCard.h"

#include <utility>

#include <cassert>
#include <cstdio>
#include <cstdlib>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : diskio
Description :
   The FatFS entry table to link on a volume slot.
==============================================================================
*/

const Diskio_drvTypeDef &  SdCardDriver::diskio () const
{
   return _diskio;
}



/*
==============================================================================
Name : attach
Description :
   The card the volume slot forwards to, until 'detach'.
==============================================================================
*/

void  SdCardDriver::attach (BYTE pdrv, SdCard & card)
{
   volume (pdrv).card_ptr = &card;
}



/*
==============================================================================
Name : detach
==============================================================================
*/

void  SdCardDriver::detach (BYTE pdrv)
{
   auto & vol = volume (pdrv);

   // if in 'Reboot', fault injector needs to be reset before (and so
   // consumed)
   if (vol.injector) fail ("fault injector still set");

   vol.card_ptr = nullptr;
}



/*
==============================================================================
Name : set_fault_injector
==============================================================================
*/

void  SdCardDriver::set_fault_injector (BYTE pdrv, FaultInjector injector)
{
   assert (bool (injector));

   auto & vol = volume (pdrv);

   if (vol.injector) fail ("fault injector already set");

   vol.injector = std::move (injector);
   vol.injector_run_flag = false;
}



/*
==============================================================================
Name : reset_fault_injector
==============================================================================
*/

void  SdCardDriver::reset_fault_injector (BYTE pdrv)
{
   auto & vol = volume (pdrv);

   if (!vol.injector) fail ("no fault injector set");
   if (!vol.injector_run_flag) fail ("fault injector never run");

   vol.injector = nullptr;
   vol.injector_run_flag = false;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_reset_stats
==============================================================================
*/

void  SdCardDriver::impl_reset_stats ()
{
   _nbr_bytes_read = 0;
   _nbr_bytes_written = 0;
}



/*
==============================================================================
Name : impl_nbr_bytes_read
==============================================================================
*/

std::size_t SdCardDriver::impl_nbr_bytes_read () const
{
   return _nbr_bytes_read;
}



/*
==============================================================================
Name : impl_nbr_bytes_written
==============================================================================
*/

std::size_t SdCardDriver::impl_nbr_bytes_written () const
{
   return _nbr_bytes_written;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : fail
==============================================================================
*/

void  SdCardDriver::fail (const char * what)
{
   std::fprintf (stderr, "SdCardDriver: %s\n", what);
   std::fflush (stderr);
   std::abort ();
}



/*
==============================================================================
Name : volume
==============================================================================
*/

SdCardDriver::Volume &  SdCardDriver::volume (BYTE pdrv)
{
   assert (pdrv < _VOLUMES);

   return _volumes [pdrv];
}



/*
==============================================================================
Name : fault
==============================================================================
*/

DRESULT  SdCardDriver::fault (Volume & vol, Op op, DWORD sector, UINT count)
{
   if (!vol.injector) return RES_OK;   // none set

   vol.injector_run_flag = true;

   const auto result = vol.injector (op, sector, count);
   assert ((result == RES_OK) || (result == RES_ERROR) || (result == RES_NOTRDY));

   return result;
}



/*
==============================================================================
Name : ff_init
==============================================================================
*/

DSTATUS  SdCardDriver::ff_init (BYTE pdrv)
{
   auto & self = use ();
   auto & vol = self.volume (pdrv);

   if (vol.card_ptr == nullptr) return STA_NOINIT | STA_NODISK;
   if (self.fault (vol, Op::Initialize, 0, 0) != RES_OK) return STA_NOINIT;

   return vol.card_ptr->impl_init ();
}



/*
==============================================================================
Name : ff_status
==============================================================================
*/

DSTATUS  SdCardDriver::ff_status (BYTE pdrv)
{
   auto & self = use ();
   auto & vol = self.volume (pdrv);

   if (vol.card_ptr == nullptr) return STA_NOINIT | STA_NODISK;
   if (self.fault (vol, Op::Status, 0, 0) != RES_OK) return STA_NOINIT;

   return vol.card_ptr->impl_status ();
}



/*
==============================================================================
Name : ff_read
==============================================================================
*/

DRESULT  SdCardDriver::ff_read (BYTE pdrv, BYTE * buf, DWORD sector, UINT count)
{
   auto & self = use ();
   auto & vol = self.volume (pdrv);

   if (vol.card_ptr == nullptr) return RES_NOTRDY;

   const auto fault_result = self.fault (vol, Op::Read, sector, count);
   if (fault_result != RES_OK) return fault_result;

   const auto result = vol.card_ptr->impl_read (buf, sector, count);
   if (result == RES_OK) self._nbr_bytes_read += std::size_t (count) * SdCard::SectorSize;

   return result;
}



/*
==============================================================================
Name : ff_write
==============================================================================
*/

DRESULT  SdCardDriver::ff_write (BYTE pdrv, const BYTE * buf, DWORD sector, UINT count)
{
   auto & self = use ();
   auto & vol = self.volume (pdrv);

   if (vol.card_ptr == nullptr) return RES_NOTRDY;

   const auto fault_result = self.fault (vol, Op::Write, sector, count);
   if (fault_result != RES_OK) return fault_result;

   const auto result = vol.card_ptr->impl_write (buf, sector, count);
   if (result == RES_OK) self._nbr_bytes_written += std::size_t (count) * SdCard::SectorSize;

   return result;
}



/*
==============================================================================
Name : ff_ioctl
==============================================================================
*/

DRESULT  SdCardDriver::ff_ioctl (BYTE pdrv, BYTE cmd, void * buf)
{
   auto & vol = use ().volume (pdrv);

   if (vol.card_ptr == nullptr) return RES_NOTRDY;

   return vol.card_ptr->impl_ioctl (cmd, buf);
}



}  // namespace rig
}  // namespace erb

#endif // erb_USE_FATFS



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
