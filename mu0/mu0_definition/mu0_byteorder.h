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
#	undef  __mu0_byte_order__
#	undef  __mu0_order_leen__
#	undef  __mu0_order_been__
#	define MU0_HAVE_BYTEORDER 0
#	if defined(__LITTLE_ENDIAN__)
#		if __LITTLE_ENDIAN__
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER     1
#			define __mu0_byte_order__     __BYTE_ORDER__
#			define __mu0_order_leen__     __ORDER_LITTLE_ENDIAN__
#			define __mu0_order_been__     __ORDER_BIG_ENDIAN__
#		endif
#	elif defined(__BIG_ENDIAN__)
#		if __BIG_ENDIAN__
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#			define __mu0_byte_order__      __BYTE_ORDER__
#			define __mu0_order_leen__      __ORDER_LITTLE_ENDIAN__
#			define __mu0_order_been__      __ORDER_BIG_ENDIAN__
#		endif
#	elif MU0_HAVE_CC_MSVC
#		if defined(_M_PPC) || defined(_M_ALPHA)
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#			define __ORDER_LITTLE_ENDIAN__ (1234)
#			define __ORDER_BIG_ENDIAN__    (4321)
#			define __BYTE_ORDER__          __ORDER_BIG_ENDIAN__
#			define __mu0_byte_order__      __BYTE_ORDER__
#			define __mu0_order_leen__      __ORDER_LITTLE_ENDIAN__
#			define __mu0_order_been__      __ORDER_BIG_ENDIAN__
#		else
#			undef  MU0_HAVE_BYTEORDER
#			define MU0_HAVE_BYTEORDER      1
#			define __ORDER_LITTLE_ENDIAN__ (1234)
#			define __ORDER_BIG_ENDIAN__    (4321)
#			define __BYTE_ORDER__          __ORDER_LITTLE_ENDIAN__
#			define __mu0_byte_order__      __BYTE_ORDER__
#			define __mu0_order_leen__      __ORDER_LITTLE_ENDIAN__
#			define __mu0_order_been__      __ORDER_BIG_ENDIAN__
#		endif
#	elif MU0_HAVE_CC_ICC
#		undef  MU0_HAVE_BYTEORDER
#		define MU0_HAVE_BYTEORDER         1
#		ifndef __BYTE_ORDER__
#			define __ORDER_LITTLE_ENDIAN__ (1234)
#			define __ORDER_BIG_ENDIAN__    (4321)
#			define __BYTE_ORDER__          __ORDER_LITTLE_ENDIAN__
#		endif
#		define __mu0_byte_order__         __BYTE_ORDER__
#		define __mu0_order_leen__         __ORDER_LITTLE_ENDIAN__
#		define __mu0_order_been__         __ORDER_BIG_ENDIAN__
#	endif

#endif /* !MU0_BYTEORDER_H */

/* EOF */