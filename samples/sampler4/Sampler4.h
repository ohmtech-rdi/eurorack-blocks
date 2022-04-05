// Sampler4.h

#pragma once

#include "artifacts/Sampler4Ui.h"
//#include "artifacts/Sampler4Data.h" Uncomment if you use some 'data' resources
#include "erb/erb.h"


struct Sampler4
{
   // The UI elements defined in Sampler4.erbui are in 'ui'
   Sampler4Ui ui;

   // The data resources defined in Sampler4.erbb are in 'data'
   // Uncomment if you use some 'data' resources
   //Sampler4Data data;

   void  init ();
   void  process ();

   // Put here your DSP objects
};
