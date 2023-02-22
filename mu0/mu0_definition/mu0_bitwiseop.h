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

__mu0_static_inline__
int __mu0_bit_digits_ll__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(unsigned long long) * __MU0_CHAR_BIT__)); }

__mu0_static_inline__
int __mu0_bit_digits_l__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(unsigned long     ) * __MU0_CHAR_BIT__)); }

__mu0_static_inline__
int __mu0_bit_digits_i__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(unsigned int      ) * __MU0_CHAR_BIT__)); }

__mu0_static_inline__
int __mu0_bit_digits_s__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(unsigned short    ) * __MU0_CHAR_BIT__)); }

__mu0_static_inline__
int __mu0_bit_digits_c__(void)
{ return __mu0_const_cast__(int, (__mu0_sizeof__(unsigned char     ) * __MU0_CHAR_BIT__)); }

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ int __mu0_bit_digits__ (const unsigned long long __x) { __mu0_unused__(__x); return __mu0_bit_digits_ll__ (); }
__mu0_overload__ int __mu0_bit_digits__ (const unsigned long      __x) { __mu0_unused__(__x); return __mu0_bit_digits_l__  (); }
__mu0_overload__ int __mu0_bit_digits__ (const unsigned int       __x) { __mu0_unused__(__x); return __mu0_bit_digits_i__  (); }
__mu0_overload__ int __mu0_bit_digits__ (const unsigned short     __x) { __mu0_unused__(__x); return __mu0_bit_digits_s__  (); }
__mu0_overload__ int __mu0_bit_digits__ (const unsigned char      __x) { __mu0_unused__(__x); return __mu0_bit_digits_c__  (); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_bit_digits__(__x) __mu0_generic__(__x \
	, unsigned long long : __mu0_bit_digits_ll__       \
	, unsigned long      : __mu0_bit_digits_l__        \
	, unsigned int       : __mu0_bit_digits_i__        \
	, unsigned short     : __mu0_bit_digits_s__        \
	, unsigned char      : __mu0_bit_digits_c__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_bit_digits__(__x)                        \
	((__mu0_isofkind__(unsigned long long, __x))          \
		? __mu0_bit_digits_ll__()                          \
		: ((__mu0_isofkind__(unsigned long, __x))          \
			? __mu0_bit_digits_l__()                        \
			: ((__mu0_isofkind__(unsigned int, __x))        \
				? __mu0_bit_digits_i__()                     \
				: ((__mu0_isofkind__(unsigned short, __x))   \
					? __mu0_bit_digits_s__()                  \
					: ((__mu0_isofkind__(unsigned char, __x)) \
						? __mu0_bit_digits_c__()               \
						: 0                                    \
					)                                         \
				)                                            \
			)                                               \
		)                                                  \
	)
#	else
#	define __mu0_bit_digits__(__x)                                        \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long long))          \
		? __mu0_bit_digits_ll__()                                          \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long))          \
			? __mu0_bit_digits_l__()                                        \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned int))        \
				? __mu0_bit_digits_i__()                                     \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned short))   \
					? __mu0_bit_digits_s__()                                  \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned char)) \
						? __mu0_bit_digits_c__()                               \
						: 0                                                    \
					)                                                         \
				)                                                            \
			)                                                               \
		)                                                                  \
	)
#	endif

__mu0_static_inline__ int __mu0_cntlz_ll__(const unsigned long long __x);
__mu0_static_inline__ int __mu0_cntlz_l__ (const unsigned long      __x);
__mu0_static_inline__ int __mu0_cntlz_i__ (const unsigned int       __x);
__mu0_static_inline__ int __mu0_cntlz_s__ (const unsigned short     __x);
__mu0_static_inline__ int __mu0_cntlz_c__ (const unsigned char      __x);

__mu0_static_inline__
int __mu0_cntlz_ll__(const unsigned long long __x)
{
	const int d = __mu0_bit_digits_i__();
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	return ((__x & 0xFFFFFFFF00000000ULL)
		?     __mu0_cntlz_i__(__x >> d)
		: d + __mu0_cntlz_i__(__x & 0xFFFFFFFFULL)
	);
#	else
	return ((__x & 0xFFFFFFFF00000000UL)
		?     __mu0_cntlz_i__(__x >> d)
		: d + __mu0_cntlz_i__(__x & 0xFFFFFFFFUL)
	);
#	endif
}

