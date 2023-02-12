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

// mu0_byteorder.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_compiler.h>

#ifndef MU0_BYTEORDER_H
#define MU0_BYTEORDER_H 1

#	undef  MU0_HAVE_BYTEORDER
#	undef  __MU0_BYTE_ORDER__
#	undef  __MU0_ORDER_LEEN__
#	undef  __MU0_ORDER_BEEN__
#	define MU0_HAVE_BYTEORDER 0
#	if defined(__LITTLE_ENDIAN__)
#		if __LITTLE_ENDIAN__
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER     1
#			define __MU0_BYTE_ORDER__     __BYTE_ORDER__
#			define __MU0_ORDER_LEEN__     __ORDER_LITTLE_ENDIAN__
#			define __MU0_ORDER_BEEN__     __ORDER_BIG_ENDIAN__
#		endif
#	elif defined(__BIG_ENDIAN__)
#		if __BIG_ENDIAN__
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#			define __MU0_BYTE_ORDER__      __BYTE_ORDER__
#			define __MU0_ORDER_LEEN__      __ORDER_LITTLE_ENDIAN__
#			define __MU0_ORDER_BEEN__      __ORDER_BIG_ENDIAN__
#		endif
#	elif MU0_HAVE_CC_ARMCC
#		undef  MU0_HAVE_BYTEORDER
#		define MU0_HAVE_BYTEORDER         1
#		ifndef __BYTE_ORDER__
#			define __ORDER_LITTLE_ENDIAN__ (1234)
#			define __ORDER_BIG_ENDIAN__    (4321)
#			if defined(__ARM_BIG_ENDIAN)
#				define __BYTE_ORDER__       __ORDER_BIG_ENDIAN__
#			else
#				define __BYTE_ORDER__       __ORDER_LITTLE_ENDIAN__
#			endif
#		endif
#		define __MU0_BYTE_ORDER__         __BYTE_ORDER__
#		define __MU0_ORDER_LEEN__         __ORDER_LITTLE_ENDIAN__
#		define __MU0_ORDER_BEEN__         __ORDER_BIG_ENDIAN__
#	elif MU0_HAVE_CC_MSVCC
#		if defined(_M_PPC) || defined(_M_ALPHA)
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#			define __ORDER_LITTLE_ENDIAN__ (1234)
#			define __ORDER_BIG_ENDIAN__    (4321)
#			define __BYTE_ORDER__          __ORDER_BIG_ENDIAN__
#			define __MU0_BYTE_ORDER__      __BYTE_ORDER__
#			define __MU0_ORDER_LEEN__      __ORDER_LITTLE_ENDIAN__
#			define __MU0_ORDER_BEEN__      __ORDER_BIG_ENDIAN__
#		else
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#			define __ORDER_LITTLE_ENDIAN__ (1234)
#			define __ORDER_BIG_ENDIAN__    (4321)
#			define __BYTE_ORDER__          __ORDER_LITTLE_ENDIAN__
#			define __MU0_BYTE_ORDER__      __BYTE_ORDER__
#			define __MU0_ORDER_LEEN__      __ORDER_LITTLE_ENDIAN__
#			define __MU0_ORDER_BEEN__      __ORDER_BIG_ENDIAN__
#		endif
#	elif MU0_HAVE_CC_ITLCC
#		undef  MU0_HAVE_BYTEORDER
#		define MU0_HAVE_BYTEORDER         1
#		ifndef __BYTE_ORDER__
#			define __ORDER_LITTLE_ENDIAN__ (1234)
#			define __ORDER_BIG_ENDIAN__    (4321)
#			define __BYTE_ORDER__          __ORDER_LITTLE_ENDIAN__
#		endif
#		define __MU0_BYTE_ORDER__         __BYTE_ORDER__
#		define __MU0_ORDER_LEEN__         __ORDER_LITTLE_ENDIAN__
#		define __MU0_ORDER_BEEN__         __ORDER_BIG_ENDIAN__
#	endif


#	if !MU0_HAVE_BYTEORDER
#	if   MU0_HAVE_DARWIN || MU0_HAVE_OPENBSD 
#		include <machine/endian.h>
#	elif MU0_HAVE_ANDROID || MU0_HAVE_LINUX || MU0_HAVE_NUTTX
#		include <endian.h>
#	elif MU0_HAVE_SOLARIS
#		include <sys/byteorder.h>
#	elif MU0_HAVE_FREEBSD || MU0_HAVE_NETBSD || MU0_HAVE_DRAGONFLYBSD
#		include <sys/endian.h>
#	endif
#		if   defined(__BYTE_ORDER)
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#			define __MU0_BYTE_ORDER__      __BYTE_ORDER
#			define __MU0_ORDER_LEEN__      __LITTLE_ENDIAN
#			define __MU0_ORDER_BEEN__      __BIG_ENDIAN
#		elif defined(BYTE_ORDER)
#			define __MU0_BYTE_ORDER__      BYTE_ORDER
#			define __MU0_ORDER_LEEN__      LITTLE_ENDIAN
#			define __MU0_ORDER_BEEN__      BIG_ENDIAN
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#		endif
#	endif

#	if !MU0_HAVE_BYTEORDER
#		error mu0_byteorder.h
#	endif

#endif /* !MU0_BYTEORDER_H */

/* EOF */