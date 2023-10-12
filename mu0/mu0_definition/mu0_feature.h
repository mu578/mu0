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
#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC  || MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_MSVCL
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
#	undef  __mu0_issame__
#	undef  __mu0_issafe__
#	undef  __mu0_isuint__
#	undef  __mu0_issint__
#	define MU0_HAVE_TYPEOF 0

#	if   MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_MSVCL
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__             __typeof__
#		define __mu0_kindof__(__x)        __mu0_typeof__((__mu0_typeof__(__x))(__x))
#		define __mu0_isoftype__(_Tp, __x) ((__builtin_types_compatible_p(_Tp, __mu0_typeof__(__x))) ? 1 : 0)
#		define __mu0_isofkind__(_Tp, __x) ((__builtin_types_compatible_p(_Tp, __mu0_kindof__(__x))) ? 1 : 0)
#		define __mu0_issame__(_Tp, _Up)   ((__builtin_types_compatible_p(__mu0_typeof__(_Tp), __mu0_typeof__(_Up))) ? 1 : 0)
# 		define __mu0_decay__(__x)                                        \
		__mu0_typeof__(                                                  \
			__builtin_choose_expr(                                        \
					__mu0_isoftype__(               ___mu0_sint1_t___, __x) \
				|| __mu0_isoftype__(const          ___mu0_sint1_t___, __x) \
				|| __mu0_isoftype__(volatile       ___mu0_sint1_t___, __x) \
				|| __mu0_isoftype__(const volatile ___mu0_sint1_t___, __x) \
				, (___mu0_sint1_t___)1                                     \
			, __builtin_choose_expr(                                      \
					__mu0_isoftype__(               ___mu0_uint1_t___, __x) \
				|| __mu0_isoftype__(const          ___mu0_uint1_t___, __x) \
				|| __mu0_isoftype__(volatile       ___mu0_uint1_t___, __x) \
				|| __mu0_isoftype__(const volatile ___mu0_uint1_t___, __x) \
				, (___mu0_uint1_t___)1                                     \
			, __builtin_choose_expr(                                      \
					__mu0_isoftype__(               ___mu0_sint2_t___, __x) \
				|| __mu0_isoftype__(const          ___mu0_sint2_t___, __x) \
				|| __mu0_isoftype__(volatile       ___mu0_sint2_t___, __x) \
				|| __mu0_isoftype__(const volatile ___mu0_sint2_t___, __x) \
				, (___mu0_sint2_t___)1                                     \
			, __builtin_choose_expr(                                      \
					__mu0_isoftype__(               ___mu0_uint2_t___, __x) \
				|| __mu0_isoftype__(const          ___mu0_uint2_t___, __x) \
				|| __mu0_isoftype__(volatile       ___mu0_uint2_t___, __x) \
				|| __mu0_isoftype__(const volatile ___mu0_uint2_t___, __x) \
				, (___mu0_uint2_t___)1                                     \
			, ((__x) + 0)                                                 \
			))))                                                          \
		)
#	elif MU0_HAVE_C23
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__             typeof
#		define __mu0_kindof__(__x)        typeof_unequal(__x)
#		define __mu0_isoftype__(_Tp, x)   ((__mu0_typeof__(_Tp) == __mu0_typeof__(__x)) ? 1 : 0)
#		define __mu0_isofkind__(_Tp, x)   ((__mu0_typeof__(_Tp) == __mu0_typeof__(__x) || __mu0_typeof__(_Tp) == __mu0_kindof__(__x))  ? 1 : 0)
#		define __mu0_issame__(_Tp, _Up)   (__mu0_generic__(((_Tp){0}), _Up: 1, default: 0) && __mu0_generic__(((_Up){0}), _Tp: 1, default: 0))
# 		define __mu0_decay__(__x)         __mu0_kindof__(__x)
#	elif MU0_HAVE_CC_ITLGC && MU0_HAVE_GENERIC
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__             __typeof__
#		define __mu0_kindof__(__x)        __mu0_typeof__((__mu0_typeof__(__x))(__x))
#		define __mu0_isoftype__(_Tp, x)   __mu0_generic__((__x), _Tp : 1, default: 0)
#		define __mu0_isofkind__(_Tp, x)   __mu0_generic__((__x), _Tp : 1, default: 0)
#		define __mu0_issame__(_Tp, _Up)   (__mu0_generic__(((_Tp){0}), _Up: 1, default: 0) && __mu0_generic__(((_Up){0}), _Tp: 1, default: 0))
# 		define __mu0_decay__(__x)         __mu0_kindof__(__x)
#	endif

