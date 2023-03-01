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
#	define __mu0_min__(__a, __b) (((__a) < (__b)) ? (__a) : (__b))
#	define __mu0_max__(__a, __b) (((__a) > (__b)) ? (__a) : (__b))
#	define __mu0_abs__(__a)      (((__a) == 0   ) ? 0     : (((__a) > 0) ? (__a) : -(__a)))
#	endif

#	define __mu0_inline_abs__(__a) (((__a) == 0   ) ? 0     : (((__a) > 0) ? (__a) : -(__a)))

#	define __mu0_clamp__(__a, __c, __b) \
	(__mu0_max__(__c, __mu0_min__(__a, __b)))

#	define ___mu0_gcd_11___(__a, __b) (0)
#	define ___mu0_gcd_10___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_11___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_09___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_10___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_07___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_09___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_06___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_07___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_05___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_06___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_04___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_05___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_03___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_04___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_02___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_03___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_01___(__a, __b) ((((!(__b))) * (__a)) + (!!(__b)) * ___mu0_gcd_02___((__b), (__a) % ((__b) + !(__b))))
#	define ___mu0_gcd_00___(__a, __b) (((__a >= __b) * ___mu0_gcd_01___(__a, __b) + (__a < __b) * ___mu0_gcd_01___(__b,__a)))
#	define ___mu0_lcm_00___(__a, __b) ((((__a) * (__b))) / ___mu0_gcd_00___(__a, __b))

#	define ___mu0_gcd___(_Uint, __a, __b, __c)               \
__mu0_scope_begin__                                         \
	_Uint ___mu0_gcd__a___ = __mu0_const_cast__(_Uint, __a); \
	_Uint ___mu0_gcd__b___ = __mu0_const_cast__(_Uint, __b); \
	if (___mu0_gcd__a___ && ___mu0_gcd__b___) { for (        \
			;                                                  \
			   (___mu0_gcd__a___ %= ___mu0_gcd__b___)          \
			&& (___mu0_gcd__b___ %= ___mu0_gcd__a___)          \
			;                                                  \
		);                                                    \
	}                                                        \
	__c = ___mu0_gcd__a___ | ___mu0_gcd__b___;               \
__mu0_scope_end__

#	define ___mu0_lcm___(_Uint, __a, __b, __c)        \
__mu0_scope_begin__                                  \
	_Uint ___mu0_lcm__c___;                           \
	___mu0_gcd___(_Uint, __a, __b, ___mu0_lcm__c___); \
	__c = (___mu0_lcm__c___                           \
		? ((__a * __b) / ___mu0_lcm__c___)             \
		: __mu0_const_cast__(_Uint, 0)                 \
	);                                                \
__mu0_scope_end__

__mu0_static_inline__
const unsigned long long __mu0_gcd_ll__(const unsigned long long __a, const unsigned long long __b)
{
	unsigned long long c;
	___mu0_gcd___(unsigned long long, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned long __mu0_gcd_l__(const unsigned long __a, const unsigned long __b)
{
	unsigned long c;
	___mu0_gcd___(unsigned long, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned int __mu0_gcd_i__(const unsigned int __a, const unsigned int __b)
{
	unsigned int c;
	___mu0_gcd___(unsigned int, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned short __mu0_gcd_s__(const unsigned short __a, const unsigned short __b)
{
	unsigned short c;
	___mu0_gcd___(unsigned short, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned char __mu0_gcd_c__(const unsigned char __a, const unsigned char __b)
{
	unsigned char c;
	___mu0_gcd___(unsigned char, __a, __b, c);
	return c;
}

#	define __mu0_inline_gcd_const__(_Int, __a, __b) __mu0_const_cast__(_Int, ___mu0_gcd_00___(__mu0_inline_abs__(__a), __mu0_inline_abs__(__b)))
#	define __mu0_inline_gcd__(_Int, __a, __b)       __mu0_const_cast__(_Int, __mu0_gcd_i__   (__mu0_inline_abs__(__a), __mu0_inline_abs__(__b)))

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
	unsigned long long c;
	___mu0_lcm___(unsigned long long, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned long __mu0_lcm_l__(const unsigned long __a, const unsigned long __b)
{
	unsigned long c;
	___mu0_lcm___(unsigned long, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned int __mu0_lcm_i__(const unsigned int __a, const unsigned int __b)
{
	unsigned int c;
	___mu0_lcm___(unsigned int, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned short __mu0_lcm_s__(const unsigned short __a, const unsigned short __b)
{
	unsigned short c;
	___mu0_lcm___(unsigned short, __a, __b, c);
	return c;
}

__mu0_static_inline__
const unsigned char __mu0_lcm_c__(const unsigned char __a, const unsigned char __b)
{
	unsigned char c;
	___mu0_lcm___(unsigned char, __a, __b, c);
	return c;
}

#	define __mu0_inline_lcm_const__(_Int, __a, __b) __mu0_const_cast__(_Int, ___mu0_lcm_00___(__mu0_inline_abs__(__a), __mu0_inline_abs__(__b)))
#	define __mu0_inline_lcm__(_Int, __a, __b)       __mu0_const_cast__(_Int, __mu0_lcm_i__   (__mu0_inline_abs__(__a), __mu0_inline_abs__(__b)))

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