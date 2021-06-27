/*****************************************************************************

      File.cpp
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "erb/File.h"

#include "erb/Sd.h"



namespace erb
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

File::File (Sd & sd)
#if defined (erb_TARGET_VCV_RACK)
:  _sd (sd)
#endif
{
#if defined (erb_TARGET_DAISY)
   ((void)sd);
#endif
}



/*
==============================================================================
Name : dtor
==============================================================================
*/

File::~File ()
{
   close ();
}



/*
==============================================================================
Name : is_open
==============================================================================
*/

bool  File::is_open () const
{
#if defined (erb_TARGET_DAISY)
   return _state != State::None;

#elif defined (erb_TARGET_VCV_RACK)
   return _stream.is_open ();

#endif
}



/*
==============================================================================
Name : open
==============================================================================
*/

void  File::open (const char * path_utf8_0, Mode mode)
{
   if (is_open ()) close ();

#if defined (erb_TARGET_DAISY)
   BYTE ff_mode = (mode == Mode::Read) ? FA_READ : FA_WRITE;

   auto err = f_open (&_fil, path_utf8_0, ff_mode);
   _state = (err == FR_OK) ? State::Ok : State::Fail;

#elif defined (erb_TARGET_VCV_RACK)
   std::string absolute_path = _sd.impl_root () + path_utf8_0;

   _stream.open (absolute_path.c_str (), to_ios_base_openmode (mode));
#endif
}



/*
==============================================================================
Name : close
==============================================================================
*/

void  File::close ()
{
   if (!is_open ()) return;

#if defined (erb_TARGET_DAISY)
   f_close (&_fil); // ignore result
   _state = State::None;

#elif defined (erb_TARGET_VCV_RACK)
   _stream.close ();

#endif
}



/*
==============================================================================
Name : operator bool
==============================================================================
*/

File::operator bool () const
{
   return ! fail ();
}



/*
==============================================================================
Name : operator !
==============================================================================
*/

bool  File::operator ! () const
{
   return fail ();
}



/*
==============================================================================
Name : good
==============================================================================
*/

bool  File::good () const
{
#if defined (erb_TARGET_DAISY)
   return _state == State::Ok;

#elif defined (erb_TARGET_VCV_RACK)
   return _stream.good ();

#endif
}



/*
==============================================================================
Name : eof
==============================================================================
*/

bool  File::eof () const
{
#if defined (erb_TARGET_DAISY)
   return f_eof (&_fil) != 0;

#elif defined (erb_TARGET_VCV_RACK)
   return _stream.eof ();

#endif
}



/*
==============================================================================
Name : fail
==============================================================================
*/

bool  File::fail () const
{
#if defined (erb_TARGET_DAISY)
   return _state == State::Fail;

#elif defined (erb_TARGET_VCV_RACK)
   return _stream.fail ();

#endif
}



/*
==============================================================================
Name : read
==============================================================================
*/

File::Size  File::read (void * dst, Size size)
{
#if defined (erb_TARGET_DAISY)
   Size read_size = 0;

   auto err = f_read (&_fil, dst, size, &read_size);
   _state = (err == FR_OK) ? State::Ok : State::Fail;

   return read_size;

#elif defined (erb_TARGET_VCV_RACK)
   return _stream.readsome (
      reinterpret_cast <std::fstream::char_type *> (dst), size
   );

#endif
}



/*
==============================================================================
Name : write
==============================================================================
*/

File::Size  File::write (const void * src, Size size)
{
#if defined (erb_TARGET_DAISY)
   Size write_size = 0;

   auto err = f_write (&_fil, dst, size, &write_size);
   _state = (err == FR_OK) ? State::Ok : State::Fail;

   return write_size;

#elif defined (erb_TARGET_VCV_RACK)
   auto pos_start = _stream.tellp ();
   _stream.write (
      reinterpret_cast <const std::fstream::char_type *> (src), size
   );
   auto pos_end = _stream.tellp ();
   return pos_end - pos_start;

#endif
}



/*
==============================================================================
Name : flush
==============================================================================
*/

void  File::flush ()
{
#if defined (erb_TARGET_DAISY)
   auto err = f_sync (&_fil);
   _state = (err == FR_OK) ? State::Ok : State::Fail;

#elif defined (erb_TARGET_VCV_RACK)
   _stream.flush ();

#endif
}



/*
==============================================================================
Name : seek
==============================================================================
*/

void  File::seek (Position pos)
{
#if defined (erb_TARGET_DAISY)
   auto err = f_lseek (&_fil, pos);
   _state = (err == FR_OK) ? State::Ok : State::Fail;

#elif defined (erb_TARGET_VCV_RACK)
   _stream.seekg (pos);

#endif
}



/*
==============================================================================
Name : tell
==============================================================================
*/

File::Position File::tell ()
{
#if defined (erb_TARGET_DAISY)
   return f_tell (&_fil);

#elif defined (erb_TARGET_VCV_RACK)
   return _stream.tellg ();

#endif
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : to_ios_base_openmode
==============================================================================
*/

#if defined (erb_TARGET_VCV_RACK)
std::ios_base::openmode File::to_ios_base_openmode (Mode mode)
{
   switch (mode)
   {
   case Mode::Read:
      return std::ios_base::in;
      //break;

   case Mode::Write:
      return std::ios_base::out;
      //break;
   }

   return std::ios_base::in;
}
#endif



}  // namespace erb



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
