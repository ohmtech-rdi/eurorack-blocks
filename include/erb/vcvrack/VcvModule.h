/*****************************************************************************

      VcvModule.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/vcvrack/VcvConstants.h"
#include "erb/vcvrack/VcvModuleListeners.h"

#include <array>
#include <functional>
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



class VcvParamBase;
class VcvInputBase;
class VcvOutputBase;
class VcvLightBase;

class VcvAudioIn;
class VcvAudioOut;

struct VcvPin;

class VcvModule
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  VcvModule () = default;
   virtual        ~VcvModule () = default;

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

   uint64_t       now_ms ();

   void           add (VcvParamBase & param);
   void           add (VcvInputBase & input);
   void           add (VcvOutputBase & output);
   void           add (VcvLightBase & light);

   void           add (VcvAudioIn & input);
   void           add (VcvAudioOut & output);

   void           impl_process ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   using VcvParams = std::vector <VcvParamBase *>;
   using VcvInputs = std::vector <VcvInputBase *>;
   using VcvOutputs = std::vector <VcvOutputBase *>;
   using VcvLights = std::vector <VcvLightBase *>;

   using VcvAudioInputs = std::vector <VcvAudioIn *>;
   using VcvAudioOutputs = std::vector <VcvAudioOut *>;

   std::function <void ()>
                  _buffer_callback;

   uint64_t       _now_spl = 0ull;
   uint64_t       _now_ms = 0ull;

   VcvParams      _params;
   VcvInputs      _inputs;
   VcvOutputs     _outputs;
   VcvLights      _lights;

   VcvAudioInputs _audio_inputs;
   VcvAudioOutputs
                  _audio_outputs;

   VcvModuleListeners
                  _listeners;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvModule (const VcvModule & rhs) = delete;
                  VcvModule (VcvModule && rhs) = delete;
   VcvModule &    operator = (const VcvModule & rhs) = delete;
   VcvModule &    operator = (VcvModule && rhs) = delete;
   bool           operator == (const VcvModule & rhs) const = delete;
   bool           operator != (const VcvModule & rhs) const = delete;



}; // class VcvModule



}  // namespace erb



#include "erb/vcvrack/VcvModule.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
