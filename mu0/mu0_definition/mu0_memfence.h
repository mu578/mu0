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

// mu0_memfence.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_compiler.h>

#ifndef MU0_MEMFENCE_H
#define MU0_MEMFENCE_H 1

#	undef  MU0_HAVE_MEMFENCE
#	undef  __mu0_memfence_acquire__
#	undef  __mu0_memfence_release__
#	undef  __mu0_memfence_full__
#	undef  __mu0_memfence_read__
#	undef  __mu0_memfence_write__
#	define MU0_HAVE_MEMFENCE 0

#	if MU0_HAVE_CC_MSVCC
#	if MU0_HAVE_X86 || MU0_HAVE_X64 && !MU0_HAVE_IA64
#		undef  MU0_HAVE_MEMFENCE
#		define MU0_HAVE_MEMFENCE 1
# 		pragma intrinsic(_ReadWriteBarrier)
#		pragma intrinsic(_ReadBarrier)
#		pragma intrinsic(_WriteBarrier)
#		define __mu0_memfence_acquire__() _ReadWriteBarrier()
#		define __mu0_memfence_release__()
#		define __mu0_memfence_full__()    _ReadWriteBarrier()
#		define __mu0_memfence_read__()    _ReadBarrier()
#		define __mu0_memfence_write__()   _WriteBarrier()
#	else
#		undef  MU0_HAVE_MEMFENCE
#		define MU0_HAVE_MEMFENCE 1
#		define __mu0_memfence_acquire__() MemoryBarrier()
#		define __mu0_memfence_release__()
#		define __mu0_memfence_full__()    MemoryBarrier()
#		define __mu0_memfence_read__()    MemoryBarrier()
#		define __mu0_memfence_write__()   MemoryBarrier()
#	endif
#	endif

#	if MU0_HAVE_CC_ITLCC
#		undef  MU0_HAVE_MEMFENCE
#		define MU0_HAVE_MEMFENCE 1
# 		pragma intrinsic(_mm_mfence)
#		define __mu0_memfence_acquire__() _mm_mfence()
#		define __mu0_memfence_release__()
#		define __mu0_memfence_full__()    _mm_mfence()
#		define __mu0_memfence_read__()    _mm_lfence()
#		define __mu0_memfence_write__()   _mm_sfence()
#	endif

#	if MU0_HAVE_CC_ARMCC ||  MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUC
#		undef  MU0_HAVE_MEMFENCE
#		define MU0_HAVE_MEMFENCE 1
#		define __mu0_memfence_acquire__() __sync_synchronize()
#		define __mu0_memfence_release__()
#		define __mu0_memfence_full__()    __sync_synchronize()
#		define __mu0_memfence_read__()    __sync_synchronize()
#		define __mu0_memfence_write__()   __sync_synchronize()
#	endif

#	if !MU0_HAVE_MEMFENCE
#		error mu0_memfence.h
#	endif

#endif /* !MU0_MEMFENCE_H */

/* EOF */