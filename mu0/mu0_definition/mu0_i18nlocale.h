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

#	include <locale.h>
#	include <string.h>

#	undef  __mu0_strcoll__
#	undef  __mu0_strcoll_l__
#	undef  __mu0_strncoll__
#	undef  __mu0_strncoll_l__
#	undef  __mu0_strcmp__
#	undef  __mu0_strncmp__

#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1
#		define __mu0_strcoll__(__lhs, __rhs)                 strcoll(__lhs, __rhs)
#		define __mu0_strcoll_l__(__lhs, __rhs, __locale)     _strcoll_l(__lhs, __rhs, __locale)
#		define __mu0_strncoll__(__lhs, __rhs, n)             _strncoll(__lhs, __rhs, n)
#		define __mu0_strncoll_l__(__lhs, __rhs, n, __locale) _strncoll_l(__lhs, __rhs, n, __locale)
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
#		define __mu0_strcoll__(__lhs, __rhs)                strcoll(__lhs, __rhs)
#		define __mu0_strcoll_l__(__lhs, __rhs, __locale)    strcoll_l(__lhs, __rhs, __locale)

#		include <alloca.h>
		__mu0_static_inline__
		int ___mu0_strncoll_l___(const char * __lhs, const char * __rhs, size_t n, locale_t __locale)
		{
			char * a, * b;
			if (__lhs[n + 1] != '\0') {
				a = alloca(n + 1);
				memcpy(a, __lhs, n);
				a[n] = '\0';
			} else {
				a = __mu0_cast__(char *, __lhs);
			}
			if (__rhs[n + 1] != '\0') {
				b = alloca(n + 1);
				memcpy(b, __rhs, n);
				b[n] = '\0';
			} else {
				b = __mu0_cast__(char *, __rhs);
			}
			return strcoll_l(a, b, __locale);
		}

		__mu0_static_inline__
		int ___mu0_strncoll___(const char * __lhs, const char * __rhs, size_t n)
		{
			char * a, * b;
			if (__lhs[n + 1] != '\0') {
				a = alloca(n + 1);
				memcpy(a, __lhs, n);
				a[n] = '\0';
			} else {
				a = __mu0_cast__(char *, __lhs);
			}
			if (__rhs[n + 1] != '\0') {
				b = alloca(n + 1);
				memcpy(b, __rhs, n);
				b[n] = '\0';
			} else {
				b = __mu0_cast__(char *, __rhs);
			}
			return strcoll(a, b);
		}

#		define __mu0_strncoll__(__lhs, __rhs, n)           ___mu0_strncoll_l___(__lhs, __rhs, n)
#		define __mu0_strncoll_l__(__lhs, __rhs, n, __locale) ___mu0_strncoll___(__lhs, __rhs, n, __locale)
		typedef locale_t __mu0_i18nlocale_t__;
#	else
		typedef void * __mu0_i18nlocale_t__;
#		define __mu0_strcmp__(__lhs, __rhs)                strcmp(__lhs, __rhs)
#		define __mu0_strncmp__(__lhs, __rhs, n)            strncmp(__lhs, __rhs, n)
#	endif

__mu0_static_inline__
__mu0_i18nlocale_t__ __mu0_i18nlocale_new__(const int __mask, const char * __locale, __mu0_i18nlocale_t__ __base)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	__mu0_unused__(__mask);
	__mu0_unused__(__base);
	return _create_locale(LC_ALL, __locale);
#	elif MU0_HAVE_POSIX1_2001
	return newlocale(__mask, __locale, __base);
#	else
	__mu0_unused__(__mask);
	__mu0_unused__(__locale);
	__mu0_unused__(__base);
	return __mu0_nullptr__;
#	endif
}

__mu0_static_inline__
__mu0_i18nlocale_t__ __mu0_i18nlocale_use__(__mu0_i18nlocale_t__ __locale)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	_locale_t current = _get_current_locale();
	if (__mu0_is_nullptr__(__locale)) {
		return current;
	}
	_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
	setlocale(LC_ALL, __locale->locinfo->lc_category[LC_ALL].locale);
	return current;
#	elif MU0_HAVE_POSIX1_2001
	return uselocale(__locale);
#	else
	__mu0_unused__(__locale);
	return __mu0_nullptr__;
#	endif
}

__mu0_static_inline__
const char * __mu0_i18nlocale_set__(const int __category, const char * __locale)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	__mu0_unused__(__category);
	return setlocale(LC_ALL, __locale);
#	elif MU0_HAVE_POSIX1_2001
	return setlocale(__category, __locale);
#	else
	__mu0_unused__(__category);
	__mu0_unused__(__locale);
	return "en_EN.UTF-8";
#	endif
}

__mu0_static_inline__
const int __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ __locale)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	if (__mu0_not_nullptr__(__locale)) {
		_free_locale(__locale);
		return 0;
	}
	return -1;
#	elif MU0_HAVE_POSIX1_2001
	return freelocale(__locale);
#	else
	__mu0_unused__(__locale);
	return 0;
#	endif
}

__mu0_static_inline__
const int __mu0_i18nlocale_collate__(
	  const char *         __lhs
	, const char *         __rhs
	, __mu0_i18nlocale_t__ __locale __mu0_nullable__
) {
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	const int r = (__mu0_not_nullptr__(__locale)
		? __mu0_strcoll_l__(__lhs, __rhs, __locale)
		: __mu0_strcoll__  (__lhs, __rhs)
	);
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
#	elif MU0_HAVE_POSIX1_2001
	const int r = (__mu0_not_nullptr__(__locale)
		? __mu0_strcoll_l__(__lhs, __rhs, __locale)
		: __mu0_strcoll__  (__lhs, __rhs)
	);
#	else
	__mu0_unused__(__locale);
	const int r = __mu0_strcmp__(__lhs, __rhs);
#	endif
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
}

#endif /* !MU0_I18NLOCALE_H */

/* EOF */