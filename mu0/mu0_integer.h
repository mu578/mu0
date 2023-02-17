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

// mu0_integer.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition.h>

#ifndef MU0_INTEGER_H
#define MU0_INTEGER_H 1

#	undef  MU0_USE_INT128
#	undef  MU0_HAVE_INT128

#	define MU0_USE_INT128  1
#	define MU0_HAVE_INT128 0

#	include <stdint.h>
#	include <stdbool.h>
#	include <inttypes.h>

MU0_BEGIN_CDECL

typedef   ptrdiff_t                     mu0_ptrdiff_t;
typedef   uintmax_t                     mu0_uintmax_t;
typedef   intmax_t                      mu0_sintmax_t;

typedef   size_t                        mu0_usize_t;
typedef   ssize_t                       mu0_ssize_t;
typedef   off_t                         mu0_index_t;

#	if MU0_USE_INT128
#	if   MU0_HAVE_CC_CLANG
#		if !__is_identifier(__int128_t)
#			undef  MU0_HAVE_INT128
#			define MU0_HAVE_INT128 1
			__mu0_extension__
			typedef __uint128_t            mu0_uint128_t;
			__mu0_extension__
			typedef __int128_t             mu0_sint128_t;
#		else
			typedef uint64_t               mu0_uint128_t;
			typedef int64_t                mu0_sint128_t;
#		endif
#	elif MU0_HAVE_CC_GNUCC
#		if MU0_HAVE_X64
#			undef  MU0_HAVE_INT128
#			define MU0_HAVE_INT128 1
			__mu0_extension__
			typedef unsigned __int128      mu0_uint128_t;
			__mu0_extension__
			typedef __int128               mu0_sint128_t;
#		endif
#	endif
#	endif

#	if !MU0_HAVE_INT128
typedef uint64_t                        mu0_uint128_t;
typedef int64_t                         mu0_sint128_t;
#	endif

typedef   uint64_t                      mu0_uint64_t;
typedef   int64_t                       mu0_sint64_t;

typedef   uint32_t                      mu0_uint32_t;
typedef   int32_t                       mu0_sint32_t;

typedef   uint16_t                      mu0_uint16_t;
typedef   int16_t                       mu0_sint16_t;

typedef   uint8_t                       mu0_uint8_t;
typedef   int8_t                        mu0_sint8_t;

typedef   bool                          mu0_bool_t;
#	define mu0_true                      true
#	define mu0_false                     false

#	define mu0_uintmax(__x)              mu0_cast(mu0_uintmax_t, __x)
#	define mu0_const_uintmax(__x)        mu0_const_cast(mu0_uinmax_t, __x)

#	define mu0_uint128(__x)              mu0_cast(mu0_uint128_t, __x)
#	define mu0_const_uint128(__x)        mu0_const_cast(mu0_uin128_t, __x)

#	define mu0_uint64(__x)               mu0_cast(mu0_uint64_t, __x)
#	define mu0_const_uint64(__x)         mu0_const_cast(mu0_uint64_t, __x)
#	define mu0_sint64(__x)               mu0_cast(mu0_sint64_t, __x)
#	define mu0_const_sint64(__x)         mu0_const_cast(mu0_sint64_t, __x)

#	define mu0_uint32(__x)               mu0_cast(mu0_uint32_t, __x)
#	define mu0_const_uint32(__x)         mu0_const_cast(mu0_uint32_t, __x)
#	define mu0_sint32(__x)               mu0_cast(mu0_sint32_t, __x)
#	define mu0_const_sint32(__x)         mu0_const_cast(mu0_sint32_t, __x)

#	define mu0_uint16(__x)               mu0_cast(mu0_uint16_t, __x)
#	define mu0_const_uint16(__x)         mu0_const_cast(mu0_uint16_t, __x)
#	define mu0_sint16(__x)               mu0_cast(mu0_sint16_t, __x)
#	define mu0_const_sint16(__x)         mu0_const_cast( mu0_sint16_t, __x)

#	define mu0_uint8(__x)                mu0_cast(mu0_uint8_t, __x)
#	define mu0_const_uint8(__x)          mu0_const_cast(mu0_uint8_t, __x)
#	define mu0_sint8(__x)                mu0_cast(mu0_sint8_t, __x)
#	define mu0_const_sint8(__x)          mu0_const_cast(mu0_sint8_t, __x)

typedef   mu0_uint64_t                  mu0_uinteger_t;

#	define mu0_uinteger(__x)             mu0_cast(mu0_uinteger_t, __x)
#	define mu0_const_uinteger(__x)       mu0_const_cast(mu0_uinteger_t, __x)

typedef   mu0_sint64_t                  mu0_sinteger_t;

#	define mu0_sinteger(__x)             mu0_cast(mu0_ssinteger_t, __x)
#	define mu0_const_sinteger(__x)       mu0_const_cast(mu0_ssinteger_t, __x)

typedef   mu0_ptrdiff_t                 mu0_difference_t;

#	define mu0_difference(__x)           mu0_cast(mu0_difference_t, __x)
#	define mu0_const_difference(__x)     mu0_const_cast(mu0_difference_t, __x)

typedef   mu0_ptrdiff_t                 mu0_distance_t;

#	define mu0_distance(__x)             mu0_cast(mu0_distance_t, __x)
#	define mu0_const_distance(__x)       mu0_const_cast(mu0_distance_t, __x)

typedef   mu0_uint128_t *               mu0_vuint128_t;
typedef   mu0_sint128_t *               mu0_vsint128_t;

typedef   mu0_uint64_t *                mu0_vuint64_t;
typedef   mu0_sint64_t *                mu0_vsint64_t;

typedef   mu0_uint32_t *                mu0_vuint32_t;
typedef   mu0_sint32_t *                mu0_vsint32_t;

