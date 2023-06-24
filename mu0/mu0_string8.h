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

// mu0_string8.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_integer.h>
#include <mu0/mu0_string.h>

#ifndef MU0_STRING8_H
#define MU0_STRING8_H 1

MU0_BEGIN_CDECL

mu0_usize_t          mu0_string8_length (const mu0_tchar8_t * src);
mu0_usize_t          mu0_string8_size   (const mu0_tchar8_t * src);
mu0_usize_t          mu0_string8_count  (const mu0_tchar8_t * src);
mu0_bool_t           mu0_string8_isUTF8 (const mu0_tchar8_t * src);

const mu0_tchar8_t * mu0_string8_at(
	  const mu0_tchar8_t * src
	, const mu0_index_t    index
	,       mu0_sint32_t * width
);

const mu0_tchar8_t * mu0_string8_reverse(
	  const mu0_tchar8_t * src
	,       mu0_tchar8_t * dest
);

const mu0_tchar8_t * mu0_string8_range_at(
	  const mu0_tchar8_t * first
	, const mu0_tchar8_t * last
	, const mu0_index_t    index
	,       mu0_sint32_t * width
);

const mu0_tchar8_t * mu0_string8_range_reverse(
	  mu0_tchar8_t * first
	, mu0_tchar8_t * last
);

MU0_END_CDECL

#endif /* !MU0_STRING8_H */

/* EOF */