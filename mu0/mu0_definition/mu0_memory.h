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

// mu0_memory.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_MEMORY_H
#define MU0_MEMORY_H 1

#	include <string.h>

#	if  MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_ARMCCC || MU0_HAVE_CC_MSVCL
#		if __has_builtin(__builtin_memset)
#			define __mu0_memset__ __builtin_memset
#		else
#			define __mu0_memset__ memset
#		endif
#		if __has_builtin(__builtin_memcpy)
#			define __mu0_memcpy__ __builtin_memcpy
#		else
#			define __mu0_memcpy__ memcpy
#		endif
#		if __has_builtin(__builtin_strlen)
#			define __mu0_memlen__ __builtin_strlen
#		else
#			define __mu0_memlen__ strlen
#		endif
#	elif MU0_HAVE_CC_GNUCC
#		define __mu0_memset__ __builtin_memset
#		define __mu0_memcpy__ __builtin_memcpy
#		define __mu0_memlen__ __builtin_strlen
#	else
#		define __mu0_memset__ memset
#		define __mu0_memcpy__ memcpy
#		define __mu0_memlen__ strlen
#	endif

#endif /* !MU0_MEMORY_H */

/* EOF */