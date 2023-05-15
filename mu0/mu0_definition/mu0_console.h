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

#	undef  MU0_HAVE_CONSOLE
#	define MU0_HAVE_CONSOLE 0

#	if !MU0_HAVE_CONSOLE

		__mu0_static__ char const * const __mu0_console_color_red__    = "\033[0;31m";
		__mu0_static__ char const * const __mu0_console_color_green__  = "\033[0;32m";
		__mu0_static__ char const * const __mu0_console_color_yellow__ = "\033[0;33m";
		__mu0_static__ char const * const __mu0_console_color_blue__   = "\033[0;34m";
		__mu0_static__ char const * const __mu0_console_color_purple__ = "\033[0;35m";
		__mu0_static__ char const * const __mu0_console_color_cyan__   = "\033[0;36m";
		__mu0_static__ char const * const __mu0_console_color_clear__  = "\033[0m";

#		define __mu0_console_set_color__(_c)      fputs(_c, stderr);

#	if MU0_HAVE_ANDROID
#		undef  MU0_HAVE_CONSOLE
#		define MU0_HAVE_CONSOLE 1
#		include <android/log.h>
#		define __mu0_console_log__(...)        __android_log_print(ANDROID_LOG_DEBUG, "mu0", __VA_ARGS__)
#	else
#		undef  MU0_HAVE_CONSOLE
#		define MU0_HAVE_CONSOLE 1
#		include <stdio.h>
#		if MU0_HAVE_CC_MSVCC
#			define __mu0_console_log__(ARGS...) fprintf(stderr, ##ARGS)
#			define __mu0_console_info__(...)                                  \
				__mu0_console_set_color__(__mu0_console_color_green__);        \
				                                 fprintf(stderr, ##ARGS);      \
				__mu0_console_set_color__(__mu0_console_color_clear__)
#			define __mu0_console_warn__(...)                                  \
				__mu0_console_set_color__(__mu0_console_color_yellow__);       \
				                                 fprintf(stderr, ##ARGS);      \
				__mu0_console_set_color__(__mu0_console_color_clear__)
#			define __mu0_console_error__(...)                                 \
				__mu0_console_set_color__(__mu0_console_color_red__);          \
				                                 fprintf(stderr, ##ARGS);      \
				__mu0_console_set_color__(__mu0_console_color_clear__)
#		else
#			define __mu0_console_log__(...)     fprintf(stderr, __VA_ARGS__);
#			define __mu0_console_info__(...)                                  \
				__mu0_console_set_color__(__mu0_console_color_green__);        \
				                                 fprintf(stderr, __VA_ARGS__); \
				__mu0_console_set_color__(__mu0_console_color_clear__)
#			define __mu0_console_warn__(...)                                  \
				__mu0_console_set_color__(__mu0_console_color_yellow__);       \
				                                 fprintf(stderr, __VA_ARGS__); \
				__mu0_console_set_color__(__mu0_console_color_clear__)
#			define __mu0_console_error__(...)                                 \
				__mu0_console_set_color__(__mu0_console_color_red__);          \
				                                 fprintf(stderr, __VA_ARGS__); \
				__mu0_console_set_color__(__mu0_console_color_clear__)
#		endif
#	endif
#	endif

#	if !MU0_HAVE_CONSOLE
#		error mu0_console.h
#	endif

#endif /* !MU0_CONSOLE_H */

/* EOF */