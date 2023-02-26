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

// mu0_numeral.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_attribute.h>
#include <mu0/mu0_definition/mu0_feature.h>

#ifndef MU0_NUMERAL_H
#define MU0_NUMERAL_H 1

#	if MU0_HAVE_TYPEOF && MU0_HAVE_EXTENSION
#	define __mu0_min__(__a, __b)                             \
	__mu0_extension__ ({                                     \
		__mu0_typeof__(((__a)+(__b))) __mu0_max__a__ = (__a); \
		__mu0_typeof__(((__a)+(__b))) __mu0_max__b__ = (__b); \
		(__mu0_max__a__ < __mu0_max__b__                      \
			? __mu0_max__a__                                   \
			: __mu0_max__b__                                   \
		);                                                    \
	})
#	define __mu0_max__(__a, __b)                             \
	__mu0_extension__ ({                                     \
		__mu0_typeof__(((__a)+(__b))) __mu0_max__a__ = (__a); \
		__mu0_typeof__(((__a)+(__b))) __mu0_max__b__ = (__b); \
		(__mu0_max__a__ > __mu0_max__b__                      \
			? __mu0_max__a__                                   \
			: __mu0_max__b__                                   \
		);                                                    \
	})
#	define __mu0_abs__(__a) \
	__mu0_extension__ ({                           \
		__mu0_typeof__(__a) __mu0_abs__a__ = (__a); \
		(__mu0_abs__a__ == 0 ? 0 : (                \
			__mu0_abs__a__ > 0                       \
				?  __mu0_abs__a__                     \
				: -__mu0_abs__a__                     \
		));                                         \
	})
#	else
#	define __mu0_min__(__a, __b)      (((__a) < (__b)) ? (__a) : (__b))
#	define __mu0_max__(__a, __b)      (((__a) > (__b)) ? (__a) : (__b))
#	define __mu0_abs__(__a)           (((__a) == 0   ) ? 0     : (((__a) > 0) ? (__a) : -(__a)))
#	endif

#	define __mu0_clamp__(__a, __b, __c) (__mu0_max__(__b, __mu0_min__(__a, __c)))

__mu0_static_inline__
const unsigned long long __mu0_gcd_ll__(const unsigned long long __a, const unsigned long long __b)
{
	long long a = __a;
	long long b = __b;
	if (a && b) { for(; (a %= b) && (b %= a);); }
	return a | b;
}

__mu0_static_inline__
const unsigned long __mu0_gcd_l__(const unsigned long __a, const unsigned long __b)
{
	long a = __a;
	long b = __b;
	if (a && b) { for(; (a %= b) && (b %= a);); }
	return a | b;
}

__mu0_static_inline__
const unsigned int __mu0_gcd_i__(const unsigned int __a, const unsigned int __b)
{
	unsigned int a = __a;
	unsigned int b = __b;
	if (a && b) { for(; (a %= b) && (b %= a);); }
	return a | b;
}

__mu0_static_inline__
const unsigned short __mu0_gcd_s__(const unsigned short __a, const unsigned short __b)
{
	unsigned short a = __a;
	unsigned short b = __b;
	if (a && b) { for(; (a %= b) && (b %= a);); }
	return a | b;
}

__mu0_static_inline__
const unsigned char __mu0_gcd_c__(const unsigned char __a, const unsigned char __b)
{
	return (__mu0_const_cast__(unsigned char
		, __mu0_gcd_i__(
			  __mu0_const_cast__(unsigned int, __a)
			, __mu0_const_cast__(unsigned int, __b)
	)));
}

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const unsigned long long __mu0_gcd__ (const unsigned long long __a, const unsigned long long __b) { return __mu0_gcd_ll__ (__a, __b); }
__mu0_overload__ const unsigned long      __mu0_gcd__ (const unsigned long      __a, const unsigned long      __b) { return __mu0_gcd_l__  (__a, __b); }
__mu0_overload__ const unsigned int       __mu0_gcd__ (const unsigned int       __a, const unsigned int       __b) { return __mu0_gcd_i__  (__a, __b); }
__mu0_overload__ const unsigned short     __mu0_gcd__ (const unsigned short     __a, const unsigned short     __b) { return __mu0_gcd_s__  (__a, __b); }
__mu0_overload__ const unsigned char      __mu0_gcd__ (const unsigned char      __a, const unsigned char      __b) { return __mu0_gcd_c__  (__a, __b); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_gcd__(__a, __b) __mu0_generic__((__a)+(__b) \
	, unsigned long long : __mu0_gcd_ll__                    \
	, unsigned long      : __mu0_gcd_l__                     \
	, unsigned int       : __mu0_gcd_i__                     \
	, unsigned short     : __mu0_gcd_s__                     \
	, unsigned char      : __mu0_gcd_c__                     \
) (__a, __b)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_gcd__(__a, __b)                                    \
	((__mu0_isofkind__(unsigned long long, ((__a)+(__b))))          \
		? __mu0_gcd_ll__(__a, __b)                                   \
		: ((__mu0_isofkind__(unsigned long, ((__a)+(__b))))          \
			? __mu0_gcd_l__(__a, __b)                                 \
			: ((__mu0_isofkind__(unsigned int, ((__a)+(__b))))        \
				? __mu0_gcd_i__(__a, __b)                              \
				: ((__mu0_isofkind__(unsigned short, ((__a)+(__b))))   \
					? __mu0_gcd_s__(__a, __b)                           \
					: ((__mu0_isofkind__(unsigned char, ((__a)+(__b)))) \
						? __mu0_gcd_c__(__a, __b)                        \
						: 0                                              \
					)                                                   \
				)                                                      \
			)                                                         \
		)                                                            \
	)
#	else
#	define __mu0_gcd__(__a, __b)                                                    \
	((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned long long))          \
		? __mu0_gcd_ll__(__a, __b)                                                   \
		: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned long))          \
			? __mu0_gcd_l__(__a, __b)                                                 \
			: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned int))        \
				? __mu0_gcd_i__(__a, __b)                                              \
				: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned short))   \
					? __mu0_gcd_s__(__a, __b)                                           \
					: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned char)) \
						? __mu0_gcd_c__(__a, __b)                                        \
						: 0                                                              \
					)                                                                   \
				)                                                                      \
			)                                                                         \
		)                                                                            \
	)