typedef   mu0_uint16_t *                mu0_vuint16_t;
typedef   mu0_sint16_t *                mu0_vsint16_t;

typedef   mu0_uint8_t  *                mu0_vuint8_t;
typedef   mu0_sint8_t  *                mu0_vsint8_t;

#	define mu0_vuint128(__x)             mu0_cast(mu0_vuint128_t, __x)
#	define mu0_const_vuint128(__x)       mu0_const_cast(mu0_vuint128_t, __x)
#	define mu0_vsint128(__x)             mu0_cast(mu0_vsint128_t, __x)
#	define mu0_const_vsint128(__x)       mu0_const_cast(mu0_vsint128_t, __x)

#	define mu0_vuint64(__x)              mu0_cast(mu0_vuint64_t, __x)
#	define mu0_const_vuint64(__x)        mu0_const_cast(mu0_vuint64_t, __x)
#	define mu0_vsint64(__x)              mu0_cast(mu0_vsint64_t, __x)
#	define mu0_const_vsint64(__x)        mu0_const_cast(mu0_vsint64_t, __x)

#	define mu0_vuint32(__x)              mu0_cast(mu0_vuint32_t, __x)
#	define mu0_const_vuint32(__x)        mu0_const_cast(mu0_vuint32_t, __x)
#	define mu0_vsint32(__x)              mu0_cast(mu0_vsint32_t, __x)
#	define mu0_const_vsint32(__x)        mu0_const_cast(mu0_vsint32_t, __x)

#	define mu0_vuint16(__x)              mu0_cast(mu0_vuint16_t, __x)
#	define mu0_const_vuint16(__x)        mu0_const_cast(mu0_vuint16_t, __x)
#	define mu0_vsint16(__x)              mu0_cast(mu0_vsint16_t, __x)
#	define mu0_const_vsint16(__x)        mu0_const_cast( mu0_vsint16_t, __x)

#	define mu0_vuint8(__x)               mu0_cast(mu0_vuint8_t, __x)
#	define mu0_const_vuint8(__x)         mu0_const_cast(mu0_vuint8_t, __x)
#	define mu0_vsint8(__x)               mu0_cast(mu0_vsint8_t, __x)
#	define mu0_const_vsint8(__x)         mu0_const_cast(mu0_vsint8_t, __x)

#	if MU0_HAVE_TYPEOF
#	define mu0_is_sinteger(__x)                \
	((                                         \
		   __mu0_isoftype__(m0_sint64_t  , __x) \
		|| __mu0_isoftype__(m0_sint32_t  , __x) \
		|| __mu0_isoftype__(m0_sint16_t  , __x) \
		|| __mu0_isoftype__(m0_sint8_t   , __x) \
		|| __mu0_isoftype__(mu0_ptrdiff_t, __x) \
	) ? 1 : 0)

#	define mu0_is_uinteger(__x)              \
	((                                       \
		   __mu0_isoftype__(m0_uint64_t, __x) \
		|| __mu0_isoftype__(m0_uint32_t, __x) \
		|| __mu0_isoftype__(m0_uint16_t, __x) \
		|| __mu0_isoftype__(m0_uint8_t , __x) \
	) ? 1 : 0)
#	else
#	define mu0_is_sinteger(__x) (1)
#	define mu0_is_uinteger(__x) (1)
#	endif

#	if MU0_HAVE_INT128
__mu0_static__ const mu0_uint128_t mu0_uint128_max = UINT128_MAX;
__mu0_static__ const mu0_uint128_t mu0_uint128_min = 0U;
__mu0_static__ const mu0_sint128_t mu0_sint128_max = INT128_MAX;
__mu0_static__ const mu0_sint128_t mu0_sint128_min = INT128_MIN;
#	else
__mu0_static__ const mu0_uint128_t mu0_uint128_max = UINT64_MAX;
__mu0_static__ const mu0_uint128_t mu0_uint128_min = 0U;
__mu0_static__ const mu0_sint128_t mu0_sint128_max = INT64_MAX;
__mu0_static__ const mu0_sint128_t mu0_sint128_min = INT64_MIN;
#	endif

__mu0_static__ const mu0_uint64_t  mu0_uint64_max  = UINT64_MAX;
__mu0_static__ const mu0_uint64_t  mu0_uint64_min  = 0U;
__mu0_static__ const mu0_sint64_t  mu0_sint64_max  = INT64_MAX;
__mu0_static__ const mu0_sint64_t  mu0_sint64_min  = INT64_MIN;

__mu0_static__ const mu0_uint32_t  mu0_uint32_max  = UINT32_MAX;
__mu0_static__ const mu0_uint32_t  mu0_uint32_min  = 0U;
__mu0_static__ const mu0_sint32_t  mu0_sint32_max  = INT32_MAX;
__mu0_static__ const mu0_sint32_t  mu0_sint32_min  = INT32_MIN;

__mu0_static__ const mu0_uint16_t  mu0_uint16_max  = UINT16_MAX;
__mu0_static__ const mu0_uint16_t  mu0_uint16_min  = 0U;
__mu0_static__ const mu0_sint16_t  mu0_sint16_max  = INT16_MAX;
__mu0_static__ const mu0_sint16_t  mu0_sint16_min  = INT16_MIN;

__mu0_static__ const mu0_uint8_t   mu0_uint8_max    = UINT8_MAX;
__mu0_static__ const mu0_uint8_t   mu0_uint8_min    = 0U;
__mu0_static__ const mu0_sint8_t   mu0_sint8_max    = INT8_MAX;
__mu0_static__ const mu0_sint8_t   mu0_sint8_min    = INT8_MIN;

MU0_END_CDECL

#endif /* !MU0_INTEGER_H */

/* EOF */