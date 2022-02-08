/*
------------------------------------------------------------------------------

      %Name%.h

------------------------------------------------------------------------------
*/



//--- INCLUDE FILES ----------------------------------------------------------

#include "artifacts/%Name%Ui.h"

// Uncomment if you use some 'data' resources
//#include "artifacts/%Name%Data.h"

#include "erb/erb.h"



//----------------------------------------------------------------------------

struct %Name%
{
   // The UI elements defined in %Name%.erbui are in 'ui'
   %Name%Ui ui;

   // The data resources defined in %Name%.erbb are in 'data'
   // Uncomment if you use some 'data' resources
   //%Name%Data data;

   void  init ();
   void  process ();

   // Put here your DSP classes
};
