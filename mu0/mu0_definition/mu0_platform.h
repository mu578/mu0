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

// mu0_platform.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_compiler.h>

#ifndef MU0_PLATFORM_H
#define MU0_PLATFORM_H 1

#	include <limits.h>

#	undef  MU0_HAVE_DARWIN
#	undef  MU0_HAVE_MACOSX
#	undef  MU0_HAVE_MACOSX12
#	undef  MU0_HAVE_IOS
#	undef  MU0_HAVE_IOS10
#	undef  MU0_HAVE_IOS13
#	undef  MU0_HAVE_WINDOWS
#	undef  MU0_HAVE_MINGW
#	undef  MU0_HAVE_SOLARIS
#	undef  MU0_HAVE_FREEBSD
#	undef  MU0_HAVE_OPENBSD
#	undef  MU0_HAVE_NETBSD
#	undef  MU0_HAVE_DRAGONFLYBSD
#	undef  MU0_HAVE_ANDROID
#	undef  MU0_HAVE_LINUX
#	undef  MU0_HAVE_NUTTX
#	undef  MU0_HAVE_MINIX

#	define MU0_HAVE_DARWIN          0
#	define MU0_HAVE_MACOSX          0
#	define MU0_HAVE_IOS             0
#	define MU0_HAVE_IOS13           0
#	define MU0_HAVE_WINDOWS         0
#	define MU0_HAVE_MINGW           0
#	define MU0_HAVE_SOLARIS         0
#	define MU0_HAVE_FREEBSD         0
#	define MU0_HAVE_OPENBSD         0
#	define MU0_HAVE_NETBSD          0
#	define MU0_HAVE_DRAGONFLYBSD    0
#	define MU0_HAVE_ANDROID         0
#	define MU0_HAVE_LINUX           0
#	define MU0_HAVE_NUTTX           0
#	define MU0_HAVE_MINIX           0

#	if defined(__APPLE__) && defined(__MACH__)
#		include <Availability.h>
#		include <TargetConditionals.h>
#		if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#			include <CoreFoundation/CoreFoundation.h>
#			undef  MU0_HAVE_DARWIN
#			undef  MU0_HAVE_IOS
#			undef  MU0_HAVE_IOS10
#			undef  MU0_HAVE_IOS13
#			define MU0_HAVE_DARWIN    1
#			define MU0_HAVE_IOS       1
#			if defined(__IPHONE_10_0)
#			if __IPHONE_OS_VERSION_MIN_ALLOWED >= __IPHONE_10_0
#			define MU0_HAVE_IOS10     1
#			endif
#			endif
#			if defined(__IPHONE_13_0)
#			if __IPHONE_OS_VERSION_MIN_ALLOWED >= __IPHONE_13_0
#			define MU0_HAVE_IOS13     1
#			endif
#			endif
#		elif defined(TARGET_OS_OSX) && TARGET_OS_OSX
#			undef  MU0_HAVE_DARWIN
#			undef  MU0_HAVE_MACOSX
#			undef  MU0_HAVE_MACOSX12
#			define MU0_HAVE_DARWIN    1
#			define MU0_HAVE_MACOSX    1
#			if defined(__MAC_10_12)
#			if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_12
#			define MU0_HAVE_MACOSX12  1
#			endif
#			endif
#		else
#			warning MU0_HAVE_MACOSX
#			undef  MU0_HAVE_DARWIN
#			undef  MU0_HAVE_MACOSX
#			define MU0_HAVE_DARWIN    1
#			define MU0_HAVE_MACOSX    1
#		endif
#	elif defined(_WIN32) || defined(_WIN64)
#		undef  MU0_HAVE_WINDOWS
#		define MU0_HAVE_WINDOWS      1
#		if defined(__MINGW32__) || defined(__MINGW64__)
#			undef  MU0_HAVE_MINGW
#			define MU0_HAVE_MINGW     1
#		endif
#	elif defined(__MINGW32__) || defined(__MINGW64__)
#		undef  MU0_HAVE_MINGW
#		define MU0_HAVE_MINGW        1
#	elif                 \
	   defined(__sun)    \
	|| defined(sun)      \
	|| defined(__sun__)  \
	|| defined(__SVR4)   \
	|| defined(__svr4__)