#	if MU0_HAVE_LP64
__mu0_static_inline__
int __mu0_cntlz_l__(const unsigned long __x)
{ return __mu0_cntlz_ll__(__x); }
#	else
__mu0_static_inline__
int __mu0_cntlz_l__(const unsigned long __x)
{ return __mu0_cntlz_i__(__x); }
#	endif

__mu0_static_inline__
int __mu0_cntlz_i__(const unsigned int __x)
{
	unsigned char d = 0;
	unsigned int  x = __x;
	if (x) {
		if (x & 0xFFFF0000U) { x = x >> 16U; } else { d += 16; }
		return d + __mu0_cntlz_s__(x);
	}
	return __mu0_bit_digits_i__();
}

#	if 0

__mu0_static_inline__
int __mu0_cntlz_i__(const unsigned int __x)
{
	__mu0_static__
	const unsigned char s_table[32] =
	{
		   0,  9,  1, 10, 13, 21,  2, 29
		, 11, 14, 16, 18, 22, 25,  3, 30
		,  8, 12, 20, 28, 15, 17, 24,  7
		, 19, 27, 23,  6, 26,  5,  4, 31
	};

	const int d    = __mu0_bit_digits_i__();
	unsigned int x = __x;
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
int __mu0_cntlz_i__(const unsigned int __x)
{
	unsigned int x, d, y;
	if (__x) {
		x = __x;
		d = __mu0_bit_digits_i__();
		y = x >> 16U; if (y != 0U) { d = d - 16U; x = y; }
		y = x >>  8U; if (y != 0U) { d = d -  8U; x = y; }
		y = x >>  4U; if (y != 0U) { d = d -  4U; x = y; }
		y = x >>  2U; if (y != 0U) { d = d -  2U; x = y; }
		y = x >>  1U;
		return __mu0_cast__(int, ((y != 0U) ? d - 2U : d - x));
	}
	return __mu0_bit_digits_i__();
}

#	endif

__mu0_static_inline__
int __mu0_cntlz_s__(const unsigned short __x)
{
	unsigned char  d = 0;
	unsigned short x = __x;
	if (x) {
		if (x & 0xFF00U) { x >>= 8U; } else { d += 8; }
		return d + __mu0_cntlz_c__(x);
	}
	return __mu0_bit_digits_s__();
}

__mu0_static_inline__
int __mu0_cntlz_c__(const unsigned char __x)
{
	unsigned char d = 0;
	unsigned char x = __x;
	if (x) {
		if (((x & 0xF0U))) { x  = x >> 4U; } else { d += 4; }
		if (((x & 0x0CU))) { x  = x >> 2U; } else { d += 2; }
		if (!(x & 0x02U) ) { d += 1;      }
		return d;
	}
	return __mu0_bit_digits_c__();
}

__mu0_static_inline__ int __mu0_cnttz_ll__(const unsigned long long __x);
__mu0_static_inline__ int __mu0_cnttz_l__ (const unsigned long      __x);
__mu0_static_inline__ int __mu0_cnttz_i__ (const unsigned int       __x);
__mu0_static_inline__ int __mu0_cnttz_s__ (const unsigned short     __x);
__mu0_static_inline__ int __mu0_cnttz_c__ (const unsigned char      __x);

__mu0_static_inline__
int __mu0_cnttz_ll__(const unsigned long long __x)
{
	const int d = __mu0_bit_digits_i__();
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	return ((__x & 0x00000000FFFFFFFFULL)
		?     __mu0_cnttz_i__(__x & 0xFFFFFFFFULL)
		: d + __mu0_cnttz_i__(__x >> d)
	);
#	else
	return ((__x & 0x00000000FFFFFFFFUL)
		?     __mu0_cnttz_i__(__x & 0xFFFFFFFFUL)
		: d + __mu0_cnttz_i__(__x >> d)
	);
#	endif
}

#	if MU0_HAVE_LP64
__mu0_static_inline__
int __mu0_cnttz_l__(const unsigned long __x)
{ return __mu0_cnttz_ll__(__x); }
#	else
__mu0_static_inline__
int __mu0_cnttz_l__(const unsigned long __x)
{ return __mu0_cnttz_i__(__x); }
#	endif

__mu0_static_inline__
int __mu0_cnttz_i__(const unsigned int __x)
{
	unsigned char d = 0;
	unsigned int  x = __x;
	if (x) {
		if (!(x & 0x0000FFFFU)) { d += 16; x = x >> 16U; }
		return d + __mu0_cnttz_s__(x);
	}
	return __mu0_bit_digits_i__();
}

__mu0_static_inline__
int __mu0_cnttz_s__(const unsigned short __x)
{
	unsigned char  d = 0;
	unsigned short x = __x;
	if (x) {
		if (!(x & 0x00ff)) { d += 8; x = x >> 8U; }
		return d + __mu0_cnttz_c__(x);
	}
	return __mu0_bit_digits_s__();
}

__mu0_static_inline__ 
int __mu0_cnttz_c__(const unsigned char __x)
{
	unsigned char d = 0;
	unsigned char x = __x;
	if (x) {
		if (!(x & 0x0f)) { d += 4; x = x >> 4U; }
		if (!(x & 0x03)) { d += 2; x = x >> 2U; }
		if (!(x & 0x01)) { d += 1;              }
		return d;
	}
	return __mu0_bit_digits_c__();
}

__mu0_static_inline__ int __mu0_clz_ll__(const unsigned long long __x);
__mu0_static_inline__ int __mu0_clz_l__ (const unsigned long      __x);
__mu0_static_inline__ int __mu0_clz_i__ (const unsigned int       __x);
__mu0_static_inline__ int __mu0_clz_s__ (const unsigned short     __x);
__mu0_static_inline__ int __mu0_clz_c__ (const unsigned char      __x);

#	if   MU0_HAVE_CC_ITLCC
#		pragma intrinsic(_lzcnt_u64)
#		pragma intrinsic(_lzcnt_u32)
#		undef  MU0_HAVE_BITWISEOP
#		define MU0_HAVE_BITWISEOP 1

		__mu0_static_inline__
		int __mu0_clz_ll__(const unsigned long long __x)
		{ return (__x) ? _lzcnt_u64(__x)                                                     : __mu0_bit_digits_ll__(); }

#		if MU0_HAVE_LP64
		__mu0_static_inline__
		int __mu0_clz_l__(const unsigned long       __x)
		{ return _mu0_clz_ll__(__x); }
#		else
		__mu0_static_inline__
		int __mu0_clz_l__(const unsigned long       __x)
		{ return (__x) ? _lzcnt_u32(__x)                                                     : __mu0_bit_digits_l__();  }
#		endif

		__mu0_static_inline__
		int __mu0_clz_i__(const unsigned int        __x)
		{ return (__x) ? _lzcnt_u32(__x)                                                     : __mu0_bit_digits_i__();  }

		__mu0_static_inline__
		int __mu0_clz_s__(const unsigned short      __x)
		{ return (__x) ? _lzcnt_u32(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_s__()) : __mu0_bit_digits_s__();  }

		__mu0_static_inline__
		int __mu0_clz_c__(const unsigned char      __x)
		{ return (__x) ? _lzcnt_u32(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_c__()) : __mu0_bit_digits_c__();  }

#	elif MU0_HAVE_CC_MSVCC
#		if MU0_HAVE_AMD64
#			pragma intrinsic(__lzcnt64)
#			pragma intrinsic(__lzcnt)
#			undef  MU0_HAVE_BITWISEOP
#			define MU0_HAVE_BITWISEOP 1

			__mu0_static_inline__
			int __mu0_clz_ll__(const unsigned long long __x)
			{ return (__x) ? __lzcnt64(__x)                                                   : __mu0_bit_digits_ll__(); }

#			if MU0_HAVE_LP64
			__mu0_static_inline__
			int __mu0_clz_l__(const unsigned long       __x)
			{ return __mu0_clz_ll__(__x);  }
#			else
			__mu0_static_inline__
			int __mu0_clz_l__(const unsigned long       __x)
			{ return (__x) ? __lzcnt(__x)                                                     : __mu0_bit_digits_l__();  }
#			endif

			__mu0_static_inline__
			int __mu0_clz_i__(const unsigned int        __x)
			{ return (__x) ? __lzcnt(__x)                                                     : __mu0_bit_digits_i__();  }

			__mu0_static_inline__
			int __mu0_clz_s__(const unsigned short      __x)
			{ return (__x) ? __lzcnt(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_s__()) : __mu0_bit_digits_s__();  }

			__mu0_static_inline__
			int __mu0_clz_c__(const unsigned char       __x)
			{ return (__x) ? __lzcnt(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_c__()) : __mu0_bit_digits_c__();  }

#		else
#			if defined(_M_X64) && !defined(_M_ARM64EC)
#				pragma intrinsic(_BitScanReverse64)
#			endif
#			pragma intrinsic(_BitScanReverse)
#			undef  MU0_HAVE_BITWISEOP
#			define MU0_HAVE_BITWISEOP 1

			__mu0_static_inline__
			int __mu0_clz_ll__(const unsigned long long __x)
			{
				unsigned long index         = 0;
			#	if defined(_M_X64) && !defined(_M_ARM64EC)
				const unsigned __int64 mask = __mu0_const_cast__(__int64, __x);
				if (__x) {
					if (_BitScanReverse64(&index, mask)) {
						return (__mu0_bit_digits_ll__() - 1) - __mu0_const_cast__(int, index);
					}
				}
			#	else
				const unsigned long mask_lo = __mu0_const_cast__(unsigned long, __x);
				const unsigned int  hdigits = __mu0_bit_digits_i__();
				const unsigned long mask_hi = __mu0_const_cast__(unsigned long, (__x >> hdigits));

				if (__x) {
					if (!_BitScanReverse(&index, mask_lo) && _BitScanReverse(&index, mask_hi)) {
						index += hdigits;
					}
					return (__mu0_bit_digits_ll__() - 1) - __mu0_const_cast__(int, index);
				}
			#	endif
				return __mu0_bit_digits_ll__();
			}

#			if MU0_HAVE_LP64
			__mu0_static_inline__
			int __mu0_clz_l__(const unsigned long       __x)
			{  return __mu0_clz_ll__(__x); }
#			else
			__mu0_static_inline__
			int __mu0_clz_l__(const unsigned long       __x)
			{
				unsigned long index = 0;
				unsigned long mask  = __x;
				if (__x) {
					if (_BitScanReverse(&index, mask)) {
						return (__mu0_bit_digits_l__() - 1) - __mu0_const_cast__(int, index);
					}
				}
				return __mu0_bit_digits_l__();
			}
#			endif

			__mu0_static_inline__
			int __mu0_clz_i__(const unsigned int        __x)
			{ return (__x) ? __mu0_clz_l__(__x)                                                     : __mu0_bit_digits_i__(); }

			__mu0_static_inline__
			int __mu0_clz_s__(const unsigned short      __x)
			{ return (__x) ? __mu0_clz_i__(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_s__()) : __mu0_bit_digits_s__(); }

			__mu0_static_inline__
			int __mu0_clz_c__(const unsigned char       __x)
			{ return (__x) ? __mu0_clz_i__(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_c__()) : __mu0_bit_digits_c__(); }

#		endif
#	elif MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUC
#		undef  MU0_HAVE_BITWISEOP
#		define MU0_HAVE_BITWISEOP 1

		__mu0_static_inline__
		int __mu0_clz_ll__(const unsigned long long __x)
		{ return (__x) ? __builtin_clzll(__x)                                                       : __mu0_bit_digits_ll__(); }

		__mu0_static_inline__
		int __mu0_clz_l__(const unsigned long       __x)
		{ return (__x) ? __builtin_clzl(__x)                                                        : __mu0_bit_digits_l__();  }

		__mu0_static_inline__
		int __mu0_clz_i__(const unsigned int        __x)
		{ return (__x) ? __builtin_clz(__x)                                                         : __mu0_bit_digits_i__();  }

		__mu0_static_inline__
		int __mu0_clz_s__(const unsigned short      __x)
		{ return (__x) ? ((__builtin_clz(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_s__()))) : __mu0_bit_digits_s__();  }

		__mu0_static_inline__
		int __mu0_clz_c__(const unsigned char       __x)
		{ return (__x) ? ((__builtin_clz(__x) - (__mu0_bit_digits_i__() - __mu0_bit_digits_c__()))) : __mu0_bit_digits_c__();  }

#	else
#		undef  MU0_HAVE_BITWISEOP
#		define MU0_HAVE_BITWISEOP 1

__mu0_static_inline__ int __mu0_clz_ll__(const unsigned long long __x) { return __mu0_cntlz_ll__ (__x); }
__mu0_static_inline__ int __mu0_clz_l__ (const unsigned long      __x) { return __mu0_cntlz_l__  (__x); }
__mu0_static_inline__ int __mu0_clz_i__ (const unsigned int       __x) { return __mu0_cntlz_i__  (__x); }
__mu0_static_inline__ int __mu0_clz_s__ (const unsigned short     __x) { return __mu0_cntlz_s__  (__x); }
__mu0_static_inline__ int __mu0_clz_c__ (const unsigned char      __x) { return __mu0_cntlz_c__  (__x); }

#	endif

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ int __mu0_clz__ (const unsigned long long __x) { return __mu0_clz_ll__ (__x); }
__mu0_overload__ int __mu0_clz__ (const unsigned long      __x) { return __mu0_clz_l__  (__x); }
__mu0_overload__ int __mu0_clz__ (const unsigned int       __x) { return __mu0_clz_i__  (__x); }
__mu0_overload__ int __mu0_clz__ (const unsigned short     __x) { return __mu0_clz_s__  (__x); }
__mu0_overload__ int __mu0_clz__ (const unsigned char      __x) { return __mu0_clz_c__  (__x); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_clz__(__x) __mu0_generic__(__x \
	, unsigned long long : __mu0_clz_ll__       \
	, unsigned long      : __mu0_clz_l__        \
	, unsigned int       : __mu0_clz_i__        \
	, unsigned short     : __mu0_clz_s__        \
	, unsigned char      : __mu0_clz_c__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_clz__(__x)                               \
	((__mu0_isofkind__(unsigned long long, __x))          \
		? __mu0_clz_ll__(__x)                              \
		: ((__mu0_isofkind__(unsigned long, __x))          \
			? __mu0_clz_l__(__x)                            \
			: ((__mu0_isofkind__(unsigned int, __x))        \
				? __mu0_clz_i__(__x)                         \
				: ((__mu0_isofkind__(unsigned short, __x))   \
					? __mu0_clz_s__(__x)                      \
					: ((__mu0_isofkind__(unsigned char, __x)) \
						? __mu0_clz_c__(__x)                   \
						: 0                                    \
					)                                         \
				)                                            \
			)                                               \
		)                                                  \
	)
#	else
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
#	endif

__mu0_static_inline__ int __mu0_ctz_ll__(const unsigned long long __x);
__mu0_static_inline__ int __mu0_ctz_l__ (const unsigned long      __x);
__mu0_static_inline__ int __mu0_ctz_i__ (const unsigned int       __x);
__mu0_static_inline__ int __mu0_ctz_s__ (const unsigned short     __x);
__mu0_static_inline__ int __mu0_ctz_c__ (const unsigned char      __x);

#	if MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUC
#		undef  MU0_HAVE_BITWISEOP
#		define MU0_HAVE_BITWISEOP 1

		__mu0_static_inline__
		int __mu0_ctz_ll__(const unsigned long long __x)
		{ return (__x) ? __builtin_ctzll(__x) : __mu0_bit_digits_ll__(); }

		__mu0_static_inline__
		int __mu0_ctz_l__(const unsigned long       __x)
		{ return (__x) ? __builtin_ctzl(__x)  : __mu0_bit_digits_l__();  }

		__mu0_static_inline__
		int __mu0_ctz_i__(const unsigned int        __x)
		{ return (__x) ? __builtin_ctz(__x)   : __mu0_bit_digits_i__();  }

		__mu0_static_inline__
		int __mu0_ctz_s__(const unsigned short      __x)
		{ return (__x) ? __builtin_ctz(__x)   : __mu0_bit_digits_s__();  }

		__mu0_static_inline__
		int __mu0_ctz_c__(const unsigned char       __x)
		{ return (__x) ? __builtin_ctz(__x)   : __mu0_bit_digits_c__();  }

#	else
#		undef  MU0_HAVE_BITWISEOP
#		define MU0_HAVE_BITWISEOP 1

__mu0_static_inline__ int __mu0_ctz_ll__(const unsigned long long __x) { return __mu0_cnttz_ll__ (__x); }
__mu0_static_inline__ int __mu0_ctz_l__ (const unsigned long      __x) { return __mu0_cnttz_l__  (__x); }
__mu0_static_inline__ int __mu0_ctz_i__ (const unsigned int       __x) { return __mu0_cnttz_i__  (__x); }
__mu0_static_inline__ int __mu0_ctz_s__ (const unsigned short     __x) { return __mu0_cnttz_s__  (__x); }
__mu0_static_inline__ int __mu0_ctz_c__ (const unsigned char      __x) { return __mu0_cnttz_c__  (__x); }

#	endif

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ int __mu0_ctz__ (const unsigned long long __x) { return __mu0_ctz_ll__ (__x); }
__mu0_overload__ int __mu0_ctz__ (const unsigned long      __x) { return __mu0_ctz_l__  (__x); }
__mu0_overload__ int __mu0_ctz__ (const unsigned int       __x) { return __mu0_ctz_i__  (__x); }
__mu0_overload__ int __mu0_ctz__ (const unsigned short     __x) { return __mu0_ctz_s__  (__x); }
__mu0_overload__ int __mu0_ctz__ (const unsigned char      __x) { return __mu0_ctz_c__  (__x); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_ctz__(__x) __mu0_generic__(__x \
	, unsigned long long : __mu0_ctz_ll__       \
	, unsigned long      : __mu0_ctz_l__        \
	, unsigned int       : __mu0_ctz_i__        \
	, unsigned short     : __mu0_ctz_s__        \
	, unsigned char      : __mu0_ctz_c__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_ctz__(__x)                               \
	((__mu0_isofkind__(unsigned long long, __x))          \
		? __mu0_ctz_ll__(__x)                              \
		: ((__mu0_isofkind__(unsigned long, __x))          \
			? __mu0_ctz_l__(__x)                            \
			: ((__mu0_isofkind__(unsigned int, __x))        \
				? __mu0_ctz_i__(__x)                         \
				: ((__mu0_isofkind__(unsigned short, __x))   \
					? __mu0_ctz_s__(__x)                      \
					: ((__mu0_isofkind__(unsigned char, __x)) \
						? __mu0_ctz_c__(__x)                   \
						: 0                                    \
					)                                         \
				)                                            \
			)                                               \
		)                                                  \
	)
#	else
#	define __mu0_ctz__(__x)                                               \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long long))          \
		? __mu0_ctz_ll__(__x)                                              \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long))          \
			? __mu0_ctz_l__(__x)                                            \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned int))        \
				? __mu0_ctz_i__(__x)                                         \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned short))   \
					? __mu0_ctz_s__(__x)                                      \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned char)) \
						? __mu0_ctz_c__(__x)                                   \
						: 0                                                    \
					)                                                         \
				)                                                            \
			)                                                               \
		)                                                                  \
	)
