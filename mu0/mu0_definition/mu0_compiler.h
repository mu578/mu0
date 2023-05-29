//
// # -*- coding: utf-8, tab-width: 3 -*-

//                                                           ___                                            //
//                                                          / _ \                                           //
//                                            _   _  _   _ | | | |                                          //
//                                           | | | || | | || | | |                                          //
//                                           | |_| || |_| || |_| |                                          //
//                                           | ._,_| \___/  \___/                                           //
//                                           | |                                                            //
//                                           |_|                                                            //

// mu0_compiler.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

//#! CC_MSVCC v1929   or later (prefer clang, fuzzy support for fun)
//#! CC_ITLCC unknown or later (prefer clang, fuzzy support for fun)
//#!
//#! CC_CLANG v6.0 or later
//#!    - XCode v6.1 or later
//#!    - Visual studio clang-v16.2 or later
//#! CC_ARMCC v5.0 or later
//#! CC_GNUCC v4.8 or later

#ifndef MU0_COMPILER_H
#define MU0_COMPILER_H 1

#	ifdef __cplusplus
#		define MU0_BEGIN_CDECL {
#		define MU0_END_CDECL   }
#	else
#		define MU0_BEGIN_CDECL
#		define MU0_END_CDECL
#	endif

#	undef  MU0_HAVE_COMPILER
#	define MU0_HAVE_COMPILER 0

#	undef  MU0_HAVE_CC_MSVCC
#	undef  MU0_HAVE_CC_MSVCL
#	define MU0_HAVE_CC_MSVCC 0
#	define MU0_HAVE_CC_MSVCL 0
#	if defined(_MSC_VER) && (_MSC_VER >= 1929)
#		include <intrin.h>
#		include <BaseTsd.h>
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_MSVCC
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_MSVCC 1
#	if defined(__clang__)
#		undef  MU0_HAVE_CC_MSVCL
#		define MU0_HAVE_CC_MSVCL 1
#	endif
#	endif

#	undef  MU0_HAVE_CC_ITLCC
#	define MU0_HAVE_CC_ITLCC 0
#	undef  MU0_HAVE_CC_ITLGC
#	define MU0_HAVE_CC_ITLGC 0
#	if                           \
	   defined(__INTEL_COMPILER) \
	|| defined(__ECC)            \
	|| defined(__ICL)            \
	|| defined(__ICC)            \
	|| defined(ICC_VERSION)
#		include <intrin.h>
#		include <immintrin.h>
#		if defined(_WIN32) || defined(_WIN64)
#			include <BaseTsd.h>
#		endif
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_ITLCC
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_ITLCC 1
#		ifdef __GNUC__
#		undef  MU0_HAVE_CC_ITLGC
#		define MU0_HAVE_CC_ITLGC 1
#	endif
#	endif

#	undef  MU0_HAVE_CC_ARMCC
#	define MU0_HAVE_CC_ARMCC 0
#	if defined(__CC_ARM) && defined(__ARMCC_VERSION) && (__ARMCC_VERSION > 5000000)
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_ARMCC
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_ARMCC 1
#	endif

#	if !MU0_HAVE_COMPILER
#	undef  MU0_HAVE_CC_APLCC
#	define MU0_HAVE_CC_APLCC 0
#	if defined(__clang__) && defined(__apple_build_version__)
#	if defined(__is_identifier) && defined(__has_builtin)
#		undef  MU0_HAVE_CC_APLCC
#		define MU0_HAVE_CC_APLCC 1
#	endif
#	endif
#	endif

#	if !MU0_HAVE_COMPILER
#	undef  MU0_HAVE_CC_CLANG
#	define MU0_HAVE_CC_CLANG 0
#	if defined(__clang__)
#	if defined(__is_identifier) && defined(__has_builtin)
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_CLANG
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_CLANG 1
#	endif
#	endif
#	endif

#	if !MU0_HAVE_COMPILER
#	undef  MU0_HAVE_CC_GNUCC
#	define MU0_HAVE_CC_GNUCC  0
#	if (defined(__GNUC__) && defined(__GNUC_MINOR__))
#	if __GNUC__ + 0 > 4 || (__GNUC__ + 0 >= 4 && __GNUC_MINOR__ > 8)
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_GNUCC
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_GNUCC 1
#		ifndef __has_builtin
#			define __has_builtin(x) 0
#		endif
#	endif
#	endif
#	endif

#	if !MU0_HAVE_COMPILER
#		error mu0_compiler.h
#	endif

#endif /* !MU0_COMPILER_H */

/* EOF */