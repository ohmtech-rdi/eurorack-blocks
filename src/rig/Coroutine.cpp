/*****************************************************************************

      Coroutine.cpp
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/rig/Coroutine.h"

#include <utility>

#include <cassert>



namespace erb
{
namespace rig
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : dtor
==============================================================================
*/

Coroutine::~Coroutine ()
{
   stop ();
}



/*
==============================================================================
Name : start
Note :
   Asymmetric coroutine with function running on a thread
==============================================================================
*/

void  Coroutine::start (std::function <void ()> func)
{
   assert (!_thread.joinable ());

   _running = true;
   _thread = std::thread (&Coroutine::run, this, std::move (func));

   std::unique_lock lock (_mutex);
   wait_suspended (lock);
}



/*
==============================================================================
Name : stop
==============================================================================
*/

void  Coroutine::stop ()
{
   if (!_thread.joinable ()) return;

   {
      std::unique_lock lock (_mutex);
      _stop = true;
      _running = true;
      _cv.notify_all ();
   }

   _thread.join ();
}



/*
==============================================================================
Name : resume
==============================================================================
*/

void  Coroutine::resume ()
{
   assert (_thread.joinable ());

   std::unique_lock lock (_mutex);
   assert (!_running);
   assert (!_done);

   _running = true;
   _cv.notify_all ();
   wait_suspended (lock);
}



/*
==============================================================================
Name : suspend
==============================================================================
*/

void  Coroutine::suspend ()
{
   std::unique_lock lock (_mutex);
   assert (_running);

   _running = false;
   _cv.notify_all ();
   _cv.wait (lock, [this] () { return _running; });

   if (_stop) throw Stop {};
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  Coroutine::run (std::function <void ()> func)
{
   try
   {
      func ();
   }
   catch (Stop &)
   {
   }
   catch (...)
   {
      _exception = std::current_exception ();
   }

   std::unique_lock lock (_mutex);
   _done = true;
   _running = false;
   _cv.notify_all ();
}



/*
==============================================================================
Name : wait_suspended
==============================================================================
*/

void  Coroutine::wait_suspended (std::unique_lock <std::mutex> & lock)
{
   _cv.wait (lock, [this] () { return !_running; });

   if (_exception)
   {
      auto exception = _exception;
      _exception = nullptr;
      std::rethrow_exception (exception);
   }
}



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
