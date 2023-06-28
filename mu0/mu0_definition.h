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

#	include <mu0/mu0_definition/mu0_atomic.h>
#	include <mu0/mu0_definition/mu0_attribute.h>
#	include <mu0/mu0_definition/mu0_bitoperator.h>
#	include <mu0/mu0_definition/mu0_byteorder.h>
#	include <mu0/mu0_definition/mu0_byteswap.h>
#	include <mu0/mu0_definition/mu0_chartrait.h>
#	include <mu0/mu0_definition/mu0_clocktime.h>
#	include <mu0/mu0_definition/mu0_compiler.h>
#	include <mu0/mu0_definition/mu0_console.h>
#	include <mu0/mu0_definition/mu0_cpuyield.h>
#	include <mu0/mu0_definition/mu0_feature.h>
#	include <mu0/mu0_definition/mu0_i18ndatetime.h>
#	include <mu0/mu0_definition/mu0_i18nlocale.h>
#	include <mu0/mu0_definition/mu0_language.h>
#	include <mu0/mu0_definition/mu0_barrier.h>
#	include <mu0/mu0_definition/mu0_numeral.h>
#	include <mu0/mu0_definition/mu0_parallelize.h>
#	include <mu0/mu0_definition/mu0_platform.h>
#	include <mu0/mu0_definition/mu0_spinlock.h>

MU0_BEGIN_CDECL

enum mu0_endian
{
	  mu0_endian_little           = __mu0_order_leen__
	, mu0_endian_big              = __mu0_order_been__
	, mu0_endian_native           = __mu0_byte_order__
};

enum mu0_ordering
{
	  mu0_ordering_less           = -1
	, mu0_ordering_equal          =  0
	, mu0_ordering_greater        =  1
};

enum mu0_dateformat
{
	  mu0_dateformat_iso8601_full = __mu0_dateformat_iso8601_full__
	, mu0_dateformat_iso8601_long = __mu0_dateformat_iso8601_long__
	, mu0_dateformat_iso8601_zulu = __mu0_dateformat_iso8601_zulu__
	, mu0_dateformat_rfc3339_full = __mu0_dateformat_rfc3339_full__
	, mu0_dateformat_rfc3339_long = __mu0_dateformat_rfc3339_long__
	, mu0_dateformat_rfc3339_zulu = __mu0_dateformat_rfc3339_zulu__
};

typedef __mu0_i18nlocale_t__          mu0_locale_t;
typedef __mu0_calendar_date_t__       mu0_calendar_date_t;

#	define mu0_min(__a, __b)           __mu0_inline_min__(__a, __b)
#	define mu0_max(__a, __b)           __mu0_inline_max__(__a, __b)
#	define mu0_abs(__a)                __mu0_inline_abs__(__a)

#	define mu0_gcd_constexpr(__a, __b) __mu0_inline_gcd_constexpr__(__a, __b)
#	define mu0_lcm_constexpr(__a, __b) __mu0_inline_lcm_constexpr__(__a, __b)
#	define mu0_gcd(__a, __b)           __mu0_inline_gcd__(__a, __b)
#	define mu0_lcm(__a, __b)           __mu0_inline_lcm__(__a, __b)

#	define mu0_console_log             __mu0_console_log__
#	define mu0_console_info            __mu0_console_info__
#	define mu0_console_warn            __mu0_console_warn__
#	define mu0_console_error           __mu0_console_error__

#	define mu0_scope_begin             __mu0_scope_begin__
#	define mu0_scope_end               __mu0_scope_end__

#	define mu0_nullptr                 __mu0_nullptr__
#	define mu0_is_nullptr(__x)         __mu0_is_nullptr__(__x)
#	define mu0_not_nullptr(__x)        __mu0_not_nullptr__(__x)
#	define mu0_infer(__x)              __mu0_infer__(__x)

#	define mu0_cast(_Tp, __x)          __mu0_cast__(_Tp, __x)
#	define mu0_const_cast(_Tp, __x)    __mu0_const_cast__(_Tp, __x)

#	define mu0_unused(__x)             __mu0_unused__(__x)

MU0_END_CDECL

#endif /* !MU0_DEFINITION_H */

/* EOF */