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

#	undef  MU0_USE_STDCOMPLEX
#	undef  MU0_HAVE_STDCOMPLEX

#	define MU0_HAVE_FASTMATH   0

#	define MU0_USE_FLOAT128    1
#	define MU0_HAVE_FLOAT128   0

#	define MU0_USE_FLOAT64     1
#	define MU0_HAVE_FLOAT64    0

#	define MU0_USE_FLOAT32     1
#	define MU0_HAVE_FLOAT32    0

#	define MU0_USE_FLOAT16     1
#	define MU0_HAVE_FLOAT16    0

#	define MU0_USE_STDCOMPLEX  0
#	define MU0_HAVE_STDCOMPLEX 0

#	if MU0_USE_FLOAT128 || MU0_USE_FLOAT64 || MU0_USE_FLOAT32 || MU0_USE_FLOAT16
#		undef  __STDC_WANT_IEC_60559_TYPES_EXT__
#		define __STDC_WANT_IEC_60559_TYPES_EXT__ 1
#	endif

#	include <fenv.h>
#	include <float.h>
#	include <math.h>

#	if MU0_USE_STDCOMPLEX
#	if MU0_HAVE_POSIX1_2001
#	if !defined(__STDC_NO_COMPLEX__)
#		include <complex.h>
#		if __STDC_IEC_559_COMPLEX__
# 			if !defined(_Imaginary_I) && defined(_Complex_I)
#				define _Imaginary_I _Complex_I
#			endif
#		endif
# 		if (defined(_Imaginary_I) || defined(_Complex_I))
#			undef  MU0_HAVE_STDCOMPLEX
#			define MU0_HAVE_STDCOMPLEX 1
#		endif
#	endif
#	endif
#	endif

MU0_BEGIN_CDECL

#	define mu0_fp_ilogb0                                FP_ILOGB0
#	define mu0_fp_ilogbnan                              FP_ILOGBNAN

#	define mu0_fp_classify_infinite                     FP_INFINITE
#	define mu0_fp_classify_nan                          FP_NAN
#	define mu0_fp_classify_normal                       FP_NORMAL
#	define mu0_fp_classify_subnormal                    FP_SUBNORMAL
#	define mu0_fp_classify_zero                         FP_ZERO

#	define mu0_fp_classify(x)                           fpclassify(x)
#	define mu0_fp_isfinite(x)                           isfinite(x)
#	define mu0_fp_isgreater(x, y)                       isgreater(x, y)
#	define mu0_fp_isgreaterequal(x, y)                  isgreaterequal(x, y)
#	define mu0_fp_isinf(x)                              isinf(x)
#	define mu0_fp_isless(x, y)                          isless(x, y)
#	define mu0_fp_islessequal(x, y)                     islessequal(x, y)
#	define mu0_fp_islessgreater(x, y)                   islessgreater(x, y)
#	define mu0_fp_isnan(x)                              isnan(x)
#	define mu0_fp_isnormal(x)                           isnormal(x)
#	define mu0_fp_isunordered(x, y)                     isunordered(x, y)
#	define mu0_fp_signbit(x)                            signbit(x)

typedef long double                                    mu0_fpex_t;
#	if MU0_HAVE_STDCOMPLEX
typedef long double _Complex                           mu0_cpex_t;
#	endif

#	if MU0_USE_FLOAT128
#	if   MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCCC
#		if   !__is_identifier(_Float128) && defined(__FLT128_MAX__) && __clang_major__ >= 16
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef _Float128                             mu0_fp128_t;
#		if MU0_HAVE_STDCOMPLEX
			typedef _Float128 _Complex                    mu0_cfp128_t;
#		endif
#		elif !__is_identifier(_Float128x) && defined(__FLT128_MAX__)
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef _Float128x                            mu0_fp128_t;
#		if MU0_HAVE_STDCOMPLEX
			typedef _Float128x _Complex                   mu0_cfp128_t;
#		endif
#		elif !__is_identifier(__float128) && defined(__FLT128_MAX__)
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef __float128                            mu0_fp128_t;
#		if MU0_HAVE_STDCOMPLEX
			typedef __float128 _Complex                   mu0_cfp128_t;
#		endif
#		endif
#	elif MU0_HAVE_CC_GNUCC
#		if defined(__FLT128_MAX__)
#			undef  MU0_HAVE_FLOAT128
#			define MU0_HAVE_FLOAT128 1
			__mu0_extension__
			typedef _Float128                             mu0_fp128_t;
