/*****************************************************************************

      SubmoduleDaisySeed.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/SubmoduleDaisySeed.h"

#undef erb_DAISY_HEARTBEAT



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

SubmoduleDaisySeed::SubmoduleDaisySeed ()
{
   enable_fz ();

   _this_ptr = this;

   _seed.Configure ();
   _seed.Init (true /* boost */);

   _seed.SetAudioBlockSize (erb_BUFFER_SIZE);
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : init_gpio_input
==============================================================================
*/

void  SubmoduleDaisySeed::init_gpio_input (Pin pin, Pull pull)
{
   dsy_gpio gpio;
   gpio.pin = pin;
   gpio.mode = DSY_GPIO_MODE_INPUT;
   gpio.pull
      = pull == Pull::Down
      ? DSY_GPIO_PULLDOWN
      : DSY_GPIO_PULLUP;

   dsy_gpio_init (&gpio);
}



/*
==============================================================================
Name : read_gpio
==============================================================================
*/

uint8_t  SubmoduleDaisySeed::read_gpio (Pin pin)
{
   dsy_gpio gpio;
   gpio.pin = pin;
   // all the other fields are irrelevant

   return dsy_gpio_read (&gpio);
}



/*
==============================================================================
Name : init_gpio_output
==============================================================================
*/

void  SubmoduleDaisySeed::init_gpio_output (Pin pin)
{
   dsy_gpio gpio;
   gpio.pin = pin;
   gpio.mode = DSY_GPIO_MODE_OUTPUT_PP;
   gpio.pull = DSY_GPIO_NOPULL;

   dsy_gpio_init (&gpio);
}



/*
==============================================================================
Name : write_gpio
==============================================================================
*/

void  SubmoduleDaisySeed::write_gpio (Pin pin, uint8_t val)
{
   dsy_gpio gpio;
   gpio.pin = pin;
   // all the other fields are irrelevant

   dsy_gpio_write (&gpio, val);
}



/*
==============================================================================
Name : init_dac_channels
==============================================================================
*/

void  SubmoduleDaisySeed::init_dac_channels (std::initializer_list <DacPin> dac_pins)
{
   daisy::DacHandle::Channel channel
      = daisy::DacHandle::Channel::BOTH;

   if (dac_pins.size () == 1)
   {
      auto dac_pin = *dac_pins.begin ();
      if (dac_pin.pin == DacPin0.pin)
      {
         channel = daisy::DacHandle::Channel::ONE;
      }
      else
      {
         channel = daisy::DacHandle::Channel::TWO;
      }
   }

   daisy::DacHandle::Config cfg;
   cfg.bitdepth = daisy::DacHandle::BitDepth::BITS_12;
   cfg.buff_state = daisy::DacHandle::BufferState::ENABLED;
   cfg.mode = daisy::DacHandle::Mode::POLLING;
   cfg.chn = channel;
   _seed.dac.Init (cfg);
}



/*
==============================================================================
Name : write_dac
==============================================================================
*/

void  SubmoduleDaisySeed::write_dac (DacPin pin, uint16_t val)
{
   auto channel
      = (pin.pin == DacPin0.pin)
      ? daisy::DacHandle::Channel::ONE
      : daisy::DacHandle::Channel::TWO;

   _seed.dac.WriteValue (channel, val);
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : enable_fz
Description :
   Enable FZ (flush-to-zero) denormal behavior
==============================================================================
*/

void  SubmoduleDaisySeed::enable_fz ()
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

void  SubmoduleDaisySeed::do_run ()
{
   _seed.adc.Start ();
   _seed.StartAudio (audio_callback_proc);

   for (;;) {}
}



/*
==============================================================================
Name : audio_callback_proc
==============================================================================
*/

void  SubmoduleDaisySeed::audio_callback_proc (float ** in, float ** out, size_t size)
{
   _this_ptr->audio_callback (in, out, size);
}



/*
==============================================================================
Name : audio_callback
==============================================================================
*/

void  SubmoduleDaisySeed::audio_callback (float ** in, float ** out, size_t /* size */)
{
   raw_audio_inputs = in;
   raw_audio_outputs = out;

   _run ();

   _clock.tick ();

#if defined (erb_DAISY_HEARTBEAT)
   static uint16_t phase = 0;
   phase += 100;
   _seed.SetLed (phase < 32000);
#endif
}



SubmoduleDaisySeed * SubmoduleDaisySeed::_this_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
