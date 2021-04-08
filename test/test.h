/*****************************************************************************

      test.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <exception>

#include <cstdio>



#if defined (__GNUC__) || defined (__clang__)
   #define erb_TEST(expr) \
      do { if (!(expr)) {printf ("      Test failed: %s line: %d\n      %s\n", __PRETTY_FUNCTION__, __LINE__, #expr); std::terminate ();}} while (false)
   #define erb_TEST_FAILED \
      do {printf ("      Test failed: %s line: %d\n", __PRETTY_FUNCTION__, __LINE__); std::terminate ();} while (false)

#elif defined (_MSC_VER)
   #define erb_TEST(expr) \
      do { if (!(expr)) {printf ("      Test failed: %s line: %d\n      %s\n", __FUNCDNAME__, __LINE__, #expr); std::terminate ();}} while (false)
   #define erb_TEST_FAILED \
      do {printf ("      Test failed: %s line: %d\n", __FUNCDNAME__, __LINE__); std::terminate ();} while (false)

#else
   #error Unsupported Compiler.

#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
