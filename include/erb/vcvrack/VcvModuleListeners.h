/*****************************************************************************

      VcvModuleListeners.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>



namespace erb
{



class VcvModuleListener;

class VcvModuleListeners
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VcvModuleListeners () = default;
   virtual        ~VcvModuleListeners () = default;

   void           add (VcvModuleListener & control);

   void           notify_audio_buffer_start ();
   void           notify_audio_buffer_end ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum {         NBR_MAX_GPIO = 128 };
   std::array <VcvModuleListener *, NBR_MAX_GPIO>
                  _listeners = {};
   size_t         _nbr_listener = 0;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvModuleListeners (const VcvModuleListeners & rhs) = delete;
                  VcvModuleListeners (VcvModuleListeners && rhs) = delete;
   VcvModuleListeners &
                  operator = (const VcvModuleListeners & rhs) = delete;
   VcvModuleListeners &
                  operator = (VcvModuleListeners && rhs) = delete;
   bool           operator == (const VcvModuleListeners & rhs) const = delete;
   bool           operator != (const VcvModuleListeners & rhs) const = delete;



}; // class VcvModuleListeners



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
