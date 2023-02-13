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

// mu0_language.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_compiler.h>

#ifndef MU0_LANGUAGE_H
#define MU0_LANGUAGE_H 1

#	ifdef __cplusplus
#		ifndef __STDC__
#			define __STDC__ 1
#		endif
#	endif

#	undef  MU0_HAVE_CPP98
#	undef  MU0_HAVE_CPP03
#	undef  MU0_HAVE_CPP11
#	undef  MU0_HAVE_CPP14
#	undef  MU0_HAVE_CPP17
#	undef  MU0_HAVE_CPP20

#	define MU0_HAVE_CPP98 0
#	define MU0_HAVE_CPP03 0
#	define MU0_HAVE_CPP11 0
#	define MU0_HAVE_CPP14 0
#	define MU0_HAVE_CPP17 0
#	define MU0_HAVE_CPP20 0

#	ifdef __cplusplus

#		undef  __stdmuc__
#		undef  __stdmucpp__
#		undef  __stdmuc_version__
#		undef  __stdmucpp_version__

#		define  __stdmuc__          0
#		define  __stdmucpp__        1
#		define __stdmuc_version__   0L
#		define __stdmucpp_version__ 202302L

#		undef  MU0_HAVE_CPP98
#		define MU0_HAVE_CPP98    1
#		if __cplusplus >= 199711L
#			undef  MU0_HAVE_CPP03
#			define MU0_HAVE_CPP03 1
#		endif
#		if __cplusplus >= 201103L
#			undef  MU0_HAVE_CPP11
#			define MU0_HAVE_CPP11 1
#		endif
#		if __cplusplus >= 201402L
#			undef  MU0_HAVE_CPP14
#			define MU0_HAVE_CPP14 1
#		endif
#		if __cplusplus >= 201703L
#			undef  MU0_HAVE_CPP17
#			define MU0_HAVE_CPP17 1
#		endif
#		if __cplusplus > 201703L
#			undef  MU0_HAVE_CPP20
#			define MU0_HAVE_CPP20 1
#		endif
#	endif

#	undef  MU0_HAVE_C89
#	undef  MU0_HAVE_C90
#	undef  MU0_HAVE_C95
#	undef  MU0_HAVE_C99
#	undef  MU0_HAVE_C11
#	undef  MU0_HAVE_C17
#	undef  MU0_HAVE_C23
#	define MU0_HAVE_C89 0
#	define MU0_HAVE_C90 0
#	define MU0_HAVE_C95 0
#	define MU0_HAVE_C99 0
#	define MU0_HAVE_C11 0
#	define MU0_HAVE_C17 0
#	define MU0_HAVE_C23 0

#	if defined(__STDC__) && defined(__STDC_VERSION__)
#		undef  __stdmuc__
#		undef  __stdmucpp__
#		undef  __stdmuc_version__
#		undef  __stdmucpp_version__

#		define  __stdmuc__          1
#		define  __stdmucpp__        0
#		define __stdmuc_version__   202302L
#		define __stdmucpp_version__ 0L

#		undef  MU0_HAVE_C89
#		define MU0_HAVE_C891
#		if __STDC__ == 1
#			undef  MU0_HAVE_C90
#			define MU0_HAVE_C90    1
#			if (__STDC_VERSION__ >= 199409L)
#				undef  MU0_HAVE_C95
#				define MU0_HAVE_C95 1
#			endif
#			if (__STDC_VERSION__ >= 199901L)
#				undef  MU0_HAVE_C99
#				define MU0_HAVE_C99 1
#			endif
#			if (__STDC_VERSION__ >= 201112L)
#				undef  MU0_HAVE_C11
#				define MU0_HAVE_C11 1
#			endif
#			if (__STDC_VERSION__ >= 201710L)
#				undef  MU0_HAVE_C17
#				define MU0_HAVE_C17 1
#			endif
#			if (__STDC_VERSION__ >= 202312L)
#				undef  MU0_HAVE_C23
#				define MU0_HAVE_C23 1
#			endif
#		endif
#	endif

#	if !MU0_HAVE_C11 && !MU0_HAVE_CPP11
#	if !defined(_MSC_VER)
#		if !defined(__STDC_FORMAT_MACROS)
#			define __STDC_FORMAT_MACROS   1
#		endif
#		if !defined(__STDC_CONSTANT_MACROS)
#			define __STDC_CONSTANT_MACROS 1
#		endif
#	endif
#	endif

#	undef  MU0_HAVE_POSIX1_2001
#	undef  MU0_HAVE_POSIX1_2008
#	define MU0_HAVE_POSIX1_2001 0
#	define MU0_HAVE_POSIX1_2008 0

#	include <unistd.h>
#	include <stddef.h>

#	if                                                            \
	   (defined(_POSIX_VERSION)  && (_POSIX_VERSION  >= 200112L)) \
	|| (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200112L))
#		undef  MU0_HAVE_POSIX1_2001
#		define MU0_HAVE_POSIX1_2001 1
#	endif
#	if                                                            \
	   (defined(_POSIX_VERSION)  && (_POSIX_VERSION  >= 200809L)) \
	|| (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200809L))
#		undef  MU0_HAVE_POSIX1_2008
#		define MU0_HAVE_POSIX1_2008 1
#	endif

#endif /* !MU0_LANGUAGE_H */

/* EOF */