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

// mu0_bitoperator.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_attribute.h>
#include <mu0/mu0_definition/mu0_console.h>
#include <mu0/mu0_definition/mu0_feature.h>

#ifndef MU0_BITOPERATOR_H
#define MU0_BITOPERATOR_H 1

#	undef  MU0_HAVE_BITOPERATOR
#	define MU0_HAVE_BITOPERATOR 0

#	include <limits.h>
#	include <string.h>

#	define ___mu0_bit_rev___(_Tp, __x)                                                                    \
	__mu0_scope_begin__                                                                                   \
		___mu0_uint4_t___ ___mu0_bit_rev__d___ = __mu0_cast__(___mu0_uint4_t___, __mu0_bit_digits__(__x)); \
		_Tp               ___mu0_bit_rev__m___ = ~(__mu0_const_cast__(_Tp, 0));                            \
		while (___mu0_bit_rev__d___ >>= 1) {                                                               \
			___mu0_bit_rev__m___ ^= ___mu0_bit_rev__m___ << (___mu0_bit_rev__d___);                         \
			(__x) = ((__x) & ~___mu0_bit_rev__m___) >> ___mu0_bit_rev__d___                                 \
					| ((__x) &___mu0_bit_rev__m___) << ___mu0_bit_rev__d___;                                  \
		}                                                                                                  \
	__mu0_scope_end__

#	define __mu0_bitset_rev_u8__(__x)                       \
	__mu0_scope_begin__                                     \
		(__x) = ((__x) & 0xF0) >> 4U | ((__x) & 0x0F) << 4U; \
		(__x) = ((__x) & 0xCC) >> 2U | ((__x) & 0x33) << 2U; \
		(__x) = ((__x) & 0xAA) >> 1U | ((__x) & 0x55) << 1U; \
	__mu0_scope_end__

#	define ___mu0_bitset_pattern_u1___ "%c%c%c%c%c%c%c%c"
#	define ___mu0_bitset_format_u1___(__x) \
	  (((__x) & 0x80U) ? '1' : '0')        \
	, (((__x) & 0x40U) ? '1' : '0')        \
	, (((__x) & 0x20U) ? '1' : '0')        \
	, (((__x) & 0x10U) ? '1' : '0')        \
	, (((__x) & 0x08U) ? '1' : '0')        \
	, (((__x) & 0x04U) ? '1' : '0')        \
	, (((__x) & 0x02U) ? '1' : '0')        \
	, (((__x) & 0x01U) ? '1' : '0')

#	define ___mu0_bitset_pattern_u2___ \
	___mu0_bitset_pattern_u1___ ___mu0_bitset_pattern_u1___

#	define ___mu0_bitset_pattern_u4___ \
	___mu0_bitset_pattern_u2___ ___mu0_bitset_pattern_u2___

#	define ___mu0_bitset_pattern_u8___ \
	___mu0_bitset_pattern_u4___ ___mu0_bitset_pattern_u4___

#	define ___mu0_bitset_format_u2___(__x) \
	___mu0_bitset_format_u1___((__x) >> 8U), ___mu0_bitset_format_u1___((__x))

#	define ___mu0_bitset_format_u4___(__x) \
	___mu0_bitset_format_u2___((__x) >> 16U), ___mu0_bitset_format_u2___((__x))

#	define ___mu0_bitset_format_u8___(__x) \
	___mu0_bitset_format_u4___((__x) >> 32U), ___mu0_bitset_format_u4___((__x))

#	define ___mu0_bitset_print_u1___(__x)                    \
	__mu0_console_log__("" ___mu0_bitset_pattern_u1___  "\n" \
	, ___mu0_bitset_format_u1___(__mu0_const_cast__(___mu0_uint1_t___, __x)))

#	define ___mu0_bitset_print_u2___(__x)                   \
	__mu0_console_log__("" ___mu0_bitset_pattern_u2___ "\n" \
	, ___mu0_bitset_format_u2___(__mu0_const_cast__(___mu0_uint2_t___, __x)))

#	define ___mu0_bitset_print_u4___(__x)                   \
	__mu0_console_log__("" ___mu0_bitset_pattern_u4___ "\n" \
	, ___mu0_bitset_format_u4___(__mu0_const_cast__(___mu0_uint4_t___, __x)))

#	if MU0_HAVE_LP64
#	define ___mu0_bitset_print_u8___(__x)                   \
	__mu0_console_log__("" ___mu0_bitset_pattern_u8___ "\n" \
	, ___mu0_bitset_format_u8___(__mu0_const_cast__(___mu0_uintx_t___, __x)))
#	else
#	define ___mu0_bitset_print_u8___(__x)                   \
	__mu0_console_log__("" ___mu0_bitset_pattern_u8___ "\n" \
	, ___mu0_bitset_format_u8___(__mu0_const_cast__(___mu0_uint8_t___, __x)))
#	endif

