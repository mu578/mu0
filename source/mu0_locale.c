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

#	if !MU0_HAVE_WINDOWS && !MU0_HAVE_ANDROID
#		include <xlocale.h>
#	endif

#include <locale.h>
#include <string.h>

#	undef  __mu0_memset__
#	undef  __mu0_memcpy__
#	undef  __mu0_memmove__
#	undef  __mu0_strlen__
#	undef  __mu0_strchr__

#	undef  MU0_HAVE_LOCALE
#	undef  __mu0_locale_t__ 
#	undef  __mu0_setlocale__
#	undef  __mu0_newlocale__
#	undef  __mu0_freelocale__
#	undef  __MU0_LOCALE_CATEGORY_ALL__ 
#	undef  __MU0_LOCALE_CATEGORY_COLLATE__
#	undef  __MU0_LOCALE_CATEGORY_CTYPE__
#	undef  __MU0_LOCALE_CATEGORY_MESSAGES__
#	undef  __MU0_LOCALE_CATEGORY_MONETARY__
#	undef  __MU0_LOCALE_CATEGORY_NUMERIC__
#	undef  __MU0_LOCALE_CATEGORY_TIME__
#	undef  __MU0_LOCALE_CATEGORY_MASK_ALL__
#	undef  __MU0_LOCALE_CATEGORY_MASK_COLLATE__
#	undef  __MU0_LOCALE_CATEGORY_MASK_CTYPE__
#	undef  __MU0_LOCALE_CATEGORY_MASK_MESSAGES__
#	undef  __MU0_LOCALE_CATEGORY_MASK_MONETARY__
#	undef  __MU0_LOCALE_CATEGORY_MASK_NUMERIC__
#	undef  __MU0_LOCALE_CATEGORY_MASK_TIME__ 
#	define MU0_HAVE_LOCALE 0

#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_LOCALE
#		define MU0_HAVE_LOCALE 1
#		define __mu0_locale_t__                      _locale_t
#		define __mu0_setlocale__(category, name)     setlocale(category, name)
#		define __mu0_newlocale__(category, name)     _create_locale(category, name)
#		define __mu0_freelocale__(locale)            _free_locale(((__mu0_locale_t__)locale))
#		define __MU0_LOCALE_CATEGORY_ALL__           LC_ALL
#		define __MU0_LOCALE_CATEGORY_COLLATE__       LC_COLLATE
#		define __MU0_LOCALE_CATEGORY_CTYPE__         LC_CTYPE
#		define __MU0_LOCALE_CATEGORY_MESSAGES__      LC_MESSAGES
#		define __MU0_LOCALE_CATEGORY_MONETARY__      LC_MONETARY
#		define __MU0_LOCALE_CATEGORY_NUMERIC__       LC_NUMERIC
#		define __MU0_LOCALE_CATEGORY_TIME__          LC_TIME
#		define __MU0_LOCALE_CATEGORY_MASK_ALL__      LC_ALL
#		define __MU0_LOCALE_CATEGORY_MASK_COLLATE__  LC_COLLATE
#		define __MU0_LOCALE_CATEGORY_MASK_CTYPE__    LC_CTYPE
#		define __MU0_LOCALE_CATEGORY_MASK_MESSAGES__ LC_MESSAGES
#		define __MU0_LOCALE_CATEGORY_MASK_MONETARY__ LC_MONETARY
#		define __MU0_LOCALE_CATEGORY_MASK_NUMERIC__  LC_NUMERIC
#		define __MU0_LOCALE_CATEGORY_MASK_TIME__     LC_TIME
#	elif MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_LOCALE
#		define MU0_HAVE_LOCALE 1
#		define __mu0_locale_t__                      locale_t
#		define __mu0_setlocale__(category, name)     setlocale(category, name)
#		define __mu0_newlocale__(category, name)     newlocale(category, name, NULL)
#		define __mu0_freelocale__(locale)            freelocale(((__mu0_locale_t__)locale))
#		define __MU0_LOCALE_CATEGORY_ALL__           LC_ALL
#		define __MU0_LOCALE_CATEGORY_COLLATE__       LC_COLLATE
#		define __MU0_LOCALE_CATEGORY_CTYPE__         LC_CTYPE
#		define __MU0_LOCALE_CATEGORY_MESSAGES__      LC_MESSAGES
#		define __MU0_LOCALE_CATEGORY_MONETARY__      LC_MONETARY
#		define __MU0_LOCALE_CATEGORY_NUMERIC__       LC_NUMERIC
#		define __MU0_LOCALE_CATEGORY_TIME__          LC_TIME
#		define __MU0_LOCALE_CATEGORY_MASK_ALL__      LC_ALL_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_COLLATE__  LC_COLLATE_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_CTYPE__    LC_CTYPE_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_MESSAGES__ LC_MESSAGES_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_MONETARY__ LC_MONETARY_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_NUMERIC__  LC_NUMERIC_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_TIME__     LC_TIME_MASK
#	endif

