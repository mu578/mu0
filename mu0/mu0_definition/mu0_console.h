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

// mu0_console.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_compiler.h>

#ifndef MU0_CONSOLE_H
#define MU0_CONSOLE_H 1

#	if MU0_HAVE_ANDROID
#		include <android/log.h>
#		define __mu0_console_log__(...)         __android_log_print(ANDROID_LOG_DEBUG, "mu0", __VA_ARGS__)
#	else
#		include <stdio.h>
#		if MU0_HAVE_CC_MSVCC
#			define __mu0_console_log__(ARGS...) fprintf(stderr, ##ARGS)
#		else
#			define __mu0_console_log__(...)     fprintf(stderr, __VA_ARGS__)
#		endif
#	endif

#endif /* !MU0_CONSOLE_H */

/* EOF */