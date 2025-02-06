/*****************************************************************************

      BoardSeed2DfmEvalEuro.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <filesystem>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

BoardSeed2DfmEvalEuro::BoardSeed2DfmEvalEuro ()
: BoardGeneric (
   7, 7, 4, // digital/analog/audio inputs
   0, 2, 4  // digital/analog/audio outputs
)
{
#if defined (erb_USE_FATFS) && erb_USE_FATFS
   FATFS_LinkDriver (&_ff_driver, _ff_path);
#endif
}



/*
==============================================================================
Name : dtor
==============================================================================
*/

BoardSeed2DfmEvalEuro::~BoardSeed2DfmEvalEuro ()
{
#if defined (erb_USE_FATFS) && erb_USE_FATFS
   reset_sd ();
#endif
}



/*
==============================================================================
Name : set_sd
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
bool  BoardSeed2DfmEvalEuro::set_sd (const char * path_0)
{
   if (_ff_file_ptr)
   {
      reset_sd ();
   }

   try
   {
      const auto fsize = std::filesystem::file_size (path_0);
      if (fsize % _ff_sector_size != 0)
      {
         return false;  // abort
      }
      _ff_sector_cnt = fsize / _ff_sector_size;
   }
   catch (...)
   {
      return false;  // abort
   }

   _ff_file_ptr = fopen (path_0, "rb");
   if (_ff_file_ptr == nullptr)
   {
      _ff_sector_cnt = 0;
      return false;  // abort
   }

   return true;
}
#endif



/*
==============================================================================
Name : reset_sd
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
void  BoardSeed2DfmEvalEuro::reset_sd ()
{
   if (_ff_file_ptr)
   {
      ::fclose (_ff_file_ptr);
      _ff_file_ptr = nullptr;
      _ff_sector_cnt = 0;
   }
}
#endif



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ff_init
Reference :
   http://elm-chan.org/fsw/ff/doc/dinit.html
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
DSTATUS  BoardSeed2DfmEvalEuro::ff_init (BYTE pdrv)
{
   return 0;
}
#endif



/*
==============================================================================
Name : ff_status
Reference :
   http://elm-chan.org/fsw/ff/doc/dstat.html
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
DSTATUS  BoardSeed2DfmEvalEuro::ff_status (BYTE pdrv)
{
   return 0;
}
#endif



/*
==============================================================================
Name : ff_read
Reference :
   http://elm-chan.org/fsw/ff/doc/dread.html
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
DRESULT  BoardSeed2DfmEvalEuro::ff_read (BYTE pdrv, BYTE * buf, DWORD sector, UINT count)
{
   if (!_ff_file_ptr) return RES_ERROR;

   assert (sector < _ff_sector_cnt);

   long offset = long (sector) * _ff_sector_size;

   auto err = ::fseek (_ff_file_ptr, offset, 0);
   if (err != 0) return RES_ERROR;

   auto count_read = ::fread (buf, _ff_sector_size, count, _ff_file_ptr);
   if (count_read != count) return RES_ERROR;

   return RES_OK;
}
#endif



/*
==============================================================================
Name : ff_write
Reference :
   http://elm-chan.org/fsw/ff/doc/dwrite.html
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
DRESULT  BoardSeed2DfmEvalEuro::ff_write (BYTE pdrv, const BYTE * buf, DWORD sector, UINT count)
{
   if (!_ff_file_ptr) return RES_ERROR;

   long offset = long (sector) * _ff_sector_size;

   auto err = ::fseek (_ff_file_ptr, offset, 0);
   if (err != 0) return RES_ERROR;

   auto count_written = ::fwrite (buf, _ff_sector_size, count, _ff_file_ptr);
   if (count_written != count) return RES_ERROR;

   return RES_OK;
}
#endif



/*
==============================================================================
Name : ff_ioctl
Reference :
   http://elm-chan.org/fsw/ff/doc/dioctl.html
==============================================================================
*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS
DRESULT  BoardSeed2DfmEvalEuro::ff_ioctl (BYTE pdrv, BYTE cmd, void * buf)
{
   if (!_ff_file_ptr) return RES_NOTRDY;

   switch (cmd)
   {
   case CTRL_SYNC:
      return RES_OK;

   case GET_SECTOR_COUNT:
      *reinterpret_cast <DWORD *> (buf) = _ff_sector_cnt;
      return RES_OK;

   case GET_SECTOR_SIZE:
      // Shouldn't be called as _MIN_SS == _MAX_SS == 512
      *reinterpret_cast <DWORD *> (buf) = _ff_sector_size;
      return RES_OK;

   case GET_BLOCK_SIZE:
      *reinterpret_cast <DWORD *> (buf) = 1;
      return RES_OK;

   default:
      return RES_PARERR;
   }
}
#endif



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