#	endif

__mu0_static_inline__
const unsigned long long __mu0_lcm_ll__(const unsigned long long __a, const unsigned long long __b)
{
	const unsigned long long c = __mu0_gcd_ll__(__a, __b);
#	if MU0_HAVE_C99 || MU0_HAVE_CPP11
	return c ? (__a / c * __b) : 0ULL;
#	else
	return c ? (__a / c * __b) : 0UL;
#	endif
}

__mu0_static_inline__
const unsigned long __mu0_lcm_l__(const unsigned long __a, const unsigned long __b)
{
	const unsigned long c = __mu0_gcd_l__(__a, __b);
	return c ? (__a / c * __b) : 0UL;
}

__mu0_static_inline__
const unsigned int __mu0_lcm_i__(const unsigned int __a, const unsigned int __b)
{
	const unsigned int c = __mu0_gcd_i__(__a, __b);
	return c ? (__a / c * __b) : 0U;
}

__mu0_static_inline__
const unsigned short __mu0_lcm_s__(const unsigned short __a, const unsigned short __b)
{
	const unsigned short c = __mu0_gcd_s__(__a, __b);
	return c ? (__a / c * __b) : 0;
}

__mu0_static_inline__
const unsigned char __mu0_lcm_c__(const unsigned char __a, const unsigned char __b)
{
	return (__mu0_const_cast__(unsigned char
		, __mu0_lcm_i__(
			  __mu0_const_cast__(unsigned int, __a)
			, __mu0_const_cast__(unsigned int, __b)
	)));
}

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const unsigned long long __mu0_lcm__ (const unsigned long long __a, const unsigned long long __b) { return __mu0_lcm_ll__ (__a, __b); }
__mu0_overload__ const unsigned long      __mu0_lcm__ (const unsigned long      __a, const unsigned long      __b) { return __mu0_lcm_l__  (__a, __b); }
__mu0_overload__ const unsigned int       __mu0_lcm__ (const unsigned int       __a, const unsigned int       __b) { return __mu0_lcm_i__  (__a, __b); }
__mu0_overload__ const unsigned short     __mu0_lcm__ (const unsigned short     __a, const unsigned short     __b) { return __mu0_lcm_s__  (__a, __b); }
__mu0_overload__ const unsigned char      __mu0_lcm__ (const unsigned char      __a, const unsigned char      __b) { return __mu0_lcm_c__  (__a, __b); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_lcm__(__a, __b) __mu0_generic__((__a)+(__b) \
	, unsigned long long : __mu0_lcm_ll__                    \
	, unsigned long      : __mu0_lcm_l__                     \
	, unsigned int       : __mu0_lcm_i__                     \
	, unsigned short     : __mu0_lcm_s__                     \
	, unsigned char      : __mu0_lcm_c__                     \
) (__a, __b)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_lcm__(__a, __b)                                    \
	((__mu0_isofkind__(unsigned long long, ((__a)+(__b))))          \
		? __mu0_lcm_ll__(__a, __b)                                   \
		: ((__mu0_isofkind__(unsigned long, ((__a)+(__b))))          \
			? __mu0_lcm_l__(__a, __b)                                 \
			: ((__mu0_isofkind__(unsigned int, ((__a)+(__b))))        \
				? __mu0_lcm_i__(__a, __b)                              \
				: ((__mu0_isofkind__(unsigned short, ((__a)+(__b))))   \
					? __mu0_lcm_s__(__a, __b)                           \
					: ((__mu0_isofkind__(unsigned char, ((__a)+(__b)))) \
						? __mu0_lcm_c__(__a, __b)                        \
						: 0                                              \
					)                                                   \
				)                                                      \
			)                                                         \
		)                                                            \
	)
#	else
#	define __mu0_lcm__(__a, __b)                                                    \
	((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned long long))          \
		? __mu0_lcm_ll__(__a, __b)                                                   \
		: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned long))          \
			? __mu0_lcm_l__(__a, __b)                                                 \
			: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned int))        \
				? __mu0_lcm_i__(__a, __b)                                              \
				: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned short))   \
					? __mu0_lcm_s__(__a, __b)                                           \
					: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(unsigned char)) \
						? __mu0_lcm_c__(__a, __b)                                        \
						: 0                                                              \
					)                                                                   \
				)                                                                      \
			)                                                                         \
		)                                                                            \
	)
#	endif

#endif /* !MU0_NUMERAL_H */

/* EOF */