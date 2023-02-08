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

#ifndef MU0_PLATFORM_H
#define MU0_PLATFORM_H 1

#	undef  MU0_HAVE_DARWIN
#	undef  MU0_HAVE_MACOSX
#	undef  MU0_HAVE_IOS
#	undef  MU0_HAVE_WINDOWS
#	undef  MU0_HAVE_SOLARIS
#	undef  MU0_HAVE_FREEBSD
#	undef  MU0_HAVE_OPENBSD
#	undef  MU0_HAVE_NETBSD
#	undef  MU0_HAVE_ANDROID
#	undef  MU0_HAVE_LINUX

#	define MU0_HAVE_DARWIN  0
#	define MU0_HAVE_MACOSX  0
#	define MU0_HAVE_IOS     0
#	define MU0_HAVE_WINDOWS 0
#	define MU0_HAVE_SOLARIS 0
#	define MU0_HAVE_FREEBSD 0
#	define MU0_HAVE_OPENBSD 0
#	define MU0_HAVE_NETBSD  0
#	define MU0_HAVE_ANDROID 0
#	define MU0_HAVE_LINUX   0
if defined(__APPLE__) && defined(__MACH__)
#		if TARGET_OS_IPHONE
#			undef  MU0_HAVE_DARWIN 0
#			undef  MU0_HAVE_IOS    0
#			define MU0_HAVE_DARWIN 1
#			define MU0_HAVE_IOS    1
#		else
#			undef  MU0_HAVE_DARWIN 0
#			undef  MU0_HAVE_MACOSX 0
#			define MU0_HAVE_DARWIN 1
#			define MU0_HAVE_MACOSX 1
#		endif
#	elif defined(_WIN32) || defined(_WIN64)
#		undef  MU0_HAVE_WINDOWS 0
#		define MU0_HAVE_WINDOWS 1
#	elif defined(__sun) || defined(sun)
#		undef  MU0_HAVE_SOLARIS 0
#		define MU0_HAVE_SOLARIS 1
#	elif defined(__FreeBSD__)
#		undef  MU0_HAVE_FREEBSD 0
#		define MU0_HAVE_FREEBSD 1
#	elif defined(__OpenBSD__)
#		undef  MU0_HAVE_OPENBSD 0
#		define MU0_HAVE_OPENBSD 1
#	elif defined(__NetBSD__)
#		undef  MU0_HAVE_NETBSD  0
#		define MU0_HAVE_NETBSD  1
#	elif defined(ANDROID) || defined(__ANDROID__)
#		undef  MU0_HAVE_ANDROID 0
#		define MU0_HAVE_ANDROID 1
#	elif defined(__linux__)
#		undef  MU0_HAVE_LINUX   0
#		define MU0_HAVE_LINUX   1
#	endif


#	undef  MU0_HAVE_XI86
#	undef  MU0_HAVE_IA32
#	undef  MU0_HAVE_AMD64
#	undef  MU0_HAVE_IA64
#	undef  MU0_HAVE_ARMT
#	undef  MU0_HAVE_ARM32
#	undef  MU0_HAVE_ARMV6
#	undef  MU0_HAVE_ARMV7
#	undef  MU0_HAVE_ARM64

#	define MU0_HAVE_XI86  0
#	define MU0_HAVE_IA32  0
#	define MU0_HAVE_AMD64 0
#	define MU0_HAVE_IA64  0
#	define MU0_HAVE_ARMT  0
#	define MU0_HAVE_ARM32 0
#	define MU0_HAVE_ARMV6 0
#	define MU0_HAVE_ARMV7 0
#	define MU0_HAVE_ARM64 0

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
	|| defined(__ATOM__)      \
	|| defined(__THW_INTEL__) \
	|| defined(__I86__)       \
	|| defined(__INTEL__)     \
	|| deinded (_M_I286)      \
	|| defined(_386)
