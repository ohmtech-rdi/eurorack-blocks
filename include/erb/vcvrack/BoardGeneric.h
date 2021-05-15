/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/Configuration.h"
#include "erb/detail/Clock.h"
#include "erb/detail/DoubleBuffer.h"
#include "erb/detail/JaggedArray.h"

#include <array>
#include <functional>
#include <map>
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
                  BoardGeneric (const Configuration & configuration);
   virtual        ~BoardGeneric () = default;

   size_t         nbr_params () const;
   size_t         nbr_inputs () const;
   size_t         nbr_outputs () const;
   size_t         nbr_lights () const;

   void           impl_bind (size_t idx, rack::engine::Param & param);
   void           impl_bind (size_t idx, rack::engine::Input & input);
   void           impl_bind (size_t idx, rack::engine::Output & output);
   void           impl_bind (size_t idx, rack::engine::Light & light);

   template <typename F>
   void           bind_process (F && f);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   size_t         impl_to_vcv_index (const void * data) const;

   bool           impl_need_process ();
   void           impl_pull_audio_inputs ();
   void           impl_push_audio_outputs ();

   void           impl_preprocess ();
   void           impl_process ();
   void           impl_postprocess ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:
   enum : size_t
   {
                  // Digital Inputs
                  HW_ROW_BUTTON = 0,
                  HW_ROW_GATE_IN,

                  // Analog Inputs
                  HW_ROW_POTS = 0,
                  HW_ROW_CV_IN,

                  // Audio Inputs
                  HW_ROW_AUDIO_IN = 0,

                  // Digital Outputs
                  HW_ROW_GATE_OUT = 0,

                  // Analog Outputs
                  HW_ROW_CV_OUT = 0,
                  HW_ROW_LED,

                  // Audio Outputs
                  HW_ROW_AUDIO_OUT = 0,
   };

   JaggedArray <uint8_t>
                  _digital_inputs;
   JaggedArray <float>
                  _analog_inputs;
   JaggedArray <Buffer>
                  _audio_inputs;

   JaggedArray <uint8_t>
                  _digital_outputs;
   JaggedArray <float>
                  _analog_outputs;
   JaggedArray <Buffer>
                  _audio_outputs;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum : size_t
   {
                  // Params
                  VCV_ROW_BUTTON = 0,
                  VCV_ROW_POT,

                  // Inputs
                  VCV_ROW_GATE_IN = 0,
                  VCV_ROW_CV_IN,
                  VCV_ROW_AUDIO_IN,

                  // Outputs
                  VCV_ROW_GATE_OUT = 0,
                  VCV_ROW_CV_OUT,
                  VCV_ROW_AUDIO_OUT,

                  // Lights
                  VCV_ROW_LED = 0,
   };

   void           resize_params (size_t nbr_buttons, size_t nbr_pots);
   void           resize_inputs (size_t nbr_gate_ins, size_t nbr_cv_ins, size_t nbr_audio_ins);
   void           resize_outputs (size_t nbr_gate_outs, size_t nbr_cv_outs, size_t nbr_audio_outs);
   void           resize_lights (size_t nbr_leds);

   void           init ();

   void           init_digital_inputs ();
   void           init_analog_inputs ();
   void           init_audio_inputs ();

   void           init_digital_outputs ();
   void           init_analog_outputs ();
   void           init_audio_outputs ();

   template <typename T, typename U>
   void           setup_hw_representation (T & hw, size_t hw_row, U & vcv, size_t vcv_row);

   const Configuration
                  _configuration;

   Clock          _clock;

   JaggedArray <rack::engine::Param *>
                  _params;
   JaggedArray <rack::engine::Input *>
                  _inputs;
   JaggedArray <rack::engine::Output *>
                  _outputs;
   JaggedArray <rack::engine::Light *>
                  _lights;

   std::map <const void * /* data */, size_t /* vcv index relative to type */>
                  _to_vcv_index;

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