#	endif

#	define __mu0_countl_zero__(__x) (__mu0_clz__(__x))
#	define __mu0_countr_zero__(__x) (__mu0_ctz__(__x))

__mu0_static_inline__ int __mu0_bit_width_ll__(const unsigned long long __x);
__mu0_static_inline__ int __mu0_bit_width_l__ (const unsigned long      __x);
__mu0_static_inline__ int __mu0_bit_width_i__ (const unsigned int       __x);
__mu0_static_inline__ int __mu0_bit_width_s__ (const unsigned short     __x);
__mu0_static_inline__ int __mu0_bit_width_c__ (const unsigned char      __x);

__mu0_static_inline__
int __mu0_bit_width_ll__(const unsigned long long __x)
{
	return __mu0_bit_digits_ll__() - __mu0_ctz_ll__(__x);
}

__mu0_static_inline__
int __mu0_bit_width_l__(const unsigned long       __x)
{
	return __mu0_bit_digits_l__ () - __mu0_ctz_l__ (__x);
}

__mu0_static_inline__
int __mu0_bit_width_i__(const unsigned int        __x)
{
	return __mu0_bit_digits_i__  () - __mu0_ctz_l__  (__x);
}

__mu0_static_inline__
int __mu0_bit_width_s__(const unsigned short      __x)
{
	return __mu0_bit_digits_s__() - __mu0_ctz_s__(__x);
}
__mu0_static_inline__
int __mu0_bit_width_c__(const unsigned char       __x)
{
	return __mu0_bit_digits_c__() - __mu0_ctz_c__(__x);
}

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ int __mu0_bit_width__ (const unsigned long long __x) { return __mu0_bit_width_ll__ (__x); }
__mu0_overload__ int __mu0_bit_width__ (const unsigned long      __x) { return __mu0_bit_width_l__  (__x); }
__mu0_overload__ int __mu0_bit_width__ (const unsigned int       __x) { return __mu0_bit_width_i__  (__x); }
__mu0_overload__ int __mu0_bit_width__ (const unsigned short     __x) { return __mu0_bit_width_s__  (__x); }
__mu0_overload__ int __mu0_bit_width__ (const unsigned char      __x) { return __mu0_bit_width_c__  (__x); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_bit_width__(__x) __mu0_generic__(__x \
	, unsigned long long : __mu0_bit_width_ll__       \
	, unsigned long      : __mu0_bit_width_l__        \
	, unsigned int       : __mu0_bit_width_i__        \
	, unsigned short     : __mu0_bit_width_s__        \
	, unsigned char      : __mu0_bit_width_c__        \
) (__x)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_bit_width__(__x)                         \
	((__mu0_isofkind__(unsigned long long, __x))          \
		? __mu0_bit_width_ll__(__x)                        \
		: ((__mu0_isofkind__(unsigned long, __x))          \
			? __mu0_bit_width_l__(__x)                      \
			: ((__mu0_isofkind__(unsigned int, __x))        \
				? __mu0_bit_width_i__(__x)                   \
				: ((__mu0_isofkind__(unsigned short, __x))   \
					? __mu0_bit_width_s__(__x)                \
					: ((__mu0_isofkind__(unsigned char, __x)) \
						? __mu0_bit_width_c__(__x)             \
						: 0                                    \
					)                                         \
				)                                            \
			)                                               \
		)                                                  \
	)
#	else
#	define __mu0_bit_width__(__x)                                         \
	((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long long))          \
		? __mu0_bit_width_ll__(__x)                                        \
		: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned long))          \
			? __mu0_bit_width_l__(__x)                                      \
			: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned int))        \
				? __mu0_bit_width_i__(__x)                                   \
				: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned short))   \
					? __mu0_bit_width_s__(__x)                                \
					: ((__mu0_sizeof__(__x) == __mu0_sizeof__(unsigned char)) \
						? __mu0_bit_width_c__(__x)                             \
						: 0                                                    \
					)                                                         \
				)                                                            \
			)                                                               \
		)                                                                  \
	)
