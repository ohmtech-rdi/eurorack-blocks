/*****************************************************************************

      DacDaisy.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace daisy
{
class DacHandle;
}

namespace erb
{



class DacDaisy
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   using Channel = size_t;

   inline         DacDaisy (daisy::DacHandle & dac, std::initializer_list <Channel> channels);
   virtual        ~DacDaisy () = default;

   inline void    write (size_t index, uint16_t val);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   daisy::DacHandle &
                  _dac;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DacDaisy (const DacDaisy & rhs) = delete;
                  DacDaisy (DacDaisy && rhs) = delete;
   DacDaisy &     operator = (const DacDaisy & rhs) = delete;
   DacDaisy &     operator = (DacDaisy && rhs) = delete;
   bool           operator == (const DacDaisy & rhs) const = delete;
   bool           operator != (const DacDaisy & rhs) const = delete;



}; // class DacDaisy



}  // namespace erb



#include "erb/daisy/DacDaisy.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
