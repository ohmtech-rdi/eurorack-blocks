/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Filesystem.h"
#include "erb/detail/Clock.h"
#include "erb/detail/DoubleBuffer.h"

#include <functional>
#include <variant>
#include <vector>



namespace rack
{
namespace engine
{
struct Param;
struct Input;
struct Output;
struct Light;
}
}

namespace erb
{



class BoardGeneric
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  BoardGeneric (size_t nbr_digital_inputs, size_t nbr_analog_inputs, size_t nbr_audio_inputs, size_t nbr_digital_outputs, size_t nbr_analog_outputs, size_t nbr_audio_outputs);
   virtual        ~BoardGeneric () = default;

   template <class Control, class VcvModel>
   void           impl_bind (Control & control, VcvModel & model);

   // Clock
   inline const uint64_t &
                  clock () { return _clock.ms (); }



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   bool           impl_need_process ();
   void           impl_pull_audio_inputs ();
   void           impl_push_audio_outputs ();

   void           impl_preprocess ();
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
   Filesystem     _sd;



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

   struct BindingGateIn
   {
      void        process ();
      uint8_t *   data_ptr;
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
      BindingButton,
      BindingCvIn,
      BindingGateIn,
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