#	endif

__mu0_static_inline__ unsigned long long __mu0_bit_ceil_ll__(const unsigned long long __x);
__mu0_static_inline__ unsigned long      __mu0_bit_ceil_l__ (const unsigned long      __x);
__mu0_static_inline__ unsigned int       __mu0_bit_ceil_i__ (const unsigned int       __x);
__mu0_static_inline__ unsigned short     __mu0_bit_ceil_s__ (const unsigned short     __x);
__mu0_static_inline__ unsigned char      __mu0_bit_ceil_c__ (const unsigned char      __x);

__mu0_static_inline__
unsigned long long __mu0_bit_ceil_ll__(const unsigned long long __x)
{
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	const unsigned long long one = 1ULL;
#	else
	const unsigned long long one = 1UL;
#	endif
	return __x > 1 ? (one << __mu0_bit_width_ll__(__x - one)) : one;
}

__mu0_static_inline__
unsigned long __mu0_bit_ceil_l__(const unsigned long            __x)
{
	const unsigned long one = 1UL;
	return __x > 1 ? (one << __mu0_bit_width_l__(__x - one)) : one;
}

__mu0_static_inline__
unsigned int __mu0_bit_ceil_i__(const unsigned int              __x)
{
	const unsigned int one = 1U;
	return __x > 1 ? (one << __mu0_bit_width_i__(__x - one)) : one;
}

