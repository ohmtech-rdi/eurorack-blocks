/*****************************************************************************

      TestDc.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "artifacts/TestDcUi.h"
#include "artifacts/TestDcData.h"

#include "erb/erb.h"

#include <atomic>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct TestDc
{
   TestDcUi ui;

   void  process ();
   void  idle ();
};
