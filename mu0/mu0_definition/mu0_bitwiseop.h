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

// mu0_bitwiseop.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_console.h>
#include <mu0/mu0_definition/mu0_feature.h>

#ifndef MU0_BITWISEOP_H
#define MU0_BITWISEOP_H 1

#	undef  MU0_HAVE_BITWISEOP
#	define MU0_HAVE_BITWISEOP 0

#	include <limits.h>

#	if defined(__CHAR_BIT__)
#		define __MU0_CHAR_BIT__ __CHAR_BIT__
#	elif defined(CHAR_BIT)
#		define __MU0_CHAR_BIT__ CHAR_BIT
#	else
#		define __MU0_CHAR_BIT__ (8U)
#	endif

#	define __mu0_bit_counts__(__x) (__mu0_sizeof__(__x) / __MU0_CHAR_BIT__)
#	define __mu0_bit_digits__(__x) (__mu0_sizeof__(__x) * __MU0_CHAR_BIT__)

__mu0_static_inline__
int __mu0_cnttz_i__(const unsigned int __x)
{
	unsigned int x = __x;
	unsigned int d = __mu0_const_cast__(unsigned int, __mu0_bit_digits__(x));
	unsigned int y;

	if (x > 0) {
		y = x >> 16U; if (y != 0U) { d = d - 16U; x = y; }
		y = x >>  8U; if (y != 0U) { d = d -  8U; x = y; }
		y = x >>  4U; if (y != 0U) { d = d -  4U; x = y; }
		y = x >>  2U; if (y != 0U) { d = d -  2U; x = y; }
		y = x >>  1U;

		return __mu0_cast__(int, ((y != 0U) ? d - 2U : d - x));
	}
	return __mu0_cast__(int, __mu0_bit_counts__(x));
}

__mu0_static_inline__
int __mu0_cnttz_ll__(const unsigned long long __x)
{
	const unsigned int x = 0U;
	const unsigned int d = __mu0_const_cast__(unsigned int, __mu0_bit_counts__(x));
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	return ((__x & 0xFFFFFFFF00000000ULL)
		?     __mu0_cnttz_i__(__x >> d)
		: d + __mu0_cnttz_i__(__x & 0xFFFFFFFFULL)
	);
#	else
	return ((__x & 0xFFFFFFFF00000000U)
		?     __mu0_cnttz_i__(__x >> d)
		: d + __mu0_cnttz_i__(__x & 0xFFFFFFFFU)
	);
#	endif
}

__mu0_static_inline__
int __mu0_cnttz_l__(const unsigned long __x)
{
#	if defined(__LP64__)
	return __mu0_cnttz_ll__(__x);
#	else
	return __mu0_cnttz_i__(__x);
#	endif
}

