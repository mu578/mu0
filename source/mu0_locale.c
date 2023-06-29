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
const mu0_tchar8_t * mu0_locale_name(
	  const mu0_tchar8_t * language
	, const mu0_tchar8_t * territory
	, const mu0_tchar8_t * modifier  __mu0_nullable__
) {
	return __mu0_i18nlocale_id__(language, territory, modifier);
}

mu0_locale_t * mu0_locale_create(
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

const mu0_tchar8_t * mu0_locale_interface(void)
{
	return __mu0_i18nlocale_user__();
}

const mu0_tchar8_t * mu0_locale_identifier(
	  const mu0_bool_t     collator
	, const mu0_locale_t * locale   __mu0_nullable__
) {
	const mu0_sint32_t category = ((collator == mu0_true) ? LC_COLLATE : LC_ALL);
	return __mu0_i18nlocale_get__(category, locale);
}

mu0_sint32_t mu0_locale_delete(
	mu0_locale_t * locale
) {
	return __mu0_i18nlocale_free__(locale);
}

enum mu0_ordering mu0_locale_compare(
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_locale_t * locale __mu0_nullable__
) { return __mu0_i18nlocale_compare__(lhs, rhs, locale); }

enum mu0_ordering mu0_locale_compare_n(
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_uint32_t   n
	, const mu0_locale_t * locale __mu0_nullable__
) { return __mu0_i18nlocale_compare_n__(lhs, rhs, n, locale); }

/* EOF */