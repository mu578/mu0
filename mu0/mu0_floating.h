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

// mu0_floating.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition.h>

#ifndef MU0_FLOATING_H
#define MU0_FLOATING_H 1

#	undef  MU0_USE_FLOAT128
#	undef  MU0_HAVE_FLOAT128

#	undef  MU0_USE_FLOAT64
#	undef  MU0_HAVE_FLOAT64

#	undef  MU0_USE_FLOAT32
#	undef  MU0_HAVE_FLOAT32

#	undef  MU0_USE_FLOAT16
#	undef  MU0_HAVE_FLOAT16

#	define MU0_USE_FLOAT128  1
#	define MU0_HAVE_FLOAT128 0

#	define MU0_USE_FLOAT64   1
#	define MU0_HAVE_FLOAT64  0

#	define MU0_USE_FLOAT32   1
#	define MU0_HAVE_FLOAT32  0

#	define MU0_USE_FLOAT16   1
#	define MU0_HAVE_FLOAT16  0

#	if MU0_USE_FLOAT128 || MU0_USE_FLOAT64 || MU0_USE_FLOAT32 || MU0_USE_FLOAT16
#		undef  __STDC_WANT_IEC_60559_TYPES_EXT__
#		define __STDC_WANT_IEC_60559_TYPES_EXT__ 1
#	endif

#	include <float.h>
#	include <math.h>

MU0_BEGIN_CDECL

typedef long double             mu0_fpex_t;

#	if MU0_USE_FLOAT128
#	if   MU0_HAVE_CC_CLANG
#		if   !__is_identifier(_Float128)
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef _Float128      mu0_fp128_t;
#		elif !__is_identifier(_Float128x)
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef _Float128x     mu0_fp128_t;
#		elif !__is_identifier(__float128)
#		if ((defined(__STDC_IEC_60559_TYPES__) || defined(__STDC_IEC_559__)) && defined(FLT128_MAX)) || defined(__FLOAT128__) || defined(__SIZEOF_FLOAT128__)
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef __float128     mu0_fp128_t;
#		endif
#		endif
#	elif MU0_HAVE_CC_GNUCC
#		if ((defined(__STDC_IEC_60559_TYPES__) || defined(__STDC_IEC_559__)) && defined(FLT128_MAX)) || defined(__FLOAT128__) || defined(__SIZEOF_FLOAT128__)
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef _Float128      mu0_fp128_t;
#		endif
#	endif
#	endif

#	if !MU0_HAVE_FLOAT128
typedef long double             mu0_fp128_t;
#	endif

#	if MU0_USE_FLOAT64
#	if   MU0_HAVE_CC_CLANG
#		if !__is_identifier(_Float64)
#			undef  MU0_HAVE_FLOAT64
#			define MU0_HAVE_FLOAT64 1
			__mu0_extension__
			typedef _Float64       mu0_fp64_t;;
#		endif
#	elif MU0_HAVE_CC_GNUCC
#			undef  MU0_HAVE_FLOAT64
#			define MU0_HAVE_FLOAT64 1
		__mu0_extension__
		typedef _Float64          mu0_fp64_t;
#	endif
#	endif

#	if !MU0_HAVE_FLOAT64
typedef double                  mu0_fp64_t;
#	endif

#	if MU0_USE_FLOAT32
#	if   MU0_HAVE_CC_CLANG
#		if !__is_identifier(_Float32)
#			undef  MU0_HAVE_FLOAT32
#			define MU0_HAVE_FLOAT32 1
			__mu0_extension__
			typedef _Float32       mu0_fp32_t;
#		endif
#	elif MU0_HAVE_CC_GNUCC
#			undef  MU0_HAVE_FLOAT32
#			define MU0_HAVE_FLOAT32 1
		__mu0_extension__
		typedef _Float32          mu0_fp32_t;
#	endif
#	endif

#	if !MU0_HAVE_FLOAT32
typedef float                   mu0_fp32_t;
#	endif

