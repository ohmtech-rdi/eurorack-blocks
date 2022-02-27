// %Name%.h

#pragma once

#include "artifacts/%Name%Ui.h"
//#include "artifacts/%Name%Data.h" Uncomment if you use some 'data' resources
#include "erb/erb.h"


struct %Name%
{
   // The UI elements defined in %Name%.erbui are in 'ui'
   %Name%Ui ui;

   // The data resources defined in %Name%.erbb are in 'data'
   // Uncomment if you use some 'data' resources
   //%Name%Data data;

   void  init ();
   void  process ();

   // Put here your DSP objects
};
