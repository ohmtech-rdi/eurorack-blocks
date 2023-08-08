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

   void  rotate (float /* angle_rad */) { /* degenerated */ }
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
} __attribute__((packed));

template <std::size_t Width, std::size_t Height>
using Pixels = std::array <PixelRgba, Width * Height>;


struct Panel_ER_OLEDM066_1W_I2C
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
   };
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

      auto paint = nvgImagePattern (
         vg,
         0, 0, Panel::width, Panel::height,
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

      float margin_x = rack::mm2px ((Panel::visual_width - Panel::active_width) * 0.5f);
      float margin_y = rack::mm2px ((Panel::visual_height - Panel::active_height) * 0.5f);

      nvgBeginPath (vg);
      nvgRect (vg, margin_x, margin_y, box.size.x - 2 * margin_x, box.size.y - 2 * margin_y);
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
