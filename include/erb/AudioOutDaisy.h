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

   using Frame = std::array <float, buffer_size>;

                  AudioOutDaisy (Module & module);
   virtual        ~AudioOutDaisy () override = default;

   size_t         size () const;
   Frame &        operator [] (size_t index);

   Frame          left;
   Frame          right;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;
   virtual void   impl_notify_audio_buffer_end () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Module &       _module;



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