#	if MU0_HAVE_CC_MSVCC
#	if MU0_HAVE_AMD64
	__mu0_static_inline__
	int __mu0_clz_ll__(const unsigned long long __x)
	{ return (__x > 0) ? __lzcnt64(__x)                              : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

	__mu0_static_inline__
	int __mu0_clz_l__(const unsigned long __x)
	{ return (__x > 0) ? __lzcnt(__x)                                : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

	__mu0_static_inline__
	int __mu0_clz_i__(const unsigned int __x)
	{ return (__x > 0) ? __lzcnt(__x)                                : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

	__mu0_static_inline__
	int __mu0_clz_i__(const unsigned int __x)
	{ return (__x > 0) ? __mu0_clz_l__(__x)                          : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

	__mu0_static_inline__
	int __mu0_clz_s__(const unsigned short __x)
	{ return (__x > 0) ? __mu0_clz_i__(__x) - (__MU0_CHAR_BIT__ * 2) : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

	__mu0_static_inline__
	int __mu0_clz_c__(const unsigned char __x)
	{ return (__x > 0) ? __mu0_clz_i__(__x) - (__MU0_CHAR_BIT__ * 3) : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

#	else
#		if defined(_M_X64) && !defined(_M_ARM64EC)
#			pragma intrinsic(_BitScanReverse64)
#		endif
#		pragma intrinsic(_BitScanReverse)

#		undef  MU0_HAVE_BITWISEOP
#		define MU0_HAVE_BITWISEOP 1

	__mu0_static_inline__
	int __mu0_clz_ll__(const unsigned long long __x)
	{
		unsigned long index         = 0;
	#	if defined(_M_X64) && !defined(_M_ARM64EC)
		const unsigned __int64 mask = __mu0_const_cast__(__int64, __x);
		if (__x > 0) {
			if (_BitScanReverse64(&index, mask)) {
				return __mu0_cast__(int, (__mu0_bit_counts__(__x) - 1) - index);
			}
		}
	#	else
		const unsigned long mask_lo = __mu0_const_cast__(unsigned long, __x);
		const unsigned int  hdigits = __mu0_const_cast__(unsigned int, __mu0_bit_counts__(mask_lo));
		const unsigned long mask_hi = __mu0_const_cast__(unsigned long, (__x >> hdigits));

		if (__x > 0) {
			if (!_BitScanReverse(&index, mask_lo) && _BitScanReverse(&index, mask_hi)) {
				index += hdigits;
			}
			return __mu0_cast__(int, (__mu0_bit_counts__(__x) - 1) - index);
		}
	#	endif
		return __mu0_cast__(int, __mu0_bit_counts__(__x));
	}

	__mu0_static_inline__
	int __mu0_clz_l__(const unsigned long __x)
	{
		unsigned long index = 0;
		unsigned long mask  = __x;
		if (__x > 0) {
			if (_BitScanReverse(&index, mask)) {
				return __mu0_cast__(int, (__mu0_bit_counts__(__x) - 1) - index);
			}
		}
		return __mu0_cast__(int, __mu0_bit_counts__(__x));
	}

	__mu0_static_inline__
	int __mu0_clz_i__(const unsigned int __x)
	{ return (__x > 0) ? __mu0_clz_l__(__x)                          : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

	__mu0_static_inline__
	int __mu0_clz_s__(const unsigned short __x)
	{ return (__x > 0) ? __mu0_clz_i__(__x) - (__MU0_CHAR_BIT__ * 2) : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

	__mu0_static_inline__
	int __mu0_clz_c__(const unsigned char __x)
	{ return (__x > 0) ? __mu0_clz_i__(__x) - (__MU0_CHAR_BIT__ * 3) : __mu0_cast__(int, __mu0_bit_counts__(__x)); }

#		endif
#	elif MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUC

#	undef  MU0_HAVE_BITWISEOP
#	define MU0_HAVE_BITWISEOP 1

#	define __mu0_clz_ll__(__x) \
	(__mu0_cast__(int, (__x) ? __builtin_clzll(__x)                            : __mu0_bit_counts__(__x)))

#	define __mu0_clz_l__(__x) \
	(__mu0_cast__(int, (__x) ? __builtin_clzl(__x)                             : __mu0_bit_counts__(__x)))

#	define __mu0_clz_i__(__x) \
	(__mu0_cast__(int, (__x) ? __builtin_clz(__x)                              : __mu0_bit_counts__(__x)))

#	define __mu0_clz_s__(__x) \
	(__mu0_cast__(int, (__x) ? ((__builtin_clz(__x) - (__MU0_CHAR_BIT__ * 2))) : __mu0_bit_counts__(__x)))

#	define __mu0_clz_c__(__x) \
	(__mu0_cast__(int, (__x) ? ((__builtin_clz(__x) - (__MU0_CHAR_BIT__ * 3))) : __mu0_bit_counts__(__x)))

#	endif

#	if MU0_HAVE_BITWISEOP
#	define __mu0_clz__(__x)                                               \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long long))          \
		? __mu0_clz_ll__(__x)                                              \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long))          \
			? __mu0_clz_l__(__x)                                            \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned int))        \
				? __mu0_clz_i__(__x)                                         \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned short))   \
					? __mu0_clz_s__(__x)                                      \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned char)) \
						? __mu0_clz_c__(__x)                                   \
						: 0                                                    \
					)                                                         \
				)                                                            \
			)                                                               \
		)                                                                  \
	)
