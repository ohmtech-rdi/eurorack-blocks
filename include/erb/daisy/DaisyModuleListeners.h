/*****************************************************************************

      DaisyModuleListeners.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>

#include <cstddef>



namespace erb
{



class DaisyModuleListener;

class DaisyModuleListeners
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  DaisyModuleListeners () = default;
   virtual        ~DaisyModuleListeners () = default;

   void           add (DaisyModuleListener & control);

   void           notify_audio_buffer_start ();
   void           notify_audio_buffer_end ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_MAX_GPIO = 128 };
   std::array <DaisyModuleListener *, NBR_MAX_GPIO>
                  _listeners = {};
   size_t         _nbr_listener = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyModuleListeners (const DaisyModuleListeners & rhs) = delete;
                  DaisyModuleListeners (DaisyModuleListeners && rhs) = delete;
   DaisyModuleListeners &
                  operator = (const DaisyModuleListeners & rhs) = delete;
   DaisyModuleListeners &
                  operator = (DaisyModuleListeners && rhs) = delete;
   bool           operator == (const DaisyModuleListeners & rhs) const = delete;
   bool           operator != (const DaisyModuleListeners & rhs) const = delete;



}; // class DaisyModuleListeners



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
