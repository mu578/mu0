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

// mu0_string.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_string.h>

#include <string.h>

#	undef  __mu0_strlen__
#	define __mu0_strlen__  strlen

mu0_usize_t mu0_string8_length(const mu0_string8_t src)
{
	return __mu0_strlen__(src);
}

mu0_usize_t mu0_string8_size(const mu0_string8_t src)
{
	return __mu0_strlen__(src) + 1U;
}

mu0_usize_t mu0_string8_count(const mu0_string8_t src)
{
	mu0_string8_t p = src;
	mu0_usize_t   c = 0;
	for (; *p; ++p) {
		if ((*p & 0xC0) != 0x80) {
			++c;
		}
	}
	return c;
}

/* EOF */