#	if defined(__CHAR_BIT__)
#		define __mu0_char_bit__ __CHAR_BIT__
#	elif defined(CHAR_BIT)
#		define __mu0_char_bit__ CHAR_BIT
#	else
#		define __mu0_char_bit__ (8U)
#	endif

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_digits_u8__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(___mu0_uint8_t___) * __mu0_char_bit__)); }

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_digits_ux__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(___mu0_uintx_t___) * __mu0_char_bit__)); }

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_digits_u4__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(___mu0_uint4_t___) * __mu0_char_bit__)); }

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_digits_u2__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(___mu0_uint2_t___) * __mu0_char_bit__)); }

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_digits_u1__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(___mu0_uint1_t___) * __mu0_char_bit__)); }

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_digits__(const ___mu0_uint8_t___ __x) { __mu0_unused__(__x); return __mu0_bit_digits_u8__(); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_digits__(const ___mu0_uintx_t___ __x) { __mu0_unused__(__x); return __mu0_bit_digits_ux__(); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_digits__(const ___mu0_uint4_t___ __x) { __mu0_unused__(__x); return __mu0_bit_digits_u4__(); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_digits__(const ___mu0_uint2_t___ __x) { __mu0_unused__(__x); return __mu0_bit_digits_u2__(); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_digits__(const ___mu0_uint1_t___ __x) { __mu0_unused__(__x); return __mu0_bit_digits_u1__(); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_bit_digits__(__x) __mu0_generic__(__x \
	, ___mu0_uint8_t___ : __mu0_bit_digits_u8__        \
	, ___mu0_uintx_t___ : __mu0_bit_digits_ux__        \
	, ___mu0_uint4_t___ : __mu0_bit_digits_u4__        \
	, ___mu0_uint2_t___ : __mu0_bit_digits_u2__        \
	, ___mu0_uint1_t___ : __mu0_bit_digits_u1__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_bit_digits__(__x)                            \
	((__mu0_isofkind__(___mu0_uint8_t___, __x))               \
		? __mu0_bit_digits_u8__()                              \
		: ((__mu0_isofkind__(___mu0_uintx_t___, __x))          \
			? __mu0_bit_digits_ux__()                           \
			: ((__mu0_isofkind__(___mu0_uint4_t___, __x))       \
				? __mu0_bit_digits_u4__()                        \
				: ((__mu0_isofkind__(___mu0_uint2_t___, __x))    \
					? __mu0_bit_digits_u2__()                     \
					: ((__mu0_isofkind__(___mu0_uint1_t___, __x)) \
						? __mu0_bit_digits_u1__()                  \
						: 0                                        \
					)                                             \
				)                                                \
			)                                                   \
		)                                                      \
	)
#	else
#	define __mu0_bit_digits__(__x)                                            \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint8_t___))               \
		? __mu0_bit_digits_u8__()                                              \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uintx_t___))          \
			? __mu0_bit_digits_ux__()                                           \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint4_t___))       \
				? __mu0_bit_digits_u4__()                                        \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint2_t___))    \
					? __mu0_bit_digits_u2__()                                     \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint1_t___)) \
						? __mu0_bit_digits_u1__()                                  \
						: 0                                                        \
					)                                                             \
				)                                                                \
			)                                                                   \
		)                                                                      \
	)
