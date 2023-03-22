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

// mu0_parallelize.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_platform.h>

#ifndef MU0_PARALLELIZE_H
#define MU0_PARALLELIZE_H 1

#	undef  MU0_HAVE_PARALLELIZE
#	define MU0_HAVE_PARALLELIZE 0

#	if _OPENMP
#		undef  MU0_HAVE_PARALLELIZE
#		define MU0_HAVE_PARALLELIZE 1
#		if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_ARMCC
#		pragma GCC diagnostic push
#		pragma GCC diagnostic ignored "-Wpedantic"
#		endif
#		include <omp.h>
#		if MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_ARMCC
#		pragma GCC diagnostic pop
#		endif
#	endif

#endif /* !MU0_PARALLELIZE_H */

/* EOF */