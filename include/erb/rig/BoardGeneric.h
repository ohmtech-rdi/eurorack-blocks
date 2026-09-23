/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/detail/Clock.h"

#include <array>
#include <map>
#include <vector>

#include <cstddef>
#include <cstdint>



namespace erb
{
namespace rig
{



class BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using PersistentMap = std::map <std::size_t, std::vector <uint8_t>>;

                  BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs);
   virtual        ~BoardGeneric () = default;

   // Clock
   inline const uint64_t &
                  clock () { return _clock.ms (); }

   inline const uint8_t &
                  npr () { return _npr; }

   template <std::size_t N>
   inline std::array <uint8_t, N>
                  load (size_t page);

   template <typename Data>
   inline void    save (size_t page, const Data & data);

   inline void    erase (size_t page);

   PersistentMap &
                  use_persistent_map ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   virtual void   impl_preprocess ();
   void           impl_postprocess ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
   std::vector <uint8_t>
                  _digital_inputs;
   std::vector <float>
                  _analog_inputs;
   std::vector <Buffer>
                  _audio_inputs;

   std::vector <uint8_t>
                  _digital_outputs;
   std::vector <float>
                  _analog_outputs;
   std::vector <Buffer>
                  _audio_outputs;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   Clock          _clock;

   uint8_t        _npr = 0;
   uint32_t       _npr_rand_state = 0;

   PersistentMap  _persistent_map;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  BoardGeneric (const BoardGeneric & rhs) = delete;
                  BoardGeneric (BoardGeneric && rhs) = delete;
   BoardGeneric & operator = (const BoardGeneric & rhs) = delete;
   BoardGeneric & operator = (BoardGeneric && rhs) = delete;
   bool           operator == (const BoardGeneric & rhs) const = delete;
   bool           operator != (const BoardGeneric & rhs) const = delete;



}; // class BoardGeneric



}  // namespace rig
}  // namespace erb



#include "erb/rig/BoardGeneric.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
