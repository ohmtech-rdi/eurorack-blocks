/*****************************************************************************

      DaisyAudioIn.h
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

class DaisyAudioIn
:  public DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Buffer = std::array <float, buffer_size>;

                  DaisyAudioIn (DaisyModule & module, AudioInPin pin);
   virtual        ~DaisyAudioIn () override = default;

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
                  DaisyAudioIn () = delete;
                  DaisyAudioIn (const DaisyAudioIn & rhs) = delete;
                  DaisyAudioIn (DaisyAudioIn && rhs) = delete;
   DaisyAudioIn & operator = (const DaisyAudioIn & rhs) = delete;
   DaisyAudioIn & operator = (DaisyAudioIn && rhs) = delete;
   bool           operator == (const DaisyAudioIn & rhs) const = delete;
   bool           operator != (const DaisyAudioIn & rhs) const = delete;



}; // class DaisyAudioIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
