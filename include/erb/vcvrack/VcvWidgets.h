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

#include <cstddef>



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
};

struct Rogan6Ps {};

template <>
struct AlphaPot <Rogan6Ps>: rack::Rogan6PSWhite {
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan5Ps {};

template <>
struct AlphaPot <Rogan5Ps>: rack::Rogan {
   AlphaPot() {
      setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan5PSWhite.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan5PS_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan5PSWhite_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};


struct Rogan3Ps {};

template <>
struct AlphaPot <Rogan3Ps>: rack::Rogan3PSWhite {
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan3S {};

template <>
struct AlphaPot <Rogan3S>: rack::Rogan {
   AlphaPot() {
      setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan3SWhite.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan3PS_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan3SWhite_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};


struct Rogan2Ps {};

template <>
struct AlphaPot <Rogan2Ps>: rack::Rogan2PSWhite {
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan2SBlack {};

template <>
struct AlphaPot <Rogan2SBlack>: rack::Rogan {
   AlphaPot() {
      setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan2SGray.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan2PS_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan2SBlack_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan1Ps {};

template <>
struct AlphaPot <Rogan1Ps>: rack::Rogan1PSWhite {
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan1P {};

template <>
struct AlphaPot <Rogan1P>: rack::Rogan1PWhite {
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan1S {};

template <>
struct AlphaPot <Rogan1S>: rack::Rogan {
   AlphaPot() {
      setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1S.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan1PS_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1SWhite_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct Rogan1SBlack {};

template <>
struct AlphaPot <Rogan1SBlack>: rack::Rogan {
   AlphaPot() {
      setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1S.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan1PS_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1SBlack_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

struct SifamDbn151 {
   static constexpr const char * resource_0 = "res/sifam.dbn151.white.svg";
};

struct SifamDrn111 {
   static constexpr const char * resource_0 = "res/sifam.drn111.white.svg";
};


template <typename KnobTrait>
struct BournsPec11R: rack::app::SvgKnob {
   BournsPec11R() {
      minAngle = 0;
      maxAngle = 1000 * 2 * float (M_PI);
      shadow->blurRadius = 5;
      setSvg (APP->window->loadSvg (
         rack::asset::plugin (plugin_instance, KnobTrait::resource_0)
      ));
   }
};

template <>
struct BournsPec11R <Rogan2SBlack>: rack::Rogan {
   BournsPec11R() {
      minAngle = 0;
      maxAngle = 1000 * 2 * float (M_PI);
      setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan2SGray.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan2S_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan2SBlack_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

template <>
struct BournsPec11R <Rogan1S>: rack::Rogan {
   BournsPec11R() {
      minAngle = 0;
      maxAngle = 1000 * 2 * float (M_PI);
      setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1S.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1S_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1SWhite_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

template <>
struct BournsPec11R <Rogan1SBlack>: rack::Rogan {
   BournsPec11R() {
      minAngle = 0;
      maxAngle = 1000 * 2 * float (M_PI);
      setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1S.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1S_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan1SBlack_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};

template <>
struct BournsPec11R <Rogan3S>: rack::Rogan {
   BournsPec11R() {
      minAngle = 0;
      maxAngle = 1000 * 2 * float (M_PI);
      setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan3SWhite.svg")));
      bg->setSvg (rack::Svg::load (rack::asset::system ("res/ComponentLibrary/Rogan3PS_bg.svg")));
      fg->setSvg (rack::Svg::load (rack::asset::plugin (plugin_instance, "res/Rogan3SWhite_fg.svg")));
   }
   void  rotate (float /* angle_rad */) { /* degenerated */ }
};




struct SongHuei9 : rack::Trimpot
{
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
         sw->setSvg(frames [std::size_t (index)]);
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



struct Davies1900hBlack : rack::Davies1900hBlackKnob
{
   void  rotate (float /* angle_rad */) {}
};



template <typename Base>
struct Led3mm : rack::MediumLight <Base>
{
   void  rotate (float /* angle_rad */) {}
};



struct PixelRgba
{
   std::uint8_t r;
   std::uint8_t g;
   std::uint8_t b;
   std::uint8_t a;
};

template <std::size_t Width, std::size_t Height>
using Pixels = std::array <PixelRgba, Width * Height>;


struct Panel_ER_OLEDM066_1
{
   // https://www.buydisplay.com/download/manual/ER-OLEDM0.66-1_Datasheet.pdf

   static constexpr std::size_t width = 64;
   static constexpr std::size_t height = 48;

   using Storage = std::array <std::uint8_t, width * height / 8>;

   // mm
   static constexpr float visual_width = 15.42f;
   static constexpr float visual_height = 12.06f;
   static constexpr float active_width = 13.42f;
   static constexpr float active_height = 10.06f;
   static constexpr float dot_size = 0.19f;

   static Pixels <width, height>  to_pixels (const Storage & data)
   {
      Pixels <width, height> ret;
      for (size_t x = 0 ; x < width ; ++x)
      {
         for (size_t y = 0 ; y < height ; ++y)
         {
            bool on = data [x + (y / 8) * width] & (1 << (y % 8));

            ret [y * width + x] = on ? PixelRgba {255, 255, 255, 255} : PixelRgba {0, 0, 0, 0};
         }
      }

      return ret;
   }
};


struct Panel_ER_OLEDM015_2
{
   // https://www.buydisplay.com/download/manual/ER-OLEDM015-2_Datasheet.pdf

   static constexpr std::size_t width = 128;
   static constexpr std::size_t height = 64;

   using Storage = std::array <std::uint8_t, width * height / 8>;

   // mm
   static constexpr float visual_width = 37.052f;
   static constexpr float visual_height = 19.516f;
   static constexpr float active_width = 35.052f;
   static constexpr float active_height = 17.516f;
   static constexpr float dot_size = 0.254f;

   static Pixels <width, height>  to_pixels (const Storage & data)
   {
      Pixels <width, height> ret;
      for (size_t x = 0 ; x < width ; ++x)
      {
         for (size_t y = 0 ; y < height ; ++y)
         {
            bool on = data [x + (y / 8) * width] & (1 << (y % 8));

            ret [y * width + x] = on ? PixelRgba {255, 255, 255, 255} : PixelRgba {0, 0, 0, 0};
         }
      }

      return ret;
   }
};



enum class OledModuleFilter
{
   White, Red
};

template <typename Panel, OledModuleFilter Filter = OledModuleFilter::White>
struct OledModule : rack::OpaqueWidget
{
   template <typename Control>
   OledModule (Control & control)
   :  _control_data (control.impl_data)
   {
      box.size = rack::mm2px (rack::Vec (Panel::visual_width, Panel::visual_height));
   }

   void  rotate (float /* angle_rad */) { /* not supported */ }

   void draw (const DrawArgs & args) override {
      NVGcontext * const vg = args.vg;

      auto pixels = Panel::to_pixels (_control_data);

      if (_image == -1)
      {
         _image = nvgCreateImageRGBA (
            vg, Panel::width, Panel::height,
            NVG_IMAGE_PREMULTIPLIED | NVG_IMAGE_NEAREST,
            reinterpret_cast <const unsigned char *> (&pixels [0])
         );
      }
      else
      {
         nvgUpdateImage (vg, _image, reinterpret_cast <const unsigned char *> (&pixels [0]));
      }

      nvgBeginPath (vg);
      nvgRoundedRect (vg, 0, 0, box.size.x, box.size.y, 1);
      nvgFillColor (vg, nvgRGB (0, 0, 0));
      nvgFill (vg);

      const float margin_x = rack::mm2px ((Panel::visual_width - Panel::active_width) * 0.5f);
      const float margin_y = rack::mm2px ((Panel::visual_height - Panel::active_height) * 0.5f);
      const float active_x = margin_x;
      const float active_width = box.size.x - 2 * margin_x;
      const float active_y = margin_y;
      const float active_height = box.size.y - 2 * margin_y;

      auto paint = nvgImagePattern (
         vg,
         active_x, active_y, active_width, active_height,
         0, _image, 1.f
      );

      switch (Filter)
      {
      case OledModuleFilter::White:
      default:
         // nothing
         break;

      case OledModuleFilter::Red:
         paint.innerColor = nvgRGB (255, 0, 0);
         break;
      }

      nvgBeginPath (vg);
      nvgRect (vg, active_x, active_y, active_width, active_height);
      nvgFillPaint (vg, paint);
      nvgFill (vg);

      auto paint2 = nvgLinearGradient (
         vg, 0, 0, 0, box.size.y * 0.5f,
         nvgRGBA (255, 255, 255, 96), nvgRGBA (0, 0, 0, 0)
      );

      nvgBeginPath (vg);
      nvgRoundedRect (
         vg, rack::mm2px (0.1f), rack::mm2px (0.2f),
         box.size.x - rack::mm2px (0.2f), box.size.y * 0.5f, 1
      );
      nvgFillPaint (vg, paint2);
      nvgFill (vg);
   }

private:
   const typename Panel::Storage & _control_data;
   int _image = -1;
};



template <typename Widget, typename T>
Widget * createWidgetCentered (rack::math::Vec pos, T & control)
{
   auto * w = new Widget {control};  // ahlala
   w->box.pos = pos.minus (w->box.size.div (2));
   return w;
}



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
