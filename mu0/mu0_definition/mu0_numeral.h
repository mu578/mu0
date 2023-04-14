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

#	define __mu0_inline_min__(__a, __b) (((__a) < (__b)) ? (__a) : (__b))
#	define __mu0_inline_max__(__a, __b) (((__a) > (__b)) ? (__a) : (__b))
#	define __mu0_inline_abs__(__a)      (((__a) == 0   ) ? 0     : (((__a) > 0) ? (__a) : -(__a)))

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
#	define __mu0_min__(__a, __b) __mu0_inline_min__(__a, __b)
#	define __mu0_max__(__a, __b) __mu0_inline_max__(__a, __b)
#	define __mu0_abs__(__a)      __mu0_inline_abs__(__a)
#	endif

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

#	define ___mu0_lcm___(_Uint, __a, __b, __c)         \
__mu0_scope_begin__                                   \
	_Uint ___mu0_lcm__u1___;                           \
	___mu0_gcd___(_Uint, __a, __b, ___mu0_lcm__u1___); \
	__c = (___mu0_lcm__u1___                           \
		? ((__a * __b) / ___mu0_lcm__u1___)             \
		: __mu0_const_cast__(_Uint, 0)                  \
	);                                                 \
__mu0_scope_end__

__mu0_static_inline__
const ___mu0_uint8_t___ __mu0_gcd_u8__(const ___mu0_uint8_t___ __a, const ___mu0_uint8_t___ __b)
{
	___mu0_uint8_t___ c;
	___mu0_gcd___(___mu0_uint8_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uintx_t___ __mu0_gcd_ux__(const ___mu0_uintx_t___ __a, const ___mu0_uintx_t___ __b)
{
	___mu0_uintx_t___ c;
	___mu0_gcd___(___mu0_uintx_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uint4_t___ __mu0_gcd_u4__(const ___mu0_uint4_t___ __a, const ___mu0_uint4_t___ __b)
{
	___mu0_uint4_t___ c;
	___mu0_gcd___(___mu0_uint4_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uint2_t___ __mu0_gcd_u2__(const ___mu0_uint2_t___ __a, const ___mu0_uint2_t___ __b)
{
	___mu0_uint2_t___ c;
	___mu0_gcd___(___mu0_uint2_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uint1_t___ __mu0_gcd_u1__(const ___mu0_uint1_t___ __a, const ___mu0_uint1_t___ __b)
{
	___mu0_uint1_t___ c;
	___mu0_gcd___(___mu0_uint1_t___, __a, __b, c);
	return c;
}

#	define __mu0_inline_gcd_constexpr__(__a, __b) __mu0_const_cast__(___mu0_uint4_t___, ((__a) && (__b) ? ___mu0_gcd_00___(__mu0_inline_abs__(__a), __mu0_inline_abs__(__b)) : 0))
#	define __mu0_inline_gcd__(__a, __b)       __mu0_gcd_u4__(        \
	  __mu0_const_cast__(___mu0_uint4_t___, __mu0_inline_abs__(__a)) \
	, __mu0_const_cast__(___mu0_uint4_t___, __mu0_inline_abs__(__b)) \
)

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const ___mu0_uint8_t___ __mu0_gcd__(const ___mu0_uint8_t___ __a, const ___mu0_uint8_t___ __b) { return __mu0_gcd_u8__(__a, __b); }
__mu0_overload__ const ___mu0_uintx_t___ __mu0_gcd__(const ___mu0_uintx_t___ __a, const ___mu0_uintx_t___ __b) { return __mu0_gcd_ux__(__a, __b); }
__mu0_overload__ const ___mu0_uint4_t___ __mu0_gcd__(const ___mu0_uint4_t___ __a, const ___mu0_uint4_t___ __b) { return __mu0_gcd_u4__(__a, __b); }
__mu0_overload__ const ___mu0_uint2_t___ __mu0_gcd__(const ___mu0_uint2_t___ __a, const ___mu0_uint2_t___ __b) { return __mu0_gcd_u2__(__a, __b); }
__mu0_overload__ const ___mu0_uint1_t___ __mu0_gcd__(const ___mu0_uint1_t___ __a, const ___mu0_uint1_t___ __b) { return __mu0_gcd_u1__(__a, __b); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_gcd__(__a, __b) __mu0_generic__((__a)+(__b) \
	, ___mu0_uint8_t___ : __mu0_gcd_u8__                     \
	, ___mu0_uintx_t___ : __mu0_gcd_ux__                     \
	, ___mu0_uint4_t___ : __mu0_gcd_u4__                     \
	, ___mu0_uint2_t___ : __mu0_gcd_u2__                     \
	, ___mu0_uint1_t___ : __mu0_gcd_u1__                     \
) (__a, __b)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_gcd__(__a, __b)                                        \
	((__mu0_isofkind__(___mu0_uint8_t___, ((__a)+(__b))))               \
		? __mu0_gcd_u8__(__a, __b)                                       \
		: ((__mu0_isofkind__(___mu0_uintx_t___, ((__a)+(__b))))          \
			? __mu0_gcd_ux__(__a, __b)                                    \
			: ((__mu0_isofkind__(___mu0_uint4_t___, ((__a)+(__b))))       \
				? __mu0_gcd_u4__(__a, __b)                                 \
				: ((__mu0_isofkind__(___mu0_uint2_t___, ((__a)+(__b))))    \
					? __mu0_gcd_u2__(__a, __b)                              \
					: ((__mu0_isofkind__(___mu0_uint1_t___, ((__a)+(__b)))) \
						? __mu0_gcd_u1__(__a, __b)                           \
						: 0                                                  \
					)                                                       \
				)                                                          \
			)                                                             \
		)                                                                \
	)
#	else
#	define __mu0_gcd__(__a, __b)                                                        \
	((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint8_t___))               \
		? __mu0_gcd_u8__(__a, __b)                                                       \
		: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uintx_t___))          \
			? __mu0_gcd_ux__(__a, __b)                                                    \
			: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint4_t___))       \
				? __mu0_gcd_u4__(__a, __b)                                                 \
				: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint2_t___))    \
					? __mu0_gcd_u2__(__a, __b)                                              \
					: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint1_t___)) \
						? __mu0_gcd_u1__(__a, __b)                                           \
						: 0                                                                  \
					)                                                                       \
				)                                                                          \
			)                                                                             \
		)                                                                                \
	)
