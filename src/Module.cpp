/*****************************************************************************

      Module.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Module.h"

#include "erb/CvIn.h"
#include "erb/GateIn.h"
#include "erb/GateOut.h"
#include "erb/Led.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Module::Module ()
:  _adc_channels (_seed)
{
   enable_fz ();

   _this_ptr = this;

   const bool boost = false;

   _seed.Configure ();
   _seed.Init (boost);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : now_ms
==============================================================================
*/

uint32_t Module::now_ms ()
{
   return _seed.system.GetNow ();
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  Module::add (AnalogControlBase & control, const dsy_gpio_pin & pin)
{
   _adc_channels.add (control, pin);
   _controls.add (control);
}



/*
==============================================================================
Name : add
==============================================================================
*/

void  Module::add (Control & control)
{
   _controls.add (control);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : enable_fz
Description :
   Enable FZ (flush-to-zero) denormal behavior
==============================================================================
*/

void  Module::enable_fz ()
{
   uint32_t fpscr = __get_FPSCR ();
   fpscr |= 0x01000000; // FZ bit
   __set_FPSCR (fpscr);
}



/*
==============================================================================
Name : do_run
==============================================================================
*/

void  Module::do_run ()
{
   _adc_channels.init ();

   _seed.adc.Start ();
   _seed.StartAudio (audio_callback_proc);

   for (;;) {}
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  Module::audio_callback_proc (float ** in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  Module::audio_callback (float ** in, float ** out, size_t size)
{
   _controls.process ();

   _audio_callback (out, in, size);

   // Map (-1.f, 1.f) to eurorack audio level (-5V, 5V)
   constexpr float gain_out = 0.433f;

   for (size_t i = 0 ; i < size ; ++i)
   {
      out [0][i] *= gain_out;
      out [1][i] *= gain_out;
   }
}



Module * Module::_this_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