#		undef  MU0_HAVE_SOLARIS
#		define MU0_HAVE_SOLARIS      1
#	elif defined(__FreeBSD__)
#		undef  MU0_HAVE_FREEBSD
#		define MU0_HAVE_FREEBSD      1
#	elif defined(__OpenBSD__)
#		undef  MU0_HAVE_OPENBSD
#		define MU0_HAVE_OPENBSD      1
#	elif defined(__NetBSD__)
#		undef  MU0_HAVE_NETBSD
#		define MU0_HAVE_NETBSD       1
#	elif defined(__DragonFly__)
#		undef  MU0_HAVE_DRAGONFLYBSD
#		define MU0_HAVE_DRAGONFLYBSD 1
#	elif defined(ANDROID) || defined(__ANDROID__)
#		undef  MU0_HAVE_ANDROID
#		define MU0_HAVE_ANDROID      1
#	elif defined(__linux__)
#		undef  MU0_HAVE_LINUX
#		define MU0_HAVE_LINUX        1
#	elif defined(__NuttX__)
#		undef  MU0_HAVE_NUTTX
#		define MU0_HAVE_NUTTX        1
#	elif defined(__minix)
#		undef  MU0_HAVE_MINIX
#		define MU0_HAVE_MINIX        1
#	endif

#	undef  MU0_HAVE_ARCH
#	define MU0_HAVE_ARCH      0

#	undef  MU0_HAVE_X86
#	undef  MU0_HAVE_X64
#	undef  MU0_HAVE_IA32
#	undef  MU0_HAVE_AMD64
#	undef  MU0_HAVE_IA64
#	undef  MU0_HAVE_ARMTB
#	undef  MU0_HAVE_ARM32
#	undef  MU0_HAVE_ARMV6
#	undef  MU0_HAVE_ARMV7
#	undef  MU0_HAVE_ARM64

#	define MU0_HAVE_X86      0
#	define MU0_HAVE_X64      0
#	define MU0_HAVE_IA32     0
#	define MU0_HAVE_IA64     0
#	define MU0_HAVE_AMD64    0
#	define MU0_HAVE_ARMTB    0
#	define MU0_HAVE_ARM32    0
#	define MU0_HAVE_ARMV6    0
#	define MU0_HAVE_ARMV7    0
#	define MU0_HAVE_ARM64    0

#	if                        \
	   defined(i386)          \
	|| defined(__i386)        \
	|| defined(__i386__)      \
	|| defined(__i486__)      \
	|| defined(__i586__)      \
	|| defined(__i686__)      \
	|| defined(_M_I86)        \
	|| defined(_M_IX86)       \
	|| defined(__X86__)       \
	|| defined(_X86_)         \
	|| defined(__AVX__)       \
	|| defined(__AVX2__)      \
	|| defined(__AVX512BW__)  \
	|| defined(__AVX512CD__)  \
	|| defined(__AVX512DQ__)  \
	|| defined(__AVX512F__)   \
	|| defined(__AVX512VL__)  \
	|| defined(__ATOM__)      \
	|| defined(__THW_INTEL__) \
	|| defined(__I86__)       \
	|| defined(__INTEL__)     \
	|| defined(_M_I286)       \
	|| defined(_386)
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_X86
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_X86   1
#	endif

#	if                                          \
	  (defined(_M_X64) && !defined(_M_ARM64EC)) \
	|| defined(__X86_64__)                      \
	|| defined(__x86_64__)
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_X86
#		undef  MU0_HAVE_X64
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_X86   0
#		define MU0_HAVE_X64   1
#	endif

#	if                                           \
	   defined(__amd64__)                        \
	|| defined(__amd64)                          \
	|| defined(_M_AMD64)                         \
	|| (defined(_M_X64) && !defined(_M_ARM64EC)) \
	|| defined(__X86_64__)                       \
	|| defined(__x86_64__)
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_X86
#		undef  MU0_HAVE_X64
#		undef  MU0_HAVE_IA32
#		undef  MU0_HAVE_AMD64
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_X86   0
#		define MU0_HAVE_X64   1
#		define MU0_HAVE_IA32  1
#		define MU0_HAVE_AMD64 1
#	endif

