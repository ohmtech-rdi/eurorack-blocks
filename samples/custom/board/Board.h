// Board.h

#pragma once

#if defined (erb_TARGET_DAISY)
   #include "BoardFirmware.h"

#elif defined (erb_TARGET_VCV_RACK)
   #include "BoardSimulator.h"

#endif
