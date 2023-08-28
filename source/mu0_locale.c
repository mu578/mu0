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
	return __mu0_i18nlocale_make__(language, territory, modifier);
}

mu0_locale_t * mu0_locale_create(
	  const      mu0_tchar8_t *  language
	, const      mu0_tchar8_t *  territory
	, const      mu0_tchar8_t *  modifier  __mu0_nullable__
	, const enum mu0_localegroup grouping
) {
	      mu0_sint32_t   mask = LC_ALL_MASK;
	const mu0_tchar8_t * name = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	switch (grouping)
	{
		case mu0_localegroup_collator :
		{
			mask = LC_COLLATE_MASK;
		}
		break;
		case mu0_localegroup_monetary :
		{
			mask = LC_MONETARY_MASK;
		}
		break;
		case mu0_localegroup_numerics :
		{
			mask = LC_NUMERIC_MASK;
		}
		break;
		case mu0_localegroup_datetime :
		{
			mask = LC_TIME_MASK;
		}
		break;
		default:
		{ /***/ }
		break;
	}
	if (__mu0_not_nullptr__(name)) {
		return __mu0_i18nlocale_new__(mask, name, __mu0_nullptr__);
	}
	return __mu0_nullptr__;
}

mu0_sint32_t mu0_locale_global(
	  const      mu0_tchar8_t *  language
	, const      mu0_tchar8_t *  territory
	, const      mu0_tchar8_t *  modifier  __mu0_nullable__
	, const enum mu0_localegroup grouping
) {
	      mu0_sint32_t   category = LC_ALL;
	const mu0_tchar8_t * name     = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	switch (grouping)
	{
		case mu0_localegroup_collator :
		{
			category = LC_COLLATE;
		}
		break;
		case mu0_localegroup_monetary :
		{
			category = LC_MONETARY;
		}
		break;
		case mu0_localegroup_numerics :
		{
			category = LC_NUMERIC;
		}
		break;
		case mu0_localegroup_datetime :
		{
			category = LC_TIME;
		}
		break;
		default:
		{ /***/ }
		break;
	}
	if (__mu0_not_nullptr__(name)) {
		if (__mu0_not_nullptr__(__mu0_i18nlocale_set__(category, name))) {
			return 0;
		}
	}
	return -1;
}

const mu0_tchar8_t * mu0_locale_interface (
	  mu0_tchar8_t language[3]  __mu0_nullable__
	, mu0_tchar8_t territory[3] __mu0_nullable__
) {
	return __mu0_i18nlocale_user__(language, territory);
}

const mu0_tchar8_t * mu0_locale_identifier(
	  const enum mu0_localegroup grouping
	, const      mu0_locale_t *  locale   __mu0_nullable__
) {
	mu0_sint32_t category = LC_ALL;
	switch (grouping)
	{
		case mu0_localegroup_collator :
		{
			category = LC_COLLATE;
		}
		break;
		case mu0_localegroup_monetary :
		{
			category = LC_MONETARY;
		}
		break;
		case mu0_localegroup_numerics :
		{
			category = LC_NUMERIC;
		}
		break;
		case mu0_localegroup_datetime :
		{
			category = LC_TIME;
		}
		break;
		default:
		{ /***/ }
		break;
	}
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