#	if                      \
	   defined(__ia64__)    \
	|| defined(__itanium__) \
	|| defined(_IA64)       \
	|| defined(__IA64__)    \
	|| defined(__ia64)      \
	|| defined(_M_IA64)
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_X86
#		undef  MU0_HAVE_X64
#		undef  MU0_HAVE_IA32
#		undef  MU0_HAVE_IA64
#		undef  MU0_HAVE_AMD64
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_X86   0
#		define MU0_HAVE_X64   1
#		define MU0_HAVE_IA32  0
#		define MU0_HAVE_IA64  1
#		define MU0_HAVE_AMD64 0
#	endif

#	if                       \
	   defined(__arm__)      \
	|| defined(ARM)          \
	|| defined(_M_ARM)       \
	|| defined(_M_ARMT)      \
	|| defined(__arm)        \
	&& !defined(__aarch64__) \
	&& !defined(__arm64__)   \
	&& !defined(_M_ARM64)    \
	&& !defined(_M_ARM64EC)
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_ARM32
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_ARM32 1
#	endif

#	if                                    \
	   defined(__ARM_ARCH_6__)            \
	|| defined(__ARM_ARCH_6J__)           \
	|| defined(__ARM_ARCH_6K__)           \
	|| defined(__ARM_ARCH_6Z__)           \
	|| defined(__ARM_ARCH_6ZK__)          \
	|| defined(__ARM_ARCH_6T2__)          \
	|| (defined(__TARGET_ARCH_ARM) && (   \
			__TARGET_ARCH_ARM == 6          \
	))                                    \
	|| (defined(_M_ARM) && (              \
			_M_ARM            == 6          \
	))
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_ARM32
#		undef  MU0_HAVE_ARMV6
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_ARM32 1
#		define MU0_HAVE_ARMV6 1
#		if                                 \
			   defined(__thumb__)           \
			|| defined(__TARGET_ARCH_THUMB) \
			|| defined(_M_ARMT)
#			undef  MU0_HAVE_ARMTB
#			define MU0_HAVE_ARMTB 1
#		endif
#	endif

#	if                                  \
	   defined(__ARM_ARCH_7__)          \
	|| defined(__ARM_ARCH_7A__)         \
	|| defined(__ARM_ARCH_7R__)         \
	|| defined(__ARM_ARCH_7M__)         \
	|| defined(__ARM_ARCH_7S__)         \
	|| defined(_M_ARM_ARMV7VE)          \
	|| (defined(__TARGET_ARCH_ARM) && ( \
			__TARGET_ARCH_ARM == 7        \
	))                                  \
	|| (defined(_M_ARM) && (            \
			_M_ARM            == 7        \
	))
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_ARMTB
#		undef  MU0_HAVE_ARM32
#		undef  MU0_HAVE_ARMV6
#		undef  MU0_HAVE_ARMV7
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_ARMTB 0
#		define MU0_HAVE_ARM32 1
#		define MU0_HAVE_ARMV6 0
#		define MU0_HAVE_ARMV7 1
#	endif

#	if                                  \
	   defined(__aarch64__)             \
	|| defined(__arm64__)               \
	|| defined(__ARM_ARCH_8__)          \
	|| defined(__ARM_ARCH_8A__)         \
	|| defined(_M_ARM64)                \
	|| defined(_M_ARM64EC)              \
	|| (defined(__TARGET_ARCH_ARM) && ( \
			__TARGET_ARCH_ARM == 8        \
	))                                  \
	|| (defined(_M_ARM) && (            \
			_M_ARM            == 8        \
	))
#		undef  MU0_HAVE_ARCH
#		undef  MU0_HAVE_ARMTB
#		undef  MU0_HAVE_ARM32
#		undef  MU0_HAVE_ARMV6
#		undef  MU0_HAVE_ARMV7
#		undef  MU0_HAVE_ARM64
#		define MU0_HAVE_ARCH  1
#		define MU0_HAVE_ARMTB 0
#		define MU0_HAVE_ARM32 0
#		define MU0_HAVE_ARMV6 0
#		define MU0_HAVE_ARMV7 0
#		define MU0_HAVE_ARM64 1
#	endif

#	undef  MU0_HAVE_LP32
#	undef  MU0_HAVE_ILP32
#	undef  MU0_HAVE_LLP64
#	undef  MU0_HAVE_LP64
#	undef  MU0_HAVE_ILP64
#	undef  MU0_HAVE_SILP64

