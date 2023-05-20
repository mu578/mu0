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

#include <mu0/mu0_definition/mu0_attribute.h>
#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_I18NLOCALE_H
#define MU0_I18NLOCALE_H 1

#	undef  MU0_HAVE_I18NLOCALE
#	undef  __mu0_alloca__
#	undef  __mu0_memcpy__
#	undef  __mu0_strcoll__
#	undef  __mu0_strcoll_l__
#	undef  __mu0_strncoll__
#	undef  __mu0_strncoll_l__
#	undef  __mu0_strcmp__
#	undef  __mu0_strncmp__
#	define MU0_HAVE_I18NLOCALE 0

#	if MU0_HAVE_POSIX1_2001 && !MU0_HAVE_ANDROID && !MU0_HAVE_LINUX && !MU0_HAVE_NUTTX
#	include <xlocale.h>
#	endif
#	if MU0_HAVE_POSIX1_2001
#	include <langinfo.h>
#	endif
#	include <locale.h>
#	include <string.h>

#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1
		typedef _locale_t __mu0_i18nlocale_t__;
#		define __mu0_strncoll_l__(__lhs, __rhs, __n, __locale)  _strncoll_l(__lhs, __rhs, __n, __locale)
#		define __mu0_strncoll__(__lhs, __rhs, __n)              _strncoll  (__lhs, __rhs, __n)
#		define __mu0_strcoll_l__(__lhs, __rhs, __locale)        _strcoll_l (__lhs, __rhs, __locale)
#		define __mu0_strcoll__(__lhs, __rhs)                    strcoll    (__lhs, __rhs)
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
		typedef locale_t __mu0_i18nlocale_t__;
#		define __mu0_strcoll_l__(__lhs, __rhs, __locale)       strcoll_l(__lhs, __rhs, __locale)
#		define __mu0_strcoll__(__lhs, __rhs)                   strcoll  (__lhs, __rhs)

#		include <alloca.h>
#		define __mu0_alloca__ alloca
#		define __mu0_memcpy__ memcpy

		__mu0_static_inline__
		const ___mu0_sint4_t___ ___mu0_strncoll_l___(
			  const ___mu0_tint1_t___ * __lhs
			, const ___mu0_tint1_t___ * __rhs
			, const ___mu0_uint4_t___   __n
			, __mu0_i18nlocale_t__      __locale __mu0_nullable__
		) {
			const ___mu0_uint4_t___ need_a = (__lhs[__n] != '\0') ? 1 : 0;
			const ___mu0_uint4_t___ need_b = (__rhs[__n] != '\0') ? 1 : 0;
			___mu0_tint1_t___ * a, * b;
			if (need_a) {
				a      = __mu0_alloca__(__n + 1);
				__mu0_memcpy__(a, __lhs, __n);
				a[__n] = '\0';
			}
			if (need_b) {
				b      = __mu0_alloca__(__n + 1);
				__mu0_memcpy__(b, __rhs, __n);
				b[__n] = '\0';
			}
			return __mu0_not_nullptr__(__locale)
				? __mu0_strcoll_l__(need_a ? a : __lhs, need_b ? b : __rhs, __locale)
				: __mu0_strcoll__  (need_a ? a : __lhs, need_b ? b : __rhs)
			;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ ___mu0_strncoll___(
			  const ___mu0_tint1_t___ * __lhs
			, const ___mu0_tint1_t___ * __rhs
			, const ___mu0_uint4_t___   __n
		) { return ___mu0_strncoll_l___(__lhs, __rhs, __n, __mu0_nullptr__); }

#		define __mu0_strncoll__(__lhs, __rhs, __n)             ___mu0_strncoll___  (__lhs, __rhs, __n)
#		define __mu0_strncoll_l__(__lhs, __rhs, __n, __locale) ___mu0_strncoll_l___(__lhs, __rhs, __n, __locale)
#	else
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 0
		typedef void * __mu0_i18nlocale_t__;
#		define __mu0_strcmp__(__lhs, __rhs)                    strcmp (__lhs, __rhs)
#		define __mu0_strncmp__(__lhs, __rhs, __n)              strncmp(__lhs, __rhs, __n)
#	endif

__mu0_static_inline__
__mu0_i18nlocale_t__ __mu0_i18nlocale_new__(const ___mu0_sint4_t___ __mask, const ___mu0_tint1_t___ * __locale, __mu0_i18nlocale_t__ __base)
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
const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	__mu0_unused__(__category);
	if (__mu0_is_nullptr__(__locale)) {
		return setlocale(LC_ALL, __mu0_nullptr__);
	}
	return __locale->locinfo->lc_category[LC_ALL].locale;
#	elif MU0_HAVE_POSIX1_2001 && !MU0_HAVE_ANDROID && !MU0_HAVE_LINUX && !MU0_HAVE_NUTTX
	if (__mu0_is_nullptr__(__locale)) {
		return setlocale(__category, __mu0_nullptr__);
	}
	return querylocale((__category == LC_ALL ? LC_ALL_MASK : LC_COLLATE_MASK), __locale);
#	elif MU0_HAVE_POSIX1_2001
	if (__mu0_is_nullptr__(__locale)) {
		return setlocale(__category, __mu0_nullptr__);
	}
	return nl_langinfo_l(_NL_LOCALE_NAME(__category == LC_ALL ? LC_ALL : LC_COLLATE), __locale);
#	else
	__mu0_unused__(__category);
	__mu0_unused__(__locale);
	return "en_EN.UTF-8";
#	endif
}