#	endif

__mu0_static_inline__
const ___mu0_uint8_t___ __mu0_lcm_u8__(const ___mu0_uint8_t___ __a, const ___mu0_uint8_t___ __b)
{
	___mu0_uint8_t___ c;
	___mu0_lcm___(___mu0_uint8_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uintx_t___ __mu0_lcm_ux__(const ___mu0_uintx_t___ __a, const ___mu0_uintx_t___ __b)
{
	___mu0_uintx_t___ c;
	___mu0_lcm___(___mu0_uintx_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uint4_t___ __mu0_lcm_u4__(const ___mu0_uint4_t___ __a, const ___mu0_uint4_t___ __b)
{
	___mu0_uint4_t___ c;
	___mu0_lcm___(___mu0_uint4_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uint2_t___ __mu0_lcm_u2__(const ___mu0_uint2_t___ __a, const ___mu0_uint2_t___ __b)
{
	___mu0_uint2_t___ c;
	___mu0_lcm___(___mu0_uint2_t___, __a, __b, c);
	return c;
}

__mu0_static_inline__
const ___mu0_uint1_t___ __mu0_lcm_u1__(const ___mu0_uint1_t___ __a, const ___mu0_uint1_t___ __b)
{
	___mu0_uint1_t___ c;
	___mu0_lcm___(___mu0_uint1_t___, __a, __b, c);
	return c;
}

#	define __mu0_inline_lcm_constexpr__(__a, __b) __mu0_const_cast__(___mu0_uint4_t___, ((__a) && (__b) ? ___mu0_lcm_00___(__mu0_inline_abs__(__a), __mu0_inline_abs__(__b)) : 0))
#	define __mu0_inline_lcm__(__a, __b)       __mu0_lcm_u4__(        \
	  __mu0_const_cast__(___mu0_uint4_t___, __mu0_inline_abs__(__a)) \
	, __mu0_const_cast__(___mu0_uint4_t___, __mu0_inline_abs__(__b)) \
)

#	if   MU0_HAVE_OVERLOAD
__mu0_overload__ const ___mu0_uint8_t___ __mu0_lcm__(const ___mu0_uint8_t___ __a, const ___mu0_uint8_t___ __b) { return __mu0_lcm_u8__(__a, __b); }
__mu0_overload__ const ___mu0_uintx_t___ __mu0_lcm__(const ___mu0_uintx_t___ __a, const ___mu0_uintx_t___ __b) { return __mu0_lcm_ux__(__a, __b); }
__mu0_overload__ const ___mu0_uint4_t___ __mu0_lcm__(const ___mu0_uint4_t___ __a, const ___mu0_uint4_t___ __b) { return __mu0_lcm_u4__(__a, __b); }
__mu0_overload__ const ___mu0_uint2_t___ __mu0_lcm__(const ___mu0_uint2_t___ __a, const ___mu0_uint2_t___ __b) { return __mu0_lcm_u2__(__a, __b); }
__mu0_overload__ const ___mu0_uint1_t___ __mu0_lcm__(const ___mu0_uint1_t___ __a, const ___mu0_uint1_t___ __b) { return __mu0_lcm_u1__(__a, __b); }
#	elif MU0_HAVE_GENERIC
#	define __mu0_lcm__(__a, __b) __mu0_generic__((__a)+(__b) \
	, ___mu0_uint8_t___ : __mu0_lcm_u8__                     \
	, ___mu0_uintx_t___ : __mu0_lcm_ux__                     \
	, ___mu0_uint4_t___ : __mu0_lcm_u4__                     \
	, ___mu0_uint2_t___ : __mu0_lcm_u2__                     \
	, ___mu0_uint1_t___ : __mu0_lcm_u1__                     \
) (__a, __b)
#	elif MU0_HAVE_TYPEOF
#	define __mu0_lcm__(__a, __b)                                        \
	((__mu0_isofkind__(___mu0_uint8_t___, ((__a)+(__b))))               \
		? __mu0_lcm_u8__(__a, __b)                                       \
		: ((__mu0_isofkind__(___mu0_uintx_t___, ((__a)+(__b))))          \
			? __mu0_lcm_ux__(__a, __b)                                    \
			: ((__mu0_isofkind__(___mu0_uint4_t___, ((__a)+(__b))))       \
				? __mu0_lcm_u4__(__a, __b)                                 \
				: ((__mu0_isofkind__(___mu0_uint2_t___, ((__a)+(__b))))    \
					? __mu0_lcm_u2__(__a, __b)                              \
					: ((__mu0_isofkind__(___mu0_uint1_t___, ((__a)+(__b)))) \
						? __mu0_lcm_u1__(__a, __b)                           \
						: 0                                                  \
					)                                                       \
				)                                                          \
			)                                                             \
		)                                                                \
	)
#	else
#	define __mu0_lcm__(__a, __b)                                                        \
	((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint8_t___))               \
		? __mu0_lcm_u8__(__a, __b)                                                       \
		: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uintx_t___))          \
			? __mu0_lcm_ux__(__a, __b)                                                    \
			: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint4_t___))       \
				? __mu0_lcm_u4__(__a, __b)                                                 \
				: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint2_t___))    \
					? __mu0_lcm_u2__(__a, __b)                                              \
					: ((__mu0_sizeof__(((__a)+(__b))) == __mu0_sizeof__(___mu0_uint1_t___)) \
						? __mu0_lcm_u1__(__a, __b)                                           \
						: 0                                                                  \
					)                                                                       \
				)                                                                          \
			)                                                                             \
		)                                                                                \
	)
#	endif

#endif /* !MU0_NUMERAL_H */

/* EOF */