/*****************************************************************************

      VcvAudioOut.h
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

class VcvAudioOut
:  public VcvOutputBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Buffer = std::array <float, buffer_size>;

                  VcvAudioOut (VcvModule & module, VcvAudioOutPin pin);
   virtual        ~VcvAudioOut () override = default;

   VcvAudioOut &
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
                  VcvAudioOut () = delete;
                  VcvAudioOut (const VcvAudioOut & rhs) = delete;
                  VcvAudioOut (VcvAudioOut && rhs) = delete;
   VcvAudioOut &  operator = (const VcvAudioOut & rhs) = delete;
   VcvAudioOut &  operator = (VcvAudioOut && rhs) = delete;
   bool           operator == (const VcvAudioOut & rhs) const = delete;
   bool           operator != (const VcvAudioOut & rhs) const = delete;



}; // class VcvAudioOut



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
