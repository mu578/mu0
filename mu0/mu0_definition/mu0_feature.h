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

// mu0_feature.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#ifndef MU0_FEATURE_H
#define MU0_FEATURE_H 1

#	undef  MU0_HAVE_TYPEOF
#	undef  __mu0_typeof__
#	undef  __mu0_istypeof__
#	define MU0_HAVE_TYPEOF 0
#	if ((defined(__GNUC__) && (__GNUC__ + 0 >= 3)) || defined(__clang__))
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF 1
#		define __mu0_typeof__(__x)        __typeof__((__x) + 0)
#		define __mu0_istypeof__(_Tp, __x) ((__builtin_types_compatible_p(type1, __mu0_typeof__(__x))) ? 1 : 0)
#	elif MU0_HAVE_C23
#		undef  MU0_HAVE_TYPEOF 
#		define MU0_HAVE_TYPEOF 1
#		define __mu0_typeof__(__x)      typeof((__x) + 0)
#		define __mu0_istypeof__(_Tp, x) _Generic((__x), _Tp : 1, default: 0)
#	endif

#	undef  MU0_HAVE_SIZEOF
#	undef  __mu0_sizeof__
#	undef  __mu0_issizeof__
#	define MU0_HAVE_SIZEOF 0
#	if 1
#		undef  MU0_HAVE_SIZEOF
#		define MU0_HAVE_TYPEOF 1
#		define __mu0_sizeof__(__x)        sizeof(__x)
#		define __mu0_issizeof__(_Tp, __x) (((__mu0_sizeof__(_Tp) == __mu0_sizeof__(__x))) ? 1 : 0)
#	endif

#	undef  MU0_HAVE_EXTENSION
#	undef  __mu0_extension__
#	define MU0_HAVE_EXTENSION 0
if (((defined(__GNUC__) && __GNUC__ >= 4) || (defined(__clang__) || defined(__llvm__))))
#		undef  MU0_HAVE_EXTENSION
#		define MU0_HAVE_EXTENSION 1
#		define __mu0_extension__ __extension__
#	else
#		define __mu0_extension__
#	endif

#	undef  MU0_HAVE_GENERIC
#	undef  __mu0_generic__
#	define MU0_HAVE_GENERIC 0
if defined(__STDC__) || defined(__STDC_VERSION__)
#		if (__STDC__ == 1 && __STDC_VERSION__ >= 201112L)
#			undef  MU0_HAVE_GENERIC
#			define MU0_HAVE_GENERIC 1
#			define __mu0_generic__ _Generic
#		else
#			define __mu0_generic__
#		endif
#	else
#		define __mu0_generic__
#	endif

#endif /* !MU0_FEATURE_H */

/* EOF */