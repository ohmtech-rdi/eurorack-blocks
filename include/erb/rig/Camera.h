/*****************************************************************************

      Camera.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Display.h"
#include "erb/rig/Bench.h"
#include "erb/rig/Connection.h"
#include "erb/rig/Screen.h"
#include "erb/rig/SystemClockVirtual.h"

#include <source_location>
#include <string>



namespace erb
{
namespace rig
{



template <typename Format>
class Camera
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   struct Setup
   {
      std::string directory;
      ScreenFile::Rotate
                  rotate = ScreenFile::Rotate::R0;
   };

   inline explicit
                  Camera (Setup setup);
   virtual        ~Camera ();

   inline Connection
                  bind (Bench & bench, Display <Format> & display);

   inline bool    same (const std::string & name) const;
   inline void    wait_until_same (const std::string & name, SystemClockVirtual::duration timeout, std::source_location sloc = std::source_location::current ());
   inline void    check_same (const std::string & name, std::source_location sloc = std::source_location::current ()) const;
   inline void    snapshot (const std::string & name) const;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   inline ScreenFile
                  impl_file (const std::string & name) const;
   inline void    impl_unbind ();
   inline void    impl_write_actual (const ScreenFile & file) const;

   const Setup    _setup;
   Bench *        _bench_ptr = nullptr;
   Display <Format> *
                  _display_ptr = nullptr;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Camera () = delete;
                  Camera (const Camera & rhs) = delete;
                  Camera (Camera && rhs) = delete;
   Camera &       operator = (const Camera & rhs) = delete;
   Camera &       operator = (Camera && rhs) = delete;
   bool           operator == (const Camera & rhs) const = delete;
   bool           operator != (const Camera & rhs) const = delete;



}; // class Camera



}  // namespace rig
}  // namespace erb



#include "erb/rig/Camera.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
