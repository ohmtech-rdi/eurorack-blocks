/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Buffer.h"
#include "erb/detail/Clock.h"
#include "erb/rig/Context.h"
#include "erb/rig/Bench.h"
#include "erb/rig/Probe.h"
#include "erb/rig/Screen.h"
#include "erb/rig/SystemClockVirtual.h"

#include "erb/Button.h"
#include "erb/CvIn.h"
#include "erb/Encoder.h"
#include "erb/EncoderButton.h"
#include "erb/GateIn.h"
#include "erb/Pot.h"

#include <array>
#include <chrono>
#include <functional>
#include <map>
#include <source_location>
#include <span>
#include <string>
#include <vector>

#include <cstddef>
#include <cstdint>



namespace erb
{
namespace rig
{



class BoardGeneric
:  public Bench
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

   struct Stats
   {
      std::map <std::size_t, std::size_t>
                  qspi_erases;   // per page
      std::map <std::size_t, std::size_t>
                  qspi_saves;    // per page
      std::size_t sram_pool_position = 0;
      std::size_t sdram_pool_position = 0;
      std::size_t sd_bytes_read = 0;
      std::size_t sd_bytes_written = 0;
      uint64_t    block_count = 0;
      uint64_t    idle_count = 0;
      double      wall_seconds = 0.0;
      float       output_max_abs = 0.f;     // audio outputs
      std::size_t output_nbr_non_finite = 0;
   };

                  BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs);
   virtual        ~BoardGeneric ();

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

   const char *   control_name (const void * control_ptr) const override;

   template <typename T>
   T              probe (const std::string & key) const;

   template <typename Predicate>
   void           wait_until (Predicate predicate, SystemClockVirtual::duration timeout, std::source_location sloc = std::source_location::current ());
   template <typename T>
   void           wait_until_equal (const Probe & probe, const T & expected, SystemClockVirtual::duration timeout, std::source_location sloc = std::source_location::current ());

   inline uint64_t
                  block_count () const { return _block_count; }
   inline uint64_t
                  idle_count () const { return _idle_count; }

   Stats          stats () const;

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

   void           impl_setup (const ContextMap & context);
   void           impl_boot (Glue glue);

   // Bench
   std::size_t    impl_bind (SlotKind kind, const void * slot_data) override;
   void           impl_unbind (SlotKind kind, std::size_t index) override;
   std::span <const std::uint8_t>
                  impl_recording_digital (std::size_t index) const override;
   std::span <const float>
                  impl_recording_analog (std::size_t index) const override;
   std::span <const float>
                  impl_recording_audio (std::size_t index) const override;
   std::uint64_t  impl_recorded_blocks () const override;
   bool           impl_pump_until (const std::function <bool ()> & predicate, SystemClockVirtual::duration timeout) override;

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
                  BlocksPerIdle = (IdlePeriodSamples + erb_BUFFER_SIZE / 2) / erb_BUFFER_SIZE;

   void           impl_reset_stats ();
   void           impl_print_stats () const;
   void           impl_step ();
   void           impl_step_pair ();
   void           impl_step_block ();
   void           impl_block ();
   void           impl_idle ();
   void           impl_steps (std::size_t nbr_steps);
   template <typename Predicate>
   bool           impl_wait_until (Predicate predicate, SystemClockVirtual::duration timeout);
   template <typename T>
   static std::string
                  impl_to_string (const T & value);
   template <typename T>
   static std::size_t
                  impl_slot_index (const std::vector <T> & slots, const T & data);
   uint8_t &      impl_digital_slot (const uint8_t & data);
   float &        impl_analog_slot (const float & data);

   static constexpr std::size_t
                  DebounceBlocks = 8; // debounce win 7hi=pressed 8hi=held
   static constexpr std::size_t
                  TriggerBlocks = 3; // 1ms at 16 samples 48kHz

   bool           _setup_flag = false;
   bool           _boot_flag = false;
   bool           _start_flag = false;
   Glue           _glue;

   struct Recorded
   {
      std::size_t bindings = 0;
      std::vector <uint8_t>
                  digital;
      std::vector <float>
                  samples;    // analog and audio
   };

   std::map <std::size_t, Recorded>
                  _digital_recordings;
   std::map <std::size_t, Recorded>
                  _analog_recordings;
   std::map <std::size_t, Recorded>
                  _audio_recordings;
   std::size_t    _nbr_bindings = 0;
   uint64_t       _recorded_blocks = 0;   // since 'start'

   std::map <std::size_t, Recorded> &
                  impl_recordings (SlotKind kind);

   Mode           _mode = Mode::UiFast;
   uint64_t       _block_count = 0;
   uint64_t       _idle_count = 0;

   std::map <std::size_t, std::size_t>
                  _qspi_erases;
   std::map <std::size_t, std::size_t>
                  _qspi_saves;
   std::chrono::steady_clock::time_point
                  _wall_start;
   float          _output_max_abs = 0.f;
   std::size_t    _output_nbr_non_finite = 0;



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
