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

// mu0_locale.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_integer.h>
#include <mu0/mu0_string.h>

#ifndef MU0_LOCALE_H
#define MU0_LOCALE_H 1

MU0_BEGIN_CDECL

typedef void * mu0_locale_t;

mu0_locale_t mu0_locale_create(
	  const mu0_tchar8_t * language
	, const mu0_tchar8_t * territory
	, const mu0_tchar8_t * modifier  __mu0_nullable__
	, const mu0_bool_t     collator
);

mu0_sint32_t mu0_locale_global(
	  const mu0_tchar8_t * language
	, const mu0_tchar8_t * territory
	, const mu0_tchar8_t * modifier  __mu0_nullable__
	, const mu0_bool_t     collator
);

const mu0_tchar8_t * mu0_locale_identifier(
	  const mu0_bool_t   collator
	, const mu0_locale_t locale   __mu0_nullable__
);

mu0_sint32_t mu0_locale_delete(mu0_locale_t locale);

enum mu0_ordering mu0_locale_compare(
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_locale_t   locale __mu0_nullable__
);

enum mu0_ordering mu0_locale_compare_n(
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_uint32_t   n
	, const mu0_locale_t   locale __mu0_nullable__
);

MU0_END_CDECL

#endif /* !MU0_LOCALE_H */

/* EOF */