#		if MU0_HAVE_STDCOMPLEX
			typedef _Float128 _Complex                    mu0_cfp128_t;
#		endif
#		endif
#	endif
#	endif

#	if !MU0_HAVE_FLOAT128
typedef long double                                    mu0_fp128_t;
#	if MU0_HAVE_STDCOMPLEX
typedef long double _Complex                           mu0_cfp128_t;
#	endif
#	endif

#	if !MU0_HAVE_STDCOMPLEX
typedef struct { mu0_fp128_t u_re; mu0_fp128_t u_im; } mu0_cfp128_t;
#	if MU0_HAVE_C11
#	define mu0_cfp128(__re, __im)                {         __mu0_const_cast__(mu0_fp128_t, __re),         __mu0_const_cast__(mu0_fp128_t, __im) }
#	else
#	define mu0_cfp128(__re, __im) (mu0_cfp128_t) { .u_re = __mu0_const_cast__(mu0_fp128_t, __re), .u_im = __mu0_const_cast__(mu0_fp128_t, __im) }
#	endif
#	else
#	if __STDC_IEC_559_COMPLEX__
#	define mu0_cfp128(__re, __im) (__mu0_cast__(mu0_cfp128_t, (__mu0_const_cast__(mu0_fp128_t, __re) + _Imaginary_I * __mu0_const_cast__(mu0_fp128_t, __im))))
#	else
#	define mu0_cfp128(__re, __im) (__mu0_cast__(mu0_cfp128_t, (__mu0_const_cast__(mu0_fp128_t, __re) + _Complex_I   * __mu0_const_cast__(mu0_fp128_t, __im))))
#	endif
#	endif

#	if MU0_USE_FLOAT64
#	if   MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCCC
#		if !__is_identifier(_Float64)
#			undef  MU0_HAVE_FLOAT64
#			define MU0_HAVE_FLOAT64 1
			__mu0_extension__
			typedef _Float64                              mu0_fp64_t;
#			if MU0_HAVE_STDCOMPLEX
			typedef _Float64 _Complex                     mu0_cfp64_t;
#			endif
#		endif
#	elif MU0_HAVE_CC_GNUCC
#			undef  MU0_HAVE_FLOAT64
#			define MU0_HAVE_FLOAT64 1
		__mu0_extension__
		typedef _Float64                                 mu0_fp64_t;
#		if MU0_HAVE_STDCOMPLEX
		typedef _Float64 _Complex                        mu0_cfp64_t;
#		endif
#	endif
#	endif

#	if !MU0_HAVE_FLOAT64
typedef double                                         mu0_fp64_t;
#	if MU0_HAVE_STDCOMPLEX
typedef double _Complex                                mu0_cfp64_t;
#	endif
#	endif

#	if !MU0_HAVE_STDCOMPLEX
typedef struct { mu0_fp64_t u_re; mu0_fp64_t u_im; }   mu0_cfp64_t;
#	if MU0_HAVE_C11
#	define mu0_cfp64(__re, __im)               {         __mu0_const_cast__(mu0_fp64_t, __re),         __mu0_const_cast__(mu0_fp64_t, __im) }
#	else
#	define mu0_cfp64(__re, __im) (mu0_cfp64_t) { .u_re = __mu0_const_cast__(mu0_fp64_t, __re), .u_im = __mu0_const_cast__(mu0_fp64_t, __im) }
#	endif
#	else
#	if __STDC_IEC_559_COMPLEX__
#	define mu0_cfp64(__re, __im) (__mu0_cast__(mu0_cfp64_t, (__mu0_const_cast__(mu0_fp64_t, __re) + _Imaginary_I * __mu0_const_cast__(mu0_fp64_t, __im))))
#	else
#	define mu0_cfp64(__re, __im) (__mu0_cast__(mu0_cfp64_t, (__mu0_const_cast__(mu0_fp64_t, __re) + _Complex_I   * __mu0_const_cast__(mu0_fp64_t, __im))))
#	endif
#	endif

#	if MU0_USE_FLOAT32
#	if   MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCCC
#		if !__is_identifier(_Float32)
#			undef  MU0_HAVE_FLOAT32
#			define MU0_HAVE_FLOAT32 1
			__mu0_extension__
			typedef _Float32                              mu0_fp32_t;
#			if MU0_HAVE_STDCOMPLEX
			typedef _Float32 _Complex                     mu0_cfp32_t;
#			endif
#		endif
#	elif MU0_HAVE_CC_GNUCC
#			undef  MU0_HAVE_FLOAT32
#			define MU0_HAVE_FLOAT32 1
		__mu0_extension__
		typedef _Float32                                 mu0_fp32_t;
