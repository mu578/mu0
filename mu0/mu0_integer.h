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

#	if MU0_USE_INT128
#	if   MU0_HAVE_CC_CLANG
#		if !__is_identifier(__int128_t)
#			undef  MU0_HAVE_INT128
#			define MU0_HAVE_INT128 1
			__mu0_extension__
			typedef __uint128_t        mu0_uint128_t;
			__mu0_extension__
			typedef __int128_t         mu0_sint128_t;
#		endif
#	elif MU0_HAVE_CC_GNUCC
#		if MU0_HAVE_X64
#			undef  MU0_HAVE_INT128
#			define MU0_HAVE_INT128 1
			__mu0_extension__
			typedef unsigned __int128  mu0_uint128_t;
			__mu0_extension__
			typedef __int128           mu0_sint128_t;
#		endif
#	endif
#	endif

#	if !MU0_HAVE_INT128
typedef   uint64_t                  mu0_uint128_t;
typedef   int64_t                   mu0_sint128_t;
#	endif

typedef   uint64_t                  mu0_uint64_t;
typedef   int64_t                   mu0_sint64_t;

typedef   uint32_t                  mu0_uint32_t;
typedef   int32_t                   mu0_sint32_t;

typedef   uint16_t                  mu0_uint16_t;
typedef   int16_t                   mu0_sint16_t;

typedef   uint8_t                   mu0_uint8_t;
typedef   int8_t                    mu0_sint8_t;

typedef   ptrdiff_t                 mu0_ptrdiff_t;
typedef   uintptr_t                 mu0_uintptr_t;
typedef   uintmax_t                 mu0_uintmax_t;
typedef   intmax_t                  mu0_sintmax_t;

typedef   size_t                    mu0_usize_t;
typedef   ssize_t                   mu0_ssize_t;
typedef   off_t                     mu0_index_t;

typedef   bool                      mu0_bool_t;
#	define mu0_true                  true
#	define mu0_false                 false

#	define mu0_uintmax(__x)          __mu0_cast__(mu0_uintmax_t, __x)
#	define mu0_const_uintmax(__x)    __mu0_const_cast__(mu0_uintmax_t, __x)

#	define mu0_uint128(__x)          __mu0_cast__(mu0_uint128_t, __x)
#	define mu0_const_uint128(__x)    __mu0_const_cast__(mu0_uint128_t, __x)
#	define mu0_sint128(__x)          __mu0_cast__(mu0_sint128_t, __x)
#	define mu0_const_sint128(__x)    __mu0_const_cast__(mu0_sint128_t, __x)

#	define mu0_uint64(__x)           __mu0_cast__(mu0_uint64_t, __x)
#	define mu0_const_uint64(__x)     __mu0_const_cast__(mu0_uint64_t, __x)
#	define mu0_sint64(__x)           __mu0_cast__(mu0_sint64_t, __x)
#	define mu0_const_sint64(__x)     __mu0_const_cast__(mu0_sint64_t, __x)

#	define mu0_uint32(__x)           __mu0_cast__(mu0_uint32_t, __x)
#	define mu0_const_uint32(__x)     __mu0_const_cast__(mu0_uint32_t, __x)
#	define mu0_sint32(__x)           __mu0_cast__(mu0_sint32_t, __x)
#	define mu0_const_sint32(__x)     __mu0_const_cast__(mu0_sint32_t, __x)

#	define mu0_uint16(__x)           __mu0_cast__(mu0_uint16_t, __x)
#	define mu0_const_uint16(__x)     __mu0_const_cast__(mu0_uint16_t, __x)
#	define mu0_sint16(__x)           __mu0_cast__(mu0_sint16_t, __x)
#	define mu0_const_sint16(__x)     __mu0_const_cast__( mu0_sint16_t, __x)