__mu0_static_inline__
unsigned short __mu0_bit_ceil_s__(const unsigned short          __x)
{
	const unsigned short one = 1;
	return __x > 1 ? (one << __mu0_bit_width_s__(__x - one)) : one;
}

__mu0_static_inline__
unsigned char __mu0_bit_ceil_c__(const unsigned char            __x)
{
	const unsigned char one = 1;
	return __x > 1 ? (one << __mu0_bit_width_c__(__x - one)) : one;
}

__mu0_static_inline__ unsigned long long __mu0_bit_floor_ll__(const unsigned long long __x);
__mu0_static_inline__ unsigned long      __mu0_bit_floor_l__ (const unsigned long      __x);
__mu0_static_inline__ unsigned int       __mu0_bit_floor_i__ (const unsigned int       __x);
__mu0_static_inline__ unsigned short     __mu0_bit_floor_s__ (const unsigned short     __x);
__mu0_static_inline__ unsigned char      __mu0_bit_floor_c__ (const unsigned char      __x);

__mu0_static_inline__
unsigned long long __mu0_bit_floor_ll__(const unsigned long long __x)
{
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	const unsigned long long one  = 1ULL;
	const unsigned long long zero = 0ULL;
#	else
	const unsigned long long one  = 1UL;
	const unsigned long long zero = 0UL;
#	endif
	return __x != zero ? (one << (__mu0_bit_width_ll__(__x) - one)) : zero;
}

