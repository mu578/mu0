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

// mu0_chartrait.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_CHARTRAIT_H
#define MU0_CHARTRAIT_H 1

MU0_BEGIN_CDECL

typedef ___mu0_uint4_t___ ___mu0_uchar4_t___;
typedef ___mu0_sint4_t___ ___mu0_schar4_t___;
typedef ___mu0_uint4_t___ ___mu0_tchar4_t___;

typedef ___mu0_uint2_t___ ___mu0_uchar2_t___;
typedef ___mu0_sint2_t___ ___mu0_schar2_t___;
typedef ___mu0_uint2_t___ ___mu0_tchar2_t___;

typedef ___mu0_uint1_t___ ___mu0_uchar1_t___;
typedef ___mu0_sint1_t___ ___mu0_schar1_t___;
typedef ___mu0_tint1_t___ ___mu0_tchar1_t___;

#	define __mu0_cfind_n__(_CharT, __src, __pos, __n, __char, __r) \
__mu0_scope_begin__                                               \
	___mu0_uint4_t___ __mu0_cfind_n__x__ = 0U;                     \
	___mu0_sint8_t___ __mu0_cfind_n__i__;                          \
	if (__pos < __n) {                                             \
		__r                = __src + __pos;                         \
		__mu0_cfind_n__i__ = __n   - __pos;                         \
		for (; __mu0_cfind_n__i__; (void) --__mu0_cfind_n__i__) {   \
			if (*__r == __char) {                                    \
				__mu0_cfind_n__x__ = 1U;                              \
				break;                                                \
			}                                                        \
			++__r;                                                   \
		}                                                           \
	}                                                              \
	if (!__mu0_cfind_n__x__) {                                     \
		__r = __mu0_nullptr__;                                      \
	}                                                              \
__mu0_scope_end__

#	define __mu0_cfind__(_CharT, __first, __last, __char, __r)                         \
__mu0_scope_begin__                                                                   \
	const ___mu0_sint8_t___ __mu0_cfind__k__ = 0;                                      \
	const ___mu0_sint8_t___ __mu0_cfind__n__ = __last - __first;                       \
	__mu0_cfind_n__(_CharT, __first, __mu0_cfind__k__, __mu0_cfind__n__, __char, __r); \
	if (__mu0_is_nullptr__(_r)) {                                                      \
		__r = __last;                                                                   \
	}                                                                                  \
__mu0_scope_end__

#	define __mu0_slength__(_CharT, __src, __r)                                         \
__mu0_scope_begin__                                                                   \
	const _CharT * __mu0_slength__i__ = __mu0_const_cast__(_CharT *, __src);           \
	const _CharT   __mu0_slength__z__ = __mu0_const_cast__(_CharT  , 0);               \
	__r                               = 0;                                             \
	for (; (*__mu0_slength__i__ != __mu0_slength__z__); (void) ++__mu0_slength__i__) { \
		++__r;                                                                          \
	}                                                                                  \
__mu0_scope_end__

#	define __mu0_scmp_n__(_CharT, __src1, __src2, __n, __r)                                    \
__mu0_scope_begin__                                                                           \
	const _CharT *    __mu0_scmp_n__i__ = __mu0_const_cast__(_CharT *, __src1);                \
	const _CharT *    __mu0_scmp_n__j__ = __mu0_const_cast__(_CharT *, __src2);                \
	___mu0_sint8_t___ __mu0_scmp_n__n__ = __mu0_const_cast__(___mu0_sint8_t___, __n);          \
	__r                                 = 0;                                                   \
	for (; __mu0_scmp_n__n__; --__mu0_scmp_n__n__, ++__mu0_scmp_n__i__, ++__mu0_scmp_n__j__) { \
		if (*__mu0_scmp_n__i__ < *__mu0_scmp_n__j__) {                                          \
			__r = -1;                                                                            \
			break;                                                                               \
		}                                                                                       \
		if (*__mu0_scmp_n__j__ <  *__mu0_scmp_n__i__) {                                         \
			__r = 1;                                                                             \
			break;                                                                               \
		}                                                                                       \
	}                                                                                          \
__mu0_scope_end__

MU0_END_CDECL

#endif /* !MU0_CHARTRAIT_H */

/* EOF */