#	if !MU0_HAVE_TYPEOF && MU0_HAVE_CPP11
#		include <type_traits>
#		undef  MU0_HAVE_TYPEOF
#		define MU0_HAVE_TYPEOF            1
#		define __mu0_typeof__(__x)        ::std::remove_reference<decltype(__x)>::type
#		define __mu0_kindof__(__x)        ::std::decay<decltype(__x)>::type
#		define __mu0_isoftype__(_Tp, x)   ((::std::is_same<_Tp , __mu0_typeof__(__x)>::value == true) ? 1 : 0)
#		define __mu0_isofkind__(_Tp, x)   ((::std::is_same<_Tp , __mu0_typeof__(__x)>::value == true || ::std::is_same<_Tp , __mu0_kindof__(__x) >::value == true) ? 1 : 0)
#		define __mu0_issame__(_Tp, _Up)   ((::std::is_same<__Tp , _Up>::value == true) ? 1 : 0)
# 		define __mu0_decay__(__x)         __mu0_kindof__(__x)
#	endif

#	if MU0_HAVE_TYPEOF
#		define __mu0_issafe__(__a, __b)   (sizeof(__mu0_typeof__(__a)) == sizeof(__mu0_typeof__(__b))  && __mu0_issame__(__mu0_typeof__(__a), __mu0_typeof__(__b)))
#		if MU0_HAVE_CHAR_UNSIGNED
#			define __mu0_isuint__(__x)                            \
			(                                                     \
				  __mu0_isofkind__(___mu0_uint8_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uintx_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uint4_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uint2_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uint1_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_tint1_t___, __x) ? 1 : 0 \
				: 0                                                \
			)

#			define __mu0_issint__(__x)                            \
			(                                                     \
				  __mu0_isofkind__(___mu0_sint8_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sintx_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sint4_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sint2_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sint1_t___, __x) ? 1 : 0 \
				: 0                                                \
			)
#		else
#			define __mu0_isuint__(__x)                            \
			(                                                     \
				  __mu0_isofkind__(___mu0_uint8_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uintx_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uint4_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uint2_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_uint1_t___, __x) ? 1 : 0 \
				: 0                                                \
			)

#			define __mu0_issint__(__x)                            \
			(                                                     \
				  __mu0_isofkind__(___mu0_sint8_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sintx_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sint4_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sint2_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_sint1_t___, __x) ? 1 : 0 \
				: __mu0_isofkind__(___mu0_tint1_t___, __x) ? 1 : 0 \
				: 0                                                \
			)
#		endif
#	else
#		define __mu0_issafe__(__a, __b) (sizeof(__a) == sizeof(__b))
#		define __mu0_isuint__(__x)      (0)
#		define __mu0_issint__(__x)      (0)
#	endif

#	if MU0_HAVE_TYPEOF
#	define __mu0_infer__(__x) __mu0_decay__(__x)
#	else
#	warning "mu0_feature.h"
#	define __mu0_infer__(__x) void
#	endif

#	undef  MU0_HAVE_SIZEOF
#	undef  __mu0_sizeof__
#	undef  __mu0_isofsize__
#	define MU0_HAVE_SIZEOF 0
#	if 1
#		undef  MU0_HAVE_SIZEOF
#		define MU0_HAVE_SIZEOF            1
#		define __mu0_sizeof__(__x)        sizeof(__x)
#		define __mu0_isofsize__(_Tp, __x) (((__mu0_sizeof__(_Tp) == __mu0_sizeof__(__x))) ? 1 : 0)
#	endif

#	undef  MU0_HAVE_ADDRESSOF
#	undef  __mu0_addressof__
#	define MU0_HAVE_ADDRESSOF 0
#	if 1
#		undef  MU0_HAVE_ADDRESSOF
#		define MU0_HAVE_ADDRESSOF         1
#		if   MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_MSVCL
#			if (__has_builtin(__builtin_addressof))
#				define __mu0_addressof__(__x) __builtin_addressof(__x)
#			else
#				define __mu0_addressof__(__x) (&(__x))
#			endif
#		elif MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_ITLGC
#			define __mu0_addressof__(__x) __builtin_addressof(__x)
#		else
#			define __mu0_addressof__(__x) (&(__x))
#		endif
#	endif

#	undef  MU0_HAVE_ALIGNOF
#	undef  __mu0_alignof__
#	define MU0_HAVE_ALIGNOF 0
#	if 1
#		undef  MU0_HAVE_ALIGNOF
#		define MU0_HAVE_ALIGNOF         1
#		if   MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_MSVCL
#			if   (__has_builtin(__builtin_alignof))
#				define __mu0_alignof__(__x) __builtin_alignof(__x)
#			elif (__has_feature(c_alignof))
#				define __mu0_alignof__(__x) _Alignof(__x)
#			else
#				define __mu0_alignof__(__x) __alignof__(__x)
#			endif
#		elif MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_ITLGC
#			define __mu0_alignof__(__x) __alignof__(__x)
#		elif MU0_HAVE_CC_MSVC || MU0_HAVE_CC_ITLCC
#			define __mu0_alignof__(__x) __alignof(__x)
#		else
#			define __mu0_alignof__(__x) (__mu0_sizeof__(__x) <= 8U ? __mu0_sizeof__(__x) : 16U)
#		endif
#	endif

#endif /* !MU0_FEATURE_H */

/* EOF */