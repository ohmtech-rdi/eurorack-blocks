// %Name%.cpp

#include "%Name%.h"

#include <cstddef>



void  %Name%::init ()
{
   // This function is called once, before the first 'process' is called.
   // you can setup your module here.
}


void  %Name%::process ()
{
   // This function is called regularly every buffer size
   // get your audio input(s) if any, and write to your audio output(s)

   for (std::size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out [i] = ui.audio_in [i];
   }
}
