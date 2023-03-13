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

// mu0_i18nlocale.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_platform.h>
#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_I18NLOCALE_H
#define MU0_I18NLOCALE_H 1

#	undef  MU0_HAVE_I18NLOCALE
#	define MU0_HAVE_I18NLOCALE 0

#	if !MU0_HAVE_WINDOWS && !MU0_HAVE_ANDROID
#		include <xlocale.h>
#	endif

#include <locale.h>
#include <string.h>

#	undef  __mu0_strcoll__
#	undef  __mu0_strcoll_l__
#	undef  __mu0_strcmp__

#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1
#		define __mu0_strcoll__(lhs, rhs)            strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale)  _strcoll_l(lhs, rhs, locale)
#		define __mu0_strcmp__(lhs, rhs)             strcmp(lhs, rhs)
		typedef _locale_t __mu0_i18nlocale_t__;
#		define LC_ALL_MASK      0
#		define LC_COLLATE_MASK  0
#		define LC_CTYPE_MASK    0
#		define LC_MESSAGES_MASK 0
#		define LC_MONETARY_MASK 0
#		define LC_NUMERIC_MASK  0
#		define LC_TIME_MASK     0
#	elif MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1
#		define __mu0_strcoll__(lhs, rhs)            strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale)  strcoll_l(lhs, rhs, locale)
#		define __mu0_strcmp__(lhs, rhs)             strcmp(lhs, rhs)
		typedef locale_t __mu0_i18nlocale_t__;
#	else
		typedef void * __mu0_i18nlocale_t__;
#		define __mu0_strcmp__(lhs, rhs)             strcmp(lhs, rhs)
#	endif

__mu0_static_inline__
__mu0_i18nlocale_t__ __mu0_i18nlocale_new__(const int mask, const char * locale, __mu0_i18nlocale_t__ base)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	__mu0_unused__(mask);
	__mu0_unused__(base);
	return _create_locale(LC_ALL, locale);
#	elif MU0_HAVE_POSIX1_2001
	return newlocale(mask, locale, base);
#	else
	__mu0_unused__(mask);
	__mu0_unused__(locale);
	__mu0_unused__(base);
	return __mu0_nullptr__;
#	endif
}

__mu0_static_inline__
__mu0_i18nlocale_t__ __mu0_i18nlocale_use__(__mu0_i18nlocale_t__ loc)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	_locale_t current = _get_current_locale();
	if (__mu0_is_nullptr__(loc)) {
		return current;
	}
	_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
	setlocale(LC_ALL, loc->locinfo->lc_category[LC_ALL].locale);
	return current;
#	elif MU0_HAVE_POSIX1_2001
	return uselocale(loc);
#	else
	__mu0_unused__(loc);
	return __mu0_nullptr__;
#	endif
}

__mu0_static_inline__
const char * __mu0_i18nlocale_set__(const int category, const char * locale)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	__mu0_unused__(category);
	return setlocale(LC_ALL, locale);
#	elif MU0_HAVE_POSIX1_2001
	return setlocale(category, locale);
#	else
	__mu0_unused__(category);
	__mu0_unused__(locale);
	return "en_EN.UTF-8";
#	endif
}

__mu0_static_inline__
const int __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ loc)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	if (__mu0_not_nullptr__(loc)) {
		_free_locale(loc);
		return 0;
	}
	return -1;
#	elif MU0_HAVE_POSIX1_2001
	return freelocale(loc);
#	else
	__mu0_unused__(loc);
	return 0;
#	endif
}

__mu0_static_inline__
const int __mu0_i18nlocale_collate__(
	  const char *         lhs
	, const char *         rhs
	, __mu0_i18nlocale_t__ loc __mu0_nullable__
) {
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	const int r = (__mu0_not_nullptr__(loc)
		? __mu0_strcoll_l__(lhs, rhs, loc)
		: __mu0_strcoll__  (lhs, rhs)
	);
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
#	elif MU0_HAVE_POSIX1_2001
	const int r = (__mu0_not_nullptr__(loc)
		? __mu0_strcoll_l__(lhs, rhs, loc)
		: __mu0_strcoll__  (lhs, rhs)
	);
#	else
	__mu0_unused__(loc);
	const int r = __mu0_strcmp__(lhs, rhs);
#	endif
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
}

#endif /* !MU0_I18NLOCALE_H */

/* EOF */