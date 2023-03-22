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

// mu0_spinlock.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_atomic.h>
#include <mu0/mu0_definition/mu0_feature.h>

#ifndef MU0_SPINLOCK_H
#define MU0_SPINLOCK_H 1

#	undef  MU0_HAVE_SPINLOCK
#	define MU0_HAVE_SPINLOCK 1

#	define __mu0_spinlock_initializer__ { 0 }
        struct __mu0_spinlock__        { __mu0_volatile__ ___mu0_uint4_t___ u_r0; };
typedef struct __mu0_spinlock__        __mu0_spinlock_t__;

__mu0_static_inline__
void __mu0_spinlock_init__(__mu0_spinlock_t__ * __s)
{ __s->u_r0 = 0; }

__mu0_static_inline__
___mu0_uint4_t___ __mu0_spinlock_trylock__(__mu0_spinlock_t__ * __s)
{
	___mu0_uint4_t___ r0;
	__mu0_atomic_bool_compare_and_swap__(
		  __mu0_volatile__ ___mu0_uint4_t___
		, &__s->u_r0
		, 0
		, 1
		, r0
	);
	return r0;
}

__mu0_static_inline__
void __mu0_spinlock_lock__(__mu0_spinlock_t__ * __s)
{
	while(!__mu0_spinlock_trylock__(__s)) {
		__mu0_cpu_yield__();
	}
}

__mu0_static_inline__
void __mu0_spinlock_unlock__(__mu0_spinlock_t__ * __s)
{
	__mu0_barrier_acquire__();
	__s->u_r0 = 0;
	__mu0_barrier_release__();
}

#	if !MU0_HAVE_SPINLOCK
#		error mu0_spinlock.h
#	endif

#endif /* !MU0_SPINLOCK_H */

/* EOF */