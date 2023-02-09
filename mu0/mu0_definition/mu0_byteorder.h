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

MU0_BEGIN_CDECL

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
#	elif MU0_HAVE_CC_MSVC
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
#	elif MU0_HAVE_CC_ICC
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
#		error mu0_byteorder.h
#	endif

MU0_END_CDECL

#endif /* !MU0_BYTEORDER_H */

/* EOF */