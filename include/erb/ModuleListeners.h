/*****************************************************************************

      ModuleListeners.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>



namespace erb
{



class ModuleListener;

class ModuleListeners
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  ModuleListeners () = default;
   virtual        ~ModuleListeners () = default;

   void           add (ModuleListener & control);

   void           notify_audio_buffer_start ();
   void           notify_audio_buffer_end ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_MAX_GPIO = 31 };
   std::array <ModuleListener *, NBR_MAX_GPIO>
                  _listeners = {};
   size_t         _nbr_listener = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  ModuleListeners (const ModuleListeners & rhs) = delete;
                  ModuleListeners (ModuleListeners && rhs) = delete;
   ModuleListeners &
                  operator = (const ModuleListeners & rhs) = delete;
   ModuleListeners &
                  operator = (ModuleListeners && rhs) = delete;
   bool           operator == (const ModuleListeners & rhs) const = delete;
   bool           operator != (const ModuleListeners & rhs) const = delete;



}; // class ModuleListeners



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
