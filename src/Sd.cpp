/*****************************************************************************

      Sd.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Sd.h"

#if defined (erb_TARGET_DAISY)
   #include "sys/fatfs.h"

#elif defined (erb_TARGET_VCV_RACK)
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

Sd::Sd (Filesystem & filesystem)
:  impl_data (filesystem)
{
}



/*
==============================================================================
Name : mount
Description :
   Return 'true' iff mounting the SD card succeeded.
==============================================================================
*/

bool  Sd::mount ()
{
#if defined (erb_TARGET_DAISY)
   auto err = f_mount (&SDFatFS, SDPath, 1);

   if (err == FR_OK) return true;
   if (err == FR_NOT_READY) return true;

   return false; // failed

#elif defined (erb_TARGET_VCV_RACK)
   if (_root.empty ()) return false;

   // check that the directory exists
   return access (_root.c_str (), F_OK) == 0;
#endif
}



/*
==============================================================================
Name : mount
Description :
   Return 'true' iff mounting the SD card succeeded.
==============================================================================
*/

void  Sd::unmount ()
{
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
