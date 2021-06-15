/*****************************************************************************

      SdImpl.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <string>



namespace erb
{



class SdImpl
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  SdImpl () = default;
   virtual        ~SdImpl () = default;

   void           set_root (std::string root_path_utf8);

   bool           mount ();
   void           unmount ();

   File           open (const char * path_0, File::Mode mode);
   Directory      list (const char * path_0);



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   std::string    _root;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SdImpl (const SdImpl & rhs) = delete;
                  SdImpl (SdImpl && rhs) = delete;
   SdImpl &       operator = (const SdImpl & rhs) = delete;
   SdImpl &       operator = (SdImpl && rhs) = delete;
   bool           operator == (const SdImpl & rhs) const = delete;
   bool           operator != (const SdImpl & rhs) const = delete;



}; // class SdImpl



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
