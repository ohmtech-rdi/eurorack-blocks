/*****************************************************************************

      File.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (erb_TARGET_DAISY)
   #include "sys/fatfs.h"

#elif defined (erb_TARGET_VCV_RACK)
   #include <fstream>

#endif



namespace erb
{



class Sd;

class File
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Mode
   {
      Read, Write,
   };

#if defined (erb_TARGET_DAISY)
   using Position = FSIZE_t;
   using Size = UINT;

#elif defined (erb_TARGET_VCV_RACK)
   using Position = std::fstream::pos_type;
   using Size = std::streamsize;

#endif

   inline         File (Sd & sd);
   virtual        ~File ();

   bool           is_open () const;
   void           open (const char * path_utf8_0, Mode mode);
   void           close ();

   explicit       operator bool () const;
   bool           operator ! () const;

   bool           good () const;
   bool           eof () const;
   bool           fail () const;

   Size           read (void * dst, Size size);
   Size           write (const void * src, Size size);
   void           flush ();

   void           seek (Position pos);
   Position       tell ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

#if defined (erb_TARGET_DAISY)
   enum class State
   {
      None, Ok, Fail
   };

   FIL            _fil;
   State          _state = State::None;

#elif defined (erb_TARGET_VCV_RACK)
   std::ios_base::openmode
                  to_ios_base_openmode (Mode mode);

   Sd &           _sd;
   std::fstream   _stream;

#endif



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  File () = delete;
                  File (const File & rhs) = delete;
                  File (File && rhs) = delete;
   File &         operator = (const File & rhs) = delete;
   File &         operator = (File && rhs) = delete;
   bool           operator == (const File & rhs) const = delete;
   bool           operator != (const File & rhs) const = delete;



}; // class File



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