#	if MU0_USE_FLOAT16
#	if   MU0_HAVE_CC_CLANG
#		if !__is_identifier(_Float16)
#			undef  MU0_HAVE_FLOAT16
#			define MU0_HAVE_FLOAT16 1
			__mu0_extension__
			typedef _Float16       mu0_fp16_t;
#		elif !__is_identifier(__fp16)
#			undef  MU0_HAVE_FLOAT16
#			define MU0_HAVE_FLOAT16 1
			__mu0_extension__
			typedef __fp16         mu0_fp16_t;
#		endif
#	elif MU0_HAVE_CC_GNUCC && MU0_HAVE_ARM64
#		undef  MU0_HAVE_FLOAT16
#		define MU0_HAVE_FLOAT16 1
		__mu0_extension__
		typedef _Float16          mu0_fp16_t;
#	endif
#	endif

#	if !MU0_HAVE_FLOAT16
typedef float                   mu0_fp16_t;
#	endif

#	define mu0_fpex(__x)         __mu0_cast__(mu0_fpex_t, __x)
#	define mu0_const_fpex(__x)   __mu0_const_cast__(mu0_fpex_t, __x)

#	define mu0_fp128(__x)        __mu0_cast__(mu0_fp128_t, __x)
#	define mu0_const_fp128(__x)  __mu0_const_cast__(mu0_fp128_t, __x)

#	define mu0_fp64(__x)         __mu0_cast__(mu0_fp64_t, __x)
#	define mu0_const_fp64(__x)   __mu0_const_cast__(mu0_fp64_t, __x)

#	define mu0_fp32(__x)         __mu0_cast__(mu0_fp32_t, __x)
#	define mu0_const_fp32(__x)   __mu0_const_cast__(mu0_fp32_t, __x)

#	define mu0_fp16(__x)         __mu0_cast__(mu0_fp16_t, __x)
#	define mu0_const_fp16(__x)   __mu0_const_cast__(mu0_fp16_t, __x)

#	if   MU0_HAVE_GENERIC
#	if   MU0_HAVE_FLOAT128 && MU0_HAVE_FLOAT16
#	define mu0_is_floating_point(__x) __mu0_generic__((__x) + 0U \
		, mu0_fp128_t : 1                                         \
		, mu0_fp64_t  : 1                                         \
		, mu0_fp32_t  : 1                                         \
		, mu0_fp16_t  : 1                                         \
		, default     : 0                                         \
	)
#	elif  MU0_HAVE_FLOAT128
#	define mu0_is_floating_point(__x) __mu0_generic__((__x) + 0U \
		, mu0_fp128_t : 1                                         \
		, mu0_fp64_t  : 1                                         \
		, mu0_fp32_t  : 1                                         \
		, default     : 0                                         \
	)
#	elif  MU0_HAVE_FLOAT16
#	define mu0_is_floating_point(__x) __mu0_generic__((__x) + 0U \
		, mu0_fpex_t : 1                                          \
		, mu0_fp64_t : 1                                          \
		, mu0_fp32_t : 1                                          \
		, mu0_fp16_t : 1                                          \
		, default    : 0                                          \
	)
#	else
#	define mu0_is_floating_point(__x) __mu0_generic__((__x) + 0U \
		, mu0_fpex_t : 1                                          \
		, mu0_fp64_t : 1                                          \
		, mu0_fp32_t : 1                                          \
		, default    : 0                                          \
	)
#	endif
#	elif MU0_HAVE_TYPEOF
#	define mu0_is_floating_point(__x)        \
	((                                       \
		   __mu0_isofkind__(mu0_fp128_t, __x) \
		|| __mu0_isofkind__(mu0_fp64_t , __x) \
		|| __mu0_isofkind__(mu0_fp32_t , __x) \
		|| __mu0_isofkind__(mu0_fp16_t , __x) \
	) ? 1 : 0)
#	else
#	define mu0_is_floating_point(__x) (1)
#	endif

MU0_END_CDECL

#endif /* !MU0_FLOATING_H */

/* EOF */