/*****************************************************************************

      def.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



#if defined (__GNUC__) && ! defined (__clang__)
   #define erb_GNUC_SWITCH_COVERAGE_FIX 1

#else
   #define erb_GNUC_SWITCH_COVERAGE_FIX 0

#endif


/*\\\ WARNINGS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#if defined (__clang__)
   #define erb_DISABLE_WARNINGS_DAISY \
      _Pragma ("clang diagnostic push")

   #define erb_RESTORE_WARNINGS \
      _Pragma ("clang diagnostic pop")

#elif defined (__GNUC__)
   #define erb_DISABLE_WARNINGS_DAISY \
      _Pragma ("GCC diagnostic push") \
      _Pragma ("GCC diagnostic ignored \"-Wpedantic\"") \
      _Pragma ("GCC diagnostic ignored \"-Wignored-qualifiers\"") \
      _Pragma ("GCC diagnostic ignored \"-Wunused-parameter\"") \

   #define erb_RESTORE_WARNINGS \
      _Pragma ("GCC diagnostic pop")

#elif defined (_MSC_VER)
   #define erb_DISABLE_WARNINGS_DAISY \
      __pragma (warning (push))

   #define erb_RESTORE_WARNINGS \
      __pragma (warning (pop))

#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