#		if MU0_HAVE_STDCOMPLEX
		typedef _Float32 _Complex                        mu0_cfp32_t;
#		endif
#	endif
#	endif

#	if !MU0_HAVE_FLOAT32
typedef float                                          mu0_fp32_t;
#	if MU0_HAVE_STDCOMPLEX
typedef float _Complex                                 mu0_cfp32_t;
#	endif
#	endif

#	if !MU0_HAVE_STDCOMPLEX
typedef struct { mu0_fp32_t u_re; mu0_fp32_t u_im; }   mu0_cfp32_t;
#	if MU0_HAVE_C11
#	define mu0_cfp32(__re, __im)               {         __mu0_const_cast__(mu0_fp32_t, __re),         __mu0_const_cast__(mu0_fp32_t, __im) }
#	else
#	define mu0_cfp32(__re, __im) (mu0_cfp32_t) { .u_re = __mu0_const_cast__(mu0_fp32_t, __re), .u_im = __mu0_const_cast__(mu0_fp32_t, __im) }
#	endif
#	else
#	if __STDC_IEC_559_COMPLEX__
#	define mu0_cfp32(__re, __im) (__mu0_cast__(mu0_cfp32_t, (__mu0_const_cast__(mu0_fp32_t, __re) + _Imaginary_I * __mu0_const_cast__(mu0_fp32_t, __im))))
#	else
#	define mu0_cfp32(__re, __im) (__mu0_cast__(mu0_cfp32_t, (__mu0_const_cast__(mu0_fp32_t, __re) + _Complex_I   * __mu0_const_cast__(mu0_fp32_t, __im))))
#	endif
#	endif

#	if MU0_USE_FLOAT16
#	if   MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCCC
#		if !__is_identifier(_Float16) && defined(__FLT16_MAX__) && __clang_major__ >= 16
#			undef  MU0_HAVE_FLOAT16
#			define MU0_HAVE_FLOAT16 1
			__mu0_extension__
			typedef _Float16                              mu0_fp16_t;
#		if MU0_HAVE_STDCOMPLEX
			typedef _Float16 _Complex                     mu0_cfp16_t;
#		endif
#		elif !__is_identifier(__fp16) && defined(__FLT16_MAX__) && __clang_major__ >= 16
#			undef  MU0_HAVE_FLOAT16
#			define MU0_HAVE_FLOAT16 1
			__mu0_extension__
			typedef __fp16                                mu0_fp16_t;
#		if MU0_HAVE_STDCOMPLEX
			typedef __fp16 _Complex                       mu0_cfp16_t;
#		endif
#		endif
#	elif MU0_HAVE_CC_GNUCC
#		if defined(__FLT16_MAX__)
#			undef  MU0_HAVE_FLOAT16
#			define MU0_HAVE_FLOAT16 1
			__mu0_extension__
			typedef _Float16                              mu0_fp16_t;
#		if MU0_HAVE_STDCOMPLEX
			typedef _Float16 _Complex                     mu0_cfp16_t;
#		endif
#		endif
#	endif
#	endif

#	if !MU0_HAVE_FLOAT16
typedef float                                          mu0_fp16_t;
#	if MU0_HAVE_STDCOMPLEX
typedef float _Complex                                 mu0_cfp16_t;
#	endif
#	endif

#	if !MU0_HAVE_STDCOMPLEX
typedef struct { mu0_fp16_t u_re; mu0_fp16_t u_im; }   mu0_cfp16_t;
#	if MU0_HAVE_C11
#	define mu0_cfp16(__re, __im)               {         __mu0_const_cast__(mu0_fp16_t, __re),         __mu0_const_cast__(mu0_fp16_t, __im) }
#	else
#	define mu0_cfp16(__re, __im) (mu0_cfp16_t) { .u_re = __mu0_const_cast__(mu0_fp16_t, __re), .u_im = __mu0_const_cast__(mu0_fp16_t, __im) }
#	endif
#	else
#	if __STDC_IEC_559_COMPLEX__
#	define mu0_cfp16(__re, __im) (__mu0_cast__(mu0_cfp16_t, (__mu0_const_cast__(mu0_fp16_t, __re) + _Imaginary_I * __mu0_const_cast__(mu0_fp16_t, __im))))
#	else
#	define mu0_cfp16(__re, __im) (__mu0_cast__(mu0_cfp16_t, (__mu0_const_cast__(mu0_fp16_t, __re) + _Complex_I   * __mu0_const_cast__(mu0_fp16_t, __im))))
#	endif
#	endif

