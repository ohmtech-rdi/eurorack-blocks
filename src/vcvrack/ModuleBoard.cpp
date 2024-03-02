/*****************************************************************************

      ModuleBoard.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/ModuleBoard.h"

#include <algorithm>

#include <cassert>



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

ModuleBoard::ModuleBoard ()
:  _sram_memory_pool_storage ()
#if (erb_SDRAM_USE_FLAG)
,  _sdram_memory_pool_storage ()
#endif
,  _sram (&_sram_memory_pool_storage [0])
#if (erb_SDRAM_USE_FLAG)
,  _sdram (&_sdram_memory_pool_storage [0])
#endif
{
}



/*
==============================================================================
Name : current
==============================================================================
*/

ModuleBoard &  ModuleBoard::current ()
{
   assert (_current_ptr != nullptr);

   return *_current_ptr;
}



/*
==============================================================================
Name : sram
==============================================================================
*/

Sram &   ModuleBoard::sram ()
{
   return _sram;
}



/*
==============================================================================
Name : sdram
==============================================================================
*/

#if (erb_SDRAM_USE_FLAG)
Sdram &  ModuleBoard::sdram ()
{
   return _sdram;
}
#endif



/*
==============================================================================
Name : Scoped::ctor
==============================================================================
*/

ModuleBoard::Scoped::Scoped (ModuleBoard & board)
:  _board_ptr (&board)
{
   ModuleBoard::impl_set_current (_board_ptr);
}



/*
==============================================================================
Name : Scoped::dtor
==============================================================================
*/

ModuleBoard::Scoped::~Scoped ()
{
   ModuleBoard::impl_unset_current (_board_ptr);
   _board_ptr = nullptr;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : impl_set_current
==============================================================================
*/

void  ModuleBoard::impl_set_current (ModuleBoard * board_ptr)
{
   assert (board_ptr != nullptr);
   assert (_current_ptr == nullptr);

   _current_ptr = board_ptr;
}



/*
==============================================================================
Name : impl_unset_current
==============================================================================
*/

void  ModuleBoard::impl_unset_current (ModuleBoard * board_ptr)
{
   ((void) (board_ptr));

   assert (board_ptr != nullptr);
   assert (_current_ptr == board_ptr);

   _current_ptr = nullptr;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

thread_local ModuleBoard * ModuleBoard::_current_ptr = nullptr;



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
