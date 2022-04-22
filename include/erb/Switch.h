/*****************************************************************************

      Switch.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Button.h"

#include <cstdint>



namespace erb
{



enum class SwitchPosition
{
   First, Center, Last
};

template <size_t NbrPosition>
class Switch
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   static constexpr float ValueMin = 0.f;
   static constexpr float ValueMax = float (NbrPosition) - 1.f;

   static_assert (NbrPosition == 2 || NbrPosition == 3);

   inline         Switch (const uint8_t & data_0, const uint8_t & data_1);
   virtual        ~Switch () = default;

   inline bool    position_first () const;
   inline bool    position_center () const;
   inline bool    position_last () const;
   inline         operator SwitchPosition () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   void           impl_preprocess ();
   inline void    impl_postprocess () {}

   Button         _0;
   Button         _1;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Switch (const Switch & rhs) = delete;
                  Switch (Switch && rhs) = delete;
   Switch &       operator = (const Switch & rhs) = delete;
   Switch &       operator = (Switch && rhs) = delete;
   bool           operator == (const Switch & rhs) const = delete;
   bool           operator != (const Switch & rhs) const = delete;



}; // class Switch



}  // namespace erb



#include "erb/Switch.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
