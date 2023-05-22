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

// mu0_atomic.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_barrier.h>

#ifndef MU0_ATOMIC_H
#define MU0_ATOMIC_H 1

#	undef  MU0_HAVE_ATOMIC
#	undef  MU0_HAVE_ATSWAP
#	undef  __mu0_atomic_sub_and_fetch__
#	undef  __mu0_atomic_or_and_fetch__
#	undef  __mu0_atomic_and_and_fetch__
#	undef  __mu0_atomic_xor_and_fetch__
#	undef  __mu0_atomic_nand_fetch__
#	undef  __mu0_atomic_bool_compare_and_swap__
#	undef  __mu0_atomic_val_compare_and_swap__
#	undef  __mu0_atomic_swap__
#	define MU0_HAVE_ATOMIC 0
#	define MU0_HAVE_ATSWAP 0

#	if!MU0_HAVE_ATOMIC
#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_ARMCCC || MU0_HAVE_CC_MSVCL
#	undef  MU0_HAVE_ATOMIC
#	define MU0_HAVE_ATOMIC 1

#	define __mu0_atomic_fetch_and_add__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_add(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_sub__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_sub(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_or__(_Sc, __ptr, __value, __result)                     \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_or(__ptr, __value)                                        \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_and__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_and(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_xor__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_xor(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_nand__(_Sc, __ptr, __value, __result)                   \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_nand(__ptr, __value);                                     \
__mu0_scope_end__

#	define __mu0_atomic_add_and_fetch__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_add_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_sub_and_fetch__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_sub_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_or_and_fetch__(_Sc, __ptr, __value, __result)                     \
__mu0_scope_begin__                                                                      \
	__result = __sync_sync_or_and_fetch(__ptr, __value);                                  \
__mu0_scope_end__

#	define __mu0_atomic_and_and_fetch__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_and_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_xor_and_fetch__(_Sc, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_xor_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_nand_fetch__(_Sc, __ptr, __value, __result)                       \
__mu0_scope_begin__                                                                      \
	__result = __sync_nand_fetch(__ptr, __value);                                         \
__mu0_scope_end__


#	define __mu0_atomic_bool_compare_and_swap__(_Sc, __ptr, __oldval, __newval, __result) \
__mu0_scope_begin__                                                                      \
	__result = __sync_bool_compare_and_swap(__ptr, __oldval, __newval) ? 1 : 0;           \
__mu0_scope_end__

#	define __mu0_atomic_val_compare_and_swap__(_Sc, __ptr, __oldval, __newval, __result)  \
__mu0_scope_begin__                                                                      \
	__result = __sync_val_compare_and_swap(__ptr, __oldval, __newval);                    \
__mu0_scope_end__

#	endif
#	endif

#	if!MU0_HAVE_ATOMIC
#	undef  MU0_HAVE_ATOMIC
#	define MU0_HAVE_ATOMIC 1