#	define mu0_fpex(__x)        __mu0_cast__(mu0_fpex_t, __x)
#	define mu0_const_fpex(__x)  __mu0_const_cast__(mu0_fpex_t, __x)

#	define mu0_fp128(__x)       __mu0_cast__(mu0_fp128_t, __x)
#	define mu0_const_fp128(__x) __mu0_const_cast__(mu0_fp128_t, __x)

#	define mu0_fp64(__x)        __mu0_cast__(mu0_fp64_t, __x)
#	define mu0_const_fp64(__x)  __mu0_const_cast__(mu0_fp64_t, __x)

#	define mu0_fp32(__x)        __mu0_cast__(mu0_fp32_t, __x)
#	define mu0_const_fp32(__x)  __mu0_const_cast__(mu0_fp32_t, __x)

#	define mu0_fp16(__x)        __mu0_cast__(mu0_fp16_t, __x)
#	define mu0_const_fp16(__x)  __mu0_const_cast__(mu0_fp16_t, __x)

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

#	if MU0_HAVE_FLOAT128

#	define __mu0_fp128_const__(__c) __c

__mu0_static__ const mu0_fp128_t mu0_fp128_max_exp = FLT128_MAX_EXP;
__mu0_static__ const mu0_fp128_t mu0_fp128_log_max = __mu0_fp128_const__(11356.0);

__mu0_static__ const mu0_fp128_t mu0_fp128_max     = FLT128_MAX;
__mu0_static__ const mu0_fp128_t mu0_fp128_min     = FLT128_MIN;
__mu0_static__ const mu0_fp128_t mu0_fp128_nan     = NAN;
__mu0_static__ const mu0_fp128_t mu0_fp128_inf     = INFINITY;
__mu0_static__ const mu0_fp128_t mu0_fp128_zero    = __mu0_fp128_const__(0.0);
__mu0_static__ const mu0_fp128_t mu0_fp128_half    = __mu0_fp128_const__(0.5);
__mu0_static__ const mu0_fp128_t mu0_fp128_one     = __mu0_fp128_const__(1.0);
__mu0_static__ const mu0_fp128_t mu0_fp128_two     = __mu0_fp128_const__(2.0);
__mu0_static__ const mu0_fp128_t mu0_fp128_ten     = __mu0_fp128_const__(10.0);

#	else

#	define __mu0_fp128_const__(__c) __c ## L

__mu0_static__ const mu0_fp128_t mu0_fp128_max_exp = LDBL_MAX_EXP;
__mu0_static__ const mu0_fp128_t mu0_fp128_log_max = __mu0_fp128_const__(11356.0);

__mu0_static__ const mu0_fp128_t mu0_fp128_max     = LDBL_MAX;
__mu0_static__ const mu0_fp128_t mu0_fp128_min     = LDBL_MIN;
__mu0_static__ const mu0_fp128_t mu0_fp128_nan     = NAN;
__mu0_static__ const mu0_fp128_t mu0_fp128_inf     = INFINITY;
__mu0_static__ const mu0_fp128_t mu0_fp128_zero    = __mu0_fp128_const__(0.0);
__mu0_static__ const mu0_fp128_t mu0_fp128_half    = __mu0_fp128_const__(0.5);
__mu0_static__ const mu0_fp128_t mu0_fp128_one     = __mu0_fp128_const__(1.0);
__mu0_static__ const mu0_fp128_t mu0_fp128_two     = __mu0_fp128_const__(2.0);
__mu0_static__ const mu0_fp128_t mu0_fp128_ten     = __mu0_fp128_const__(10.0);

#	endif

#	define __mu0_fp64_const__(__c) __c

__mu0_static__ const mu0_fp32_t  mu0_fp64_max_exp  = DBL_MAX_EXP;
__mu0_static__ const mu0_fp32_t  mu0_fp64_log_max  = __mu0_fp64_const__(709.0);

