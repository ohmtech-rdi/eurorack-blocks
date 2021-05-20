/*****************************************************************************

      VcvAudioIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvConstants.h"
#include "erb/vcvrack/VcvInputBase.h"
#include "erb/vcvrack/VcvPins.h"

#include <array>



namespace erb
{



class VcvModule;

class VcvAudioIn
:  public VcvInputBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Buffer = std::array <float, buffer_size>;

                  VcvAudioIn (VcvModule & module, VcvAudioInPin pin);
   virtual        ~VcvAudioIn () override = default;

                  operator Buffer () const;

   size_t         size () const;
   const float &  operator [] (size_t index);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_pull_sample ();

   // VcvModuleListener
   virtual void   impl_notify_audio_buffer_start () override;



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
                  VcvAudioIn () = delete;
                  VcvAudioIn (const VcvAudioIn & rhs) = delete;
                  VcvAudioIn (VcvAudioIn && rhs) = delete;
   VcvAudioIn &   operator = (const VcvAudioIn & rhs) = delete;
   VcvAudioIn &   operator = (VcvAudioIn && rhs) = delete;
   bool           operator == (const VcvAudioIn & rhs) const = delete;
   bool           operator != (const VcvAudioIn & rhs) const = delete;



}; // class VcvAudioIn



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
