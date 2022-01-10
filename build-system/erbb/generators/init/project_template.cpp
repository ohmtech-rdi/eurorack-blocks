/*
------------------------------------------------------------------------------

      %Name%.cpp

------------------------------------------------------------------------------
*/



//--- INCLUDE FILES ----------------------------------------------------------

#include "%Name%.h"



/*
------------------------------------------------------------------------------
Name : init
------------------------------------------------------------------------------
*/

void  %Name%::init ()
{
   // This function is called once, before the first 'process' is called
   // you can setup your module here.
}



/*
------------------------------------------------------------------------------
Name : process
------------------------------------------------------------------------------
*/

void  %Name%::process ()
{
   // This function is called regularly every buffer size
   // get your audio input(s) if any, and write to your audio output(s)

   for (size_t i = 0 ; i < erb_BUFFER_SIZE ; ++i)
   {
      ui.audio_out [i] = ui.audio_in [i];
   }
}
