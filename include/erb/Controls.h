/*****************************************************************************

      Controls.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>



namespace erb
{



class Control;

class Controls
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Controls () = default;
   virtual        ~Controls () = default;

   void           add (Control & control);

   void           process ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_MAX_GPIO = 31 };
   std::array <Control *, NBR_MAX_GPIO>
                  _controls = {};
   size_t         _nbr_control = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Controls (const Controls & rhs) = delete;
                  Controls (Controls && rhs) = delete;
   Controls &     operator = (const Controls & rhs) = delete;
   Controls &     operator = (Controls && rhs) = delete;
   bool           operator == (const Controls & rhs) const = delete;
   bool           operator != (const Controls & rhs) const = delete;



}; // class Controls



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