#		undef  MU0_HAVE_XI86
#		define MU0_HAVE_XI86 1
#	endif

#	if                                           \
		defined(__amd64__)                        \
	|| defined(__amd64)                          \
	|| defined(_M_AMD64)                         \
	|| (defined(_M_X64) && !defined(_M_ARM64EC)) \
	|| defined(__X86_64__)                       \
	|| defined(__x86_64__)
#		undef  MU0_HAVE_XI86
#		undef  MU0_HAVE_IA32
#		undef  MU0_HAVE_AMD64
#		define MU0_HAVE_XI86  0
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
#		undef  MU0_HAVE_XI86
#		undef  MU0_HAVE_IA32
#		undef  MU0_HAVE_AMD64
#		undef  MU0_HAVE_IA64
#		define MU0_HAVE_XI86  0
#		define MU0_HAVE_IA32  0
#		define MU0_HAVE_AMD64 0
#		define MU0_HAVE_IA64  1
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
	&& !defined(_M_ARM64EC)  \
#		undef  MU0_HAVE_ARM32
#		define MU0_HAVE_ARM32 1
#	endif

#	if                                         \
		defined(__ARM_ARCH_6__)                 \
	|| defined(__ARM_ARCH_6J__)                \
	|| defined(__ARM_ARCH_6K__)                \
	|| defined(__ARM_ARCH_6Z__)                \
	|| defined(__ARM_ARCH_6ZK__)               \
	|| defined(__ARM_ARCH_6T2__)               \
	|| (defined(__TARGET_ARCH_ARM) && (        \
			__TARGET_ARCH_ARM = 6                \
	))                                         \
	|| (defined(_M_ARM) && (                   \
			_M_ARM            = 6                \
	))
#		undef  MU0_HAVE_ARM32
#		undef  MU0_HAVE_ARMV6
#		define MU0_HAVE_ARM32 1
#		define MU0_HAVE_ARMV6 1
#		if                                     \
				defined(__thumb__)               \
			|| defined(__TARGET_ARCH_THUMB)     \
			|| defined(_M_ARMT)
#			undef  MU0_HAVE_ARMT
#			define MU0_HAVE_ARMT 1
#		endif
#	endif

#	if                                        \
		defined(__ARM_ARCH_7__)                \
	|| defined(__ARM_ARCH_7A__)               \
	|| defined(__ARM_ARCH_7R__)               \
	|| defined(__ARM_ARCH_7M__)               \
	|| defined(__ARM_ARCH_7S__)               \
	|| defined(_M_ARM_ARMV7VE)                \
	|| (defined(__TARGET_ARCH_ARM) && (       \
			__TARGET_ARCH_ARM = 7               \
	))                                        \
	|| (defined(_M_ARM) && (                  \
			_M_ARM            = 7               \
	))
#		undef  MU0_HAVE_ARMT
#		undef  MU0_HAVE_ARM32
#		undef  MU0_HAVE_ARMV6
#		undef  MU0_HAVE_ARMV7
#		define MU0_HAVE_ARMT  0
#		define MU0_HAVE_ARM32 1
#		define MU0_HAVE_ARMV7 0
#		define MU0_HAVE_ARMV7 1
#	endif

#	if                      \
	   defined(__aarch64__) \
	|| defined(__arm64__)   \
	|| defined(_M_ARM64)    \
	|| defined(_M_ARM64EC)
#		undef  MU0_HAVE_ARMT
#		undef  MU0_HAVE_ARM32
#		undef  MU0_HAVE_ARMV6
#		undef  MU0_HAVE_ARMV7
#		undef  MU0_HAVE_ARM64
#		define MU0_HAVE_ARMT  0
#		define MU0_HAVE_ARM32 0
#		define MU0_HAVE_ARMV6 0
#		define MU0_HAVE_ARMV7 0
#		define MU0_HAVE_ARM64 1
#	endif


#endif /* !MU0_PLATFORM_H */

/* EOF */