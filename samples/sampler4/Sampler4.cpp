// Sampler4.cpp

#include "Sampler4.h"


Sampler4::Track::Track (erb::Encoder & select_, erb::Button & trigger_button_, erb::Led <erb::PinType::Pwm> & trigger_led_, erb::GateIn & trigger_gate_)
:  select (select_)
,  trigger_button (trigger_button_)
,  trigger_led (trigger_led_)
,  trigger_gate (trigger_gate_)
{
}

void  Sampler4::init ()
{
}


void  Sampler4::process ()
{
   // This function is called regularly every buffer size
   // get your audio input(s) if any, and write to your audio output(s)

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out [i] = 0.f;
   }
}
