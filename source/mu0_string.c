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
	mu0_usize_t   i = 0, j = 0;
	mu0_string8_t p = src;
	mu0_uchar8_t  c = mu0_const_uchar8(*(p + 0));
	mu0_uint32_t  c0, c1, c2, c3;

	for (; c != 0; ++j) {
		c0  = (c & 0x80) >> 7U;
		c1  = (c & 0x40) >> 6U;
		c2  = (c & 0x20) >> 5U;
		c3  = (c & 0x10) >> 4U;
		i  += 1U + c0 * c1 + c0 * c1 * c2 + c0 * c1 * c2 * c3;
		c   = mu0_const_uchar8(*(p + i));
	}
	return j;
}

/* EOF */