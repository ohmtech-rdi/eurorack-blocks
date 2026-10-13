/*****************************************************************************

      SdCard.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS

#include "ff.h"
#include "ff_gen_drv.h"

#include <string>
#include <vector>

#include <cstddef>
#include <cstdint>



namespace erb
{
namespace rig
{



class SdCard
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr std::size_t
                  SectorSize = 512;

                  SdCard () = default;
                  ~SdCard () = default;
                  SdCard (const SdCard & rhs) = default;
                  SdCard (SdCard && rhs) = default;
   SdCard &       operator = (const SdCard & rhs) = default;
   SdCard &       operator = (SdCard && rhs) = default;

   inline bool    empty () const;
   inline std::size_t
                  size () const;

   void           format (std::size_t size);

   void           add (const std::string & host_path, const std::string & card_path);
   void           write (const std::string & card_path, const std::vector <std::uint8_t> & content);
   void           remove (const std::string & card_path);

   std::vector <std::uint8_t>
                  read (const std::string & card_path);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // from 'SdCardDriver', the card attached to the volume
   DSTATUS        impl_init () const;
   DSTATUS        impl_status () const;
   DRESULT        impl_read (BYTE * buf, DWORD sector, UINT count) const;
   DRESULT        impl_write (const BYTE * buf, DWORD sector, UINT count);
   DRESULT        impl_ioctl (BYTE cmd, void * buf) const;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct ScopedVolume
   {
                  ScopedVolume (SdCard & card, bool mount_flag);
                  ~ScopedVolume ();

      std::string file (const std::string & card_path) const;

      char        path [4] = {};
      BYTE        pdrv = 0;
      FATFS       fs = {};
   };

   static void    check (FRESULT result, const char * what, const std::string & path);

   std::vector <std::uint8_t>
                  _bytes;  // entire card in memory



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const SdCard & rhs) const = delete;
   bool           operator != (const SdCard & rhs) const = delete;



}; // class SdCard



}  // namespace rig
}  // namespace erb



#include "erb/rig/SdCard.hpp"

#endif // erb_USE_FATFS



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