__mu0_static_inline__
unsigned long __mu0_bit_floor_l__(const unsigned long            __x)
{
	const unsigned long one  = 1UL;
	const unsigned long zero = 0UL;
	return __x != zero ? (one << (__mu0_bit_width_l__(__x) - one)) : zero;
}

__mu0_static_inline__
unsigned int __mu0_bit_floor_i__(const unsigned int              __x)
{
	const unsigned int one  = 1U;
	const unsigned int zero = 0U;
	return __x != zero ? (one << (__mu0_bit_width_i__(__x) - one)) : zero;
}

__mu0_static_inline__
unsigned short __mu0_bit_floor_s__(const unsigned short          __x)
{
	const unsigned short one  = 1;
	const unsigned short zero = 0;
	return __x != zero ? (one << (__mu0_bit_width_s__(__x) - one)) : zero;
}

__mu0_static_inline__
unsigned char __mu0_bit_floor_c__(const unsigned char            __x)
{
	const unsigned char one  = 1;
	const unsigned char zero = 0;
	return __x != zero ? (one << (__mu0_bit_width_c__(__x) - one)) : zero;
}

#	define __mu0_bit_reverse__(_Tp, __x)                                                               \
	__mu0_scope_begin__                                                                                \
		unsigned int __mu0_bit_reverse__digits__ = __mu0_cast__(unsigned int, __mu0_bit_digits__(__x)); \
		_Tp          __mu0_bit_reverse__mask__   = ~(__mu0_const_cast__(_Tp, 0));                       \
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
#	define __mu0_bitset_format_u8__(__x) \
	  (((__x) & 0x80U) ? '1' : '0')      \
	, (((__x) & 0x40U) ? '1' : '0')      \
	, (((__x) & 0x20U) ? '1' : '0')      \
	, (((__x) & 0x10U) ? '1' : '0')      \
	, (((__x) & 0x08U) ? '1' : '0')      \
	, (((__x) & 0x04U) ? '1' : '0')      \
	, (((__x) & 0x02U) ? '1' : '0')      \
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

