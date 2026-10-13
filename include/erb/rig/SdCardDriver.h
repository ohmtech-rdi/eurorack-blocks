/*****************************************************************************

      SdCardDriver.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_USE_FATFS) && erb_USE_FATFS

#include "ff.h"
#include "ff_gen_drv.h"

#include <array>
#include <functional>

#include <cstddef>



namespace erb
{
namespace rig
{



class SdCard;

class SdCardDriver
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Op
   {
      Initialize, Status, Read, Write
   };

   using FaultInjector = std::function <DRESULT (Op op, DWORD sector, UINT count)>;

   static inline SdCardDriver &
                  use ();

   const Diskio_drvTypeDef &
                  diskio () const;

   void           attach (BYTE pdrv, SdCard & card);
   void           detach (BYTE pdrv);

   void           set_fault_injector (BYTE pdrv, FaultInjector injector);
   void           reset_fault_injector (BYTE pdrv);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // stats
   void           impl_reset_stats ();
   std::size_t    impl_nbr_bytes_read () const;
   std::size_t    impl_nbr_bytes_written () const;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
                  SdCardDriver () = default;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   struct Volume
   {
      SdCard *    card_ptr = nullptr;
      FaultInjector
                  injector;
      bool        injector_run_flag = false;
   };

   static void    fail (const char * what);

   Volume &       volume (BYTE pdrv);
   DRESULT        fault (Volume & volume, Op op, DWORD sector, UINT count);

   static DSTATUS ff_init (BYTE pdrv);
   static DSTATUS ff_status (BYTE pdrv);
   static DRESULT ff_read (BYTE pdrv, BYTE * buf, DWORD sector, UINT count);
   static DRESULT ff_write (BYTE pdrv, const BYTE * buf, DWORD sector, UINT count);
   static DRESULT ff_ioctl (BYTE pdrv, BYTE cmd, void * buf);

   const Diskio_drvTypeDef
                  _diskio = { ff_init, ff_status, ff_read, ff_write, ff_ioctl };

   std::array <Volume, _VOLUMES>
                  _volumes;   // one per FatFS volume slot

   std::size_t    _nbr_bytes_read = 0;
   std::size_t    _nbr_bytes_written = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

                  SdCardDriver (const SdCardDriver & rhs) = delete;
                  SdCardDriver (SdCardDriver && rhs) = delete;
   SdCardDriver & operator = (const SdCardDriver & rhs) = delete;
   SdCardDriver & operator = (SdCardDriver && rhs) = delete;
   bool           operator == (const SdCardDriver & rhs) const = delete;
   bool           operator != (const SdCardDriver & rhs) const = delete;



}; // class SdCardDriver



}  // namespace rig
}  // namespace erb



#include "erb/rig/SdCardDriver.hpp"

#endif // erb_USE_FATFS



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
