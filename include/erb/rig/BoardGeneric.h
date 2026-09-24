/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/detail/Clock.h"
#include "erb/rig/SystemClockVirtual.h"

#include <array>
#include <functional>
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

   struct Glue
   {
      std::function <void ()>
                  preprocess;
      std::function <void ()>
                  process;
      std::function <void ()>
                  postprocess;
      std::function <void ()>
                  idle;
   };

                  BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs);
   virtual        ~BoardGeneric () = default;

   void           start ();
   void           run (SystemClockVirtual::duration duration);

   inline uint64_t
                  frame_count () const { return _frame_count; }
   inline uint64_t
                  idle_count () const { return _idle_count; }

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

   void           impl_setup ();
   void           impl_boot (Glue glue);

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

   enum class Mode
   {
      UiFast,
      Lockstep,
   };

   static constexpr uint64_t
                  IdlePeriodMs = 6; // min period for firmware
   static constexpr uint64_t
                  IdlePeriodSamples = (uint64_t (erb_SAMPLE_RATE) * IdlePeriodMs) / 1000;
   static constexpr uint64_t
                  FramesPerIdle = (IdlePeriodSamples + erb_BUFFER_SIZE / 2) / erb_BUFFER_SIZE;

   void           impl_step ();
   void           impl_step_pair ();
   void           impl_step_frame ();
   void           impl_frame ();
   void           impl_idle ();

   bool           _setup_flag = false;
   bool           _boot_flag = false;
   bool           _start_flag = false;
   Glue           _glue;

   std::size_t    _nbr_measurements = 0;

   Mode           _mode = Mode::UiFast;
   uint64_t       _frame_count = 0;
   uint64_t       _idle_count = 0;



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
