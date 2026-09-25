/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/detail/Clock.h"
#include "erb/rig/Screen.h"
#include "erb/rig/SystemClockVirtual.h"

#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/Encoder.h"
#include "erb/EncoderButton.h"
#include "erb/GateIn.h"
#include "erb/Pot.h"

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
      std::function <const char * (const void * control_ptr)>
                  control_name;
   };

                  BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs);
   virtual        ~BoardGeneric () = default;

   void           start ();
   void           run (SystemClockVirtual::duration duration);

   // ui
   void           press (Button & button);
   void           release (Button & button);
   void           click (Button & button);
   void           long_press (Button & button, SystemClockVirtual::duration duration);
   template <EncoderLeadingType LeadingType>
   void           scroll (Encoder <LeadingType> & encoder, int nbr_detents);
   template <EncoderLeadingType LeadingType>
   void           scroll (EncoderButton <LeadingType> & encoder, int nbr_detents);
   void           trigger (GateIn & gate);
   void           set (GateIn & gate, bool state);
   template <FloatRange Range>
   void           set (Pot <Range> & pot, float value);
   template <FloatRange Range>
   void           set (CvIn <Range> & cv, float value);

   const char *   control_name (const void * control_ptr) const;

   template <typename Predicate>
   void           wait_until (Predicate predicate, SystemClockVirtual::duration timeout);
   template <typename Format>
   void           wait_until_equal (Display <Format> & display, const Screen <Format> & screen, SystemClockVirtual::duration timeout);

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
   void           impl_steps (std::size_t nbr_steps);
   template <typename Predicate>
   bool           impl_wait_until (Predicate predicate, SystemClockVirtual::duration timeout);
   uint8_t &      impl_digital_slot (const uint8_t & data);
   float &        impl_analog_slot (const float & data);

   static constexpr std::size_t
                  DebounceFrames = 8; // debounce win 7hi=pressed 8hi=held
   static constexpr std::size_t
                  TriggerFrames = 3; // 1ms at 16 samples 48kHz

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
