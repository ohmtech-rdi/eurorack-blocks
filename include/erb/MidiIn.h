/*****************************************************************************

      MidiIn.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/MidiMessage.h"
#include "erb/Stream.h"



namespace erb
{



class MidiIn
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         MidiIn (const Stream & data);
   virtual        ~MidiIn () = default;

   MidiMessage    pop ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   const Stream & impl_data;
   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  MidiIn () = delete;
                  MidiIn (const MidiIn & rhs) = delete;
                  MidiIn (MidiIn && rhs) = delete;
   MidiIn &       operator = (const MidiIn & rhs) = delete;
   MidiIn &       operator = (MidiIn && rhs) = delete;
   bool           operator == (const MidiIn & rhs) const = delete;
   bool           operator != (const MidiIn & rhs) const = delete;



}; // class MidiIn



}  // namespace erb



#include "erb/MidiIn.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