__mu0_static_inline__
const ___mu0_tint1_t___ * __mu0_i18nlocale_set__(const ___mu0_sint4_t___ __category, const ___mu0_tint1_t___ * __locale)
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
const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ __locale)
{
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	if (__mu0_not_nullptr__(__locale)) {
		_free_locale(__locale);
		return 0;
	}
	return -1;
#	elif MU0_HAVE_POSIX1_2001 && !MU0_HAVE_ANDROID && !MU0_HAVE_LINUX && !MU0_HAVE_NUTTX
	return freelocale(__locale);
#	elif MU0_HAVE_POSIX1_2001
	freelocale(__locale);
	return 0;
#	else
	__mu0_unused__(__locale);
	return 0;
#	endif
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18nlocale_compare__(
	  const ___mu0_tint1_t___ * __lhs
	, const ___mu0_tint1_t___ * __rhs
	, __mu0_i18nlocale_t__      __locale __mu0_nullable__
) {
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
		? __mu0_strcoll_l__(__lhs, __rhs, __locale)
		: __mu0_strcoll__  (__lhs, __rhs)
	);
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
#	elif MU0_HAVE_POSIX1_2001
	const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
		? __mu0_strcoll_l__(__lhs, __rhs, __locale)
		: __mu0_strcoll__  (__lhs, __rhs)
	);
#	else
	__mu0_unused__(__locale);
	const ___mu0_sint4_t___ r = __mu0_strcmp__(__lhs, __rhs);
#	endif
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18nlocale_compare_n__(
	  const ___mu0_tint1_t___ * __lhs
	, const ___mu0_tint1_t___ * __rhs
	, const ___mu0_uint4_t___   __n
	, __mu0_i18nlocale_t__      __locale __mu0_nullable__
) {
#	if   MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
	const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
		? __mu0_strncoll_l__(__lhs, __rhs, __n, __locale)
		: __mu0_strncoll__  (__lhs, __rhs, __n)
	);
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
#	elif MU0_HAVE_POSIX1_2001
	const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
		? __mu0_strncoll_l__(__lhs, __rhs, __n, __locale)
		: __mu0_strncoll__  (__lhs, __rhs, __n)
	);
#	else
	__mu0_unused__(__locale);
	const ___mu0_sint4_t___ r = __mu0_strncmp__(__lhs, __rhs, __n);
#	endif
	return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
}

#endif /* !MU0_I18NLOCALE_H */

/* EOF */