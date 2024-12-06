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
      Status      open (const char * path_0, const char * mode_0);
      Status      close ();

   private:
      FIL         _file;
   };

   inline         SdMmc (FATFS & fs);
   virtual        ~SdMmc () = default;

   Status         mount (const char * path_0, MountOption option);
   Status         unmount (const char * path_0);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_preprocess () {}
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