#	define mu0_uint8(__x)            __mu0_cast__(mu0_uint8_t, __x)
#	define mu0_const_uint8(__x)      __mu0_const_cast__(mu0_uint8_t, __x)
#	define mu0_sint8(__x)            __mu0_cast__(mu0_sint8_t, __x)
#	define mu0_const_sint8(__x)      __mu0_const_cast__(mu0_sint8_t, __x)

typedef   mu0_uint64_t              mu0_uinteger_t;

#	define mu0_uinteger(__x)         __mu0_cast__(mu0_uinteger_t, __x)
#	define mu0_const_uinteger(__x)   __mu0_const_cast__(mu0_uinteger_t, __x)

typedef   mu0_sint64_t              mu0_sinteger_t;

#	define mu0_sinteger(__x)         __mu0_cast__(mu0_ssinteger_t, __x)
#	define mu0_const_sinteger(__x)   __mu0_const_cast__(mu0_ssinteger_t, __x)

typedef   mu0_ptrdiff_t             mu0_difference_t;

#	define mu0_difference(__x)       __mu0_cast__(mu0_difference_t, __x)
#	define mu0_const_difference(__x) __mu0_const_cast__(mu0_difference_t, __x)

typedef   mu0_ptrdiff_t             mu0_distance_t;

#	define mu0_distance(__x)         __mu0_cast__(mu0_distance_t, __x)
#	define mu0_const_distance(__x)   __mu0_const_cast__(mu0_distance_t, __x)

#	if   MU0_HAVE_GENERIC
#	if   MU0_HAVE_INT128
#	define mu0_is_sinteger(__x) __mu0_generic__((__x) + 0 \
		, mu0_sint128_t : 1                                \
		, mu0_sint64_t  : 1                                \
		, mu0_sint32_t  : 1                                \
		, mu0_sint16_t  : 1                                \
		, mu0_sint8_t   : 1                                \
		, default       : 0                                \
	)
#	define mu0_is_uinteger(__x) __mu0_generic__((__x) + 0 \
		, mu0_uint128_t : 1                                \
		, mu0_uint64_t  : 1                                \
		, mu0_uint32_t  : 1                                \
		, mu0_uint16_t  : 1                                \
		, mu0_uint8_t   : 1                                \
		, default       : 0                                \
	) 
#	else
#	define mu0_is_sinteger(__x) __mu0_generic__((__x) + 0 \
		, mu0_sint64_t : 1                                 \
		, mu0_sint32_t : 1                                 \
		, mu0_sint16_t : 1                                 \
		, mu0_sint8_t  : 1                                 \
		, default      : 0                                 \
	)
#	define mu0_is_uinteger(__x) __mu0_generic__((__x) + 0 \
		, mu0_uint64_t : 1                                 \
		, mu0_uint32_t : 1                                 \
		, mu0_uint16_t : 1                                 \
		, mu0_uint8_t  : 1                                 \
		, default      : 0                                 \
	)
#	endif
#	elif MU0_HAVE_TYPEOF
#	define mu0_is_sinteger(__x)                 \
	((                                          \
		   __mu0_isofkind__(mu0_sint128_t , __x) \
		|| __mu0_isofkind__(mu0_sint64_t  , __x) \
		|| __mu0_isofkind__(mu0_sint32_t  , __x) \
		|| __mu0_isofkind__(mu0_sint16_t  , __x) \
		|| __mu0_isofkind__(mu0_sint8_t   , __x) \
		|| __mu0_isofkind__(mu0_ptrdiff_t, __x)  \
	) ? 1 : 0)

#	define mu0_is_uinteger(__x)                \
	((                                         \
		   __mu0_isofkind__(mu0_uint128_t, __x) \
		|| __mu0_isofkind__(mu0_uint64_t , __x) \
		|| __mu0_isofkind__(mu0_uint32_t , __x) \
		|| __mu0_isofkind__(mu0_uint16_t , __x) \
		|| __mu0_isofkind__(mu0_uint8_t  , __x) \
	) ? 1 : 0)
