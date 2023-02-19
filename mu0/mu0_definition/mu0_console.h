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
#include <mu0/mu0_definition/mu0_bitset.h>

#ifndef MU0_CONSOLE_H
#define MU0_CONSOLE_H 1

#	if MU0_HAVE_ANDROID
#		include <android/log.h>
#		define __mu0_console__(...)      __android_log_print(ANDROID_LOG_DEBUG, "mu0", __VA_ARGS__)
#	else
#		include <stdio.h>
#		if MU0_HAVE_CC_MSVCC
#		define __mu0_console__(ARGS...) fprintf(stderr, ##ARGS)
#		else
#		define __mu0_console__(...)     fprintf(stderr, __VA_ARGS__)
#		endif
#	endif

#	define __mu0_bitset_print_u8__(__x) \
	__mu0_console__("" __mu0_bitset_pattern_u8__ "\n", __mu0_bitset_format_u8__(((unsigned char)(__x))))

#	define __mu0_bitset_print_u16__(__x) \
	__mu0_console__("" __mu0_bitset_pattern_u16__ "\n", __mu0_bitset_format_u16__(((unsigned short)(__x))))

#	define __mu0_bitset_print_u32__(__x) \
	__mu0_console__("" __mu0_bitset_pattern_u32__ "\n", __mu0_bitset_format_u32__(((unsigned int)(__x))))

#	define __mu0_bitset_print_u64__(__x) \
	__mu0_console__("" __mu0_bitset_pattern_u64__ "\n", __mu0_bitset_format_u64__(((unsigned long long)(__x))))

#endif /* !MU0_CONSOLE_H */

/* EOF */