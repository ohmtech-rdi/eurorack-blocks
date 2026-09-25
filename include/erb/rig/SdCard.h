/*****************************************************************************

      SdCard.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS

#include "ff.h"
#include "ff_gen_drv.h"

#include <array>
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
   virtual        ~SdCard () = default;
                  SdCard (const SdCard & rhs) = default;
                  SdCard (SdCard && rhs) = default;
   SdCard &       operator = (const SdCard & rhs) = default;
   SdCard &       operator = (SdCard && rhs) = default;

   inline bool    empty () const;
   inline std::size_t
                  size () const;

   void           format (std::size_t size);

   void           add (const std::string & host_path, const std::string & card_path);
   void           remove (const std::string & card_path);

   std::vector <std::uint8_t>
                  read (const std::string & card_path);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static const Diskio_drvTypeDef &
                  impl_driver ();
   static void    impl_attach (BYTE pdrv, SdCard * card_ptr);

   // stats
   static void    impl_reset_stats ();
   static std::size_t
                  impl_nbr_bytes_read ();
   static std::size_t
                  impl_nbr_bytes_written ();

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

   static DSTATUS ff_init (BYTE pdrv);
   static DSTATUS ff_status (BYTE pdrv);
   static DRESULT ff_read (BYTE pdrv, BYTE * buf, DWORD sector, UINT count);
   static DRESULT ff_write (BYTE pdrv, const BYTE * buf, DWORD sector, UINT count);
   static DRESULT ff_ioctl (BYTE pdrv, BYTE cmd, void * buf);

   std::vector <std::uint8_t>
                  _bytes;  // entire card in memory

   static std::array <SdCard *, _VOLUMES>
                  _attached;
   static std::size_t
                  _nbr_bytes_read;
   static std::size_t
                  _nbr_bytes_written;



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
