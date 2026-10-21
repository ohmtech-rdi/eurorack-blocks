/*****************************************************************************

      Coroutine.h
      Copyright (c) 2026 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <condition_variable>
#include <exception>
#include <functional>
#include <mutex>
#include <thread>



namespace erb
{
namespace rig
{



class Coroutine
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   struct Stop {};

                  Coroutine () = default;
                  ~Coroutine ();

   // caller
   void           start (std::function <void ()> func);
   void           stop ();
   void           resume ();

   // from function body
   void           suspend ();



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   void           run (std::function <void ()> func);
   void           wait_suspended (std::unique_lock <std::mutex> & lock);

   std::thread    _thread;
   std::mutex     _mutex;
   std::condition_variable
                  _cv;
   bool           _running = false; // function body
   bool           _stop = false;
   bool           _done = false;    // function body returned or threw
   std::exception_ptr
                  _exception;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Coroutine (const Coroutine & rhs) = delete;
                  Coroutine (Coroutine && rhs) = delete;
   Coroutine &    operator = (const Coroutine & rhs) = delete;
   Coroutine &    operator = (Coroutine && rhs) = delete;
   bool           operator == (const Coroutine & rhs) const = delete;
   bool           operator != (const Coroutine & rhs) const = delete;



}; // class Coroutine



}  // namespace rig
}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
