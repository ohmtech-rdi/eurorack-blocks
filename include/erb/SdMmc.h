/*****************************************************************************

      SdMmc.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "ff.h"



namespace erb
{



class SdMmc
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   // Reference: http://elm-chan.org/fsw/ff/doc/rc.html
   enum class Status
   {
      OK = 0,   // Succeeded

      DiskError,
      AssertionFailed,
      NotReady,
      FileNotFound,
      PathNotFound,
      PathInvalid,
      Denied,
      AlreadyExist,
      InvalidObject,
      WriteProtected,
      InvalidDrive,
      NotEnabled,
      NoFilesystem,
      MkfsAborted,
      Timeout,
      Locked,
      LfnBufferTooSmall,
      TooManyOpenFiles,
      InvalidParameter,
   };

   enum class MountOption
   {
      Defer = 0, Immediate
   };

   // WARNING: Can't live on stack per FatFS libDaisy configuration
   class File
   {
   public:
      inline      ~File ();
      inline Status
                  open (const char * path_0, const char * mode_0);
      inline Status
                  close ();

      inline Status
                  seek (std::size_t offset);
      inline Status
                  read (void * buf, std::size_t & size);
      inline Status
                  write (const void * buf, std::size_t & size);
      inline std::size_t
                  size () const;

   private:
      FIL         _file;
   };

   class Directory
   {
   public:
      struct FileInfo
      {
         std::size_t
                  size;
         bool     is_read_only;
         bool     is_hidden;
         bool     is_system;
         bool     is_directory;
         bool     is_archive;
         char     name_0 [256];  // '\0' past last item of the directory
         char     alt_name_0 [13];
      };
      inline      ~Directory ();
      inline Status
                  open (const char * path_0);
      inline Status
                  close ();

      inline Status
                  read (FileInfo & file_info);

   private:
      DIR         _dir;
   };

   inline         SdMmc (FATFS & fs);
   virtual        ~SdMmc () = default;

   inline Status  mount (const char * path_0, MountOption option);
   inline Status  unmount (const char * path_0);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   FATFS &        _fs;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SdMmc () = delete;
                  SdMmc (const SdMmc & rhs) = delete;
                  SdMmc (SdMmc && rhs) = delete;
   SdMmc &        operator = (const SdMmc & rhs) = delete;
   SdMmc &        operator = (SdMmc && rhs) = delete;
   bool           operator == (const SdMmc & rhs) const = delete;
   bool           operator != (const SdMmc & rhs) const = delete;



}; // class SdMmc



}  // namespace erb



#include "erb/SdMmc.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
