//
// # -*- coding: utf-8, tab-width: 3 -*-

//                                                           _                                            //
//                                                          / _ \                                           //
//                                            _   _  _   _ | | | |                                          //
//                                           | | | || | | || | | |                                          //
//                                           | |_| || |_| || |_| |                                          //
//                                           | ._,_| \_/  \_/                                           //
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
#		include <omp.h>
#	endif

#endif /* !MU0_PARALLELIZE_H */

/* EOF */