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
	mu0_uint32_t  c = mu0_const_uchar8(*(p + 0));
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

const mu0_string8_t mu0_string8_at(
	  const mu0_string8_t src
	, const mu0_index_t   index
	, mu0_sint32_t *      width
) {
	mu0_index_t   i = 0, j = 0;
	mu0_string8_t p = src;
	mu0_uint32_t  c = mu0_const_uchar8(*(p + 0));
	mu0_sint32_t  k;

	*width          = 0;
	for (; c != 0; ++i, ++j) {
		c          = mu0_const_uchar8(*(p + i));
		     if (c <= 127)           { k = 0; }
		else if ((c & 0xE0) == 0xC0) { k = 1; }
		else if ((c & 0xF0) == 0xE0) { k = 2; }
		else if ((c & 0xF8) == 0xF0) { k = 3; }
		else                         { break; }
		if(j == index) {
			*width = k + 1;
			return p + i;
		}
		i        += k;
	}
	return mu0_nullptr;
}

/* EOF */