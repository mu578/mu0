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

// mu0_definition.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#ifndef MU0_DEFINITION_H
#define MU0_DEFINITION_H 1

#	ifdef __cplusplus
#		define MU0_BEGIN_CDECL extern "C" {
#		define MU0_END_CDECL   }
#	else
#		define MU0_BEGIN_CDECL
#		define MU0_END_CDECL
#	endif

#	define MU0_HAVE_CC_GNUC 0
#	if defined(__GNUC__)
#	if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 8)
#		undef  MU0_HAVE_CC_GNUC
#		define MU0_HAVE_CC_GNUC 1
#	endif
#	endif

#	define MU0_HAVE_CC_CLANG 0
#	if defined(__clang__)
#	if defined(__is_identifier)
#		undef  MU0_HAVE_CC_CLANG
#		define MU0_HAVE_CC_CLANG 1
#	endif
#	endif

#	define MU0_HAVE_C89   1
#	define MU0_HAVE_C90   0
#	define MU0_HAVE_C94   0
#	define MU0_HAVE_C99   0
#	define MU0_HAVE_C11   0
#	define MU0_HAVE_C17   0

#	define MU0_HAVE_CPP98 0
#	define MU0_HAVE_CPP03 0
#	define MU0_HAVE_CPP11 0
#	define MU0_HAVE_CPP14 0
#	define MU0_HAVE_CPP17 0
#	define MU0_HAVE_CPP20 0

#	ifdef __cplusplus
#		undef  MU0_HAVE_CPP98
#		define MU0_HAVE_CPP98 1
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

#	if defined(__STDC__) || defined(__STDC_VERSION__)
#		undef  MU0_HAVE_C89
#		define MU0_HAVE_C89 1
#		if defined(__STDC_VERSION__)
#			undef  MU0_HAVE_C90
#			define MU0_HAVE_C90 1
#			if (__STDC_VERSION__ >= 199409L)
#				undef  MU0_HAVE_C94
#				define MU0_HAVE_C94 1
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
#		endif
#	endif

#	if !MU0_HAVE_C11 && !MU0_HAVE_CPP11
#	if !defined(_MSC_VER)
#		if !defined(__STDC_FORMAT_MACROS)
#			define __STDC_FORMAT_MACROS 1
#		endif
#		if !defined(__STDC_CONSTANT_MACROS)
#			define __STDC_CONSTANT_MACROS 1
#		endif
#	endif
#	endif

#	if !defined(__mu0_volatile__)
#		define __mu0_volatile__ volatile
#	endif

#	if !defined(__mu0_static__)
#		define __mu0_static__   static
#	endif

#	if !defined(__mu0_inline__)
#		define __mu0_inline__   inline
#	endif

#	if !defined(__mu0_inline_always__)
#		if defined(_MSC_VER)
#			define __mu0_inline_always__ __forceinline
#		elif (((defined(__GNUC__) && __GNUC__ >= 4) || (defined(__clang__) || defined(__llvm__))))
#			define __mu0_inline_always__ __inline__ __attribute__((always_inline))
#		else
#			define __mu0_inline_always__ __mu0_inline__
#		endif
#	endif

#	if !defined(__mu0_never_inline__)
#		if defined(_MSC_VER)
#			define __mu0_never_inline__ __declspec(noinline)
#		elif (((defined(__GNUC__) && __GNUC__ >= 4) || (defined(__clang__) || defined(__llvm__))))
#			define __mu0_never_inline__ __attribute__((noinline))
#		else
#			define __mu0_never_inline__
#		endif
#	endif

#	define ____mu0_static___inline__ __mu0_static__ __mu0_inline_always__

#	undef MU0_HAVE_OVERLOAD
#	undef __mu0_overload__
#	if defined(__clang__)
#	if __has_attribute(__overloadable__)
#		define MU0_HAVE_OVERLOAD 1
#		define __mu0_overload__  __mu0_static__ __attribute__((__overloadable__, __always_inline__, __unused__))
#	endif
#	endif

#	undef MU0_HAVE_TYPEOF
#	undef __mu0_typeof__
#	undef __mu0_istypeof__
#	if ((defined(__GNUC__) && (__GNUC__ + 0 >= 3)) || defined(__clang__))
#		define MU0_HAVE_TYPEOF 1
#		define __mu0_typeof__(__x)           __typeof__((__x) + 0)
#		define __mu0_istypeof__(_Tp, __x) ((__builtin_types_compatible_p(type1, __mu0_typeof__(__x))) ? 1 : 0)
#	endif

#	define __mu0_issizeof__(_Tp, __x) (((sizeof(_Tp) == sizeof(__x))) ? 1 : 0)

MU0_BEGIN_CDECL

#	define mu0_scope_begin         do     {
#	define mu0_scope_end           break; } while (0)

#	define mu0_nullptr             NULL
#	define mu0_is_nullptr(__x)     ((__x) == NULL ? 1 : 0)
#	define mu0_not_nullptr(__x)    ((__x) != NULL ? 1 : 0)

#	define mu0_cast(_Tp, __x)       (_Tp)(__x)
#	define mu0_const_cast(_Tp, __x) (const _Tp)(__x)

MU0_END_CDECL

#endif /* !MU0_DEFINITION_H */

/* EOF */