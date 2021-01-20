/*****************************************************************************

      AudioOutDaisy.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Constants.h"
#include "erb/ModuleListener.h"

#include <array>



namespace erb
{



class Module;

class AudioOutDaisy
:  public ModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Pin
   {
                  Left,
                  Right,
                  Channel0,   // alias to 'Left'
                  Channel1,   // alias to 'Right'
   };

   using Buffer = std::array <float, buffer_size>;

                  AudioOutDaisy (Module & module, Pin pin);
   virtual        ~AudioOutDaisy () override = default;

   AudioOutDaisy &
                  operator = (const Buffer & buffer);

   size_t         size () const;
   float &        operator [] (size_t index);
   void           fill (float val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;
   virtual void   impl_notify_audio_buffer_end () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   static size_t  to_channel (Pin pin);

   Module &       _module;
   const size_t   _channel;

   Buffer         _buffer;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  AudioOutDaisy () = delete;
                  AudioOutDaisy (const AudioOutDaisy & rhs) = delete;
                  AudioOutDaisy (AudioOutDaisy && rhs) = delete;
   AudioOutDaisy &operator = (const AudioOutDaisy & rhs) = delete;
   AudioOutDaisy &operator = (AudioOutDaisy && rhs) = delete;
   bool           operator == (const AudioOutDaisy & rhs) const = delete;
   bool           operator != (const AudioOutDaisy & rhs) const = delete;



}; // class AudioOutDaisy



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
