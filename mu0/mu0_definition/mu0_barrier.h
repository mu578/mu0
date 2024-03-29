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

// mu0_barrier.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_compiler.h>
#include <mu0/mu0_definition/mu0_cpuyield.h>

#ifndef MU0_BARRIER_H
#define MU0_BARRIER_H 1

#	undef  MU0_HAVE_BARRIER
#	undef  __mu0_barrier_acquire__
#	undef  __mu0_barrier_release__
#	undef  __mu0_barrier_full__
#	undef  __mu0_barrier_read__
#	undef  __mu0_barrier_write__
#	define MU0_HAVE_BARRIER 0

#	if !MU0_HAVE_BARRIER
#	if MU0_HAVE_CC_MSVCC && !MU0_HAVE_CC_MSVCL
#	if MU0_HAVE_X86 || MU0_HAVE_X64 && !MU0_HAVE_IA64
#		undef  MU0_HAVE_BARRIER
#		define MU0_HAVE_BARRIER 1
# 		pragma intrinsic(_ReadWriteBarrier)
#		pragma intrinsic(_ReadBarrier)
#		pragma intrinsic(_WriteBarrier)
#		define __mu0_barrier_full__()    _ReadWriteBarrier()
#		define __mu0_barrier_read__()    _ReadBarrier()
#		define __mu0_barrier_write__()   _WriteBarrier()
#	else
#		undef  MU0_HAVE_BARRIER
#		define MU0_HAVE_BARRIER 1
#		define __mu0_barrier_full__()    MemoryBarrier()
#		define __mu0_barrier_read__()    MemoryBarrier()
#		define __mu0_barrier_write__()   MemoryBarrier()
#	endif
#	endif
#	endif

#	if !MU0_HAVE_BARRIER
#	if MU0_HAVE_CC_ITLCC && !(MU0_HAVE_CC_ITLGC || MU0_HAVE_CC_ITLCL)
#		undef  MU0_HAVE_BARRIER
#		define MU0_HAVE_BARRIER 1
# 		pragma intrinsic(_mm_mfence)
# 		pragma intrinsic(_mm_lfence)
# 		pragma intrinsic(_mm_sfence)
#		define __mu0_barrier_full__()    _mm_mfence()
#		define __mu0_barrier_read__()    _mm_lfence()
#		define __mu0_barrier_write__()   _mm_sfence()
#	endif
#	endif

#	if !MU0_HAVE_BARRIER
#	if MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_MSVCL
#		undef  MU0_HAVE_BARRIER
#		define MU0_HAVE_BARRIER 1
#		if   MU0_HAVE_X86 || MU0_HAVE_X64 && __has_builtin(__builtin_ia32_mfence)
#			define __mu0_barrier_full__() __builtin_ia32_mfence()
#		elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64 && __has_builtin(__builtin_arm_dmb)
#			define __mu0_barrier_full__() __builtin_arm_dmb(0xB)
#		else
#			define __mu0_barrier_full__() __sync_synchronize()
#		endif
#		if MU0_HAVE_X86 || MU0_HAVE_X64 && __has_builtin(__builtin_ia32_lfence)
#			define __mu0_barrier_read__() __builtin_ia32_lfence()
#		elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64 && __has_builtin(__builtin_arm_dmb)
#			define __mu0_barrier_read__() __builtin_arm_dmb(0xA)
#		else
#			define __mu0_barrier_read__() __sync_synchronize()
#		endif
#		if MU0_HAVE_X86 || MU0_HAVE_X64 && __has_builtin(__builtin_ia32_sfence)
#			define __mu0_barrier_write__() __builtin_ia32_sfence()
#		elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64 && __has_builtin(__builtin_arm_dmb)
#			define __mu0_barrier_write__() __builtin_arm_dmb(0x9)
#		else
#			define __mu0_barrier_write__() __sync_synchronize()
#		endif
#	endif
#	endif

#	if !MU0_HAVE_BARRIER
#		error mu0_barrier.h
#	endif

#	define __mu0_barrier_acquire__() __mu0_barrier_full__()
#	define __mu0_barrier_release__() __mu0_barrier_read__(); (void)0

#endif /* !MU0_BARRIER_H */

/* EOF */