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

#include <mu0/mu0_definition/mu0_attribute.h>
#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_CPUYIELD_H
#define MU0_CPUYIELD_H 1

#	undef  MU0_HAVE_CPUYIELD
#	undef  MU0_HAVE_THRYIELD
#	undef  MU0_HAVE_CPUCLICK
#	undef  __mu0_cpuyield__
#	undef  __mu0_thryield__
#	undef  __mu0_cpuclick__
#	define MU0_HAVE_CPUYIELD 0
#	define MU0_HAVE_THRYIELD 0
#	define MU0_HAVE_CPUCLICK 0

#	if !MU0_HAVE_CPUYIELD
#	if MU0_HAVE_CC_MSVCC
#		if MU0_HAVE_CC_MSVCL
#			if   __has_builtin(__builtin_ia32_pause)
#				undef  MU0_HAVE_CPUYIELD
#				define MU0_HAVE_CPUYIELD 1
#				define __mu0_cpuyield__() __builtin_ia32_pause()
#			endif
#		endif
#		if !MU0_HAVE_CPUYIELD
#		if defined(_M_AMD64) || defined(_M_IX86)
#			undef  MU0_HAVE_CPUYIELD
#			define MU0_HAVE_CPUYIELD 1
#			pragma intrinsic(_mm_pause)
#			define __mu0_cpuyield__() _mm_pause()
#		elif defined(_M_ARM64) || defined(_M_ARM)
#			undef  MU0_HAVE_CPUYIELD
#			define MU0_HAVE_CPUYIELD 1
#			pragma intrinsic(__yield)
#			define __mu0_cpuyield__() __yield()
#		endif
#		endif
		__declspec(dllimport) void __stdcall Sleep(DWORD);
		__declspec(dllimport) int  __stdcall SwitchToThread(void);
#		if !MU0_HAVE_CPUYIELD
#			define __mu0_cpuyield__() if (!SwitchToThread()) { Sleep(0); } __mu0_delineate__
#		endif
#		undef  MU0_HAVE_THRYIELD
#		define MU0_HAVE_THRYIELD 1
#		define __mu0_thryield__()    if (!SwitchToThread()) { Sleep(1); } __mu0_delineate__
#	endif
#	endif

#	if !MU0_HAVE_CPUYIELD
#	if MU0_HAVE_CC_ITLCC
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if defined(__MIC__)
#			pragma intrinsic(_mm_delay_32)
#			define __mu0_cpuyield__() _mm_delay_32(128)
#		else
#			pragma intrinsic(_mm_pause)
#			define __mu0_cpuyield__() _mm_pause()
#		endif
#		if MU0_HAVE_WINDOWS
			__declspec(dllimport) void __stdcall Sleep(DWORD);
			__declspec(dllimport) int  __stdcall SwitchToThread(void);
#			undef  MU0_HAVE_THRYIELD
#			define MU0_HAVE_THRYIELD 1
#			define __mu0_thryield__() if (!SwitchToThread()) { Sleep(1); } __mu0_delineate__
#		endif
#	endif
#	endif

#	if !MU0_HAVE_CPUYIELD
#	if MU0_HAVE_CC_ARMCC
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __yield()
#	endif
#	endif

#	if !MU0_HAVE_CPUYIELD
#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG
#	if   MU0_HAVE_X86 || MU0_HAVE_X64 && __has_builtin(__builtin_ia32_pause)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __builtin_ia32_pause()
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64 && __has_builtin(__builtin_arm_yield)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __builtin_arm_yield()
#	elif MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __asm__ __volatile__ ("hint @pause")
#	elif MU0_HAVE_X86 || MU0_HAVE_X64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
// #		define __mu0_cpuyield__()       __asm__ __volatile__ ("pause\n")
#		define __mu0_cpuyield__()       __asm__ __volatile__("pause;" ::: "memory")
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if MU0_HAVE_ARM64
#			define __mu0_cpuyield__()    __asm__ __volatile__ ("yield;" ::: "memory")
#		else
#			if __mu0_byte_order__ == __mu0_order_leen__
#				define __mu0_cpuyield__() __asm__ __volatile__ ("yield");
#			else
#				define __mu0_cpuyield__() __asm__ __volatile__ ("or 27, 27, 27" ::: "memory")
#			endif
#		endif
#	elif defined(__ppc__) || defined(__powerpc64__) || defined(__mips__)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __asm__ __volatile__ ("sync" ::: "memory");
#	endif
#	endif
#	endif

