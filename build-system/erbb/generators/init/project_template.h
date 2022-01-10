/*
------------------------------------------------------------------------------

      %Name%.h

------------------------------------------------------------------------------
*/



//--- INCLUDE FILES ----------------------------------------------------------

#include "artifacts/%Name%Ui.h"
#include "artifacts/%Name%Data.h"

#include "erb/erb.h"



//----------------------------------------------------------------------------

struct %Name%
{
   // The UI elements defined in %Name%.erbui are in 'ui'
   %Name%Ui ui;

   // The data elements defined in %Name%.erbui are in 'data'
   %Name%Data data;

   void  init ();
   void  process ();

   // Put here your DSP classes
};
