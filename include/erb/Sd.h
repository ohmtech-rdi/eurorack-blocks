/*****************************************************************************

      Sd.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_VCV_RACK)
#include <string>
#endif



namespace erb
{



class Filesystem;

class Sd
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  Sd (Filesystem & filesystem);
   virtual        ~Sd () = default;

   bool           mount ();
   void           unmount ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   Filesystem &   impl_data;

#if defined (erb_TARGET_VCV_RACK)
   void           impl_set_root (const char * path_0);
   std::string    impl_root () const;
#endif

   inline void    impl_preprocess () {}
   inline void    impl_postprocess () {}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

#if defined (erb_TARGET_VCV_RACK)
   std::string    _root;
#endif




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
