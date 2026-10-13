/*****************************************************************************

      Camera.hpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <chrono>

#include <cassert>
#include <cstdio>



namespace erb
{
namespace rig
{



/*
==============================================================================
Name : ctor
==============================================================================
*/

template <typename Format>
Camera <Format>::Camera (Setup setup)
:  _setup (std::move (setup))
{
   assert (!_setup.directory.empty ());
   assert (_setup.directory.back () != '/');
}



/*
==============================================================================
Name : dtor
==============================================================================
*/

template <typename Format>
Camera <Format>::~Camera ()
{
   assert (_bench_ptr == nullptr);
}



/*
==============================================================================
Name : bind
==============================================================================
*/

template <typename Format>
Connection  Camera <Format>::bind (Bench & bench, Display <Format> & display)
{
   assert (_bench_ptr == nullptr);

   _bench_ptr = &bench;
   _display_ptr = &display;

   return Connection {[this] () { impl_unbind (); }};
}



/*
==============================================================================
Name : same
==============================================================================
*/

template <typename Format>
bool  Camera <Format>::same (const std::string & name) const
{
   assert (_bench_ptr != nullptr);

   const auto screen = read_screen <Format> (impl_file (name));

   return rig::same (*_display_ptr, screen);
}



/*
==============================================================================
Name : wait_until_same
==============================================================================
*/

template <typename Format>
void  Camera <Format>::wait_until_same (const std::string & name, SystemClockVirtual::duration timeout, std::source_location sloc)
{
   assert (_bench_ptr != nullptr);

   const auto file = impl_file (name);
   const auto screen = read_screen <Format> (file);
   const auto actual_path = file.actual_path ();

   const bool ok = _bench_ptr->impl_pump_until (
      [this, &screen] () { return rig::same (*_display_ptr, screen); },
      timeout
   );

   if (!ok)
   {
      const auto ms = std::chrono::duration_cast <std::chrono::milliseconds> (timeout).count ();
      std::fprintf (
         stderr,
         "wait_until_same at %s:%u: display did not match '%s' within %lld ms, actual written to '%s'\n",
         sloc.file_name (), unsigned (sloc.line ()),
         file.path.c_str (), (long long) ms, actual_path.c_str ()
      );
      std::fflush (stderr);

      impl_write_actual (file);
   }

   assert (ok);
}



/*
==============================================================================
Name : check_same
==============================================================================
*/

template <typename Format>
void  Camera <Format>::check_same (const std::string & name, std::source_location sloc) const
{
   assert (_bench_ptr != nullptr);

   const auto file = impl_file (name);
   const auto screen = read_screen <Format> (file);
   const auto actual_path = file.actual_path ();

   const bool ok = rig::same (*_display_ptr, screen);

   if (!ok)
   {
      std::fprintf (
         stderr,
         "check_same at %s:%u: display does not match '%s', actual written to '%s'\n",
         sloc.file_name (), unsigned (sloc.line ()),
         file.path.c_str (), actual_path.c_str ()
      );
      std::fflush (stderr);

      impl_write_actual (file);
   }

   assert (ok);
}



/*
==============================================================================
Name : snapshot
==============================================================================
*/

template <typename Format>
void  Camera <Format>::snapshot (const std::string & name) const
{
   assert (_bench_ptr != nullptr);

   write_screen <Format> (_display_ptr->impl_data, impl_file (name));
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_file
==============================================================================
*/

template <typename Format>
ScreenFile  Camera <Format>::impl_file (const std::string & name) const
{
   return {.path = _setup.directory + "/" + name, .rotate = _setup.rotate};
}



/*
==============================================================================
Name : impl_unbind
==============================================================================
*/

template <typename Format>
void  Camera <Format>::impl_unbind ()
{
   assert (_bench_ptr != nullptr);

   _bench_ptr = nullptr;
   _display_ptr = nullptr;
}



/*
==============================================================================
Name : impl_write_actual
==============================================================================
*/

template <typename Format>
void  Camera <Format>::impl_write_actual (const ScreenFile & file) const
{
   write_screen <Format> (_display_ptr->impl_data, {.path = file.actual_path (), .rotate = file.rotate});
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
