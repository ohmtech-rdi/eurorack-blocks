/*****************************************************************************

      SdMmc.hpp
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

SdMmc::SdMmc (FATFS & fs)
:  _fs (fs)
{
}



/*
==============================================================================
Name : mount
==============================================================================
*/

SdMmc::Status  SdMmc::mount (const char * path_0, MountOption option)
{
   auto status = f_mount (&_fs, path_0, static_cast <int> (option));

   return static_cast <Status> (status);
}



/*
==============================================================================
Name : unmount
==============================================================================
*/

SdMmc::Status  SdMmc::unmount (const char * path_0)
{
   auto status = f_mount (nullptr, path_0, 0);

   return static_cast <Status> (status);
}



/*
==============================================================================
Name : File::open
==============================================================================
*/

SdMmc::Status  SdMmc::File::open (const char * path_0, const char * mode_0)
{
   BYTE mode = 0;

   // http://elm-chan.org/fsw/ff/doc/open.html

   if (strncmp ("r", mode_0, 2) == 0)
   {
      mode = FA_READ;
   }
   else if (strncmp ("r+", mode_0, 3) == 0)
   {
      mode = FA_READ | FA_WRITE;
   }
   else if (strncmp ("w", mode_0, 2) == 0)
   {
      mode = FA_CREATE_ALWAYS | FA_WRITE;
   }
   else if (strncmp ("w+", mode_0, 3) == 0)
   {
      mode = FA_CREATE_ALWAYS | FA_WRITE | FA_READ;
   }
   else if (strncmp ("a", mode_0, 2) == 0)
   {
      mode = FA_OPEN_APPEND | FA_WRITE;
   }
   else if (strncmp ("a+", mode_0, 3) == 0)
   {
      mode = FA_OPEN_APPEND | FA_WRITE | FA_READ;
   }
   else if (strncmp ("wx", mode_0, 3) == 0)
   {
      mode = FA_CREATE_NEW | FA_WRITE;
   }
   else if (strncmp ("w+x", mode_0, 4) == 0)
   {
      mode = FA_CREATE_NEW | FA_WRITE | FA_READ;
   }

   auto status = f_open (&_file, path_0, mode);

   return static_cast <Status> (status);
}



/*
==============================================================================
Name : File::close
==============================================================================
*/

SdMmc::Status  SdMmc::File::close ()
{
   auto status = f_close (&_file);

   return static_cast <Status> (status);
}



/*
==============================================================================
Name : File::read
==============================================================================
*/

SdMmc::Status  SdMmc::File::read (void * buf, std::size_t & size)
{
   UINT actual_size = 0;
   auto status = f_read (&_file, buf, size, &actual_size);

   if (status == static_cast <FRESULT> (Status::OK))
   {
      size = actual_size;
   }

   return static_cast <Status> (status);
}



/*
==============================================================================
Name : File::write
==============================================================================
*/

SdMmc::Status  SdMmc::File::write (const void * buf, std::size_t & size)
{
   UINT actual_size = 0;
   auto status = f_write (&_file, buf, size, &actual_size);

   if (status == static_cast <FRESULT> (Status::OK))
   {
      size = actual_size;
   }

   return static_cast <Status> (status);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
