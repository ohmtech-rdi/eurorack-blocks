/*****************************************************************************

      DropDsp.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <cstddef>



class DropDsp
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Mode
   {
      HighPass, Mute
   };

   enum class State
   {
      None,
      Off, Armed, Active
   };

                  DropDsp (float sample_rate);
                  DropDsp (DropDsp && rhs) = default;
   /*virtual*/    ~DropDsp () = default;

   DropDsp &      operator = (DropDsp && rhs) = default;

   void           toggle_arm ();
   void           sync ();
   void           set_mode (Mode mode);
   void           set_highpass_freq (float freq);

   void           process (float * const out [], const float * const in [], size_t size);

   State          state ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum {         NBR_CHANNELS = 2 };

   class GainRamp
   {
   public:
      GainRamp &  operator = (float val);
                  operator float () const;

      void        process ();

      float       target = 0.f;

   private:
      float       cur = 0.f;
   };

   class Filter
   {
   public:
      void        set_sample_freq (float sample_freq);
      void        set_cutoff_freq (float freq);
      float       process (float x);

   private:
      float       _sample_freq;

      float       _z_eq_b [3];   // Direct, order z^(-n)
      float       _z_eq_a [3];   // Recursive

      float       _mem_x [2];    // Input memory, order z^(-n)
      float       _mem_y [2];    // Output memory
      int         _mem_pos = 0;  // 0 or 1
   };

   using Filters = std::array <Filter, NBR_CHANNELS>;

   bool           _arm_active = false;
   GainRamp       _active;
   GainRamp       _mode;
   Filters        _filters;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DropDsp () = delete;
                  DropDsp (const DropDsp & rhs) = delete;
   DropDsp &      operator = (const DropDsp & rhs) = delete;
   bool           operator == (const DropDsp & rhs) const = delete;
   bool           operator != (const DropDsp & rhs) const = delete;



}; // class DropDsp



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
