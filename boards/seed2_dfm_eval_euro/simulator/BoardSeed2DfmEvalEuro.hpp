/*****************************************************************************

      BoardSeed2DfmEvalEuro.hpp
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



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ff_init
Reference :
   http://elm-chan.org/fsw/ff/doc/dinit.html
==============================================================================
*/

DSTATUS  BoardSeed2DfmEvalEuro::ff_init (BYTE pdrv)
{
   return 0;
}



/*
==============================================================================
Name : ff_status
Reference :
   http://elm-chan.org/fsw/ff/doc/dstat.html
==============================================================================
*/

DSTATUS  BoardSeed2DfmEvalEuro::ff_status (BYTE pdrv)
{
   return 0;
}



/*
==============================================================================
Name : ff_read
Reference :
   http://elm-chan.org/fsw/ff/doc/dread.html
==============================================================================
*/

DRESULT  BoardSeed2DfmEvalEuro::ff_read (BYTE pdrv, BYTE * buf, DWORD sector, UINT count)
{
}



/*
==============================================================================
Name : ff_write
Reference :
   http://elm-chan.org/fsw/ff/doc/dwrite.html
==============================================================================
*/

DRESULT  BoardSeed2DfmEvalEuro::ff_write (BYTE pdrv, const BYTE * buf, DWORD sector, UINT count)
{
}



/*
==============================================================================
Name : ff_ioctl
Reference :
   http://elm-chan.org/fsw/ff/doc/dioctl.html
==============================================================================
*/

DRESULT  BoardSeed2DfmEvalEuro::ff_ioctl (BYTE pdrv, BYTE cmd, void * buf)
{
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
