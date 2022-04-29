// Custom.h

#pragma once

#include "artifacts/CustomUi.h"

#include "dsp/Filter2Poles.h"

#include "erb/erb.h"


struct Custom
{
   CustomUi ui;

   void  init ();
   void  process ();

   dsp::Filter2Poles filter;
};
