/*****************************************************************************

      DaisyModuleListener.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



class DaisyModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DaisyModuleListener () = default;
   virtual        ~DaisyModuleListener () = default;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   virtual void   impl_notify_audio_buffer_start () = 0;
   virtual void   impl_notify_audio_buffer_end () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  DaisyModuleListener (const DaisyModuleListener & rhs) = delete;
                  DaisyModuleListener (DaisyModuleListener && rhs) = delete;
   DaisyModuleListener &
                  operator = (const DaisyModuleListener & rhs) = delete;
   DaisyModuleListener &
                  operator = (DaisyModuleListener && rhs) = delete;
   bool           operator == (const DaisyModuleListener & rhs) const = delete;
   bool           operator != (const DaisyModuleListener & rhs) const = delete;



}; // class DaisyModuleListener



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
