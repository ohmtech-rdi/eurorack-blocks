/*****************************************************************************

      VcvWidgets.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/def.h"

erb_DISABLE_WARNINGS_VCVRACK
#include <rack.hpp>
erb_RESTORE_WARNINGS



extern rack::Plugin * plugin_instance;



namespace erb
{



template <typename KnobTrait>
struct AlphaPot: rack::app::SvgKnob {
   AlphaPot() {
      minAngle = -0.83f * float (M_PI);
      maxAngle = 0.83f * float (M_PI);
      shadow->blurRadius = 5;
      setSvg (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, KnobTrait::resource_0)
      ));
   }

   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan6Ps {
   static constexpr const char * resource_0 = "res/rogan.6ps.svg";
};

struct Rogan5Ps {
   static constexpr const char * resource_0 = "res/rogan.5ps.svg";
};

struct Rogan3Ps {
   static constexpr const char * resource_0 = "res/rogan.3ps.svg";
};

struct Rogan2Ps {
   static constexpr const char * resource_0 = "res/rogan.2ps.svg";
};

struct Rogan2SBlack {
   static constexpr const char * resource_0 = "res/rogan.2s.black.svg";
};

struct Rogan1Ps {
   static constexpr const char * resource_0 = "res/rogan.1ps.svg";
};

struct Rogan1S {
   static constexpr const char * resource_0 = "res/rogan.1s.svg";
};

struct Rogan1SBlack {
   static constexpr const char * resource_0 = "res/rogan.1s.black.svg";
};

struct SifamDbn151 {
   static constexpr const char * resource_0 = "res/sifam.dbn151.white.svg";
};

struct SifamDrn111 {
   static constexpr const char * resource_0 = "res/sifam.drn111.white.svg";
};



struct SongHuei9 : rack::app::SvgKnob
{
   SongHuei9 () {
      minAngle = float (-0.78 * M_PI);
      maxAngle = float (0.78 * M_PI);
      shadow->blurRadius = 5;
      setSvg (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/songhuei.9mm.svg")
      ));
   }

   void  rotate (float /* angle_rad */) { /* degenerated */ }
};



struct ThonkPj398Sm : rack::app::PortWidget
{
   rack::widget::FramebufferWidget * fb;
   rack::widget::TransformWidget * tw;
   rack::widget::SvgWidget * sw;

   ThonkPj398Sm () {
      fb = new rack::widget::FramebufferWidget;
      addChild (fb);

      tw = new rack::widget::TransformWidget;
      fb->addChild (tw);

      sw = new rack::widget::SvgWidget;
      tw->addChild (sw);

   }

   void setSvg (std::shared_ptr <rack::Svg> svg) {
      sw->setSvg (svg);
      tw->box.size = sw->box.size;
      fb->box.size = sw->box.size;
      box.size = sw->box.size;

      float angle = static_cast <float> (rand ()) / static_cast <float> (RAND_MAX) * 100.f;
      angle = float (std::fmod (angle, 2 * M_PI));

      tw->identity ();
      // Rotate SVG
      rack::math::Vec center = sw->box.getCenter ();
      tw->translate (center);
      tw->rotate (angle);
      tw->translate (center.neg ());
      fb->dirty = true;
   }

   void  rotate (float /* angle_rad */) {}
};



struct ThonkPj398SmKnurled : ThonkPj398Sm
{
   ThonkPj398SmKnurled () {
      setSvg (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/thonk.pj398sm.knurled.svg")
      ));
   }
};



struct ThonkPj398SmHex : ThonkPj398Sm
{
   ThonkPj398SmHex () {
      setSvg (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/thonk.pj398sm.hex.svg")
      ));
   }
};



struct Dailywell2Ms : rack::app::Switch
{
   rack::widget::FramebufferWidget * fb;
   rack::widget::TransformWidget * tw;
   rack::widget::SvgWidget * sw;
   std::vector <std::shared_ptr <rack::Svg>> frames;
   float angle = 0.f;

   Dailywell2Ms () {
      fb = new rack::widget::FramebufferWidget;
      addChild (fb);

      tw = new rack::widget::TransformWidget;
      fb->addChild (tw);

      sw = new rack::widget::SvgWidget;
      tw->addChild (sw);
   }

   void  rotate (float angle_rad_) {
      angle = angle_rad_;

      tw->identity ();
      // Rotate SVG
      rack::math::Vec center = sw->box.getCenter ();
      tw->translate (center);
      tw->rotate (angle);
      tw->translate (center.neg ());
}

   void addFrame (std::shared_ptr <rack::Svg> svg) {
      if (frames.empty ())
      {
         sw->setSvg (svg);
         tw->box.size = sw->box.size;
         fb->box.size = sw->box.size;
         box.size = sw->box.size;

         fb->dirty = true;
      }

      frames.push_back (svg);
   }

   void onChange (const rack::event::Change & e) override {
      rack::ParamQuantity* paramQuantity = getParamQuantity();

      if (!frames.empty() && paramQuantity) {
         int index = int (std::round (paramQuantity->getValue () - paramQuantity->getMinValue ()));
         index = rack::math::clamp (index, 0, int (frames.size ()) - 1);
         sw->setSvg(frames [size_t (index)]);
         fb->dirty = true;
      }
      ParamWidget::onChange(e);
   }
};



struct Dailywell2Ms1 : Dailywell2Ms
{
   Dailywell2Ms1 () {
      Dailywell2Ms::addFrame (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/dailywell.2ms.1.svg")
      ));

      Dailywell2Ms::addFrame (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/dailywell.2ms.3.svg")
      ));
   }
};



struct Dailywell2Ms3 : Dailywell2Ms
{
   Dailywell2Ms3 () {
      Dailywell2Ms::addFrame (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/dailywell.2ms.1.svg")
      ));

      Dailywell2Ms::addFrame (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/dailywell.2ms.2.svg")
      ));

      Dailywell2Ms::addFrame (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, "res/dailywell.2ms.3.svg")
      ));
   }
};



struct Tl1105 : rack::TL1105
{
   void  rotate (float /* angle_rad */) {}
};



struct Ckd6r : rack::CKD6
{
   void  rotate (float /* angle_rad */) {}
};



template <typename Base>
struct Led3mm : rack::MediumLight <Base>
{
   void  rotate (float /* angle_rad */) {}
};



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
