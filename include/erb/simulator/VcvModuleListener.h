/*****************************************************************************

      VcvModuleListener.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace erb
{



class VcvModuleListener
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  VcvModuleListener () = default;
   virtual        ~VcvModuleListener () = default;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   virtual void   impl_notify_audio_buffer_start () = 0;
   virtual void   impl_notify_audio_buffer_end () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  VcvModuleListener (const VcvModuleListener & rhs) = delete;
                  VcvModuleListener (VcvModuleListener && rhs) = delete;
   VcvModuleListener &
                  operator = (const VcvModuleListener & rhs) = delete;
   VcvModuleListener &
                  operator = (VcvModuleListener && rhs) = delete;
   bool           operator == (const VcvModuleListener & rhs) const = delete;
   bool           operator != (const VcvModuleListener & rhs) const = delete;



}; // class VcvModuleListener



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
