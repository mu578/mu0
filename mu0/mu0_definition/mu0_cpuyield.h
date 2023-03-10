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

#	undef  MU0_HAVE_CPUYIELD
#	undef  __mu0_sync_cpu_yield__
#	define MU0_HAVE_CPUYIELD 0

#	if MU0_HAVE_CC_MSVCC
#		if defined(_M_AMD64) || defined(_M_IX86)
#			undef  MU0_HAVE_CPUYIELD
#			define MU0_HAVE_CPUYIELD 1
#			pragma intrinsic(_mm_pause)
#			define __mu0_sync_cpu_yield__()    _mm_pause()
#		elif defined(_M_ARM64) || defined(_M_ARM)
#			undef  MU0_HAVE_CPUYIELD
#			define MU0_HAVE_CPUYIELD 1
#			pragma intrinsic(__yield)
#			define __mu0_sync_cpu_yield__()    __yield()
#		endif
#	endif

#	if MU0_HAVE_CC_ITLCC
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if defined(__MIC__)
#			pragma intrinsic(_mm_delay_32)
#			define __mu0_sync_cpu_yield__()    _mm_delay_32(128)
#		else
#			pragma intrinsic(_mm_pause)
#			define __mu0_sync_cpu_yield__()    _mm_pause()
#		endif
#	endif

#	if MU0_HAVE_CC_ARMCC
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __yield()
#	endif

#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG
#	if   __has_builtin(__builtin_ia32_pause)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __builtin_ia32_pause()
#	elif MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __asm__ __volatile__ ("hint @pause")
#	elif MU0_HAVE_X86 || MU0_HAVE_X64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __asm__ __volatile__("pause\n")
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if MU0_HAVE_ARM64
#			define __mu0_sync_cpu_yield__()    __asm__ __volatile__("yield;" ::: "memory")
#		else
#			if __mu0_byte_order__ == __mu0_order_leen__
#				define __mu0_sync_cpu_yield__() __asm__ __volatile__("yield");
#			else
#				define __mu0_sync_cpu_yield__() __asm__ __volatile__("or 27, 27, 27" ::: "memory")
#			endif
#		endif
#	elif defined(__ppc__) || defined(__powerpc64__) || defined(__mips__)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __asm__ __volatile__("sync" ::: "memory");
#	endif
#	endif

#	if MU0_HAVE_CC_GNUCC
#	if   __has_builtin(__builtin_ia32_pause)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __builtin_ia32_pause()
#	elif MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __asm__ __volatile__ ("hint @pause")
#	elif MU0_HAVE_X86 || MU0_HAVE_X64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __asm__ __volatile__("pause\n")
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if MU0_HAVE_ARM64
#			define __mu0_sync_cpu_yield__()    __asm__ __volatile__("yield;" ::: "memory")
#		else
#			if __mu0_byte_order__ == __mu0_order_leen__
#				define __mu0_sync_cpu_yield__() __asm__ __volatile__("yield");
#			else
#				define __mu0_sync_cpu_yield__() __asm__ __volatile__("or 27, 27, 27" ::: "memory")
#			endif
#		endif
#	elif defined(__mips64)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __asm__ __volatile__("pause")
#	elif defined(__ppc__) || defined(__powerpc64__) || defined(__mips__) || defined(__mips)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_sync_cpu_yield__()       __asm__ __volatile__("sync" ::: "memory");
#	endif
#	endif

#	if !MU0_HAVE_CPUYIELD
#	if MU0_HAVE_POSIX1_2001
#		include <sched.h>
#		define __mu0_sync_cpu_yield__()      sched_yield()
#	endif
#	endif

#	if !MU0_HAVE_CPUYIELD
#		error mu0_cpuyield.h
#	endif

#endif /* !MU0_CPUYIELD_H */

/* EOF */