#	define __mu0_atomic_fetch_and_op__(_Sc, _Op, __ptr, __value, __result)                \
__mu0_scope_begin__                                                                      \
	_Sc tmp;                                                                              \
	__mu0_barrier_acquire__();                                                            \
	tmp      = *__ptr;                                                                    \
	*__ptr _Op __value;                                                                   \
	__result = tmp;                                                                       \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_add__(_Sc, __ptr, __value, __result)                    \
	__mu0_atomic_fetch_and_op__(_Sc, +=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_sub__(_Sc, __ptr, __value, __result)                    \
		__mu0_atomic_fetch_and_op__(_Sc, -=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_or__(_Sc, __ptr, __value, __result)                     \
	__mu0_atomic_fetch_and_op__(_Sc, |=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_and__(_Sc, __ptr, __value, __result)                    \
	__mu0_atomic_fetch_and_op__(_Sc, &=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_xor__(_Sc, __ptr, __value, __result)                    \
	__mu0_atomic_fetch_and_op__(_Sc, ^=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_nand__(_Sc, __ptr, __value, __result)                   \
__mu0_scope_begin__                                                                      \
	_Sc tmp;                                                                              \
	__mu0_barrier_acquire__();                                                            \
	tmp      = *__ptr;                                                                    \
	*ptr     = ~tmp & __value;                                                            \
	__result = tmp;                                                                       \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_op_and_fetch__(_Sc, _Op, __ptr, __value, __result)                \
__mu0_scope_begin__                                                                      \
	__mu0_barrier_acquire__();                                                            \
	*__ptr   _Op __value;                                                                 \
	__result  = *__ptr;                                                                   \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_add_and_fetch__(_Sc, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Sc, +=, __ptr, __value, __result)

#	define __mu0_atomic_sub_and_fetch__(_Sc, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Sc, -=, __ptr, __value, __result)

#	define __mu0_atomic_or_and_fetch__(_Sc, __ptr, __value, __result)                     \
	__mu0_atomic_op_and_fetch__(_Sc, |=, __ptr, __value, __result)

#	define __mu0_atomic_and_and_fetch__(_Sc, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Sc, &=, __ptr, __value, __result)

#	define __mu0_atomic_xor_and_fetch__(_Sc, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Sc, ^=, __ptr, __value, __result)

#	define __mu0_atomic_nand_fetch__(_Sc, __ptr, __value, __result)                       \
__mu0_scope_begin__                                                                      \
	__mu0_barrier_acquire__();                                                            \
	*__ptr   = ~*ptr & __value                                                            \
	__result = *__ptr;                                                                    \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_bool_compare_and_swap__(_Sc, __ptr, __oldval, __newval, __result) \
__mu0_scope_begin__                                                                      \
	_Sc               __mu0_atomic_bool_compare_and_swap__tmp__;                          \
	___mu0_uint4_t___ __mu0_atomic_bool_compare_and_swap__bar__;                          \
	__mu0_barrier_acquire__();                                                            \
	__result                                  = 0;                                        \
	__mu0_atomic_bool_compare_and_swap__tmp__ = *__ptr;                                   \
	__mu0_atomic_bool_compare_and_swap__bar__ = 64;                                       \
	while (                                                                               \
		   __mu0_atomic_bool_compare_and_swap__bar__ > 0                                   \
		&& __mu0_atomic_bool_compare_and_swap__tmp__ == __oldval                           \
	) {                                                                                   \
		if (__mu0_atomic_bool_compare_and_swap__tmp__ == __oldval) {                       \
			__mu0_barrier_release__();                                                      \
			__mu0_barrier_acquire__();                                                      \
			*__ptr   = __newval;                                                            \
			__result = 1;                                                                   \
		}                                                                                  \
		__mu0_atomic_bool_compare_and_swap__tmp__ = *__ptr;                                \
		--__mu0_atomic_bool_compare_and_swap__bar__;                                       \
	}                                                                                     \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_val_compare_and_swap__(_Sc, __ptr, __oldval, __newval, __result)  \
__mu0_scope_begin__                                                                      \
	_Sc               __mu0_atomic_val_compare_and_swap__tmp__;                           \
	___mu0_uint4_t___ __mu0_atomic_val_compare_and_swap__bar__;                           \
	__mu0_barrier_acquire__();                                                            \
	__mu0_atomic_val_compare_and_swap__tmp__ = *__ptr;                                    \
	__mu0_atomic_val_compare_and_swap__bar__ = 64;                                        \
	while (                                                                               \
		   __mu0_atomic_val_compare_and_swap__bar__ > 0                                    \
		&& __mu0_atomic_val_compare_and_swap__tmp__ == __oldval                            \
	) {                                                                                   \
		if (__mu0_atomic_val_compare_and_swap__tmp__ == __oldval) {                        \
			__mu0_barrier_release__();                                                      \
			__mu0_barrier_acquire__();                                                      \
			*__ptr = __newval;                                                              \
		}                                                                                  \
		__mu0_atomic_val_compare_and_swap__tmp__ = *__ptr;                                 \
		--__mu0_atomic_val_compare_and_swap__bar__;                                        \
	}                                                                                     \
	__result = __mu0_atomic_val_compare_and_swap__tmp__;                                  \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	endif


#	if !MU0_HAVE_ATSWAP
#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCCC || MU0_HAVE_CC_MSVCL
#	if __has_builtin(__sync_swap)
#	undef  MU0_HAVE_ATSWAP
#	define MU0_HAVE_ATSWAP 1
#	define __mu0_atomic_swap__(_Sc, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__result = __sync_swap(__ptr, __newval)                                               \
__mu0_scope_end__
#	elif __has_builtin(__atomic_exchange_n)
#	undef  MU0_HAVE_ATSWAP
#	define MU0_HAVE_ATSWAP 1
#	define __mu0_atomic_swap__(_Sc, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__result = __atomic_exchange_n(__ptr, __newval, __ATOMIC_ACQ_REL);                    \
__mu0_scope_end__
#	elif __has_builtin(__sync_lock_test_and_set)
#	undef  MU0_HAVE_ATSWAP
#	define MU0_HAVE_ATSWAP 1
#	define __mu0_atomic_swap__(_Sc, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__mu0_barrier_acquire__();                                                            \
		__result = __sync_lock_test_and_set(__ptr, __newval);                              \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__
#	endif
#	endif
#	endif

#	if !MU0_HAVE_ATSWAP
#	if MU0_HAVE_CC_GNUCC
#	if defined(__GNUC_ATOMICS)
#	undef  MU0_HAVE_ATSWAP
#	define MU0_HAVE_ATSWAP 1
#	define __mu0_atomic_swap__(_Sc, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__result = __atomic_exchange_n(__ptr, __newval, __ATOMIC_ACQ_REL);                    \
__mu0_scope_end__
#	endif
#	endif
#	endif

#	if !MU0_HAVE_ATSWAP
#	define __mu0_atomic_swap__(_Sc, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	_Sc tmp;	                                                                             \
	__mu0_barrier_acquire__();                                                            \
	tmp      = *__ptr;                                                                    \
	*__ptr   = __newval;                                                                  \
	__result = tmp;                                                                       \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__
#	endif

#	if !MU0_HAVE_ATOMIC
#		error mu0_atomic.h
#	endif

#endif /* !MU0_ATOMIC_H */

/* EOF */