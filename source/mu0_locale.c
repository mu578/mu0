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

// mu0_locale.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_locale.h>

__mu0_static_inline__
const mu0_string8_t mu0_locale_name(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier  __mu0_nullable__
) {
	__mu0_static__
	mu0_tchar8_t  s_name[48];
	mu0_vtchar8_t variant;
	mu0_bool_t    have_name = mu0_false;
	mu0_uint64_t  k, l, p   = 0;

	//#! XPG syntax:[language[_territory[.codeset]][@modifier[+variant]]
	__mu0_memset__(s_name, 0, __mu0_sizeof__(s_name));
	if (mu0_not_nullptr(language)) {
		k = __mu0_strlen__(language);
		if (k > 0) {
			l  = k;
			__mu0_memcpy__(s_name + p, language, l);
			p += l;
			if (mu0_not_nullptr(territory)) {
				k  = __mu0_strlen__(territory);
				if (k > 0) {
					l  = __mu0_sizeof__(mu0_tchar8_t);
					__mu0_memcpy__(s_name + p, "_", mu0_min(6, l));
					p += l;
					l  = k;
					__mu0_memcpy__(s_name + p, territory, mu0_min(16, l));
					p += l;
					l  =  __mu0_sizeof__(mu0_tchar8_t) * 6;
					__mu0_memcpy__(s_name + p, ".UTF-8", l);
					have_name = mu0_true;
				}
				if (mu0_not_nullptr(modifier)) {
					variant = __mu0_strchr__(modifier, '+');
					if (mu0_not_nullptr(variant)) {
						k = variant - modifier;
					} else {
						k = __mu0_strlen__(modifier);
					}
					if (k > 0) {
						p += l;
						l  = __mu0_sizeof__(mu0_tchar8_t);
						__mu0_memcpy__(s_name + p, "@", l);
						p += l;
						l  = k ;
						__mu0_memcpy__(s_name + p, modifier, mu0_min(16, l));
					}
				}
			}
		}
	}
	return (have_name == mu0_true) ? s_name : mu0_nullptr;
}

mu0_locale_t mu0_locale_create(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier  __mu0_nullable__
	, const mu0_bool_t    collator
) {
	const mu0_sint32_t category = ((collator == mu0_true)
		? __MU0_LOCALE_MASK_COLLATE__
		: __MU0_LOCALE_MASK_ALL__
	);
	const mu0_string8_t name    = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	if (mu0_not_nullptr(name)) {
		return __mu0_newlocale__(category, name);
	}
	return mu0_nullptr;
}

mu0_sint32_t mu0_locale_global(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier  __mu0_nullable__
	, const mu0_bool_t    collator
) {
	const mu0_sint32_t category = ((collator == mu0_true)
		? __MU0_LOCALE_COLLATE__
		: __MU0_LOCALE_ALL__
	);
	const mu0_string8_t name    = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	if (mu0_not_nullptr(name)) {
		if (mu0_not_nullptr(__mu0_setlocale__(category, name))) {
			return 0;
		}
	}
	return -1;
}

mu0_sint32_t mu0_locale_delete(mu0_locale_t locale)
{
	if (mu0_not_nullptr(locale)) {
		__mu0_freelocale__(locale);
		return 0;
	}
	return -1;
}

mu0_sint32_t mu0_locale_compare(
	  const mu0_string8_t lhs
	, const mu0_string8_t rhs
	, const mu0_locale_t  locale __mu0_nullable__
) {
	const mu0_sint32_t r = mu0_const_sint32((mu0_not_nullptr(locale))
		? __mu0_strcoll_l__(lhs, rhs, locale)
		: __mu0_strcoll__(lhs, rhs)
	);
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
}

/* EOF */