#	define MU0_HAVE_LP32   1
#	define MU0_HAVE_ILP32  0
#	define MU0_HAVE_LLP64  0
#	define MU0_HAVE_LP64   0
#	define MU0_HAVE_ILP64  1
#	define MU0_HAVE_SILP64 1

#	if                    \
	   defined(__ILP32__) \
	|| defined(_ILP32)
#		undef  MU0_HAVE_LP32
#		undef  MU0_HAVE_ILP32
#		undef  MU0_HAVE_LLP64
#		undef  MU0_HAVE_LP64
#		undef  MU0_HAVE_ILP64
#		undef  MU0_HAVE_SILP64
#		define MU0_HAVE_ILP32  1
#	endif

#	if                                                    \
	   defined(__LP64__)                                  \
	|| defined(__LP64)                                    \
	|| (defined(__SIZEOF_LONG__) && __SIZEOF_LONG__ == 8)
#		undef  MU0_HAVE_LP32
#		undef  MU0_HAVE_ILP32
#		undef  MU0_HAVE_LLP64
#		undef  MU0_HAVE_LP64
#		undef  MU0_HAVE_ILP64
#		undef  MU0_HAVE_SILP64
#		define MU0_HAVE_LP64   1
#	endif

#	if                     \
		   MU0_HAVE_WINDOWS \
		|| ((defined(LONG_MAX) && defined(INT_MAX)) && (LONG_MAX == INT_MAX))
#		undef  MU0_HAVE_LP32
#		undef  MU0_HAVE_ILP32
#		undef  MU0_HAVE_LLP64
#		undef  MU0_HAVE_LP64
#		undef  MU0_HAVE_ILP64
#		undef  MU0_HAVE_SILP64
#		define MU0_HAVE_LLP64  1
#	endif

#	if !MU0_HAVE_ARCH
#		error mu0_platform.h
#	endif

#	if defined(MU0_HAVE_LP32) || defined(MU0_HAVE_ILP64) || defined(MU0_HAVE_SILP64)
#		error mu0_platform.h
#	endif

#	undef  MU0_HAVE_CHAR_UNSIGNED
#	define MU0_HAVE_CHAR_UNSIGNED 0

#	if                                                                      \
	   defined(_CHAR_UNSIGNED)                                              \
	|| defined(__CHAR_UNSIGNED__)                                           \
	|| ((defined(CHAR_MIN) && defined(SCHAR_MIN)) && CHAR_MIN != SCHAR_MIN) \
	|| (defined(CHAR_MIN) && CHAR_MIN < 0)
#	undef  MU0_HAVE_CHAR_UNSIGNED
#	define MU0_HAVE_CHAR_UNSIGNED 1
#	endif

#	if defined(__CHAR_BIT__)
#	if __CHAR_BIT__ != 8
#		error mu0_platform.h
#	endif
#	endif

#	if defined(__SIZEOF_SHORT__)
#	if __SIZEOF_SHORT__ != 2
#		error mu0_platform.h
#	endif
#	endif

#	if defined(__SIZEOF_INT__)
#	if __SIZEOF_INT__ != 4
#		error mu0_platform.h
#	endif
#	endif

#	if defined(__SIZEOF_LONG__)
#	if !(__SIZEOF_LONG__ == 8 || __SIZEOF_LONG__ == 4)
#		error mu0_platform.h
#	endif
#	endif

#	if defined(__SIZEOF_LONG_LONG__)
#	if __SIZEOF_LONG_LONG__ != 8
#		error mu0_platform.h
#	endif
#	endif

#	define ___mu0_uint8_t___ unsigned long long int
#	define ___mu0_sint8_t___   signed long long int

#	define ___mu0_uintx_t___ unsigned long int
#	define ___mu0_sintx_t___   signed long int

#	define ___mu0_uint4_t___ unsigned int
#	define ___mu0_sint4_t___   signed int

#	define ___mu0_uint2_t___ unsigned short int
#	define ___mu0_sint2_t___   signed short int

#	define ___mu0_uint1_t___ unsigned char
#	define ___mu0_sint1_t___   signed char
#	define ___mu0_tint1_t___          char

#endif /* !MU0_PLATFORM_H */

/* EOF */