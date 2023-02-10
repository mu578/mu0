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

#ifndef MU0_COMPILER_H
#define MU0_COMPILER_H 1

#	ifdef __cplusplus
#		define MU0_BEGIN_CDECL extern "C" {
#		define MU0_END_CDECL   }
#	else
#		define MU0_BEGIN_CDECL
#		define MU0_END_CDECL
#	endif

MU0_BEGIN_CDECL

#	undef  MU0_HAVE_COMPILER
#	define MU0_HAVE_COMPILER 0

#	undef  MU0_HAVE_CC_MSVC
#	define MU0_HAVE_CC_MSVC  0
#	if defined(_MSC_VER)
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_MSVC
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_MSVC  1
#	endif

#	undef  MU0_HAVE_CC_ICC
#	define MU0_HAVE_CC_ICC   0
#	undef  MU0_HAVE_CC_GICC
#	define MU0_HAVE_CC_GICC  0
#	if                           \
	   defined(__INTEL_COMPILER) \
	|| defined(__ECC)            \
	|| defined(__ICL)            \
	|| defined(__ICC)            \
	|| defined(ICC_VERSION)
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_ICC
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_ICC   1
#		ifdef __GNUC__
#		undef  MU0_HAVE_CC_GICC
#		define MU0_HAVE_CC_GICC  1
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
#	undef  MU0_HAVE_CC_GNUC
#	define MU0_HAVE_CC_GNUC  0
#	if (defined(__GNUC__) && defined(__GNUC_MINOR__))
#	if __GNUC__ + 0 > 4 || (__GNUC__ + 0 >= 4 && __GNUC_MINOR__ > 8)
#		undef  MU0_HAVE_COMPILER
#		undef  MU0_HAVE_CC_GNUC
#		define MU0_HAVE_COMPILER 1
#		define MU0_HAVE_CC_GNUC  1
#		ifndef __has_builtin
#			define __has_builtin(x) 0
#		endif
#	endif
#	endif
#	endif

#	if !MU0_HAVE_COMPILER
#		error mu0_compiler.h
#	endif

MU0_END_CDECL

#endif /* !MU0_COMPILER_H */

/* EOF */