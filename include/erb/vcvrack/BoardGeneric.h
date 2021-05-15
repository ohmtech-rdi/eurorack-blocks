/*****************************************************************************

      BoardGeneric.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

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
                  BoardGeneric () = default;
   virtual        ~BoardGeneric () = default;

   void           resize_params (size_t nbr_buttons, size_t nbr_pots);
   void           resize_inputs (size_t nbr_gate_ins, size_t nbr_cv_ins, size_t nbr_audio_ins);
   void           resize_outputs (size_t nbr_gate_outs, size_t nbr_cv_outs, size_t nbr_audio_outs);
   void           resize_lights (size_t nbr_leds);

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
   std::vector <uint8_t>
                  _digital_inputs;
   std::vector <float>
                  _analog_inputs;
   std::vector <DoubleBuffer>
                  _audio_inputs;

   std::vector <uint8_t>
                  _digital_outputs;
   std::vector <float>
                  _analog_outputs;
   std::vector <DoubleBuffer>
                  _audio_outputs;



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   enum
   {
                  ROW_BUTTON = 0,
                  ROW_POT,
   };

   enum
   {
                  ROW_GATE_IN = 0,
                  ROW_CV_IN,
                  ROW_AUDIO_IN,
   };

   enum
   {
                  ROW_GATE_OUT = 0,
                  ROW_CV_OUT,
                  ROW_AUDIO_OUT,
   };

   enum
   {
                  ROW_LED = 0,
   };

   void           init ();

   template <typename T>
   void           setup_hw_representation (T & arr, size_t size);

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
