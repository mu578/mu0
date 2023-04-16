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
#include <string.h>

#	if MU0_HAVE_I18NLOCALE
#		undef  __mu0_memset__
#		undef  __mu0_memcpy__
#		undef  __mu0_strlen__
#		undef  __mu0_strchr__
#		define __mu0_memset__ memset
#		define __mu0_memcpy__ memcpy
#		define __mu0_strlen__ strlen
#		define __mu0_strchr__ strchr
#	endif

__mu0_static_inline__
const mu0_tchar8_t * mu0_locale_name(
	  const mu0_tchar8_t * language
	, const mu0_tchar8_t * territory
	, const mu0_tchar8_t * modifier  __mu0_nullable__
) {
#	if MU0_HAVE_I18NLOCALE
	__mu0_static__
	mu0_tchar8_t   s_name[48];
	mu0_tchar8_t * variant;
	mu0_bool_t     have_name = mu0_false;
	mu0_uint64_t   k, l, p   = 0;

	//#! XPG syntax:[language[_territory[.codeset]][@modifier[+variant]]
	__mu0_memset__(s_name, 0, __mu0_sizeof__(s_name));
	if (__mu0_not_nullptr__(language)) {
		k = __mu0_strlen__(language);
		if (k > 0) {
			l  = k;
			__mu0_memcpy__(s_name + p, language, l);
			p += l;
			if (__mu0_not_nullptr__(territory)) {
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
				if (__mu0_not_nullptr__(modifier)) {
					variant = __mu0_strchr__(modifier, '+');
					if (__mu0_not_nullptr__(variant)) {
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
	return (have_name == mu0_true) ? s_name : __mu0_nullptr__;
#	else
	__mu0_unused__(language);
	__mu0_unused__(territory);
	__mu0_unused__(modifier);

	return __mu0_nullptr__;
#	endif
}

mu0_locale_t mu0_locale_create(
	  const mu0_tchar8_t * language
	, const mu0_tchar8_t * territory
	, const mu0_tchar8_t * modifier  __mu0_nullable__
	, const mu0_bool_t     collator
) {
	const mu0_sint32_t   mask = ((collator == mu0_true) ? LC_COLLATE_MASK : LC_ALL_MASK);
	const mu0_tchar8_t * name = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	if (__mu0_not_nullptr__(name)) {
		return __mu0_i18nlocale_new__(mask, name, __mu0_nullptr__);
	}
	return __mu0_nullptr__;
}

mu0_sint32_t mu0_locale_global(
	  const mu0_tchar8_t * language
	, const mu0_tchar8_t * territory
	, const mu0_tchar8_t * modifier  __mu0_nullable__
	, const mu0_bool_t     collator
) {
	const mu0_sint32_t   category = ((collator == mu0_true) ? LC_COLLATE : LC_ALL);
	const mu0_tchar8_t * name     = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	if (__mu0_not_nullptr__(name)) {
		if (__mu0_not_nullptr__(__mu0_i18nlocale_set__(category, name))) {
			return 0;
		}
	}
	return -1;
}

mu0_sint32_t mu0_locale_delete(mu0_locale_t locale)
{ return __mu0_i18nlocale_free__(locale); }

enum mu0_ordering mu0_locale_compare(
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_locale_t   locale __mu0_nullable__
) { return __mu0_i18nlocale_compare__(lhs, rhs, locale); }

enum mu0_ordering mu0_locale_compare_n(
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_uint32_t   n
	, const mu0_locale_t   locale __mu0_nullable__
) { return __mu0_i18nlocale_compare_n__(lhs, rhs, n, locale); }

/* EOF */