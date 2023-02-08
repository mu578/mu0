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
#		undef  MU0_HAVE_NETBSD 0
#		define MU0_HAVE_NETBSD 1
#	elif defined(ANDROID) || defined(__ANDROID__)
#		undef  MU0_HAVE_ANDROID 0
#		define MU0_HAVE_ANDROID 1
#	elif defined(__linux__)
#		define MU0_HAVE_LINUX 1
#	endif


#endif /* !MU0_PLATFORM_H */

/* EOF */