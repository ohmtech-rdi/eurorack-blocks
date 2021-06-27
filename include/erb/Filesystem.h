/*****************************************************************************

      Filesystem.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #include "sys/fatfs.h"

#elif defined (erb_TARGET_VCV_RACK)
   #include <string>

#endif



namespace erb
{



class Filesystem
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

#if defined (erb_TARGET_DAISY)
                  Filesystem (FATFS & fs);
#elif defined (erb_TARGET_VCV_RACK)
   inline         Filesystem () = default;
#endif
   virtual        ~Filesystem () = default;

   bool           mount ();
   void           unmount ();
   bool           is_mounted () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_VCV_RACK)
   void           impl_set_root (std::string path_utf8);
   std::string    impl_root () const;
#endif



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

#if defined (erb_TARGET_DAISY)
   FATFS &        _fs;

#elif defined (erb_TARGET_VCV_RACK)
   std::string    _root;
#endif

   bool           _mounted_flag = false;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Filesystem (const Filesystem & rhs) = delete;
                  Filesystem (Filesystem && rhs) = delete;
   Filesystem &   operator = (const Filesystem & rhs) = delete;
   Filesystem &   operator = (Filesystem && rhs) = delete;
   bool           operator == (const Filesystem & rhs) const = delete;
   bool           operator != (const Filesystem & rhs) const = delete;



}; // class Filesystem



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
