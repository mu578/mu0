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

__mu0_static_inline__
const mu0_string8_t mu0_locale_name(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier
) {
	__mu0_static__ mu0_tchar8_t s_name[48];
	mu0_bool_t    have_name = mu0_false;
	mu0_uint64_t  k, l, p   = 0;

	//#! XPG syntax: language[_territory[.codeset]][@modifier]
	memset(s_name, 0, __mu0_sizeof__(s_name));
	if (language != mu0_nullptr) {
		k = strlen(language);
		if (k > 0) {
			l  = k;
			memcpy(s_name + p, language, l);
			p += l;
			if (territory != mu0_nullptr) {
				k  = strlen(territory);
				if (k > 0) {
					l  = __mu0_sizeof__(mu0_tchar8_t);
					memcpy(s_name + p, "_", mu0_min(6, l));
					p += l;
					l  = k;
					memcpy(s_name + p, territory, mu0_min(16, l));
					p += l;
					l  =  __mu0_sizeof__(mu0_tchar8_t) * 6;
					memcpy(s_name + p, ".UTF-8", l);
					have_name = mu0_true;
				}
				if (modifier != mu0_nullptr) {
					k  = strlen(modifier);
					if (k > 0) {
						p += l;
						l  = __mu0_sizeof__(mu0_tchar8_t);
						memcpy(s_name + p, "@", l);
						p += l;
						l  = k ;
						memcpy(s_name + p, modifier, mu0_min(16, l));
					}
				}
			}
		}
	}
	return (have_name == mu0_true) ? s_name : mu0_nullptr;
}

#	undef  _MU0_LOCALE_T
#	undef  _MU0_LOCALE_CREATE
#	undef  _MU0_LOCALE_DELETE
#	undef  _MU0_LOCALE_MASK_ALL
#	undef  _MU0_LOCALE_MASK_COLLATE
#	undef  _MU0_LOCALE_STRCOLL
#	undef  _MU0_LOCALE_STRCOLL_L

#	if MU0_HAVE_WINDOWS && !(defined(__MINGW32__) || defined(__MINGW64__))
#	define _MU0_LOCALE_T                           _locale_t
#	define _MU0_LOCALE_GLOBAL(category, name)      setlocale(category, name)
#	define _MU0_LOCALE_CREATE(category, name)      _create_locale(category, name)
#	define _MU0_LOCALE_DELETE(locale)              _free_locale(mu0_cast(_locale_t, locale))
#	define _MU0_LOCALE_MASK_ALL                    LC_ALL
#	define _MU0_LOCALE_MASK_COLLATE                LC_COLLATE
#	define _MU0_LOCALE_STRCOLL(lhs, rhs)           mu0_sint32(strcoll(lhs, rhs))
#	define _MU0_LOCALE_STRCOLL_L(lhs, rhs, locale) mu0_sint32(_strcoll_l(lhs, rhs, mu0_cast(_locale_t, locale)))
#	elif   MU0_HAVE_POSIX1_2001
#	define _MU0_LOCALE_T                           locale_t
#	define _MU0_LOCALE_GLOBAL(category, name)      setlocale(category, name)
#	define _MU0_LOCALE_CREATE(category, name)      newlocale(category, name, mu0_nullptr)
#	define _MU0_LOCALE_DELETE(locale)              freelocale(mu0_cast(locale_t, locale))
#	define _MU0_LOCALE_MASK_ALL                    LC_ALL_MASK
#	define _MU0_LOCALE_MASK_COLLATE                LC_COLLATE_MASK
#	define _MU0_LOCALE_STRCOLL(lhs, rhs)           mu0_sint32(strcoll(lhs, rhs))
#	define _MU0_LOCALE_STRCOLL_L(lhs, rhs, locale) mu0_sint32(strcoll_l(lhs, rhs, mu0_cast(locale_t, locale)))
#	else
#	error "mu0_locale.c"
# endif

mu0_locale_t mu0_locale_create(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier
	, const mu0_bool_t    collator
) {
	const mu0_sint32_t category = ((collator == mu0_true)
		? _MU0_LOCALE_MASK_COLLATE
		: _MU0_LOCALE_MASK_ALL
	);
	const mu0_string8_t name    = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	if (mu0_not_nullptr(name)) {
		return _MU0_LOCALE_CREATE(category, name);
	}
	return mu0_nullptr;
}

mu0_sint32_t mu0_locale_global(
	  const mu0_string8_t language
	, const mu0_string8_t territory
	, const mu0_string8_t modifier
	, const mu0_bool_t    collator
) {
	const mu0_sint32_t category = ((collator == mu0_true)
		? _MU0_LOCALE_MASK_COLLATE
		: _MU0_LOCALE_MASK_ALL
	);
	const mu0_string8_t name    = mu0_locale_name(
		  language
		, territory
		, modifier
	);
	if (mu0_not_nullptr(name)) {
		if (mu0_not_nullptr(_MU0_LOCALE_GLOBAL(category, name))) {
			return 0;
		}
	}
	return -1;
}

mu0_sint32_t mu0_locale_delete(mu0_locale_t locale)
{
	if (locale != mu0_nullptr) {
		_MU0_LOCALE_DELETE(locale);
		return 0;
	}
	return -1;
}

mu0_sint32_t mu0_locale_compare(
	  const mu0_string8_t lhs
	, const mu0_string8_t rhs
	, const mu0_locale_t  locale
) {
	if (locale != mu0_nullptr) {
		return _MU0_LOCALE_STRCOLL_L(lhs, rhs, locale);
	}
	return _MU0_LOCALE_STRCOLL(lhs, rhs);
}

/* EOF */