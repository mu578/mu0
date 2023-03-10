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

#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_FEATURE_H
#define MU0_FEATURE_H 1

#	undef  MU0_HAVE_EXTENSION
#	undef  __mu0_extension__
#	define MU0_HAVE_EXTENSION 0
#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC  || MU0_HAVE_CC_ARMCC
#		undef  MU0_HAVE_EXTENSION
#		define MU0_HAVE_EXTENSION 1
#		define __mu0_extension__  __extension__
#	else
#		define __mu0_extension__
#	endif

#	undef  MU0_HAVE_GENERIC
#	undef  __mu0_generic__
#	define MU0_HAVE_GENERIC 0
#	if MU0_HAVE_C11
#		undef  MU0_HAVE_GENERIC
#		define MU0_HAVE_GENERIC 1
#		define __mu0_generic__  _Generic
#	else
#		define __mu0_generic__
#	endif

#	undef  MU0_HAVE_TYPEOF
#	undef  __mu0_typeof__
#	undef  __mu0_kindof__
#	undef  __mu0_isoftype__
#	undef  __mu0_isofkind__
#	define MU0_HAVE_TYPEOF 0

#	if   MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__             __typeof__
#		define __mu0_kindof__(__x)        __mu0_typeof__((__x) + 0)
#		define __mu0_isoftype__(_Tp, __x) ((__builtin_types_compatible_p(_Tp, __mu0_typeof__(__x))) ? 1 : 0)
#		define __mu0_isofkind__(_Tp, __x) ((__builtin_types_compatible_p(_Tp, __mu0_kindof__(__x))) ? 1 : 0)
#	elif MU0_HAVE_C23
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__             typeof
#		define __mu0_kindof__(__x)        typeof_unequal(__x)
#		define __mu0_isoftype__(_Tp, x)   ((__mu0_typeof__(_Tp) == __mu0_typeof__(__x)) ? 1 : 0)
#		define __mu0_isofkind__(_Tp, x)   ((__mu0_typeof__(_Tp) == __mu0_typeof__(__x) || __mu0_typeof__(_Tp) == __mu0_kindof__(__x))  ? 1 : 0)
#	elif MU0_HAVE_CC_ITLGC && MU0_HAVE_GENERIC
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__             __typeof__
#		define __mu0_kindof__(__x)        __mu0_typeof__((__x) + 0)
#		define __mu0_isoftype__(_Tp, x)   __mu0_generic__((__x), _Tp : 1, default: 0)
#		define __mu0_isofkind__(_Tp, x)   __mu0_generic__((__x), _Tp : 1, default: 0)
#	endif

#	if !MU0_HAVE_TYPEOF && MU0_HAVE_CPP11
#		include <type_traits>
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__(__x)        ::std::remove_reference<decltype(__x)>::type
#		define __mu0_kindof__(__x)        ::std::decay<decltype(__x)>::type
#		define __mu0_isoftype__(_Tp, x)   ((::std::is_same<_Tp , __mu0_typeof__(__x) >::value == true) ? 1 : 0)
#		define __mu0_isofkind__(_Tp, x)   ((::std::is_same<_Tp , __mu0_typeof__(__x) >::value == true || ::std::is_same<_Tp , __mu0_kindof__(__x) >::value == true) ? 1 : 0)
#	endif

#	if MU0_HAVE_TYPEOF
#	define __mu0_infer__(__x) __mu0_kindof__(__x)
#	else
#	define __mu0_infer__(__x) void
#	endif

#	undef  MU0_HAVE_SIZEOF
#	undef  __mu0_sizeof__
#	undef  __mu0_isofsize__
#	define MU0_HAVE_SIZEOF 0
#	if 1
#		undef  MU0_HAVE_SIZEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_sizeof__(__x)        sizeof(__x)
#		define __mu0_isofsize__(_Tp, __x) (((__mu0_sizeof__(_Tp) == __mu0_sizeof__(__x))) ? 1 : 0)
#	endif

#endif /* !MU0_FEATURE_H */

/* EOF */