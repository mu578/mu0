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

#	undef  MU0_HAVE_CC_CLANG
#	define MU0_HAVE_CC_CLANG 0
#	if defined(__clang__)
#	if defined(__is_identifier) && defined(__has_builtin)
#		undef  MU0_HAVE_CC_CLANG
#		define MU0_HAVE_CC_CLANG 1
#	endif
#	endif

#	undef  MU0_HAVE_CC_GNUC
#	define MU0_HAVE_CC_GNUC 0
#	if (defined(__GNUC__) && defined(__GNUC_MINOR__)) && !defined(__clang__)
#	if __GNUC__ + 0 > 4 || (__GNUC__ + 0 >= 4 && __GNUC_MINOR__ > 8)
#		undef  MU0_HAVE_CC_GNUC
#		define MU0_HAVE_CC_GNUC  1
#	endif
#	endif

#	undef  MU0_HAVE_CC_MSVC
#	define MU0_HAVE_CC_MSVC 0
#	if defined(_MSC_VER)
#		undef  MU0_HAVE_CC_MSVC
#		define MU0_HAVE_CC_MSVC  1
#	endif

#	undef  MU0_HAVE_CC_ICC
#	define MU0_HAVE_CC_ICC  0
#	undef  MU0_HAVE_CC_GICC
#	define MU0_HAVE_CC_GICC 0
#	if (                             \
			defined(__INTEL_COMPILER)  \
				|| defined(__ECC)       \
				|| defined(__ICL)       \
				|| defined(__ICC)       \
				|| defined(ICC_VERSION) \
		)
#		undef  MU0_HAVE_CC_ICC
#		define MU0_HAVE_CC_ICC   1
#		ifdef __GNUC__
#		undef  MU0_HAVE_CC_GICC
#		define MU0_HAVE_CC_GICC  1
#	endif
#	endif

#endif /* !MU0_COMPILER_H */

/* EOF */