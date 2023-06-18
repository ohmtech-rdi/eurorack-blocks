/*****************************************************************************

      ModuleBoard.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/config.h"
#include "erb/detail/Sram.h"
#include "erb/detail/Sdram.h"

#include <array>



namespace erb
{



class ModuleBoard
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   class Scoped
   {
   public:
                  Scoped (ModuleBoard & board);
                  ~Scoped ();

                  Scoped () = delete;
   private:
      ModuleBoard *
                  _board_ptr;
   };

                  ModuleBoard ();
   virtual        ~ModuleBoard () = default;

   static ModuleBoard &
                  current ();

   Sram &         sram ();
   Sdram &        sdram ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   static void    impl_set_current (ModuleBoard * board_ptr);
   static void    impl_unset_current (ModuleBoard * board_ptr);




/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   std::array <uint8_t, erb_SRAM_MEM_POOL_SIZE>
                  _sram_memory_pool_storage;
   std::array <uint8_t, erb_SDRAM_MEM_POOL_SIZE>
                  _sdram_memory_pool_storage;

   Sram           _sram;
   Sdram          _sdram;

   static thread_local ModuleBoard *
                  _current_ptr;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  ModuleBoard (const ModuleBoard & rhs) = delete;
                  ModuleBoard (ModuleBoard && rhs) = delete;
   ModuleBoard &operator = (const ModuleBoard & rhs) = delete;
   ModuleBoard &operator = (ModuleBoard && rhs) = delete;
   bool           operator == (const ModuleBoard & rhs) const = delete;
   bool           operator != (const ModuleBoard & rhs) const = delete;



}; // class ModuleBoard



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
