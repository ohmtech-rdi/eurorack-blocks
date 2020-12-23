/*****************************************************************************

      Module.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/AdcChannels.h"
#include "erb/Controls.h"

#if defined (__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wpedantic"
   #pragma GCC diagnostic ignored "-Wignored-qualifiers"
   #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "daisy_seed.h"

#if defined (__GNUC__)
   #pragma GCC diagnostic pop
#endif

#include <array>
#include <functional>



namespace erb
{



class CvIn;
class GateIn;
class GateOut;
class Led;

class Module
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Module ();
   virtual        ~Module () = default;

   template <typename F>
   void           run (F && f);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   uint32_t       now_ms ();
   void           add (CvIn & cv_in, const dsy_gpio_pin & pin);
   void           add (Control & control);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   using AudioCallbackSignature = void (float * const /* out */ [], const float * const /* in */ [], size_t /* size */);

   void           enable_fz ();

   void           do_run ();

   static void    audio_callback_proc (float ** in, float ** out, size_t size);
   void           audio_callback (float ** in, float ** out, size_t size);

   static Module *
                  _this_ptr;

   daisy::DaisySeed
                  _seed;
   std::function <AudioCallbackSignature>
                  _audio_callback;

   AdcChannels    _adc_channels;
   Controls       _controls;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Module (const Module & rhs) = delete;
                  Module (Module && rhs) = delete;
   Module &       operator = (const Module & rhs) = delete;
   Module &       operator = (Module && rhs) = delete;
   bool           operator == (const Module & rhs) const = delete;
   bool           operator != (const Module & rhs) const = delete;



}; // class Module



}  // namespace erb



#include "erb/Module.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
