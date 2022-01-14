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

   #define erb_DISABLE_WARNINGS_VCVRACK \
      _Pragma ("clang diagnostic push") \
      _Pragma ("clang diagnostic ignored \"-Wshadow-field-in-constructor\"") \
      _Pragma ("clang diagnostic ignored \"-Wfloat-conversion\"") \
      _Pragma ("clang diagnostic ignored \"-Wdocumentation-unknown-command\"") \
      _Pragma ("clang diagnostic ignored \"-Wdocumentation\"") \
      _Pragma ("clang diagnostic ignored \"-Wold-style-cast\"") \
      _Pragma ("clang diagnostic ignored \"-Wzero-as-null-pointer-constant\"") \
      _Pragma ("clang diagnostic ignored \"-Wreserved-id-macro\"") \
      _Pragma ("clang diagnostic ignored \"-Wgnu-anonymous-struct\"") \
      _Pragma ("clang diagnostic ignored \"-Wnested-anon-types\"") \
      _Pragma ("clang diagnostic ignored \"-Wdouble-promotion\"") \
      _Pragma ("clang diagnostic ignored \"-Wshadow\"") \
      _Pragma ("clang diagnostic ignored \"-Wconversion\"") \
      _Pragma ("clang diagnostic ignored \"-Wglobal-constructors\"") \
      _Pragma ("clang diagnostic ignored \"-Wunused-parameter\"") \
      _Pragma ("clang diagnostic ignored \"-Winconsistent-missing-destructor-override\"") \
      _Pragma ("clang diagnostic ignored \"-Wcast-align\"") \
      _Pragma ("clang diagnostic ignored \"-Wcast-qual\"") \
      _Pragma ("clang diagnostic ignored \"-Wvla\"") \
      _Pragma ("clang diagnostic ignored \"-Wvla-extension\"") \
      _Pragma ("clang diagnostic ignored \"-Wheader-hygiene\"") \
      _Pragma ("clang diagnostic ignored \"-Wunknown-warning-option\"") \
      _Pragma ("clang diagnostic ignored \"-Wsuggest-override\"") \
      _Pragma ("clang diagnostic ignored \"-Wsuggest-destructor-override\"") \

   #define erb_DISABLE_WARNINGS_FAUST_GEN \
      _Pragma ("clang diagnostic push") \
      _Pragma ("clang diagnostic ignored \"-Wunused-parameter\"") \
      _Pragma ("clang diagnostic ignored \"-Wzero-length-array\"") \

   #define erb_DISABLE_WARNINGS_GLOBAL_CTOR \
      _Pragma ("clang diagnostic push") \
      _Pragma ("clang diagnostic ignored \"-Wglobal-constructors\"") \

   #define erb_RESTORE_WARNINGS \
      _Pragma ("clang diagnostic pop")

#elif defined (__GNUC__)
   #define erb_DISABLE_WARNINGS_DAISY \
      _Pragma ("GCC diagnostic push") \
      _Pragma ("GCC diagnostic ignored \"-Wpedantic\"") \
      _Pragma ("GCC diagnostic ignored \"-Wignored-qualifiers\"") \
      _Pragma ("GCC diagnostic ignored \"-Wunused-parameter\"") \

   #define erb_DISABLE_WARNINGS_VCVRACK \
      _Pragma ("GCC diagnostic push")

   #define erb_DISABLE_WARNINGS_FAUST_GEN \
      _Pragma ("GCC diagnostic push") \
      _Pragma ("GCC diagnostic ignored \"-Wunused-parameter\"") \

   #define erb_DISABLE_WARNINGS_GLOBAL_CTOR \
      _Pragma ("GCC diagnostic push")

   #define erb_RESTORE_WARNINGS \
      _Pragma ("GCC diagnostic pop")

#elif defined (_MSC_VER)
   #define erb_DISABLE_WARNINGS_DAISY \
      __pragma (warning (push))

   #define erb_DISABLE_WARNINGS_VCVRACK \
      __pragma (warning (push))

   #define erb_DISABLE_WARNINGS_FAUST_GEN \
      __pragma (warning (push))

   #define erb_DISABLE_WARNINGS_GLOBAL_CTOR \
      __pragma (warning (push))

   #define erb_RESTORE_WARNINGS \
      __pragma (warning (pop))

#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