__mu0_static__ const mu0_fp64_t  mu0_fp64_max      = DBL_MAX;
__mu0_static__ const mu0_fp64_t  mu0_fp64_min      = DBL_MIN;
__mu0_static__ const mu0_fp64_t  mu0_fp64_nan      = NAN;
__mu0_static__ const mu0_fp64_t  mu0_fp64_inf      = INFINITY;
__mu0_static__ const mu0_fp64_t  mu0_fp64_zero     = __mu0_fp64_const__(0.0);
__mu0_static__ const mu0_fp64_t  mu0_fp64_half     = __mu0_fp64_const__(0.5);
__mu0_static__ const mu0_fp64_t  mu0_fp64_one      = __mu0_fp64_const__(1.0);
__mu0_static__ const mu0_fp64_t  mu0_fp64_two      = __mu0_fp64_const__(2.0);
__mu0_static__ const mu0_fp64_t  mu0_fp64_ten      = __mu0_fp64_const__(10.0);

#	define __mu0_fp32_const__(__c) __c ## f

__mu0_static__ const mu0_fp32_t  mu0_fp32_max_exp  = FLT_MAX_EXP;
__mu0_static__ const mu0_fp32_t  mu0_fp32_log_max  = __mu0_fp32_const__(88.0);

__mu0_static__ const mu0_fp32_t  mu0_fp32_max      = FLT_MAX;
__mu0_static__ const mu0_fp32_t  mu0_fp32_min      = FLT_MIN;
__mu0_static__ const mu0_fp32_t  mu0_fp32_nan      = NAN;
__mu0_static__ const mu0_fp32_t  mu0_fp32_inf      = INFINITY;
__mu0_static__ const mu0_fp32_t  mu0_fp32_zero     = __mu0_fp32_const__(0.0);
__mu0_static__ const mu0_fp32_t  mu0_fp32_half     = __mu0_fp32_const__(0.5);
__mu0_static__ const mu0_fp32_t  mu0_fp32_one      = __mu0_fp32_const__(1.0);
__mu0_static__ const mu0_fp32_t  mu0_fp32_two      = __mu0_fp32_const__(2.0);
__mu0_static__ const mu0_fp32_t  mu0_fp32_ten      = __mu0_fp32_const__(10.0);

#	if MU0_HAVE_FLOAT16

#	define __mu0_fp16_const__(__c) __c ## f

__mu0_static__ const mu0_fp16_t  mu0_fp16_max_exp  = FLT16_MAX_EXP;
__mu0_static__ const mu0_fp16_t  mu0_fp16_log_max  = __mu0_fp16_const__(11.0);

__mu0_static__ const mu0_fp16_t  mu0_fp16_max      = FLT16_MAX;
__mu0_static__ const mu0_fp16_t  mu0_fp16_min      = FLT16_MIN;
__mu0_static__ const mu0_fp16_t  mu0_fp16_nan      = NAN;
__mu0_static__ const mu0_fp16_t  mu0_fp16_inf      = INFINITY;
__mu0_static__ const mu0_fp16_t  mu0_fp16_zero     = __mu0_fp16_const__(0.0);
__mu0_static__ const mu0_fp16_t  mu0_fp16_half     = __mu0_fp16_const__(0.5);
__mu0_static__ const mu0_fp16_t  mu0_fp16_one      = __mu0_fp16_const__(1.0);
__mu0_static__ const mu0_fp16_t  mu0_fp16_two      = __mu0_fp16_const__(2.0);
__mu0_static__ const mu0_fp16_t  mu0_fp16_ten      = __mu0_fp16_const__(10.0);

#	else

#	define __mu0_fp16_const__(__c) __c ## f

__mu0_static__ const mu0_fp16_t  mu0_fp16_max_exp  = FLT_MAX_EXP;
__mu0_static__ const mu0_fp16_t  mu0_fp16_log_max  = __mu0_fp16_const__(88.0);
__mu0_static__ const mu0_fp16_t  mu0_fp16_max      = FLT_MAX;
__mu0_static__ const mu0_fp16_t  mu0_fp16_min      = FLT_MIN;
__mu0_static__ const mu0_fp16_t  mu0_fp16_nan      = NAN;
__mu0_static__ const mu0_fp16_t  mu0_fp16_inf      = INFINITY;
__mu0_static__ const mu0_fp16_t  mu0_fp16_zero     = __mu0_fp16_const__(0.0);
__mu0_static__ const mu0_fp16_t  mu0_fp16_half     = __mu0_fp16_const__(0.5);
__mu0_static__ const mu0_fp16_t  mu0_fp16_one      = __mu0_fp16_const__(1.0);
__mu0_static__ const mu0_fp16_t  mu0_fp16_two      = __mu0_fp16_const__(2.0);
__mu0_static__ const mu0_fp16_t  mu0_fp16_ten      = __mu0_fp16_const__(10.0);

#	endif

MU0_END_CDECL

#endif /* !MU0_FLOATING_H */

/* EOF */