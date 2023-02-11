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

// mu0_cpuyield.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_platform.h>

#ifndef MU0_CPUYIELD_H
#define MU0_CPUYIELD_H 1

MU0_BEGIN_CDECL

#	undef  MU0_HAVE_CPUYIELD
#	undef  __m0_sync_cpu_yield__
#	define MU0_HAVE_CPUYIELD 0

#  if MU0_HAVE_CC_MSVCC
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if defined(_M_AMD64) || defined(_M_IX86)
#			pragma intrinsic(_mm_pause)
#			define __m0_sync_cpu_yield__()    mm_pause()
#		elif defined(_M_ARM64) || defined(_M_ARM)
#			pragma intrinsic(__yield)
#			define __m0_sync_cpu_yield__()    __yield()
#		else
#			define __m0_sync_cpu_yield__()    __asm { rep nop }
#		endif
#  endif

#  if MU0_HAVE_CC_ITLCC
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if defined(__MIC__)
#			pragma intrinsic(_mm_delay_32)
#			define __m0_sync_cpu_yield__()    _mm_delay_32(128)
#		else
#			pragma intrinsic(_mm_pause)
#			define __m0_sync_cpu_yield__()    _mm_pause()
#		endif
#	endif

#	if MU0_HAVE_CC_ARMCC
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __yield()
#	endif

#  if MU0_HAVE_CC_CLANG
#	if   __has_builtin(__builtin_ia32_pause)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __builtin_ia32_pause()
#	elif MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __asm__ __volatile__ ("hint @pause")
#	elif MU0_HAVE_X86 || MU0_HAVE_X64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __asm__ __volatile__("pause\n")
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64 && !MU0_HAVE_CPUYIELD
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if MU0_HAVE_ARM64
#			define __m0_sync_cpu_yield__()    __asm__ __volatile__("yield;" ::: "memory")
#		else
#			if __MU0_BYTE_ORDER__ == __MU0_ORDER_LEEN__
#				define __m0_sync_cpu_yield__() __asm__ __volatile__("yield");
#			else
#				define __m0_sync_cpu_yield__() __asm__ __volatile__("or 27, 27, 27" ::: "memory")
#			endif
#		endif
#	elif defined(__ppc__) || defined(__powerpc64__) || defined(__mips__)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __asm__ __volatile__("sync" ::: "memory");
#	endif
#	endif

#  if MU0_HAVE_CC_GNUCC
#	if   __has_builtin(__builtin_ia32_pause)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __builtin_ia32_pause()
#	elif MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __asm__ __volatile__ ("hint @pause")
#	elif MU0_HAVE_X86 || MU0_HAVE_X64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __asm__ __volatile__("pause\n")
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64 && !MU0_HAVE_CPUYIELD
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if MU0_HAVE_ARM64
#			define __m0_sync_cpu_yield__()    __asm__ __volatile__("yield;" ::: "memory")
#		else
#			if __MU0_BYTE_ORDER__ == __MU0_ORDER_LEEN__
#				define __m0_sync_cpu_yield__() __asm__ __volatile__("yield");
#			else
#				define __m0_sync_cpu_yield__() __asm__ __volatile__("or 27, 27, 27" ::: "memory")
#			endif
#		endif
#	elif defined(__ppc__) || defined(__powerpc64__) || defined(__mips__)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __m0_sync_cpu_yield__()       __asm__ __volatile__("sync" ::: "memory");
#	endif
#	endif

MU0_END_CDECL

#	if !MU0_HAVE_CPUYIELD
#	if                                                            \
	   (defined(_POSIX_VERSION)  && (_POSIX_VERSION  >= 200809L)) \
	|| (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200809L))
#		include <sched.h>
#		define __m0_sync_cpu_yield__()      sched_yield()
#	endif
#	endif

MU0_BEGIN_CDECL

#	if !MU0_HAVE_CPUYIELD
#		error mu0_cpuyield.h
#	endif

MU0_END_CDECL

#endif /* !MU0_CPUYIELD_H */

/* EOF */