/*****************************************************************************

      VcvAudioOutDaisy.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvConstants.h"
#include "erb/vcvrack/VcvOutputBase.h"
#include "erb/vcvrack/VcvPins.h"

#include <array>



namespace rack
{
namespace engine
{
struct Output;
}
}



namespace erb
{



class VcvModule;

class VcvAudioOutDaisy
:  public VcvOutputBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Buffer = std::array <float, buffer_size>;

                  VcvAudioOutDaisy (VcvModule & module, VcvAudioOutDaisyPin pin);
   virtual        ~VcvAudioOutDaisy () override = default;

   VcvAudioOutDaisy &
                  operator = (const Buffer & buffer);

   size_t         size () const;
   float &        operator [] (size_t index);
   void           fill (float val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_push_sample ();

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;
   virtual void   impl_notify_audio_buffer_end () override;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   using DoubleBuffer = std::array <Buffer, 2>;

   DoubleBuffer   _buffers;
   size_t         _cur_buf = 0;
   size_t         _cur_index = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvAudioOutDaisy () = delete;
                  VcvAudioOutDaisy (const VcvAudioOutDaisy & rhs) = delete;
                  VcvAudioOutDaisy (VcvAudioOutDaisy && rhs) = delete;
   VcvAudioOutDaisy &
                  operator = (const VcvAudioOutDaisy & rhs) = delete;
   VcvAudioOutDaisy &
                  operator = (VcvAudioOutDaisy && rhs) = delete;
   bool           operator == (const VcvAudioOutDaisy & rhs) const = delete;
   bool           operator != (const VcvAudioOutDaisy & rhs) const = delete;



}; // class VcvAudioOutDaisy



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