#	if !MU0_HAVE_CPUYIELD
#	if MU0_HAVE_CC_GNUCC
#	if   MU0_HAVE_X86 || MU0_HAVE_X64 && __has_builtin(__builtin_ia32_pause)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __builtin_ia32_pause()
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64 && __has_builtin(__builtin_arm_yield)
#		warning __builtin_arm_yield
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __builtin_arm_yield()
#	elif MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __asm__ __volatile__ ("hint @pause")
#	elif MU0_HAVE_X86 || MU0_HAVE_X64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
// #		define __mu0_cpuyield__()       __asm__ __volatile__ ("pause\n")
#		define __mu0_cpuyield__()       __asm__ __volatile__("pause;" ::: "memory")
#	elif MU0_HAVE_ARM32 || MU0_HAVE_ARM64
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		if MU0_HAVE_ARM64
#			define __mu0_cpuyield__()    __asm__ __volatile__ ("yield;" ::: "memory")
#		else
#			if __mu0_byte_order__ == __mu0_order_leen__
#				define __mu0_cpuyield__() __asm__ __volatile__ ("yield");
#			else
#				define __mu0_cpuyield__() __asm__ __volatile__ ("or 27, 27, 27" ::: "memory")
#			endif
#		endif
#	elif defined(__mips64)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __asm__ __volatile__ ("pause")
#	elif defined(__ppc__) || defined(__powerpc64__) || defined(__mips__) || defined(__mips)
#		undef  MU0_HAVE_CPUYIELD
#		define MU0_HAVE_CPUYIELD 1
#		define __mu0_cpuyield__()       __asm__ __volatile__ ("sync" ::: "memory");
#	endif
#	endif
#	endif

#	if MU0_HAVE_C11 && !MU0_HAVE_THRYIELD
#	if defined(__STDC_NO_THREADS) && __STDC_NO_THREADS__ == 0
#		include <threads.h>
#		undef  MU0_HAVE_THRYIELD
#		define MU0_HAVE_THRYIELD 1
#		define __mu0_thryield__()       thrd_yield()
#	endif
#	endif

#	if !MU0_HAVE_CPUYIELD || !MU0_HAVE_THRYIELD
#	if MU0_HAVE_POSIX1_2001
#		include <sched.h>
#		if !MU0_HAVE_CPUYIELD
#			undef  MU0_HAVE_CPUYIELD
#			define MU0_HAVE_CPUYIELD 1
#			define __mu0_cpuyield__()    sched_yield()
#		endif
#		if !MU0_HAVE_THRYIELD
#			undef  MU0_HAVE_THRYIELD
#			define MU0_HAVE_THRYIELD 1
#			define __mu0_thryield__()    sched_yield()
#		endif
#	endif
#	endif

#	if !MU0_HAVE_CPUCLICK
#	if MU0_HAVE_CC_MSVCC
#	if MU0_HAVE_X86 || MU0_HAVE_X64 && !MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUCLICK
#		define MU0_HAVE_CPUCLICK 1
#		pragma intrinsic(__rdtsc)
#		define __mu0_cpuclick__() __rdtsc()
#	endif
#	endif
#	endif

#	if !MU0_HAVE_CPUCLICK
#	if MU0_HAVE_CC_ITLCC
#	if   MU0_HAVE_X64 && !MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUCLICK
#		define MU0_HAVE_CPUCLICK 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ ___mu0_cpuclick___(void)
		{
			unsigned __int64 rv = 0Ui64;
			_rdrand64_step(&rv);
			return __mu0_const_cast__(___mu0_uint8_t___, rv);
		}
#		define __mu0_cpuclick__() ___mu0_cpuclick___()
#	elif MU0_HAVE_X86 && !MU0_HAVE_IA64
#		undef  MU0_HAVE_CPUCLICK
#		define MU0_HAVE_CPUCLICK 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ ___mu0_cpuclick___(void)
		{
			unsigned __int32 rv = 0U;
			_rdrand32_step(&rv);
			return __mu0_const_cast__(___mu0_uint8_t___, rv);
		}
#		define __mu0_cpuclick__() ___mu0_cpuclick___()
#	endif
#	endif
#	endif

#	if !MU0_HAVE_CPUCLICK
#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_MSVCL
#	if   MU0_HAVE_X64
#	if __has_builtin(__builtin_ia32_rdrand64_step) && defined(__RDRND__)
#		undef  MU0_HAVE_CPUCLICK
#		define MU0_HAVE_CPUCLICK 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ ___mu0_cpuclick___(void)
		{
			___mu0_uint8_t___ rv = 0U;
			__builtin_ia32_rdrand64_step(&rv);
			return rv;
		}
#		define __mu0_cpuclick__() ___mu0_cpuclick___()
#	elif MU0_HAVE_X86
#	if __has_builtin(__builtin_ia32_rdrand32_step) && defined(__RDRND__)
#		undef  MU0_HAVE_CPUCLICK
#		define MU0_HAVE_CPUCLICK 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ ___mu0_cpuclick___(void)
		{
			___mu0_uint4_t___ rv = 0U;
			__builtin_ia32_rdrand32_step(&rv);
			return __mu0_const_cast__(___mu0_uint8_t___, rv);
		}
#		define __mu0_cpuclick__() ___mu0_cpuclick___()
#	endif
#	endif
#	endif
#	endif
#	endif

#	if !MU0_HAVE_CPUCLICK
#	if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCCC
#	if !MU0_HAVE_ARM64
#	if __has_builtin(__builtin_readcyclecounter)
#		undef  MU0_HAVE_CPUCLICK
#		define MU0_HAVE_CPUCLICK 1
#		define __mu0_cpuclick__() __builtin_readcyclecounter()
#	endif
#	endif
#	endif
#	endif

#	if !MU0_HAVE_CPUCLICK
#		define __mu0_cpuclick__() 0xBD1E836D24471959
#	endif

#	if !MU0_HAVE_CPUYIELD || !MU0_HAVE_THRYIELD
#		error mu0_cpuyield.h
#	endif

#endif /* !MU0_CPUYIELD_H */

/* EOF */