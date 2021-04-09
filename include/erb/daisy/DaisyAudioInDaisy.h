/*****************************************************************************

      DaisyAudioInDaisy.h
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

class DaisyAudioInDaisy
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Buffer = std::array <float, buffer_size>;

                  DaisyAudioInDaisy (DaisyModule & module, AudioInDaisyPin pin);
   virtual        ~DaisyAudioInDaisy () override = default;

                  operator Buffer () const;

   size_t         size () const;
   const float &  operator [] (size_t index);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   // DaisyModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   DaisyModule &       _module;
   const size_t   _channel;

   Buffer         _buffer;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyAudioInDaisy () = delete;
                  DaisyAudioInDaisy (const DaisyAudioInDaisy & rhs) = delete;
                  DaisyAudioInDaisy (DaisyAudioInDaisy && rhs) = delete;
   DaisyAudioInDaisy &
                  operator = (const DaisyAudioInDaisy & rhs) = delete;
   DaisyAudioInDaisy &
                  operator = (DaisyAudioInDaisy && rhs) = delete;
   bool           operator == (const DaisyAudioInDaisy & rhs) const = delete;
   bool           operator != (const DaisyAudioInDaisy & rhs) const = delete;



}; // class DaisyAudioInDaisy



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