#	else
#	define mu0_is_sinteger(__x) (1)
#	define mu0_is_uinteger(__x) (1)
#	endif

#	if MU0_HAVE_INT128

#	define __mu0_uint128_const__(__c) UINT128_C(__c)
#	define __mu0_sint128_const__(__c)  INT128_C(__c)

__mu0_static__ const mu0_uint128_t mu0_uint128_max = UINT128_MAX;
__mu0_static__ const mu0_uint128_t mu0_uint128_min = __mu0_uint128_const__(0);
__mu0_static__ const mu0_sint128_t mu0_sint128_max = INT128_MAX;
__mu0_static__ const mu0_sint128_t mu0_sint128_min = INT128_MIN;

#	else

#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
#	define __mu0_uint128_const__(__c) UINT64_C(__c)
#	define __mu0_sint128_const__(__c)  INT64_C(__c)
#	else
#	define __mu0_uint128_const__(__c) __c ## UL
#	define __mu0_sint128_const__(__c) __c
#	endif

__mu0_static__ const mu0_uint128_t mu0_uint128_max = UINT64_MAX;
__mu0_static__ const mu0_uint128_t mu0_uint128_min = __mu0_uint128_const__(0);
__mu0_static__ const mu0_sint128_t mu0_sint128_max = INT64_MAX;
__mu0_static__ const mu0_sint128_t mu0_sint128_min = INT64_MIN;

#	endif

#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
#	define __mu0_uint64_const__(__c) UINT64_C(__c)
#	define __mu0_sint64_const__(__c)  INT64_C(__c)
#	else
#	define __mu0_uint64_const__(__c) __c ## U
#	define __mu0_sint64_const__(__c) __c
#	endif

__mu0_static__ const mu0_uint64_t  mu0_uint64_max  = UINT64_MAX;
__mu0_static__ const mu0_uint64_t  mu0_uint64_min  = __mu0_uint64_const__(0);
__mu0_static__ const mu0_sint64_t  mu0_sint64_max  = INT64_MAX;
__mu0_static__ const mu0_sint64_t  mu0_sint64_min  = INT64_MIN;

#	define __mu0_uint32_const__(__c) UINT32_C(__c)
#	define __mu0_sint32_const__(__c)  INT32_C(__c)

__mu0_static__ const mu0_uint32_t  mu0_uint32_max  = UINT32_MAX;
__mu0_static__ const mu0_uint32_t  mu0_uint32_min  = __mu0_uint32_const__(0);
__mu0_static__ const mu0_sint32_t  mu0_sint32_max  = INT32_MAX;
__mu0_static__ const mu0_sint32_t  mu0_sint32_min  = INT32_MIN;

#	define __mu0_uint16_const__(__c) UINT16_C(__c)
#	define __mu0_sint16_const__(__c)  INT16_C(__c)

__mu0_static__ const mu0_uint16_t  mu0_uint16_max  = UINT16_MAX;
__mu0_static__ const mu0_uint16_t  mu0_uint16_min  = __mu0_uint16_const__(0);
__mu0_static__ const mu0_sint16_t  mu0_sint16_max  = INT16_MAX;
__mu0_static__ const mu0_sint16_t  mu0_sint16_min  = INT16_MIN;

#	define __mu0_uint8_const__(__c) UINT8_C(__c)
#	define __mu0_sint8_const__(__c)  INT8_C(__c)

__mu0_static__ const mu0_uint8_t   mu0_uint8_max   = UINT8_MAX;
__mu0_static__ const mu0_uint8_t   mu0_uint8_min   = __mu0_uint8_const__(0);
__mu0_static__ const mu0_sint8_t   mu0_sint8_max   = INT8_MAX;
__mu0_static__ const mu0_sint8_t   mu0_sint8_min   = INT8_MIN;

MU0_END_CDECL

#endif /* !MU0_INTEGER_H */

/* EOF */