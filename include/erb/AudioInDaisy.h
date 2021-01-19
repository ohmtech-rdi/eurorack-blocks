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

   using Frame = std::array <float, buffer_size>;

                  AudioInDaisy (Module & module);
   virtual        ~AudioInDaisy () override = default;

   size_t         size () const;
   const Frame &  operator [] (size_t index) const;

   Frame          left;
   Frame          right;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // ModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   Module &       _module;



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