#	define __mu0_bitset_print_u8__(__x)                    \
	__mu0_console_log__("" __mu0_bitset_pattern_u8__  "\n" \
	, __mu0_bitset_format_u8__(__mu0_const_cast__(unsigned char,       __x)))

#	define __mu0_bitset_print_u16__(__x)                   \
	__mu0_console_log__("" __mu0_bitset_pattern_u16__ "\n" \
	, __mu0_bitset_format_u16__(__mu0_const_cast__(unsigned short,     __x)))

#	define __mu0_bitset_print_u32__(__x)                   \
	__mu0_console_log__("" __mu0_bitset_pattern_u32__ "\n" \
	, __mu0_bitset_format_u32__(__mu0_const_cast__(unsigned int,       __x)))

#	if MU0_HAVE_LP64
#	define __mu0_bitset_print_u64__(__x)                   \
	__mu0_console_log__("" __mu0_bitset_pattern_u64__ "\n" \
	, __mu0_bitset_format_u64__(__mu0_const_cast__(unsigned long,      __x)))
#	else
#	define __mu0_bitset_print_u64__(__x)                   \
	__mu0_console_log__("" __mu0_bitset_pattern_u64__ "\n" \
	, __mu0_bitset_format_u64__(__mu0_const_cast__(unsigned long long, __x)))
#	endif

#	if !MU0_HAVE_BITWISEOP
#		error mu0_bitwiseop.h
#	endif

#endif /* !MU0_BITWISEOP_H */

/* EOF */