#	define __mu0_countl_zero__(__x) (__mu0_clz__(__x))
#	define __mu0_bit_width__(__x)   (__mu0_bit_digits__(__x) - __mu0_countl_zero__(__x))
#	endif

#	define __mu0_bit_reverse__(_Tp, __x)                                                               \
	__mu0_scope_begin__                                                                                \
		unsigned int __mu0_bit_reverse__digits__ = __mu0_cast__(unsigned int, __mu0_bit_digits__(__x)); \
		_Tp          __mu0_bit_reverse__mask__   = ~((_Tp)(0));                                         \
		while (__mu0_bit_reverse__digits__ >>= 1) {                                                     \
			__mu0_bit_reverse__mask__ ^= __mu0_bit_reverse__mask__ << (__mu0_bit_reverse__digits__);     \
			(__x) = ((__x) & ~__mu0_bit_reverse__mask__) >> __mu0_bit_reverse__digits__                  \
					| ((__x) &__mu0_bit_reverse__mask__) << __mu0_bit_reverse__digits__;                   \
		}                                                                                               \
	__mu0_scope_end__

#	define __mu0_bitset_reverse_u8__(__x)                   \
	__mu0_scope_begin__                                     \
		(__x) = ((__x) & 0xF0) >> 4U | ((__x) & 0x0F) << 4U; \
		(__x) = ((__x) & 0xCC) >> 2U | ((__x) & 0x33) << 2U; \
		(__x) = ((__x) & 0xAA) >> 1U | ((__x) & 0x55) << 1U; \
	__mu0_scope_end__

#	define __mu0_bitset_pattern_u8__ "%c%c%c%c%c%c%c%c"
#	define __mu0_bitset_format_u8__(__x)  \
	  (((__x) & 0x80U) ? '1' : '0') \
	, (((__x) & 0x40U) ? '1' : '0') \
	, (((__x) & 0x20U) ? '1' : '0') \
	, (((__x) & 0x10U) ? '1' : '0') \
	, (((__x) & 0x08U) ? '1' : '0') \
	, (((__x) & 0x04U) ? '1' : '0') \
	, (((__x) & 0x02U) ? '1' : '0') \
	, (((__x) & 0x01U) ? '1' : '0')

#	define __mu0_bitset_pattern_u16__ \
	__mu0_bitset_pattern_u8__ __mu0_bitset_pattern_u8__

#	define __mu0_bitset_pattern_u32__ \
	__mu0_bitset_pattern_u16__ __mu0_bitset_pattern_u16__

#	define __mu0_bitset_pattern_u64__ \
	__mu0_bitset_pattern_u32__ __mu0_bitset_pattern_u32__

#	define __mu0_bitset_format_u16__(__x) \
	__mu0_bitset_format_u8__((__x) >> 8U), __mu0_bitset_format_u8__((__x))

#	define __mu0_bitset_format_u32__(__x) \
	__mu0_bitset_format_u16__((__x) >> 16U), __mu0_bitset_format_u16__((__x))

#	define __mu0_bitset_format_u64__(__x) \
	__mu0_bitset_format_u32__((__x) >> 32U), __mu0_bitset_format_u32__((__x))

#	define __mu0_bitset_print_u8__(__x) \
	__mu0_console_log__("" __mu0_bitset_pattern_u8__  "\n", __mu0_bitset_format_u8__(__x)

#	define __mu0_bitset_print_u16__(__x) \
	__mu0_console_log__("" __mu0_bitset_pattern_u16__ "\n", __mu0_bitset_format_u16__(__x)

#	define __mu0_bitset_print_u32__(__x) \
	__mu0_console_log__("" __mu0_bitset_pattern_u32__ "\n", __mu0_bitset_format_u32__(__x)

#	define __mu0_bitset_print_u64__(__x) \
	__mu0_console_log__("" __mu0_bitset_pattern_u64__ "\n", __mu0_bitset_format_u64__(__x)

#	if !MU0_HAVE_BITWISEOP
#		error mu0_bitwiseop.h
#	endif

#endif /* !MU0_BITWISEOP_H */

/* EOF */