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

// mu0_string8.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_string8.h>

__mu0_static_inline__
void mu0_string8_reverse_body(mu0_tchar8_t * first, mu0_tchar8_t * last)
{
	mu0_tchar8_t * __first, * __last;
	mu0_tchar8_t c;
	__first = first;
	__last  = last;
	while (__first < __last) {
		c        = *__first;
		*__first = *__last;
		*__last  = c;
		++__first;
		--__last;
	}
}

__mu0_static_inline__
mu0_tchar8_t * mu0_string8_reverse_codepoint(mu0_tchar8_t * src)
{
	mu0_tchar8_t * __first = src;
	mu0_tchar8_t * __last  = src;
	while ((*(__last + 1U) & 0xC0) == 0x80) {
		++__last;
	}
	mu0_string8_reverse_body(__first, __last);
	return __last + 1U;
}

mu0_usize_t mu0_string8_length(const mu0_tchar8_t * src)
{
	return strlen(src);
}

mu0_usize_t mu0_string8_size(const mu0_tchar8_t * src)
{
	return strlen(src) + 1U;
}

mu0_usize_t mu0_string8_count(const mu0_tchar8_t * src)
{
	      mu0_usize_t    i = 0, j = 0;
	const mu0_tchar8_t * p = src;
	      mu0_uint32_t   c = mu0_const_uchar8(*(p + 0));
	      mu0_uint32_t   c0, c1, c2, c3;

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

mu0_bool_t mu0_string8_isUTF8(
	const mu0_tchar8_t * src
) {
	      mu0_bool_t     r = mu0_false;
	      mu0_usize_t    i = 0;
	const mu0_tchar8_t * p = src;
	      mu0_uint32_t   c0, c1, c2, c3;

	for (; *(p + 0) != 0;) {
		r = ( ((*(p + 0) & 0x80) == 0)
				|| ((*(p + 0) & 0xE0) == 0xC0 && (*(p + 1) & 0xC0) == 0x80)
				|| ((*(p + 0) & 0xF0) == 0xE0 && (*(p + 1) & 0xC0) == 0x80 && (*(p + 2) & 0xC0) == 0x80)
				|| ((*(p + 0) & 0xF8) == 0xF0 && (*(p + 1) & 0xC0) == 0x80 && (*(p + 2) & 0xC0) == 0x80 && (*(p + 3) & 0xC0) == 0x80)
		) ? mu0_true : mu0_false;
		if (r == mu0_false) {
			break;
		}
		c0  = (*(p + 0) & 0x80) >> 7U;
		c1  = (*(p + 0) & 0x40) >> 6U;
		c2  = (*(p + 0) & 0x20) >> 5U;
		c3  = (*(p + 0) & 0x10) >> 4U;
		i  += 1U + c0 * c1 + c0 * c1 * c2 + c0 * c1 * c2 * c3;
		p   = src + i;
	}
	return r;
}

const mu0_tchar8_t * mu0_string8_at(
	  const mu0_tchar8_t * src
	, const mu0_index_t    index
	,       mu0_sint32_t * width
) {
	      mu0_index_t    i = 0, j = 0;
	const mu0_tchar8_t * p = src;
	      mu0_uint32_t   c = mu0_const_uchar8(*(p + 0));
	      mu0_sint32_t   k;

	*width          = 0;
	for (; c != 0; ++i, ++j) {
		c          = mu0_const_uchar8(*(p + i));
		     if (c <= 127)           { k = 0; }
		else if ((c & 0xE0) == 0xC0) { k = 1; }
		else if ((c & 0xF0) == 0xE0) { k = 2; }
		else if ((c & 0xF8) == 0xF0) { k = 3; }
		else                         { break; }
		if (j == index) {
			*width = k + 1;
			return p + i;
		}
		i        += k;
	}
	return mu0_nullptr;
}

const mu0_tchar8_t * mu0_string8_reverse(
	  const mu0_tchar8_t * src
	,       mu0_tchar8_t * dest
) {
	mu0_tchar8_t * __first, * __last;
	if (src != dest) {
		memcpy(dest, src, strlen(src) + __mu0_sizeof__(mu0_tchar8_t));
	}
	__first = dest;
	__last  = dest;
	while (*__last != 0) {
		__last = mu0_string8_reverse_codepoint(__last);
	}
	__last = __last - 1U;
	mu0_string8_reverse_body(__first, __last);
	return __first;
}

const mu0_tchar8_t * mu0_string8_range_at(
	  const mu0_tchar8_t * first
	, const mu0_tchar8_t * last
	, const mu0_index_t    index
	,       mu0_sint32_t * width
) {
	      mu0_index_t    i       = 0, j = 0;
	const mu0_tchar8_t * __first = first, * __last = last;
	      mu0_uint32_t   c       = mu0_const_uchar8(*(__first + 0));
	      mu0_sint32_t   k;
	*width                 = 0;
	for (; c != 0 && __first != __last; ++i, ++j) {
		c          = mu0_const_uchar8(*(__first + i));
		     if (c <= 127)           { k = 0; }
		else if ((c & 0xE0) == 0xC0) { k = 1; }
		else if ((c & 0xF0) == 0xE0) { k = 2; }
		else if ((c & 0xF8) == 0xF0) { k = 3; }
		else                         { break; }
		if (j == index) {
			*width = k + 1;
			return __first + i;
		}
		i        += k;
	}
	return mu0_nullptr;
}

const mu0_tchar8_t * mu0_string8_range_reverse(
	  mu0_tchar8_t * first
	, mu0_tchar8_t * last
) {
	mu0_tchar8_t * __first, * __last;
	__first = first;
	__last  = first;
	while (*__last != 0 && __last != last) {
		__last = mu0_string8_reverse_codepoint(__last);
	}
	__last = __last - 1U;
	mu0_string8_reverse_body(__first, __last);
	return __first;
}

/* EOF */