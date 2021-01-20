/*****************************************************************************

      AudioInDaisy.h
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

class AudioInDaisy
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

                  AudioInDaisy (Module & module, Pin pin);
   virtual        ~AudioInDaisy () override = default;

                  operator Buffer () const;

   size_t         size () const;
   const float &  operator [] (size_t index);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



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
                  AudioInDaisy () = delete;
                  AudioInDaisy (const AudioInDaisy & rhs) = delete;
                  AudioInDaisy (AudioInDaisy && rhs) = delete;
   AudioInDaisy & operator = (const AudioInDaisy & rhs) = delete;
   AudioInDaisy & operator = (AudioInDaisy && rhs) = delete;
   bool           operator == (const AudioInDaisy & rhs) const = delete;
   bool           operator != (const AudioInDaisy & rhs) const = delete;



}; // class AudioInDaisy



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
