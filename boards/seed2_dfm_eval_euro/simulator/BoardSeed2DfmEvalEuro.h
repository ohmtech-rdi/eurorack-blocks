/*****************************************************************************

      BoardSeed2DfmEvalEuro.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/BoardGeneric.h"

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   #include "ff.h"
   #include "ff_gen_drv.h"
#endif



namespace erb
{



class BoardSeed2DfmEvalEuro
:  public BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         BoardSeed2DfmEvalEuro ();
   inline virtual ~BoardSeed2DfmEvalEuro () override;

   // Digital Inputs
   inline const uint8_t &
                  gpi (size_t i) { return _digital_inputs [i]; }

   // Analog Inputs
   inline const float &
                  adc (size_t i) { return _analog_inputs [i]; }

   // Audio Inputs
   inline const Buffer &
                  audioin (size_t i) { return _audio_inputs [i]; }

   // Digital Outputs
   inline uint8_t &
                  gpo (size_t i) { return _digital_outputs [i]; }

   // Analog Outputs
   inline float & dac (size_t i) { return _analog_outputs [i]; }

   // Audio Outputs
   inline Buffer &
                  audioout (size_t i) { return _audio_outputs [i]; }

   // Display
   inline typename erb::FormatSsd130x <128, 64>::Storage &
                  oled () { return _oled; }

   // SdMmc
#if defined (erb_USE_FATFS) && erb_USE_FATFS
   inline FATFS & fatfs () { return _ff; }
   inline bool    set_sd (const char * path_0);
   inline void    reset_sd ();

#else
   inline int     fatfs () { return 0; }

#endif



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   static inline DSTATUS
                  ff_init (BYTE pdrv);
   static inline DSTATUS
                  ff_status (BYTE pdrv);
   static inline DRESULT
                  ff_read (BYTE pdrv, BYTE * buf, DWORD sector, UINT count);
#if _USE_WRITE == 1
   static inline DRESULT
                  ff_write (BYTE pdrv, const BYTE * buf, DWORD sector, UINT count);
#endif
#if _USE_IOCTL == 1
   static inline DRESULT
                  ff_ioctl (BYTE pdrv, BYTE cmd, void * buf);
#endif
#endif

   erb::FormatSsd130x <128, 64>::Storage
                  _oled;

#if defined (erb_USE_FATFS) && erb_USE_FATFS
   FATFS          _ff;
   char           _ff_path [4];
   inline static std::FILE *
                  _ff_file_ptr = nullptr;
   inline static std::size_t
                  _ff_sector_cnt = 0;
   static constexpr std::size_t
                  _ff_sector_size = 512;

   const Diskio_drvTypeDef
                  _ff_driver = {
                     ff_init,
                     ff_status,
                     ff_read,
#if _USE_WRITE == 1
                     ff_write,
#endif
#if _USE_IOCTL == 1
                     ff_ioctl,
#endif
                  };
#endif


/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardSeed2DfmEvalEuro (const BoardSeed2DfmEvalEuro & rhs) = delete;
                  BoardSeed2DfmEvalEuro (BoardSeed2DfmEvalEuro && rhs) = delete;
   BoardSeed2DfmEvalEuro &
                  operator = (const BoardSeed2DfmEvalEuro & rhs) = delete;
   BoardSeed2DfmEvalEuro &
                  operator = (BoardSeed2DfmEvalEuro && rhs) = delete;
   bool           operator == (const BoardSeed2DfmEvalEuro & rhs) const = delete;
   bool           operator != (const BoardSeed2DfmEvalEuro & rhs) const = delete;



}; // class BoardSeed2DfmEvalEuro



}  // namespace erb



#include "BoardSeed2DfmEvalEuro.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