#	endif

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cntlz_u8__(const ___mu0_uint8_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cntlz_ux__(const ___mu0_uintx_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cntlz_u4__(const ___mu0_uint4_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cntlz_u2__(const ___mu0_uint2_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cntlz_u1__(const ___mu0_uint1_t___ __x);

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_u8__(const ___mu0_uint8_t___ __x)
{
	const ___mu0_sint4_t___ d = __mu0_bit_digits_u4__();
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	return ((__x & 0xFFFFFFFF00000000ULL)
		?     __mu0_cntlz_u4__(__x >> d)
		: d + __mu0_cntlz_u4__(__x & 0xFFFFFFFFULL)
	);
#	else
	return ((__x & 0xFFFFFFFF00000000UL)
		?     __mu0_cntlz_u4__(__x >> d)
		: d + __mu0_cntlz_u4__(__x & 0xFFFFFFFFUL)
	);
#	endif
}

#	if MU0_HAVE_LP64
__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_ux__(const ___mu0_uintx_t___ __x)
{ return __mu0_cntlz_u8__(__x); }
#	else
__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_ux__(const ___mu0_uintx_t___ __x)
{ return __mu0_cntlz_u4__(__x); }
#	endif

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_u4__(const ___mu0_uint4_t___ __x)
{
	___mu0_uint1_t___ d = 0;
	___mu0_uint4_t___ x = __x;
	if (x) {
		if (x & 0xFFFF0000U) { x = x >> 16U; } else { d += 16; }
		return d + __mu0_cntlz_u2__ (x);
	}
	return __mu0_bit_digits_u4__();
}

#	if 0

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_u4__(const ___mu0_uint4_t___ __x)
{
	__mu0_static__
	const ___mu0_uint1_t___ s_table[32] =
	{
		   0,  9,  1, 10, 13, 21,  2, 29
		, 11, 14, 16, 18, 22, 25,  3, 30
		,  8, 12, 20, 28, 15, 17, 24,  7
		, 19, 27, 23,  6, 26,  5,  4, 31
	};

	const ___mu0_sint4_t___ d    = __mu0_bit_digits_u4__();
	___mu0_uint4_t___ x = __x;
	if (x) {
		x = x | (x >>  1U);
		x = x | (x >>  2U);
		x = x | (x >>  4U);
		x = x | (x >>  8U);
		x = x | (x >> 16U);
		return (d - 1) - s_table[((x * 0x07C4ACDD) >> 27U) % d];
	}
	return d;
}

#	endif

#	if 0

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_u4__(const ___mu0_uint4_t___ __x)
{
	___mu0_uint4_t___ x, d, y;
	if (__x) {
		x = __x;
		d = __mu0_bit_digits_u4__();
		y = x >> 16U; if (y != 0U) { d = d - 16U; x = y; }
		y = x >>  8U; if (y != 0U) { d = d -  8U; x = y; }
		y = x >>  4U; if (y != 0U) { d = d -  4U; x = y; }
		y = x >>  2U; if (y != 0U) { d = d -  2U; x = y; }
		y = x >>  1U;
		return __mu0_cast__(int, ((y != 0U) ? d - 2U : d - x));
	}
	return __mu0_bit_digits_u4__();
}

#	endif

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_u2__(const ___mu0_uint2_t___ __x)
{
	___mu0_uint1_t___ d = 0;
	___mu0_uint2_t___ x = __x;
	if (x) {
		if (x & 0xFF00U) { x >>= 8U; } else { d += 8; }
		return d + __mu0_cntlz_u1__ (x);
	}
	return __mu0_bit_digits_u2__();
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cntlz_u1__(const ___mu0_uint1_t___ __x)
{
	___mu0_uint1_t___ d = 0;
	___mu0_uint1_t___ x = __x;
	if (x) {
		if (((x & 0xF0U))) { x  = x >> 4U; } else { d += 4; }
		if (((x & 0x0CU))) { x  = x >> 2U; } else { d += 2; }
		if (!(x & 0x02U) ) { d += 1;       }
		return d;
	}
	return __mu0_bit_digits_u1__();
}

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cnttz_u8__(const ___mu0_uint8_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cnttz_ux__(const ___mu0_uintx_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cnttz_u4__(const ___mu0_uint4_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cnttz_u2__(const ___mu0_uint2_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_cnttz_u1__(const ___mu0_uint1_t___ __x);

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cnttz_u8__(const ___mu0_uint8_t___ __x)
{
	const ___mu0_sint4_t___ d = __mu0_bit_digits_u4__();
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	return ((__x & 0x00000000FFFFFFFFULL)
		?     __mu0_cnttz_u4__(__x & 0xFFFFFFFFULL)
		: d + __mu0_cnttz_u4__(__x >> d)
	);
#	else
	return ((__x & 0x00000000FFFFFFFFUL)
		?     __mu0_cnttz_u4__(__x & 0xFFFFFFFFUL)
		: d + __mu0_cnttz_u4__(__x >> d)
	);
#	endif
}

#	if MU0_HAVE_LP64
__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cnttz_ux__(const ___mu0_uintx_t___ __x)
{ return __mu0_cnttz_u8__(__x); }
#	else
__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cnttz_ux__(const ___mu0_uintx_t___ __x)
{ return __mu0_cnttz_u4__(__x); }
#	endif

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cnttz_u4__(const ___mu0_uint4_t___ __x)
{
	___mu0_uint1_t___ d = 0;
	___mu0_uint4_t___ x = __x;
	if (x) {
		if (!(x & 0x0000FFFFU)) { d += 16; x = x >> 16U; }
		return d + __mu0_cnttz_u2__ (x);
	}
	return __mu0_bit_digits_u4__();
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_cnttz_u2__(const ___mu0_uint2_t___ __x)
{
	___mu0_uint1_t___ d = 0;
	___mu0_uint2_t___ x = __x;
	if (x) {
		if (!(x & 0x00FFU)) { d += 8; x = x >> 8U; }
		return d + __mu0_cnttz_u1__ (x);
	}
	return __mu0_bit_digits_u2__();
}

__mu0_static_inline__ 
const ___mu0_sint4_t___ __mu0_cnttz_u1__(const ___mu0_uint1_t___ __x)
{
	___mu0_uint1_t___ d = 0;
	___mu0_uint1_t___ x = __x;
	if (x) {
		if (!(x & 0X0FU)) { d += 4; x = x >> 4U; }
		if (!(x & 0x03U)) { d += 2; x = x >> 2U; }
		if (!(x & 0x01U)) { d += 1;              }
		return d;
	}
	return __mu0_bit_digits_u1__();
}

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u8__(const ___mu0_uint8_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u4__(const ___mu0_uint4_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u2__(const ___mu0_uint2_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u1__(const ___mu0_uint1_t___ __x);

#	if   MU0_HAVE_CC_ITLCC
#		pragma intrinsic(_lzcnt_u64)
#		pragma intrinsic(_lzcnt_u32)
#		undef  MU0_HAVE_BITOPERATOR
#		define MU0_HAVE_BITOPERATOR 1

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u8__(const ___mu0_uint8_t___ __x)
		{ return (__x) ? _lzcnt_u64(__x)                                                       : __mu0_bit_digits_u8__(); }

#		if MU0_HAVE_LP64
		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x)
		{ return _mu0_clz_u8__(__x); }
#		else
		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x)
		{ return (__x) ? _lzcnt_u32(__x)                                                       : __mu0_bit_digits_ux__();  }
#		endif

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u4__(const ___mu0_uint4_t___ __x)
		{ return (__x) ? _lzcnt_u32(__x)                                                       : __mu0_bit_digits_u4__();  }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u2__(const ___mu0_uint2_t___ __x)
		{ return (__x) ? _lzcnt_u32(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u2__()) : __mu0_bit_digits_u2__();  }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u1__(const ___mu0_uint1_t___ __x)
		{ return (__x) ? _lzcnt_u32(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u1__()) : __mu0_bit_digits_u1__();  }

#	elif MU0_HAVE_CC_MSVCC
#		if MU0_HAVE_AMD64
#			pragma intrinsic(__lzcnt64)
#			pragma intrinsic(__lzcnt)
#			undef  MU0_HAVE_BITOPERATOR
#			define MU0_HAVE_BITOPERATOR 1

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u8__(const ___mu0_uint8_t___ __x)
			{ return (__x) ? __lzcnt64(__x)                                                     : __mu0_bit_digits_u8__(); }

#			if MU0_HAVE_LP64
			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x)
			{ return __mu0_clz_u8__(__x);  }
#			else
			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x)
			{ return (__x) ? __lzcnt(__x)                                                       : __mu0_bit_digits_ux__(); }
#			endif

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u4__(const ___mu0_uint4_t___ __x)
			{ return (__x) ? __lzcnt(__x)                                                       : __mu0_bit_digits_u4__(); }

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u2__(const ___mu0_uint2_t___ __x)
			{ return (__x) ? __lzcnt(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u2__()) : __mu0_bit_digits_u2__(); }

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u1__(const ___mu0_uint1_t___ __x)
			{ return (__x) ? __lzcnt(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u1__()) : __mu0_bit_digits_u1__(); }

#		else
#			if defined(_M_X64) && !defined(_M_ARM64EC)
#				pragma intrinsic(_BitScanReverse64)
#			endif
#			pragma intrinsic(_BitScanReverse)
#			undef  MU0_HAVE_BITOPERATOR
#			define MU0_HAVE_BITOPERATOR 1

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u8__(const ___mu0_uint8_t___ __x)
			{
				___mu0_uintx_t___ index         = 0;
			#	if defined(_M_X64) && !defined(_M_ARM64EC)
				const unsigned __int64 mask = __mu0_const_cast__(__int64, __x);
				if (__x) {
					if (_BitScanReverse64(&index, mask)) {
						return (__mu0_bit_digits_u8__() - 1) - __mu0_const_cast__(int, index);
					}
				}
			#	else
				const ___mu0_uintx_t___ mask_lo = __mu0_const_cast__(___mu0_uintx_t___, __x);
				const ___mu0_uint4_t___ hdigits = __mu0_bit_digits_u4__();
				const ___mu0_uintx_t___ mask_hi = __mu0_const_cast__(___mu0_uintx_t___, (__x >> hdigits));

				if (__x) {
					if (!_BitScanReverse(&index, mask_lo) && _BitScanReverse(&index, mask_hi)) {
						index += hdigits;
					}
					return (__mu0_bit_digits_u8__() - 1) - __mu0_const_cast__(int, index);
				}
			#	endif
				return __mu0_bit_digits_u8__();
			}

#			if MU0_HAVE_LP64
			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x)
			{  return __mu0_clz_u8__(__x); }
#			else
			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x)
			{
				___mu0_uintx_t___ index = 0;
				___mu0_uintx_t___ mask  = __x;
				if (__x) {
					if (_BitScanReverse(&index, mask)) {
						return (__mu0_bit_digits_ux__() - 1) - __mu0_const_cast__(int, index);
					}
				}
				return __mu0_bit_digits_ux__();
			}
#			endif

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u4__(const ___mu0_uint4_t___ __x)
			{ return (__x) ? __mu0_clz_ux__(__x)                                                       : __mu0_bit_digits_u4__(); }

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u2__(const ___mu0_uint2_t___ __x)
			{ return (__x) ? __mu0_clz_u4__(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u2__()) : __mu0_bit_digits_u2__(); }

			__mu0_static_inline__
			const ___mu0_sint4_t___ __mu0_clz_u1__(const ___mu0_uint1_t___ __x)
			{ return (__x) ? __mu0_clz_u4__(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u1__()) : __mu0_bit_digits_u1__(); }

#		endif
#	elif MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUC
#		undef  MU0_HAVE_BITOPERATOR
#		define MU0_HAVE_BITOPERATOR 1

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u8__(const ___mu0_uint8_t___ __x)
		{ return (__x) ? __builtin_clzll(__x)                                                         : __mu0_bit_digits_u8__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x)
		{ return (__x) ? __builtin_clzl(__x)                                                          : __mu0_bit_digits_ux__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u4__(const ___mu0_uint4_t___ __x)
		{ return (__x) ? __builtin_clz(__x)                                                           : __mu0_bit_digits_u4__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u2__(const ___mu0_uint2_t___ __x)
		{ return (__x) ? ((__builtin_clz(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u2__()))) : __mu0_bit_digits_u2__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_clz_u1__(const ___mu0_uint1_t___  __x)
		{ return (__x) ? ((__builtin_clz(__x) - (__mu0_bit_digits_u4__() - __mu0_bit_digits_u1__()))) : __mu0_bit_digits_u1__(); }

#	else
#		undef  MU0_HAVE_BITOPERATOR
#		define MU0_HAVE_BITOPERATOR 1

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u8__(const ___mu0_uint8_t___ __x) { return __mu0_cntlz_u8__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_ux__(const ___mu0_uintx_t___ __x) { return __mu0_cntlz_ux__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u4__(const ___mu0_uint4_t___ __x) { return __mu0_cntlz_u4__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u2__(const ___mu0_uint2_t___ __x) { return __mu0_cntlz_u2__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clz_u1__(const ___mu0_uint1_t___ __x) { return __mu0_cntlz_u1__(__x); }

#	endif

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clo_u8__(const ___mu0_uint8_t___ __x) { return __mu0_clz_u8__(~__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clo_ux__(const ___mu0_uintx_t___ __x) { return __mu0_clz_ux__(~__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clo_u4__(const ___mu0_uint4_t___ __x) { return __mu0_clz_u4__(~__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clo_u2__(const ___mu0_uint2_t___ __x) { return __mu0_clz_u2__(~__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_clo_u1__(const ___mu0_uint1_t___ __x) { return __mu0_clz_u1__(~__x); }

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clz__(const ___mu0_uint8_t___ __x) { return __mu0_clz_u8__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clz__(const ___mu0_uintx_t___ __x) { return __mu0_clz_ux__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clz__(const ___mu0_uint4_t___ __x) { return __mu0_clz_u4__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clz__(const ___mu0_uint2_t___ __x) { return __mu0_clz_u2__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clz__(const ___mu0_uint1_t___ __x) { return __mu0_clz_u1__(__x); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_clz__(__x) __mu0_generic__(__x \
	, ___mu0_uint8_t___ : __mu0_clz_u8__        \
	, ___mu0_uintx_t___ : __mu0_clz_ux__        \
	, ___mu0_uint4_t___ : __mu0_clz_u4__        \
	, ___mu0_uint2_t___ : __mu0_clz_u2__        \
	, ___mu0_uint1_t___ : __mu0_clz_u1__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_clz__(__x)                                   \
	((__mu0_isofkind__(___mu0_uint8_t___, __x))               \
		? __mu0_clz_u8__(__x)                                  \
		: ((__mu0_isofkind__(___mu0_uintx_t___, __x))          \
			? __mu0_clz_ux__(__x)                               \
			: ((__mu0_isofkind__(___mu0_uint4_t___, __x))       \
				? __mu0_clz_u4__(__x)                            \
				: ((__mu0_isofkind__(___mu0_uint2_t___, __x))    \
					? __mu0_clz_u2__(__x)                         \
					: ((__mu0_isofkind__(___mu0_uint1_t___, __x)) \
						? __mu0_clz_u1__(__x)                      \
						: 0                                        \
					)                                             \
				)                                                \
			)                                                   \
		)                                                      \
	)
#	else
#	define __mu0_clz__(__x)                                                   \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint8_t___))               \
		? __mu0_clz_u8__(__x)                                                  \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uintx_t___))          \
			? __mu0_clz_ux__(__x)                                               \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint4_t___))       \
				? __mu0_clz_u4__(__x)                                            \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint2_t___))    \
					? __mu0_clz_u2__(__x)                                         \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint1_t___)) \
						? __mu0_clz_u1__(__x)                                      \
						: 0                                                        \
					)                                                             \
				)                                                                \
			)                                                                   \
		)                                                                      \
	)
#	endif

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clo__(const ___mu0_uint8_t___ __x) { return __mu0_clo_u8__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clo__(const ___mu0_uintx_t___ __x) { return __mu0_clo_ux__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clo__(const ___mu0_uint4_t___ __x) { return __mu0_clo_u4__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clo__(const ___mu0_uint2_t___ __x) { return __mu0_clo_u2__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_clo__(const ___mu0_uint1_t___ __x) { return __mu0_clo_u1__(__x); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_clo__(__x) __mu0_generic__(__x \
	, ___mu0_uint8_t___ : __mu0_clo_u8__        \
	, ___mu0_uintx_t___ : __mu0_clo_ux__        \
	, ___mu0_uint4_t___ : __mu0_clo_u4__        \
	, ___mu0_uint2_t___ : __mu0_clo_u2__        \
	, ___mu0_uint1_t___ : __mu0_clo_u1__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_clo__(__x)                                   \
	((__mu0_isofkind__(___mu0_uint8_t___, __x))               \
		? __mu0_clo_u8__(__x)                                  \
		: ((__mu0_isofkind__(___mu0_uintx_t___, __x))          \
			? __mu0_clo_ux__(__x)                               \
			: ((__mu0_isofkind__(___mu0_uint4_t___, __x))       \
				? __mu0_clo_u4__(__x)                            \
				: ((__mu0_isofkind__(___mu0_uint2_t___, __x))    \
					? __mu0_clo_u2__(__x)                         \
					: ((__mu0_isofkind__(___mu0_uint1_t___, __x)) \
						? __mu0_clo_u1__(__x)                      \
						: 0                                        \
					)                                             \
				)                                                \
			)                                                   \
		)                                                      \
	)
#	else
#	define __mu0_clo__(__x)                                                   \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint8_t___))               \
		? __mu0_clo_u8__(__x)                                                  \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uintx_t___))          \
			? __mu0_clo_ux__(__x)                                               \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint4_t___))       \
				? __mu0_clo_u4__(__x)                                            \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint2_t___))    \
					? __mu0_clo_u2__(__x)                                         \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint1_t___)) \
						? __mu0_clo_u1__(__x)                                      \
						: 0                                                        \
					)                                                             \
				)                                                                \
			)                                                                   \
		)                                                                      \
	)
#	endif

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u8__(const ___mu0_uint8_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_ux__(const ___mu0_uintx_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u4__(const ___mu0_uint4_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u2__(const ___mu0_uint2_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u1__(const ___mu0_uint1_t___ __x);

#	if MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUC
#		undef  MU0_HAVE_BITOPERATOR
#		define MU0_HAVE_BITOPERATOR 1

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_ctz_u8__(const ___mu0_uint8_t___ __x)
		{ return (__x) ? __builtin_ctzll(__x) : __mu0_bit_digits_u8__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_ctz_ux__(const ___mu0_uintx_t___ __x)
		{ return (__x) ? __builtin_ctzl(__x)  : __mu0_bit_digits_ux__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_ctz_u4__(const ___mu0_uint4_t___ __x)
		{ return (__x) ? __builtin_ctz(__x)   : __mu0_bit_digits_u4__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_ctz_u2__(const ___mu0_uint2_t___ __x)
		{ return (__x) ? __builtin_ctz(__x)   : __mu0_bit_digits_u2__(); }

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_ctz_u1__(const ___mu0_uint1_t___ __x)
		{ return (__x) ? __builtin_ctz(__x)   : __mu0_bit_digits_u1__(); }

#	else
#		undef  MU0_HAVE_BITOPERATOR
#		define MU0_HAVE_BITOPERATOR 1

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u8__(const ___mu0_uint8_t___ __x) { return __mu0_cnttz_u8__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_ux__(const ___mu0_uintx_t___ __x) { return __mu0_cnttz_ux__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u4__(const ___mu0_uint4_t___ __x) { return __mu0_cnttz_u4__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u2__(const ___mu0_uint2_t___ __x) { return __mu0_cnttz_u2__(__x); }
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_ctz_u1__(const ___mu0_uint1_t___ __x) { return __mu0_cnttz_u1__(__x); }

#	endif

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const ___mu0_sint4_t___ __mu0_ctz__(const ___mu0_uint8_t___ __x) { return __mu0_ctz_u8__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_ctz__(const ___mu0_uintx_t___ __x) { return __mu0_ctz_ux__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_ctz__(const ___mu0_uint4_t___ __x) { return __mu0_ctz_u4__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_ctz__(const ___mu0_uint2_t___ __x) { return __mu0_ctz_u2__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_ctz__(const ___mu0_uint1_t___ __x) { return __mu0_ctz_u1__(__x); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_ctz__(__x) __mu0_generic__(__x \
	, ___mu0_uint8_t___ : __mu0_ctz_u8__        \
	, ___mu0_uintx_t___ : __mu0_ctz_ux__        \
	, ___mu0_uint4_t___ : __mu0_ctz_u4__        \
	, ___mu0_uint2_t___ : __mu0_ctz_u2__        \
	, ___mu0_uint1_t___ : __mu0_ctz_u1__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_ctz__(__x)                                   \
	((__mu0_isofkind__(___mu0_uint8_t___, __x))               \
		? __mu0_ctz_u8__(__x)                                  \
		: ((__mu0_isofkind__(___mu0_uintx_t___, __x))          \
			? __mu0_ctz_ux__(__x)                               \
			: ((__mu0_isofkind__(___mu0_uint4_t___, __x))       \
				? __mu0_ctz_u4__(__x)                            \
				: ((__mu0_isofkind__(___mu0_uint2_t___, __x))    \
					? __mu0_ctz_u2__(__x)                         \
					: ((__mu0_isofkind__(___mu0_uint1_t___, __x)) \
						? __mu0_ctz_u1__(__x)                      \
						: 0                                        \
					)                                             \
				)                                                \
			)                                                   \
		)                                                      \
	)
#	else
#	define __mu0_ctz__(__x)                                                   \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint8_t___))               \
		? __mu0_ctz_u8__(__x)                                                  \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uintx_t___))          \
			? __mu0_ctz_ux__(__x)                                               \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint4_t___))       \
				? __mu0_ctz_u4__(__x)                                            \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint2_t___))    \
					? __mu0_ctz_u2__(__x)                                         \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint1_t___)) \
						? __mu0_ctz_u1__(__x)                                      \
						: 0                                                        \
					)                                                             \
				)                                                                \
			)                                                                   \
		)                                                                      \
	)
#	endif

#	define __mu0_countl_zero__(__x) (__mu0_clz__(__x))
#	define __mu0_countl_one__(__x)  (__mu0_clo__(__x))
#	define __mu0_countr_zero__(__x) (__mu0_ctz__(__x))

__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_bit_width_u8__(const ___mu0_uint8_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_bit_width_ux__(const ___mu0_uintx_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_bit_width_u4__(const ___mu0_uint4_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_bit_width_u2__(const ___mu0_uint2_t___ __x);
__mu0_static_inline__ const ___mu0_sint4_t___ __mu0_bit_width_u1__(const ___mu0_uint1_t___ __x);

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_width_u8__(const ___mu0_uint8_t___ __x)
{
	return __mu0_bit_digits_u8__() - __mu0_ctz_u8__(__x);
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_width_ux__(const ___mu0_uintx_t___ __x)
{
	return __mu0_bit_digits_ux__() - __mu0_ctz_ux__(__x);
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_width_u4__(const ___mu0_uint4_t___ __x)
{
	return __mu0_bit_digits_u4__() - __mu0_ctz_ux__(__x);
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_width_u2__(const ___mu0_uint2_t___ __x)
{
	return __mu0_bit_digits_u2__() - __mu0_ctz_u2__(__x);
}
__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_bit_width_u1__(const ___mu0_uint1_t___  __x)
{
	return __mu0_bit_digits_u1__() - __mu0_ctz_u1__(__x);
}

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_width__(const ___mu0_uint8_t___ __x) { return __mu0_bit_width_u8__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_width__(const ___mu0_uintx_t___ __x) { return __mu0_bit_width_ux__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_width__(const ___mu0_uint4_t___ __x) { return __mu0_bit_width_u4__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_width__(const ___mu0_uint2_t___ __x) { return __mu0_bit_width_u2__(__x); }
__mu0_overload__ const ___mu0_sint4_t___ __mu0_bit_width__(const ___mu0_uint1_t___ __x) { return __mu0_bit_width_u1__(__x); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_bit_width__(__x) __mu0_generic__(__x \
	, ___mu0_uint8_t___ : __mu0_bit_width_u8__        \
	, ___mu0_uintx_t___ : __mu0_bit_width_ux__        \
	, ___mu0_uint4_t___ : __mu0_bit_width_u4__        \
	, ___mu0_uint2_t___ : __mu0_bit_width_u2__        \
	, ___mu0_uint1_t___ : __mu0_bit_width_u1__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_bit_width__(__x)                             \
	((__mu0_isofkind__(___mu0_uint8_t___, __x))               \
		? __mu0_bit_width_u8__(__x)                            \
		: ((__mu0_isofkind__(___mu0_uintx_t___, __x))          \
			? __mu0_bit_width_ux__(__x)                         \
			: ((__mu0_isofkind__(___mu0_uint4_t___, __x))       \
				? __mu0_bit_width_u4__(__x)                      \
				: ((__mu0_isofkind__(___mu0_uint2_t___, __x))    \
					? __mu0_bit_width_u2__(__x)                   \
					: ((__mu0_isofkind__(___mu0_uint1_t___, __x)) \
						? __mu0_bit_width_u1__(__x)                \
						: 0                                        \
					)                                             \
				)                                                \
			)                                                   \
		)                                                      \
	)
#	else
#	define __mu0_bit_width__(__x)                                             \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint8_t___))               \
		? __mu0_bit_width_u8__(__x)                                            \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uintx_t___))          \
			? __mu0_bit_width_ux__(__x)                                         \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint4_t___))       \
				? __mu0_bit_width_u4__(__x)                                      \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint2_t___))    \
					? __mu0_bit_width_u2__(__x)                                   \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(___mu0_uint1_t___)) \
						? __mu0_bit_width_u1__(__x)                                \
						: 0                                                        \
					)                                                             \
				)                                                                \
			)                                                                   \
		)                                                                      \
	)
#	endif

__mu0_static_inline__ const ___mu0_uint8_t___ __mu0_bit_ceil_u8__(const ___mu0_uint8_t___ __x);
__mu0_static_inline__ const ___mu0_uintx_t___ __mu0_bit_ceil_ux__(const ___mu0_uintx_t___ __x);
__mu0_static_inline__ const ___mu0_uint4_t___ __mu0_bit_ceil_u4__(const ___mu0_uint4_t___ __x);
__mu0_static_inline__ const ___mu0_uint2_t___ __mu0_bit_ceil_u2__(const ___mu0_uint2_t___ __x);
__mu0_static_inline__ const ___mu0_uint1_t___ __mu0_bit_ceil_u1__(const ___mu0_uint1_t___ __x);

__mu0_static_inline__
const ___mu0_uint8_t___ __mu0_bit_ceil_u8__(const ___mu0_uint8_t___ __x)
{
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	const ___mu0_uint8_t___ one = 1ULL;
#	else
	const ___mu0_uint8_t___ one = 1UL;
#	endif
	return __x > one ? (one << __mu0_bit_width_u8__(__x - one)) : one;
}

__mu0_static_inline__
const ___mu0_uintx_t___ __mu0_bit_ceil_ux__(const ___mu0_uintx_t___ __x)
{
	const ___mu0_uintx_t___ one = 1UL;
	return __x > one ? (one << __mu0_bit_width_ux__(__x - one)) : one;
}

__mu0_static_inline__
const ___mu0_uint4_t___ __mu0_bit_ceil_u4__(const ___mu0_uint4_t___ __x)
{
	const ___mu0_uint4_t___ one = 1U;
	return __x > one ? (one << __mu0_bit_width_u4__(__x - one)) : one;
}

__mu0_static_inline__
const ___mu0_uint2_t___ __mu0_bit_ceil_u2__(const ___mu0_uint2_t___ __x)
{
	const ___mu0_uint2_t___ one = 1;
	return __x > one ? (one << __mu0_bit_width_u2__(__x - one)) : one;
}

__mu0_static_inline__
const ___mu0_uint1_t___ __mu0_bit_ceil_u1__(const ___mu0_uint1_t___ __x)
{
	const ___mu0_uint1_t___ one = 1;
	return __x > one ? (one << __mu0_bit_width_u1__(__x - one)) : one;
}

__mu0_static_inline__ const ___mu0_uint8_t___ __mu0_bit_floor_u8__(const ___mu0_uint8_t___ __x);
__mu0_static_inline__ const ___mu0_uintx_t___ __mu0_bit_floor_ux__(const ___mu0_uintx_t___ __x);
__mu0_static_inline__ const ___mu0_uint4_t___ __mu0_bit_floor_u4__(const ___mu0_uint4_t___ __x);
__mu0_static_inline__ const ___mu0_uint2_t___ __mu0_bit_floor_u2__(const ___mu0_uint2_t___ __x);
__mu0_static_inline__ const ___mu0_uint1_t___ __mu0_bit_floor_u1__(const ___mu0_uint1_t___ __x);

__mu0_static_inline__
const ___mu0_uint8_t___ __mu0_bit_floor_u8__(const ___mu0_uint8_t___ __x)
{
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	const ___mu0_uint8_t___ one  = 1ULL;
	const ___mu0_uint8_t___ zero = 0ULL;
#	else
	const ___mu0_uint8_t___ one  = 1UL;
	const ___mu0_uint8_t___ zero = 0UL;
#	endif
	return __x != zero ? (one << (__mu0_bit_width_u8__(__x) - one)) : zero;
}

__mu0_static_inline__
const ___mu0_uintx_t___ __mu0_bit_floor_ux__(const ___mu0_uintx_t___ __x)
{
	const ___mu0_uintx_t___ one  = 1UL;
	const ___mu0_uintx_t___ zero = 0UL;
	return __x != zero ? (one << (__mu0_bit_width_ux__(__x) - one)) : zero;
}

__mu0_static_inline__
const ___mu0_uint4_t___ __mu0_bit_floor_u4__(const ___mu0_uint4_t___ __x)
{
	const ___mu0_uint4_t___ one  = 1U;
	const ___mu0_uint4_t___ zero = 0U;
	return __x != zero ? (one << (__mu0_bit_width_u4__(__x) - one)) : zero;
}

__mu0_static_inline__
const ___mu0_uint2_t___ __mu0_bit_floor_u2__(const ___mu0_uint2_t___ __x)
{
	const ___mu0_uint2_t___ one  = 1;
	const ___mu0_uint2_t___ zero = 0;
	return __x != zero ? (one << (__mu0_bit_width_u2__(__x) - one)) : zero;
}

__mu0_static_inline__
const ___mu0_uint1_t___ __mu0_bit_floor_u1__(const ___mu0_uint1_t___ __x)
{
	const ___mu0_uint1_t___ one  = 1;
	const ___mu0_uint1_t___ zero = 0;
	return __x != zero ? (one << (__mu0_bit_width_u1__(__x) - one)) : zero;
}

#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCC
#		if (__has_builtin(__builtin_bit_cast))
			/* There is a raising issue with char being promoted to int */
#			define __mu0_bit_cast__(__a, __b) \
			(__a) = __builtin_bit_cast(__mu0_typeof__((__mu0_typeof__(__x))(__x)), __b)
#		else
#			define __mu0_bit_cast__(__a, __b)                                              \
			memset(__mu0_addressof__(__b), 0                     , __mu0_sizeof__((__b))); \
			memcpy(__mu0_addressof__(__b), __mu0_addressof__(__a), __mu0_sizeof__((__b)))
#		endif
#	else
#	define __mu0_bit_cast__(__a, __b)                                              \
	memset(__mu0_addressof__(__b), 0                     , __mu0_sizeof__((__b))); \
	memcpy(__mu0_addressof__(__b), __mu0_addressof__(__a), __mu0_sizeof__((__b)))
#	endif

#	if !MU0_HAVE_BITOPERATOR
#		error mu0_bitoperator.h
#	endif

#endif /* !MU0_BITOPERATOR_H */

/* EOF */