#	if MU0_HAVE_LOCALE
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		define __mu0_strcoll__(lhs, rhs)            strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale)  _strcoll_l(lhs, rhs, ((__mu0_locale_t__)locale))
#		define __mu0_locale_cmp__(lhs, rhs, locale) ((locale) \
			? __mu0_strcoll_l__(lhs, rhs, locale) \
			: __mu0_strcoll__(lhs, rhs) \
		)
#	elif MU0_HAVE_POSIX1_2001
#		define __mu0_strcoll__(lhs, rhs)            strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale)  strcoll_l(lhs, rhs, ((__mu0_locale_t__)locale))
#		define __mu0_locale_cmp__(lhs, rhs, locale) ((locale) \
			? __mu0_strcoll_l__(lhs, rhs, locale) \
			: __mu0_strcoll__(lhs, rhs) \
		)
#	endif
#	endif

#	if MU0_HAVE_LOCALE
#		define __mu0_memset__  memset
#		define __mu0_memcpy__  memcpy
#		define __mu0_memmove__ memmove
#		define __mu0_strlen__  strlen
#		define __mu0_strchr__  strchr
#	endif

__mu0_static_inline__
const mu0_string8_t mu0_locale_name(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier  __mu0_nullable__
) {
#	if MU0_HAVE_LOCALE
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
#	else
	mu0_unused(language);
	mu0_unused(territory);
	mu0_unused(modifier);

	return mu0_nullptr;
#	endif
}

mu0_locale_t mu0_locale_create(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier  __mu0_nullable__
	, const mu0_bool_t    collator
) {
#	if MU0_HAVE_LOCALE
	const mu0_sint32_t category = ((collator == mu0_true)
		? __MU0_LOCALE_CATEGORY_MASK_COLLATE__
		: __MU0_LOCALE_CATEGORY_MASK_ALL__
	);
	const mu0_string8_t name    = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	if (mu0_not_nullptr(name)) {
		return __mu0_newlocale__(category, name);
	}
#	else
	mu0_unused(language);
	mu0_unused(territory);
	mu0_unused(modifier);
	mu0_unused(collator);
#	endif
	return mu0_nullptr;
}

mu0_sint32_t mu0_locale_global(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier  __mu0_nullable__
	, const mu0_bool_t    collator
) {
#	if MU0_HAVE_LOCALE
	const mu0_sint32_t category = ((collator == mu0_true)
		? __MU0_LOCALE_CATEGORY_COLLATE__
		: __MU0_LOCALE_CATEGORY_ALL__
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
#	else
	mu0_unused(language);
	mu0_unused(territory);
	mu0_unused(modifier);
	mu0_unused(collator);
#	endif
	return -1;
}

mu0_sint32_t mu0_locale_delete(mu0_locale_t locale)
{
#	if MU0_HAVE_LOCALE
	if (mu0_not_nullptr(locale)) {
		__mu0_freelocale__(locale);
		return 0;
	}
#	else
	mu0_unused(locale);
#	endif
	return -1;
}

mu0_sint32_t mu0_locale_compare(
	  const mu0_string8_t lhs
	, const mu0_string8_t rhs
	, const mu0_locale_t  locale __mu0_nullable__
) {
	const mu0_sint32_t r = __mu0_locale_cmp__(lhs, rhs, locale);
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
}

/* EOF */