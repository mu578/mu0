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

// mu0_string.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_integer.h>

#ifndef MU0_STRING_H
#define MU0_STRING_H 1

MU0_BEGIN_CDECL

typedef          char  mu0_tchar8_t;
typedef unsigned char  mu0_uchar8_t;
typedef signed   char  mu0_schar8_t;

typedef mu0_tchar8_t * mu0_vtchar8_t;
typedef mu0_uchar8_t * mu0_vuchar8_t;
typedef mu0_schar8_t * mu0_vschar8_t;

typedef mu0_vtchar8_t  mu0_string8_t;
typedef mu0_vuchar8_t  mu0_binary8_t;

#	define mu0_tchar8(__x)        mu0_cast(mu0_tchar8_t, __x)
#	define mu0_const_tchar8(__x)  mu0_const_cast(mu0_tchar8_t, __x)
#	define mu0_uchar8(__x)        mu0_cast(mu0_uchar8_t, __x)
#	define mu0_const_uchar8(__x)  mu0_const_cast(mu0_uchar8_t, __x)
#	define mu0_schar8(__x)        mu0_cast(mu0_schar8_t, __x)
#	define mu0_const_schar8(__x)  mu0_const_cast(mu0_schar8_t, __x)

#	define mu0_vtchar8(__x)       mu0_cast(mu0_vtchar8_t, __x)
#	define mu0_const_vtchar8(__x) mu0_const_cast(mu0_vtchar8_t, __x)
#	define mu0_vuchar8(__x)       mu0_cast(mu0_vuchar8_t, __x)
#	define mu0_const_vuchar8(__x) mu0_const_cast(mu0_vuchar8_t, __x)
#	define mu0_vschar8(__x)       mu0_cast(mu0_vschar8_t, __x)
#	define mu0_const_vschar8(__x) mu0_const_cast(mu0_vschar8_t, __x)

#	define mu0_string8(__x)       mu0_cast(mu0_string8_t, __x)
#	define mu0_const_string8(__x) mu0_const_cast(mu0_string8_t, __x)
#	define mu0_binary8(__x)       mu0_cast(mu0_binary8_t, __x)
#	define mu0_const_binary8(__x) mu0_const_cast(mu0_binary8_t, __x)

mu0_usize_t mu0_string8_length(const mu0_string8_t src);
mu0_usize_t mu0_string8_size  (const mu0_string8_t src);
mu0_usize_t mu0_string8_count (const mu0_string8_t src);

const mu0_string8_t mu0_string8_at(
	  const mu0_string8_t src
	, const mu0_index_t   index
	, mu0_sint32_t *      width
);

void mu0_string8_reverse(
		  const mu0_string8_t src
		, mu0_string8_t       dest
);

void mu0_string8_range_reverse(
	  const mu0_string8_t first
	, const mu0_string8_t last
);

MU0_END_CDECL

#endif /* !MU0_STRING_H */

/* EOF */