/*****************************************************************************

      SdCard.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS

#include "erb/rig/SdCard.h"

#include <fstream>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : dtor
==============================================================================
*/

SdCard::~SdCard ()
{
   // if in 'Reboot', fault injector needs to be reset before (and so
   // consumed)
   if (_fault_injector) fail ("fault injector still set");
}



/*
==============================================================================
Name : format
Note :
   The entire card is into memory. This way we can quickly copy the entire
   card, and this allows for a clean environment because we don't keep
   anything on disk.
==============================================================================
*/

void  SdCard::format (std::size_t size)
{
   const auto nbr_sectors = (size + SectorSize - 1) / SectorSize;
   _bytes.assign (nbr_sectors * SectorSize, 0);

   ScopedVolume volume (*this, false);

   std::array <BYTE, _MAX_SS> work;
   check (f_mkfs (volume.path, FM_ANY, 0, work.data (), UINT (work.size ())), "mkfs", volume.path);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  SdCard::add (const std::string & host_path, const std::string & card_path)
{
   std::ifstream host (host_path, std::ios::binary);

   if (!host)
   {
      std::fprintf (stderr, "SdCard: cannot read '%s'\n", host_path.c_str ());
      std::fflush (stderr);
      std::abort ();
   }

   host.seekg (0, std::ios::end);
   std::vector <std::uint8_t> content (std::size_t (host.tellg ()));
   host.seekg (0, std::ios::beg);
   host.read (reinterpret_cast <char *> (content.data ()), std::streamsize (content.size ()));
   assert (host.gcount () == std::streamsize (content.size ()));

   write (card_path, content);
}



/*
==============================================================================
Name : write
==============================================================================
*/

void  SdCard::write (const std::string & card_path, const std::vector <std::uint8_t> & content)
{
   ScopedVolume volume (*this, true);

   // directories on the way

   for (auto pos = card_path.find ('/') ; pos != std::string::npos ; pos = card_path.find ('/', pos + 1))
   {
      const auto dir = volume.file (card_path.substr (0, pos));
      const auto result = f_mkdir (dir.c_str ());

      if (result != FR_EXIST) check (result, "mkdir", dir);
   }

   const auto file = volume.file (card_path);

   FIL fil;
   check (f_open (&fil, file.c_str (), FA_WRITE | FA_CREATE_ALWAYS), "open", file);

   UINT written = 0;
   check (f_write (&fil, content.data (), UINT (content.size ()), &written), "write", file);
   assert (written == content.size ());

   check (f_close (&fil), "close", file);
}



/*
==============================================================================
Name : remove
==============================================================================
*/

void  SdCard::remove (const std::string & card_path)
{
   ScopedVolume volume (*this, true);

   const auto file = volume.file (card_path);
   check (f_unlink (file.c_str ()), "unlink", file);
}



/*
==============================================================================
Name : read
==============================================================================
*/

std::vector <std::uint8_t>   SdCard::read (const std::string & card_path)
{
   ScopedVolume volume (*this, true);

   const auto file = volume.file (card_path);

   FIL fil;
   check (f_open (&fil, file.c_str (), FA_READ), "open", file);

   std::vector <std::uint8_t> content (f_size (&fil));

   UINT nbr_read = 0;
   check (f_read (&fil, content.data (), UINT (content.size ()), &nbr_read), "read", file);
   assert (nbr_read == content.size ());

   check (f_close (&fil), "close", file);

   return content;
}



/*
==============================================================================
Name : set_fault_injector
==============================================================================
*/

void  SdCard::set_fault_injector (FaultInjector injector)
{
   assert (bool (injector));

   if (_fault_injector) fail ("fault injector already set");

   _fault_injector = std::move (injector);
   _fault_injector_run_flag = false;
}



/*
==============================================================================
Name : reset_fault_injector
==============================================================================
*/

void  SdCard::reset_fault_injector ()
{
   if (!_fault_injector) fail ("no fault injector set");
   if (!_fault_injector_run_flag) fail ("fault injector never run");

   _fault_injector = nullptr;
   _fault_injector_run_flag = false;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_driver
==============================================================================
*/

const Diskio_drvTypeDef &  SdCard::impl_driver ()
{
   static const Diskio_drvTypeDef driver = { ff_init, ff_status, ff_read, ff_write, ff_ioctl };

   return driver;
}



/*
==============================================================================
Name : impl_attach
==============================================================================
*/

void  SdCard::impl_attach (BYTE pdrv, SdCard * card_ptr)
{
   assert (pdrv < _VOLUMES);

   _attached [pdrv] = card_ptr;
}



/*
==============================================================================
Name : impl_reset_stats
==============================================================================
*/

void  SdCard::impl_reset_stats ()
{
   _nbr_bytes_read = 0;
   _nbr_bytes_written = 0;
}



/*
==============================================================================
Name : impl_nbr_bytes_read
==============================================================================
*/

std::size_t SdCard::impl_nbr_bytes_read ()
{
   return _nbr_bytes_read;
}



/*
==============================================================================
Name : impl_nbr_bytes_written
==============================================================================
*/

std::size_t SdCard::impl_nbr_bytes_written ()
{
   return _nbr_bytes_written;
}



/*
==============================================================================
Name : impl_init
==============================================================================
*/

DSTATUS  SdCard::impl_init () const
{
   if (fault (Op::Initialize, 0, 0) != RES_OK) return STA_NOINIT;

   return empty () ? (STA_NOINIT | STA_NODISK) : 0;
}



/*
==============================================================================
Name : impl_status
==============================================================================
*/

DSTATUS  SdCard::impl_status () const
{
   if (fault (Op::Status, 0, 0) != RES_OK) return STA_NOINIT;

   return empty () ? (STA_NOINIT | STA_NODISK) : 0;
}



/*
==============================================================================
Name : impl_read
==============================================================================
*/

DRESULT  SdCard::impl_read (BYTE * buf, DWORD sector, UINT count) const
{
   const auto fault_result = fault (Op::Read, sector, count);
   if (fault_result != RES_OK) return fault_result;

   if (empty ()) return RES_NOTRDY;

   const std::size_t offset = std::size_t (sector) * SectorSize;
   const std::size_t length = std::size_t (count) * SectorSize;
   assert (offset + length <= _bytes.size ());

   std::memcpy (buf, _bytes.data () + offset, length);
   _nbr_bytes_read += length;

   return RES_OK;
}



/*
==============================================================================
Name : impl_write
==============================================================================
*/

DRESULT  SdCard::impl_write (const BYTE * buf, DWORD sector, UINT count)
{
   const auto fault_result = fault (Op::Write, sector, count);
   if (fault_result != RES_OK) return fault_result;

   if (empty ()) return RES_NOTRDY;

   const std::size_t offset = std::size_t (sector) * SectorSize;
   const std::size_t length = std::size_t (count) * SectorSize;
   assert (offset + length <= _bytes.size ());

   std::memcpy (_bytes.data () + offset, buf, length);
   _nbr_bytes_written += length;

   return RES_OK;
}



/*
==============================================================================
Name : impl_ioctl
==============================================================================
*/

DRESULT  SdCard::impl_ioctl (BYTE cmd, void * buf) const
{
   if (empty ()) return RES_NOTRDY;

   switch (cmd)
   {
   case CTRL_SYNC:
      return RES_OK;

   case GET_SECTOR_COUNT:
      *reinterpret_cast <DWORD *> (buf) = DWORD (_bytes.size () / SectorSize);
      return RES_OK;

   case GET_SECTOR_SIZE:
      *reinterpret_cast <WORD *> (buf) = WORD (SectorSize);
      return RES_OK;

   case GET_BLOCK_SIZE:
      *reinterpret_cast <DWORD *> (buf) = 1;
      return RES_OK;

   default:
      return RES_PARERR;
   }
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ScopedVolume::ctor
==============================================================================
*/

SdCard::ScopedVolume::ScopedVolume (SdCard & card, bool mount_flag)
{
   const auto err = FATFS_LinkDriver (&impl_driver (), path);
   assert (err == 0);

   pdrv = BYTE (path [0] - '0');
   impl_attach (pdrv, &card);

   if (mount_flag)
   {
      check (f_mount (&fs, path, 1), "mount", path);
   }
}



/*
==============================================================================
Name : ScopedVolume::dtor
==============================================================================
*/

SdCard::ScopedVolume::~ScopedVolume ()
{
   f_mount (nullptr, path, 0);
   impl_attach (pdrv, nullptr);
   FATFS_UnLinkDriver (path);
}



/*
==============================================================================
Name : ScopedVolume::file
==============================================================================
*/

std::string SdCard::ScopedVolume::file (const std::string & card_path) const
{
   return std::string (path) + card_path;
}



/*
==============================================================================
Name : check
==============================================================================
*/

void  SdCard::check (FRESULT result, const char * what, const std::string & path)
{
   if (result == FR_OK) return;  // no error

   std::fprintf (stderr, "SdCard: %s '%s' failed, FRESULT %d\n", what, path.c_str (), int (result));
   std::fflush (stderr);
   std::abort ();
}



/*
==============================================================================
Name : fail
==============================================================================
*/

void  SdCard::fail (const char * what)
{
   std::fprintf (stderr, "SdCard: %s\n", what);
   std::fflush (stderr);
   std::abort ();
}



/*
==============================================================================
Name : fault
==============================================================================
*/

DRESULT  SdCard::fault (Op op, DWORD sector, UINT count) const
{
   if (!_fault_injector) return RES_OK;   // none set

   _fault_injector_run_flag = true;

   const auto result = _fault_injector (op, sector, count);
   assert ((result == RES_OK) || (result == RES_ERROR) || (result == RES_NOTRDY));

   return result;
}



/*
==============================================================================
Name : ff_init
==============================================================================
*/

DSTATUS  SdCard::ff_init (BYTE pdrv)
{
   auto * card_ptr = _attached [pdrv];

   return (card_ptr == nullptr) ? (STA_NOINIT | STA_NODISK) : card_ptr->impl_init ();
}



/*
==============================================================================
Name : ff_status
==============================================================================
*/

DSTATUS  SdCard::ff_status (BYTE pdrv)
{
   auto * card_ptr = _attached [pdrv];

   return (card_ptr == nullptr) ? (STA_NOINIT | STA_NODISK) : card_ptr->impl_status ();
}



/*
==============================================================================
Name : ff_read
==============================================================================
*/

DRESULT  SdCard::ff_read (BYTE pdrv, BYTE * buf, DWORD sector, UINT count)
{
   auto * card_ptr = _attached [pdrv];

   return (card_ptr == nullptr) ? RES_NOTRDY : card_ptr->impl_read (buf, sector, count);
}



/*
==============================================================================
Name : ff_write
==============================================================================
*/

DRESULT  SdCard::ff_write (BYTE pdrv, const BYTE * buf, DWORD sector, UINT count)
{
   auto * card_ptr = _attached [pdrv];

   return (card_ptr == nullptr) ? RES_NOTRDY : card_ptr->impl_write (buf, sector, count);
}



/*
==============================================================================
Name : ff_ioctl
==============================================================================
*/

DRESULT  SdCard::ff_ioctl (BYTE pdrv, BYTE cmd, void * buf)
{
   auto * card_ptr = _attached [pdrv];

   return (card_ptr == nullptr) ? RES_NOTRDY : card_ptr->impl_ioctl (cmd, buf);
}



/*
==============================================================================
Name : _attached
Description :
   Cards attached to the driver, one per FatFS volume slot
==============================================================================
*/

std::array <SdCard *, _VOLUMES> SdCard::_attached = {};
std::size_t SdCard::_nbr_bytes_read = 0;
std::size_t SdCard::_nbr_bytes_written = 0;



}  // namespace rig
}  // namespace erb

#endif // erb_USE_FATFS



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
