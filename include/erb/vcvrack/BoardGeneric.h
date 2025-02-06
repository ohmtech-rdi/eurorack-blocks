/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Clock.h"
#include "erb/detail/DoubleBuffer.h"

#include <functional>
#include <map>
#include <variant>
#include <vector>

#include <cstddef>



namespace rack
{
namespace engine
{
struct Param;
struct Input;
struct Output;
struct Light;
struct Module;
}
}

namespace erb
{



class BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   using PersistentMap = std::map <std::size_t, std::vector <uint8_t>>;

                  BoardGeneric (std::size_t nbr_digital_inputs, std::size_t nbr_analog_inputs, std::size_t nbr_audio_inputs, std::size_t nbr_digital_outputs, std::size_t nbr_analog_outputs, std::size_t nbr_audio_outputs);
   virtual        ~BoardGeneric () = default;

   void           impl_bind (rack::engine::Module & module) { _vcv_module_ptr = &module; }

   template <class Control, class VcvModel>
   void           impl_bind (Control & control, VcvModel & model);

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

   PersistentMap &
                  use_persistent_map ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   bool           impl_need_process ();
   void           impl_pull_audio_inputs ();
   void           impl_push_audio_outputs ();

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

   rack::engine::Module *
                  _vcv_module_ptr = nullptr;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   Clock          _clock;

   struct BindingAudioIn
   {
      void        process ();
      Buffer *    data_ptr;
      const DoubleBuffer *
                  db_ptr;
   };

   struct BindingAudioInJackDetection
   {
      void        process ();
      BoardGeneric *
                  board_ptr;
      Buffer *    data_ptr;
      uint8_t *   npr_ptr;
      const DoubleBuffer *
                  db_ptr;
      rack::engine::Input *
                  input_ptr;
   };

   struct BindingAudioOut
   {
      void        process ();
      const Buffer *
                  data_ptr;
      DoubleBuffer *
                  db_ptr;
   };

   struct BindingButton
   {
      void        process ();
      uint8_t *   data_ptr;
      rack::engine::Param *
                  param_ptr;
   };

   struct BindingCvIn
   {
      void        process ();
      float *     data_ptr;
      rack::engine::Input *
                  input_ptr;
      bool        bipolar;
   };

   struct BindingCvInJackDetection
   {
      void        process ();
      BoardGeneric *
                  board_ptr;
      float *     data_ptr;
      uint8_t *   npr_ptr;
      rack::engine::Input *
                  input_ptr;
      bool        bipolar;
   };

   struct BindingCvOut
   {
      void        process ();
      const float *
                  data_ptr;
      rack::engine::Output *
                  output_ptr;
      bool        bipolar;
   };

   struct BindingEncoderLeadingA
   {
      void        process ();
      uint8_t *   data_a_ptr;
      uint8_t *   data_b_ptr;
      rack::engine::Param *
                  param_ptr;
   };

   struct BindingEncoderLeadingB
   {
      void        process ();
      uint8_t *   data_a_ptr;
      uint8_t *   data_b_ptr;
      rack::engine::Param *
                  param_ptr;
   };

   struct BindingEncoderButtonLeadingA
   {
      void        process ();
      uint8_t *   data_a_ptr;
      uint8_t *   data_b_ptr;
      uint8_t *   data_sw_ptr;
      rack::engine::Param *
                  param_ab_ptr;
      rack::engine::Param *
                  param_sw_ptr;
   };

   struct BindingEncoderButtonLeadingB
   {
      void        process ();
      uint8_t *   data_a_ptr;
      uint8_t *   data_b_ptr;
      uint8_t *   data_sw_ptr;
      rack::engine::Param *
                  param_ab_ptr;
      rack::engine::Param *
                  param_sw_ptr;
   };

   struct BindingGateIn
   {
      void        process ();
      uint8_t *   data_ptr;
      rack::engine::Input *
                  input_ptr;
   };

   struct BindingGateInJackDetection
   {
      void        process ();
      BoardGeneric *
                  board_ptr;
      uint8_t *   data_ptr;
      uint8_t *   npr_ptr;
      rack::engine::Input *
                  input_ptr;
   };

   struct BindingGateOut
   {
      void        process ();
      const uint8_t *
                  data_ptr;
      rack::engine::Output *
                  output_ptr;
   };

   struct BindingLedFloat
   {
      void        process ();
      const float *
                  data_ptr;
      rack::engine::Light *
                  light_ptr;
   };

   struct BindingLedBiFloat
   {
      void        process ();
      const float *
                  data_r_ptr;
      const float *
                  data_g_ptr;
      rack::engine::Light *
                  light_r_ptr;
      rack::engine::Light *
                  light_g_ptr;
   };

   struct BindingLedRgbFloat
   {
      void        process ();
      const float *
                  data_r_ptr;
      const float *
                  data_g_ptr;
      const float *
                  data_b_ptr;
      rack::engine::Light *
                  light_r_ptr;
      rack::engine::Light *
                  light_g_ptr;
      rack::engine::Light *
                  light_b_ptr;
   };

   struct BindingLedBool
   {
      void        process ();
      const uint8_t *
                  data_ptr;
      rack::engine::Light *
                  light_ptr;
   };

   struct BindingLedBiBool
   {
      void        process ();
      const uint8_t *
                  data_r_ptr;
      const uint8_t *
                  data_g_ptr;
      rack::engine::Light *
                  light_r_ptr;
      rack::engine::Light *
                  light_g_ptr;
   };

   struct BindingLedRgbBool
   {
      void        process ();
      const uint8_t *
                  data_r_ptr;
      const uint8_t *
                  data_g_ptr;
      const uint8_t *
                  data_b_ptr;
      rack::engine::Light *
                  light_r_ptr;
      rack::engine::Light *
                  light_g_ptr;
      rack::engine::Light *
                  light_b_ptr;
   };

   struct BindingPot
   {
      void        process ();
      float *     data_ptr;
      rack::engine::Param *
                  param_ptr;
      bool        bipolar;
   };

   struct BindingSwitch
   {
      void        process ();
      uint8_t *   data_0_ptr;
      uint8_t *   data_1_ptr;
      float       scale;
      rack::engine::Param *
                  param_ptr;
   };

   using BindingInputs = std::vector <std::variant <
      BindingAudioIn,
      BindingAudioInJackDetection,
      BindingButton,
      BindingCvIn,
      BindingCvInJackDetection,
      BindingEncoderLeadingA,
      BindingEncoderLeadingB,
      BindingEncoderButtonLeadingA,
      BindingEncoderButtonLeadingB,
      BindingGateIn,
      BindingGateInJackDetection,
      BindingPot,
      BindingSwitch
   >>;

   using BindingOutputs = std::vector <std::variant <
      BindingAudioOut,
      BindingCvOut,
      BindingGateOut,
      BindingLedFloat,
      BindingLedBiFloat,
      BindingLedRgbFloat,
      BindingLedBool,
      BindingLedBiBool,
      BindingLedRgbBool
   >>;

   BindingInputs  _binding_inputs;
   BindingOutputs _binding_outputs;

   std::vector <DoubleBuffer>
                  _double_buffer_inputs;
   std::vector <rack::engine::Input *>
                  _rack_audio_inputs;

   std::vector <DoubleBuffer>
                  _double_buffer_outputs;
   std::vector <rack::engine::Output *>
                  _rack_audio_outputs;

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



}  // namespace erb



#include "erb/vcvrack/BoardGeneric.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
