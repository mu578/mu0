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

#include <mu0/mu0_definition/mu0_attribute.h>
#include <mu0/mu0_definition/mu0_barrier.h>
#include <mu0/mu0_definition/mu0_feature.h>

#ifndef MU0_ATOMIC_H
#define MU0_ATOMIC_H 1

#	undef  MU0_HAVE_ATOMIC
#	define MU0_HAVE_ATOMIC 1

#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_ARMCC

#	define __mu0_atomic_fetch_and_add__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_add(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_sub__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_sub(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_or__(_Tp, __ptr, __value, __result)                     \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_or(__ptr, __value)                                        \
	__result = tmp;                                                                       \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_and__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_and(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_xor__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	_Tp tmp = __sync_fetch_and_xor(__ptr, __value);                                       \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_nand__(_Tp, __ptr, __value, __result)                   \
__mu0_scope_begin__                                                                      \
	__result = __sync_fetch_and_nand(__ptr, __value);                                     \
	__result = tmp;                                                                       \
__mu0_scope_end__

#	define __mu0_atomic_add_and_fetch__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_add_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_sub_and_fetch__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_sub_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_or_and_fetch__(_Tp, __ptr, __value, __result)                     \
__mu0_scope_begin__                                                                      \
	__result = __sync_sync_or_and_fetch(__ptr, __value);                                  \
__mu0_scope_end__

#	define __mu0_atomic_and_and_fetch__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_and_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_xor_and_fetch__(_Tp, __ptr, __value, __result)                    \
__mu0_scope_begin__                                                                      \
	__result = __sync_xor_and_fetch(__ptr, __value);                                      \
__mu0_scope_end__

#	define __mu0_atomic_nand_fetch__(_Tp, __ptr, __value, __result)                       \
__mu0_scope_begin__                                                                      \
	__result = __sync_nand_fetch(__ptr, __value);                                         \
__mu0_scope_end__


#	define __mu0_atomic_bool_compare_and_swap__(_Tp, __ptr, __oldval, __newval, __result) \
__mu0_scope_begin__                                                                      \
	__result = __sync_bool_compare_and_swap(__ptr, __oldval, __newval) ? 1 : 0;           \
__mu0_scope_end__

#	define __mu0_atomic_val_compare_and_swap__(_Tp, __ptr, __oldval, __newval, __result)  \
__mu0_scope_begin__                                                                      \
	__result = __sync_val_compare_and_swap(__ptr, __oldval, __newval);                    \
__mu0_scope_end__

#	else

#	define __mu0_atomic_fetch_and_op__(_Tp, _Op, __ptr, __value, __result)                \
__mu0_scope_begin__                                                                      \
	_Tp tmp;                                                                              \
	__mu0_barrier_acquire__();                                                            \
	tmp      = *__ptr;                                                                    \
	*__ptr _Op __value;                                                                   \
	__result = tmp;                                                                       \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_fetch_and_add__(_Tp, __ptr, __value, __result)                    \
	__mu0_atomic_fetch_and_op__(_Tp, +=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_sub__(_Tp, __ptr, __value, __result)                    \
		__mu0_atomic_fetch_and_op__(_Tp, -=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_or__(_Tp, __ptr, __value, __result)                     \
	__mu0_atomic_fetch_and_op__(_Tp, |=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_and__(_Tp, __ptr, __value, __result)                    \
	__mu0_atomic_fetch_and_op__(_Tp, &=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_xor__(_Tp, __ptr, __value, __result)                    \
	__mu0_atomic_fetch_and_op__(_Tp, ^=, __ptr, __value, __result)

#	define __mu0_atomic_fetch_and_nand__(_Tp, __ptr, __value, __result)                   \
__mu0_scope_begin__                                                                      \
	_Tp tmp;                                                                              \
	__mu0_barrier_acquire__();                                                            \
	tmp      = *__ptr;                                                                    \
	*ptr     = ~tmp & __value;                                                            \
	__result = tmp;                                                                       \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_op_and_fetch__(_Tp, _Op, __ptr, __value, __result)                \
__mu0_scope_begin__                                                                      \
	__mu0_barrier_acquire__();                                                            \
	*__ptr   _Op __value;                                                                 \
	__result  = *__ptr;                                                                   \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_add_and_fetch__(_Tp, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Tp, +=, __ptr, __value, __result)

#	define __mu0_atomic_sub_and_fetch__(_Tp, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Tp, -=, __ptr, __value, __result)

#	define __mu0_atomic_or_and_fetch__(_Tp, __ptr, __value, __result)                     \
	__mu0_atomic_op_and_fetch__(_Tp, |=, __ptr, __value, __result)

#	define __mu0_atomic_and_and_fetch__(_Tp, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Tp, &=, __ptr, __value, __result)

#	define __mu0_atomic_xor_and_fetch__(_Tp, __ptr, __value, __result)                    \
	__mu0_atomic_op_and_fetch__(_Tp, ^=, __ptr, __value, __result)

#	define __mu0_atomic_nand_fetch__(_Tp, __ptr, __value, __result)                       \
__mu0_scope_begin__                                                                      \
	__mu0_barrier_acquire__();                                                            \
	*__ptr   = ~*ptr & __value                                                            \
	__result = *__ptr;                                                                    \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_bool_compare_and_swap__(_Tp, __ptr, __oldval, __newval, __result) \
__mu0_scope_begin__                                                                      \
	_Tp               __mu0_atomic_bool_compare_and_swap__tmp__;                          \
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
			*__ptr   = __newval;                                                            \
			__result = 1;                                                                   \
		}                                                                                  \
		__mu0_atomic_bool_compare_and_swap__tmp__ = *__ptr;                                \
		--__mu0_atomic_bool_compare_and_swap__bar__;                                       \
	}                                                                                     \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	define __mu0_atomic_val_compare_and_swap__(_Tp, __ptr, __oldval, __newval, __result)  \
__mu0_scope_begin__                                                                      \
	_Tp               __mu0_atomic_val_compare_and_swap__tmp__;                           \
	___mu0_uint4_t___ __mu0_atomic_val_compare_and_swap__bar__;                           \
	__mu0_barrier_acquire__();                                                            \
	__mu0_atomic_val_compare_and_swap__tmp__ *__ptr;                                      \
	__mu0_atomic_val_compare_and_swap__bar__ = 64;                                        \
	while (                                                                               \
		   __mu0_atomic_val_compare_and_swap__bar__ > 0                                    \
		&& __mu0_atomic_val_compare_and_swap__tmp__ == __oldval                            \
	) {                                                                                   \
		if (__mu0_atomic_val_compare_and_swap__tmp__ == __oldval) {                        \
			*__ptr = __newval;                                                              \
		}                                                                                  \
		__mu0_atomic_val_compare_and_swap__tmp__ = *__ptr;                                 \
		--__mu0_atomic_val_compare_and_swap__bar__;                                        \
	}                                                                                     \
	__result = __mu0_atomic_val_compare_and_swap__tmp__;                                  \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__

#	endif

#	if defined(__clang__) && __has_builtin(__sync_swap)
#	define __mu0_atomic_swap__(_Tp, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__result = __sync_swap(__ptr, __newval)                                               \
__mu0_scope_end__
#	elif defined(__clang__) && __has_builtin(__atomic_exchange_n)
#	define __mu0_atomic_swap__(_Tp, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__result = __atomic_exchange_n(__ptr, __newval, __ATOMIC_ACQ_REL);                    \
__mu0_scope_end__
#	elif defined(__clang__) && __has_builtin(__sync_lock_test_and_set)
#	define __mu0_atomic_swap__(_Tp, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__mu0_barrier_acquire__();                                                            \
		__result = __sync_lock_test_and_set(__ptr, __newval);                              \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__
#	elif defined(__GNUC_ATOMICS)
#	define __mu0_atomic_swap__(_Tp, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	__result = __atomic_exchange_n(__ptr, __newval, __ATOMIC_ACQ_REL);                    \
__mu0_scope_end__
#	else
#	define __mu0_atomic_swap__(_Tp, __ptr, __newval, __result)                            \
__mu0_scope_begin__                                                                      \
	_Tp tmp;	                                                                             \
	__mu0_barrier_acquire__();                                                            \
	tmp      = *__ptr;                                                                    \
	*__ptr   = __newval;                                                                  \
	__result = tmp;                                                                       \
	__mu0_barrier_release__();                                                            \
__mu0_scope_end__
#	endif

typedef struct __mu0_atomic_spinlock__ { __mu0_volatile__ ___mu0_uint4_t___ u_flag; } __mu0_atomic_spinlock_t__;

__mu0_static_inline__
void __mu0_atomic_spinlock_init__(__mu0_atomic_spinlock_t__ * __s)
{ __s->u_flag = 0; }

__mu0_static_inline__
___mu0_uint4_t___ __mu0_atomic_spinlock_trylock__(__mu0_atomic_spinlock_t__ * __s)
{
	___mu0_uint4_t___ r;
	__mu0_atomic_bool_compare_and_swap__(
		  __mu0_volatile__ ___mu0_uint4_t___
		, &__s->u_flag
		, 0
		, 1
		, r
	);
	return r;
}

__mu0_static_inline__
void __mu0_atomic_spinlock_lock__(__mu0_atomic_spinlock_t__ * __s)
{
	while(!__mu0_atomic_spinlock_trylock__(__s)) {
		__mu0_cpu_yield__();
	}
}

__mu0_static_inline__
void __mu0_atomic_spinlock_unlock__(__mu0_atomic_spinlock_t__ * __s)
{
	__mu0_barrier_acquire__();
	__s->u_flag = 0;
	__mu0_barrier_release__();
}

#	if !MU0_HAVE_ATOMIC
#		error mu0_atomic.h
#	endif

#endif /* !MU0_ATOMIC_H */

/* EOF */