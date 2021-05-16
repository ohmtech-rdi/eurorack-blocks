/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/detail/Clock.h"
#include "erb/detail/DoubleBuffer.h"

#include <array>
#include <functional>
#include <map>
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

   template <typename F>
   void           bind_process (F && f);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   bool           impl_need_process ();
   void           impl_pull_audio_inputs ();
   void           impl_push_audio_outputs ();

   void           impl_preprocess ();
   void           impl_process ();
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

   struct BindingAudioIn
   {
      void        process ();
      Buffer *    data_ptr;
      DoubleBuffer *
                  db_ptr;
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
   };

   using BindingInputs = std::vector <std::variant <
      BindingAudioIn,
      BindingCvIn
   >>;

   using BindingOutputs = std::vector <std::variant <
      BindingCvOut
   >>;

   BindingInputs  _binding_inputs;
   BindingOutputs _binding_outputs;

   std::vector <DoubleBuffer>
                  _audio_double_buffer_inputs;
   std::vector <DoubleBuffer>
                  _audio_double_buffer_outputs;

   std::function <void ()>
                  _buffer_callback;



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
