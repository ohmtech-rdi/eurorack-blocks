/*****************************************************************************

      VcvAudioInDaisy.h
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

class VcvAudioInDaisy
:  public VcvInputBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using Buffer = std::array <float, buffer_size>;

                  VcvAudioInDaisy (VcvModule & module, VcvAudioInDaisyPin pin);
   virtual        ~VcvAudioInDaisy () override = default;

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
                  VcvAudioInDaisy () = delete;
                  VcvAudioInDaisy (const VcvAudioInDaisy & rhs) = delete;
                  VcvAudioInDaisy (VcvAudioInDaisy && rhs) = delete;
   VcvAudioInDaisy &
                  operator = (const VcvAudioInDaisy & rhs) = delete;
   VcvAudioInDaisy &
                  operator = (VcvAudioInDaisy && rhs) = delete;
   bool           operator == (const VcvAudioInDaisy & rhs) const = delete;
   bool           operator != (const VcvAudioInDaisy & rhs) const = delete;



}; // class VcvAudioInDaisy



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
