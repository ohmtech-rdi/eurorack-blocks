/*****************************************************************************

      %module.name%.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



// !!! THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT MODIFY !!!



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "%module.name%Ui.h"
#include "%module.name%Data.h"

#include "erb/erb.h"



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct %module.name%;

struct Soundfile {
   float ** fBuffers;
   int * fLength;   // length of each part
   int * fSR;       // sample rate of each part
   int * fOffset;   // offset of each part in the global buffer
   int fChannels;  // max number of channels of all concatenated files
};

struct Adapter
{
   inline Adapter (%module.name% & m) : module (m) {}
   inline ~Adapter () = default;

   //-- UI concepts ----------------------------------------------------------

   inline void  openTabBox (const char * /* label_0 */) { /* nothing */ }
   inline void  openHorizontalBox (const char * /* label_0 */) { /* nothing */ }
   inline void  openVerticalBox (const char * /* label_0 */) { /* nothing */ }
   inline void  closeBox () { /* nothing */ }

   inline void  addButton (const char * label_0, float * zone);
   inline void  addCheckButton (const char * label_0, float * zone);
   inline void  addVerticalSlider (const char * label_0, float * zone, float init, float min, float max, float step);
   inline void  addHorizontalSlider (const char * label_0, float * zone, float init, float min, float max, float step);
   inline void  addNumEntry (const char * label_0, float * zone, float init, float min, float max, float step);

   inline void  addHorizontalBargraph (const char * label_0, float * zone, float min, float max);
   inline void  addVerticalBargraph (const char * label_0, float * zone, float min, float max);

   inline void  addSoundfile (const char * label_0, const char * filename_0, Soundfile ** sf_zone);

   inline void  declare (float * /* zone */, const char * /* key */, const char * /* val */) { /* nothing */ }

   //-- Impl -----------------------------------------------------------------

   inline void  push_parameter (float * zone);
   inline void  preprocess ();
   inline void  postprocess ();

   %module.name% & module;

   size_t decl_index = 0;
   std::array <float *, %faust.widgets.length%> parameters;

   struct SoundfileAdapter {
      std::array <const float *, 64> channels;
      int nbr_channels;
      int length;
      int sample_rate;
   };

   std::array <SoundfileAdapter, %module.samples.length%> spl_adapter = {{
%     module.spl_adapters%
   }};

   int offset_zero = 0;
   size_t spl_index = 0;

   std::array <Soundfile, %module.samples.length%> samples = {{
%     module.samples%
   }};
};

struct dsp_memory_manager
{
   ~dsp_memory_manager () = default;

   inline void *   allocate (size_t size);
   inline void     destroy (void * ptr);
};



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct dsp {
   Soundfile * defaultsound = nullptr;
};

using UI = Adapter;
class Meta
{
public:
   inline void  declare (const char * /* key_0 */, const char * /* value_0 */) { /* nothing */ }
};

#if defined (__clang__)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wreserved-id-macro"
   #pragma clang diagnostic ignored "-Wnon-virtual-dtor"
   #pragma clang diagnostic ignored "-Wunused-parameter"
   #pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
   #pragma clang diagnostic ignored "-Wold-style-cast"

#elif defined (__GNUC__)
   #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "module_faust.h"

#if defined (__clang__)
   #pragma clang diagnostic pop
#endif



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

struct %module.name%
{
   %module.name%Ui ui;
   %module.name%Data data;

   inline void  init ();
   inline void  process ();

   Adapter adapter = Adapter { *this };
   dsp_memory_manager mem;
   mydsp dsp;
};



#include "%module.name%.hpp"
