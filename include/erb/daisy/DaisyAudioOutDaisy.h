/*****************************************************************************

      DaisyAudioOutDaisy.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/daisy/DaisyConstants.h"
#include "erb/daisy/DaisyModuleListener.h"
#include "erb/daisy/DaisyPins.h"

#include <array>



namespace erb
{



class DaisyModule;

class DaisyAudioOutDaisy
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Buffer = std::array <float, buffer_size>;

                  DaisyAudioOutDaisy (DaisyModule & module, AudioOutDaisyPin pin);
   virtual        ~DaisyAudioOutDaisy () override = default;

   DaisyAudioOutDaisy &
                  operator = (const Buffer & buffer);

   size_t         size () const;
   float &        operator [] (size_t index);
   void           fill (float val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;
   virtual void   impl_notify_audio_buffer_end () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   DaisyModule &       _module;
   const size_t   _channel;

   Buffer         _buffer;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyAudioOutDaisy () = delete;
                  DaisyAudioOutDaisy (const DaisyAudioOutDaisy & rhs) = delete;
                  DaisyAudioOutDaisy (DaisyAudioOutDaisy && rhs) = delete;
   DaisyAudioOutDaisy &
                  operator = (const DaisyAudioOutDaisy & rhs) = delete;
   DaisyAudioOutDaisy &
                  operator = (DaisyAudioOutDaisy && rhs) = delete;
   bool           operator == (const DaisyAudioOutDaisy & rhs) const = delete;
   bool           operator != (const DaisyAudioOutDaisy & rhs) const = delete;



}; // class DaisyAudioOutDaisy



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
