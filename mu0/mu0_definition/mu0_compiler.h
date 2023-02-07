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
#	if defined(__is_identifier)
#		undef  MU0_HAVE_CC_CLANG
#		define MU0_HAVE_CC_CLANG 1
#	endif
#	endif

#	undef  MU0_HAVE_CC_GNUC
#	define MU0_HAVE_CC_GNUC 0
#	if defined(__GNUC__) && !defined(__clang__)
#	if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 8)
#		undef  MU0_HAVE_CC_GNUC
#		define MU0_HAVE_CC_GNUC 1
#	endif
#	endif

#endif /* !MU0_COMPILER_H */

/* EOF */