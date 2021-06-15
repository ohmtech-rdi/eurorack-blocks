/*****************************************************************************

      Sd.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #include "erb/daisy/SdDaisy.h"

#elif defined (erb_TARGET_VCV_RACK)
   #include "erb/vcvrack/SdVcv.h"

#endif



namespace erb
{



class Sd
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   inline         Sd () = default;
   virtual        ~Sd () = default;

   bool           mount ();
   void           unmount ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_VCV_RACK)
   void           impl_simulator_root (const char * path_0);
#endif

   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   SdImpl         _pimpl;




/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Sd (const Sd & rhs) = delete;
                  Sd (Sd && rhs) = delete;
   Sd &           operator = (const Sd & rhs) = delete;
   Sd &           operator = (Sd && rhs) = delete;
   bool           operator == (const Sd & rhs) const = delete;
   bool           operator != (const Sd & rhs) const = delete;



}; // class Sd



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
