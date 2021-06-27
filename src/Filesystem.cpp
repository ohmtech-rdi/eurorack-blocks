/*****************************************************************************

      Filesystem.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Filesystem.h"

#if defined (erb_TARGET_VCV_RACK)
   #include <unistd.h>

#endif



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

#if defined (erb_TARGET_DAISY)
Filesystem::Filesystem (FATFS & fs)
:  _fs (fs)
{
}
#endif



/*
==============================================================================
Name : mount
Description :
   Return 'true' iff mounting the SD card succeeded.
==============================================================================
*/

bool  Filesystem::mount ()
{
#if defined (erb_TARGET_DAISY)
   int force_mount = 1;
   auto err = f_mount (&_fs, "1:/", force_mount);

   _mounted_flag = false;

   if (err == FR_OK) _mounted_flag = true;
   if (err == FR_NOT_READY) _mounted_flag = true;

   return _mounted_flag;

#elif defined (erb_TARGET_VCV_RACK)
   if (_root.empty ()) return false;

   // check that the directory exists
   _mounted_flag = access (_root.c_str (), F_OK) == 0;

   return _mounted_flag;
#endif
}



/*
==============================================================================
Name : unmount
==============================================================================
*/

void  Filesystem::unmount ()
{
#if defined (erb_TARGET_DAISY)
   f_unmount (SDPath); // ignore error

#elif defined (erb_TARGET_VCV_RACK)
   // nothing

#endif
}



/*
==============================================================================
Name : is_mounted
==============================================================================
*/

bool  Filesystem::is_mounted () const
{
   return _mounted_flag;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
