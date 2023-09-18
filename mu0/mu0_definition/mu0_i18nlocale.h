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
#include <mu0/mu0_definition/mu0_numeral.h>
#include <mu0/mu0_definition/mu0_memory.h>

#ifndef MU0_I18NLOCALE_H
#define MU0_I18NLOCALE_H 1

#	undef  MU0_HAVE_I18NLOCALE
#	define MU0_HAVE_I18NLOCALE 0

#	if MU0_HAVE_POSIX1_2001 \
		&& !MU0_HAVE_ANDROID \
		&& !MU0_HAVE_LINUX   \
		&& !MU0_HAVE_NUTTX   \
		&& !MU0_HAVE_MINGW
#	include <xlocale.h>
#	endif
#	if MU0_HAVE_POSIX1_2001
#	include <langinfo.h>
#	include <alloca.h>
#	endif
#	if MU0_HAVE_POSIX1_2001 || MU0_HAVE_WINDOWS
#	include <locale.h>
#	if MU0_HAVE_WINDOWS
#		define LC_MESSAGES      LC_ALL
#		define LC_ALL_MASK      0
#		define LC_COLLATE_MASK  0
#		define LC_CTYPE_MASK    0
#		define LC_MESSAGES_MASK 0
#		define LC_MONETARY_MASK 0
#		define LC_NUMERIC_MASK  0
#		define LC_TIME_MASK     0
#	endif
#	endif
#	if !MU0_HAVE_WINDOWS
#	include <stdlib.h>
#	endif
#	include <ctype.h>

__mu0_static__ struct
{
	const ___mu0_tint1_t___ * u_language;
	const ___mu0_tint1_t___ * u_territory;
} const __mu0_i18nlocale_default__[] = {
	  { "af" , "ZA" } , { "am" , "ET" } , { "be" , "BY" } , { "bg" , "BG" } , { "ca" , "ES" } , { "cs" , "CZ" }
	, { "da" , "DK" } , { "de" , "DE" } , { "de" , "AT" } , { "de" , "CH" } , { "el" , "GR" } , { "en" , "GB" }
	, { "en" , "US" } , { "en" , "AU" } , { "en" , "CA" } , { "en" , "IE" } , { "en" , "NZ" } , { "en" , "US" }
	, { "es" , "ES" } , { "et" , "EE" } , { "eu" , "ES" } , { "fi" , "FI" } , { "fr" , "FR" } , { "fr" , "BE" }
	, { "fr" , "CA" } , { "fr" , "CH" } , { "he" , "IL" } , { "hr" , "HR" } , { "hu" , "HU" } , { "hy" , "AM" }
	, { "is" , "IS" } , { "it" , "IT" } , { "it" , "CH" } , { "ja" , "JP" } , { "kk" , "KZ" } , { "ko" , "KR" }
	, { "lt" , "LT" } , { "nl" , "NL" } , { "nl" , "BE" } , { "no" , "NO" } , { "pl" , "PL" } , { "pt" , "PT" }
	, { "pt" , "BR" } , { "ro" , "RO" } , { "ru" , "RU" } , { "sk" , "SK" } , { "sl" , "SI" } , { "sr" , "YU" }
	, { "sv" , "SE" } , { "tr" , "TR" } , { "uk" , "UA" } , { "zh" , "CN" } , { "zh" , "TW" } , { "zh" , "HK" }
	, { __mu0_nullptr__ , __mu0_nullptr__ }
};

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18nlocale_find__(
	  const ___mu0_tint1_t___   __language            [ 2]
	, const ___mu0_tint1_t___   __territory           [ 2]
	,       ___mu0_tint1_t___   __identifier_language [12]
	,       ___mu0_tint1_t___   __identifier_territory[12] __mu0_nullable__
) {
	___mu0_sint4_t___   have_language  = 0;
	___mu0_sint4_t___   have_territory = 0;
	___mu0_tint1_t___   id[24]         = { 0 };
	___mu0_tint1_t___ * loc;
	___mu0_uint4_t___   i;
	__mu0_memset__(__identifier_language, 0, 12);
	if (__mu0_not_nullptr__(__identifier_territory)) {
		__mu0_memset__(__identifier_territory, 0, 12);
	}
	//#! Saving current locale.
	if (__mu0_not_nullptr__((loc = setlocale(LC_MESSAGES, "")))) {
		__mu0_memcpy__(id, loc, __mu0_sizeof__(id));
		//#! Building locale identifier for the given pair.
		__identifier_language[0] = __language[0];
		__identifier_language[1] = __language[1];
		__identifier_language[2] = '_';
		__identifier_language[3] = __territory[0];
		__identifier_language[4] = __territory[1];
		__mu0_memcpy__(__identifier_language + 5 , ".UTF-8\0" , 7);
		//#! Testing if pair is a valid locale identifier.
		if (__mu0_not_nullptr__(setlocale(LC_MESSAGES, __identifier_language))) {
			//#! There is no mismatch so filling with same identifier.
			if (__mu0_not_nullptr__(__identifier_territory)) {
				__mu0_memcpy__(__identifier_territory, __identifier_language, 12);
				have_territory = 1;
			}
			have_language = 1;
		}
		if (!have_language) {
			i = 0;
			do {
				if (__mu0_i18nlocale_default__[i].u_language[0] == __language[0] && __mu0_i18nlocale_default__[i].u_language[1] == __language[1]) {
					__identifier_language[0] = __mu0_i18nlocale_default__[i].u_language[0];
					__identifier_language[1] = __mu0_i18nlocale_default__[i].u_language[1];
					__identifier_language[2] = '_';
					__identifier_language[3] = __mu0_i18nlocale_default__[i].u_territory[0];
					__identifier_language[4] = __mu0_i18nlocale_default__[i].u_territory[1];
					__mu0_memcpy__(__identifier_language + 5, ".UTF-8\0", 7);
					have_language = 1;
					break;
				}
				++i;
			} while (__mu0_not_nullptr__(__mu0_i18nlocale_default__[i].u_language));
			if (0 == have_language) {
				have_language = 0;
				if (__mu0_not_nullptr__(setlocale(LC_MESSAGES, __identifier_language))) {
					have_language = 1;
				}
			}
		}
		if (!have_territory) {
			if (__mu0_not_nullptr__(__identifier_territory)) {
				i = 0;
				do {
					if (__mu0_i18nlocale_default__[i].u_territory[0] == __territory[0] && __mu0_i18nlocale_default__[i].u_territory[1] == __territory[1]) {
						__identifier_territory[0] = __mu0_i18nlocale_default__[i].u_language[0];
						__identifier_territory[1] = __mu0_i18nlocale_default__[i].u_language[1];
						__identifier_territory[2] = '_';
						__identifier_territory[3] = __mu0_i18nlocale_default__[i].u_territory[0];
						__identifier_territory[4] = __mu0_i18nlocale_default__[i].u_territory[1];
						__mu0_memcpy__(__identifier_territory + 5, ".UTF-8\0", 7);
						have_territory = 1;
						break;
					}
					++i;
				} while (__mu0_not_nullptr__(__mu0_i18nlocale_default__[i].u_territory));
				if (have_territory) {
					have_territory = 0;
					if (__mu0_not_nullptr__(setlocale(LC_MESSAGES, __identifier_territory))) {
						have_territory = 1;
					}
				}
			}
		}
		//#! Restoring current locale.
		setlocale(LC_MESSAGES, id);
	}
	if (!have_language) {
#		if MU0_HAVE_POSIX1_2001
		__mu0_memcpy__(__identifier_territory, "C.UTF-8\0"    ,  8);
#		else
		__mu0_memcpy__(__identifier_territory, "en_US.UTF-8\0", 12);
#		endif
	}
	if (__mu0_not_nullptr__(__identifier_territory)) {
		if (!have_language || (have_language && !have_territory)) {
			__mu0_memcpy__(__identifier_territory, __identifier_language, 12);
		}
		return have_language && have_territory ? 0 : -1;
	}
	return have_language ? 0 : -1;
}

#	if !MU0_HAVE_I18NLOCALE
#	if MU0_HAVE_WINDOWS
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1

		struct ___mu0_i18nlocale_t___
		{
			___mu0_tint1_t___ u_id[48];
			___mu0_sint4_t___ u_ct;
			_locale_t         u_lc;
		};
		typedef struct ___mu0_i18nlocale_t___ __mu0_i18nlocale_t__;

		__mu0_static_inline__
		__mu0_i18nlocale_t__ * __mu0_i18nlocale_new__(const ___mu0_sint4_t___ __mask, const ___mu0_tint1_t___ * __locale, const __mu0_i18nlocale_t__ * __base __mu0_nullable__)
		{
			__mu0_i18nlocale_t__ * locale = malloc(__mu0_sizeof__(struct ___mu0_i18nlocale_t___));
			___mu0_uint8_t___      len;
			__mu0_unused__(__mask);
			__mu0_unused__(__base);
			if (__mu0_not_nullptr__(locale)) {
				__mu0_memset__(locale, 0, __mu0_sizeof__(struct ___mu0_i18nlocale_t___));
				len                        = __mu0_const_cast__(___mu0_uint8_t___, __mu0_memlen__(__locale));
				__mu0_memcpy__(locale->u_id, __locale, len);
				locale->u_ct               = LC_ALL;
				locale->u_lc               = _create_locale(locale->u_ct, __locale);
				if (__mu0_is_nullptr__(locale->u_lc)) {
					free(locale);
					locale                  = __mu0_nullptr__;
				}
			}
			return locale;
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ * __mu0_i18nlocale_usecopy__(const __mu0_i18nlocale_t__ * __locale)
		{
			__mu0_i18nlocale_t__ * locale = __mu0_i18nlocale_new__(
				  LC_ALL_MASK
				, setlocale(LC_ALL, "")
				, __mu0_nullptr__
			);
			if (__mu0_not_nullptr__(__locale)) {
				_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
				setlocale(LC_ALL, __locale->u_id);
			}
			return locale;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_exists__(const ___mu0_tint1_t___ * __id)
		{
			const ___mu0_tint1_t___ * id = setlocale(LC_MESSAGES, "");
			_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
			if (__mu0_not_nullptr__(setlocale(LC_MESSAGES, __id))) {
				setlocale(LC_MESSAGES, id);
				return 0;
			}
			setlocale(LC_MESSAGES, id);
			return -1;
		}

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, const __mu0_i18nlocale_t__ * __locale)
		{
			__mu0_unused__(__category);
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(LC_ALL, "");
			}
			return __locale->u_id;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __identifier_language [12]
			, ___mu0_tint1_t___ __identifier_territory[12] __mu0_nullable__
		) {
			__mu0_static__ ___mu0_tint1_t___ s_id[12];
			WCHAR                            buff[LOCALE_NAME_MAX_LENGTH] = { 0 };
			if (0 != GetUserDefaultLocaleName(buff, LOCALE_NAME_MAX_LENGTH)) {
				__mu0_memset__(s_id, 0, __mu0_sizeof__(s_id));
				WideCharToMultiByte(CP_UTF8, 0, buff, 11, id, s_id, __mu0_nullptr__, __mu0_nullptr__);
				if (s_id[2] == '_' || s_id[2] == '-') {
					_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
					return __mu0_i18nlocale_find__(s_id + 0, s_id + 3, __identifier_language, __identifier_territory);
				}
			}
			return -1;
		}

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_set__(const ___mu0_sint4_t___ __category, const ___mu0_tint1_t___ * __locale)
		{
			__mu0_unused__(__category);
			return setlocale(LC_ALL, __locale);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ * __locale)
		{
			if (__mu0_not_nullptr__(__locale)) {
				if (__mu0_not_nullptr__(__locale->u_lc)) {
					_free_locale(__locale->u_lc);
				}
				free(__locale);
				__locale = __mu0_nullptr__;
				return 0;
			}
			return -1;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const __mu0_i18nlocale_t__ * __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale->u_lc)
						? _strcoll_l (__lhs, __rhs, __locale->u_lc)
						: strcoll    (__lhs, __rhs)
				)
				: strcoll (__lhs, __rhs)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare_n__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, const __mu0_i18nlocale_t__ * __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale->u_lc)
						? _strncoll_l (__lhs, __rhs, __n, __locale->u_lc)
						: _strncoll   (__lhs, __rhs, __n)
				)
				: _strncoll (__lhs, __rhs, __n)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

#	endif
#	endif

#	if !MU0_HAVE_I18NLOCALE
#	if MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1

		struct ___mu0_i18nlocale_t___
		{
			locale_t u_lc;
		};
		typedef struct ___mu0_i18nlocale_t___ __mu0_i18nlocale_t__;

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_strncoll_l__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, const __mu0_i18nlocale_t__ * __locale __mu0_nullable__)
		{
			const ___mu0_uint4_t___ need_a = (__lhs[__n] != '\0') ? 1 : 0;
			const ___mu0_uint4_t___ need_b = (__rhs[__n] != '\0') ? 1 : 0;
			___mu0_tint1_t___ * a, * b;
			if (need_a) {
				a      = alloca(__n + 1);
				__mu0_memcpy__(a, __lhs, __n);
				a[__n] = '\0';
			}
			if (need_b) {
				b      = alloca(__n + 1);
				__mu0_memcpy__(b, __rhs, __n);
				b[__n] = '\0';
			}
			return (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale->u_lc)
						? strcoll_l (need_a ? a : __lhs, need_b ? b : __rhs, __locale->u_lc)
						: strcoll   (need_a ? a : __lhs, need_b ? b : __rhs)
				)
				: strcoll (__lhs, __rhs)
			);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_strncoll__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n)
		{
			return __mu0_strncoll_l__(__lhs, __rhs, __n, __mu0_nullptr__);
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ * __mu0_i18nlocale_new__(const ___mu0_sint4_t___ __mask, const ___mu0_tint1_t___ * __locale, __mu0_i18nlocale_t__ * __base __mu0_nullable__)
		{
			__mu0_i18nlocale_t__ * locale = malloc(__mu0_sizeof__(struct ___mu0_i18nlocale_t___));
			if (__mu0_not_nullptr__(locale)) {
				__mu0_memset__(locale, 0, __mu0_sizeof__(struct ___mu0_i18nlocale_t___));
				locale->u_lc               = newlocale(__mask, __locale, __mu0_not_nullptr__(__base) ? __base->u_lc : __mu0_nullptr__);
				if (__mu0_is_nullptr__(locale->u_lc)) {
					free(locale);
					locale                  = __mu0_nullptr__;
				}
			}
			return locale;
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ * __mu0_i18nlocale_usecopy__(const __mu0_i18nlocale_t__ * __locale)
		{
			__mu0_i18nlocale_t__ * locale = __mu0_nullptr__;
			if (__mu0_not_nullptr__(__locale)) {
				if (__mu0_not_nullptr__(__locale->u_lc)) {
					locale = malloc(__mu0_sizeof__(struct ___mu0_i18nlocale_t___));
					if (__mu0_not_nullptr__(locale)) {
						locale->u_lc         = duplocale(uselocale(__locale->u_lc));
						if (__mu0_is_nullptr__(locale->u_lc)) {
							free(locale);
							locale            = __mu0_nullptr__;
						}
					}
				}
			}
			return locale;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_exists__(const ___mu0_tint1_t___ * __id)
		{
			const ___mu0_tint1_t___ * id = setlocale(LC_MESSAGES, "");
			if (__mu0_not_nullptr__(setlocale(LC_MESSAGES, __id))) {
				setlocale(LC_MESSAGES, id);
				return 0;
			}
			setlocale(LC_MESSAGES, id);
			return -1;
		}

#		if !MU0_HAVE_ANDROID && !MU0_HAVE_LINUX && !MU0_HAVE_NUTTX && !MU0_HAVE_MINGW

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category,  const __mu0_i18nlocale_t__ * __locale)
		{
			___mu0_sint4_t___ mask;
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, "");
			}
			if (__mu0_is_nullptr__(__locale->u_lc)) {
				return setlocale(__category, "");
			}
			switch (__category)
			{
				case LC_CTYPE    :
				{
					mask = LC_CTYPE_MASK;
				}
				break;
				case LC_NUMERIC  :
				{
					mask = LC_NUMERIC_MASK;
				}
				break;
				case LC_TIME     :
				{
					mask = LC_TIME_MASK;
				}
				break;
				case LC_COLLATE  :
				{
					mask = LC_COLLATE_MASK;
				}
				break;
				case LC_MONETARY :
				{
					mask = LC_MONETARY_MASK;
				}
				break;
				case LC_MESSAGES :
				{
					mask = LC_MESSAGES_MASK;
				}
				break;
				default:
				{
					mask = LC_ALL_MASK;
				}
				break;
			}
			return querylocale(mask, __locale->u_lc);
		}

#		elif !MU0_HAVE_MINGW && defined(NL_LOCALE_NAME)

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, const __mu0_i18nlocale_t__ * __locale)
		{
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, "");
			}
			if (__mu0_is_nullptr__(__locale->u_lc)) {
				return setlocale(__category, "");
			}
			return nl_langinfo_l(NL_LOCALE_NAME(__category), __locale->u_lc);
		}

#		elif !MU0_HAVE_MINGW && defined(_NL_LOCALE_NAME)

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, const __mu0_i18nlocale_t__ * __locale)
		{
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, "");
			}
			if (__mu0_is_nullptr__(__locale->u_lc)) {
				return setlocale(__category, "");
			}
			return nl_langinfo_l(_NL_LOCALE_NAME(__category), __locale->u_lc);
		}

#		elif !MU0_HAVE_MINGW && defined(_NL_ITEM) && defined(_NL_ITEM_INDEX)

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, const __mu0_i18nlocale_t__ * __locale)
		{
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, "");
			}
			if (__mu0_is_nullptr__(__locale->u_lc)) {
				return setlocale(__category, "");
			}
			return nl_langinfo_l(_NL_ITEM((__category), _NL_ITEM_INDEX(-1)), __locale->u_lc);
		}

#		else

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, const __mu0_i18nlocale_t__ * __locale)
		{
			__mu0_unused__(__category);
			__mu0_unused__(__locale);
#			if MU0_HAVE_POSIX1_2001
			return "C.UTF-8";
#			else
			return "en_US.UTF-8";
#			endif
		}

#		endif


#	if MU0_HAVE_MACOSX

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __identifier_language [12]
			, ___mu0_tint1_t___ __identifier_territory[12] __mu0_nullable__
		) {
			__mu0_static__ ___mu0_tint1_t___ s_id[12];
			FILE *            fp;
			if ((fp = popen("defaults read .GlobalPreferences AppleLocale" , "r"))) {
				__mu0_memset__(s_id, 0, __mu0_sizeof__(s_id));
				fgets(s_id, 11U, fp);
				pclose(fp);
				if (s_id[2] == '_' || s_id[2] == '-') {
					return __mu0_i18nlocale_find__(s_id + 0, s_id + 3, __identifier_language, __identifier_territory);
				}
			}
			return -1;
		}

#	elif MU0_HAVE_IOS

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __identifier_language [12]
			, ___mu0_tint1_t___ __identifier_territory[12] __mu0_nullable__
		) {
			__mu0_static__ ___mu0_tint1_t___ s_id[12];
			__mu0_memset__(s_id, 0, __mu0_sizeof__(s_id));
			if (CFStringGetCString(CFLocaleGetValue(CFLocaleCopyCurrent(), kCFLocaleIdentifier), s_id, 11U, kCFStringEncodingUTF8)) {
				if (s_id[2] == '_' || s_id[2] == '-') {
					return __mu0_i18nlocale_find__(s_id + 0, s_id + 3, __identifier_language, __identifier_territory);
				}
			}
			return -1;
		}

#	else

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __identifier_language [12]
			, ___mu0_tint1_t___ __identifier_territory[12] __mu0_nullable__
		) {
#			if MU0_HAVE_POSIX1_2001
				__mu0_memcpy__(__identifier_language, "C.UTF-8\0"    ,  8);
#			else
				__mu0_memcpy__(__identifier_language, "en_US.UTF-8\0", 12);
#			endif
			if (__mu0_not_nullptr__(__identifier_territory)) {
				__mu0_memcpy__(__identifier_territory, __identifier_language, 12);
			}
			return 0;
		}

#	endif

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_set__(const ___mu0_sint4_t___ __category, const ___mu0_tint1_t___ * __locale)
		{
			return setlocale(__category, __locale);
		}

#		if !MU0_HAVE_ANDROID && !MU0_HAVE_LINUX && !MU0_HAVE_NUTTX && !MU0_HAVE_MINGW

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ * __locale)
		{
			if (__mu0_not_nullptr__(__locale)) {
				if (__mu0_not_nullptr__(__locale->u_lc)) {
					return freelocale(__locale->u_lc);
				}
			}
			return -1;
		}

#		else

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ * __locale)
		{
			if (__mu0_not_nullptr__(__locale)) {
				if (__mu0_not_nullptr__(__locale->u_lc)) {
					freelocale(__locale->u_lc);
					return 0;
				}
			}
			return -1;
		}

#		endif

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const __mu0_i18nlocale_t__ * __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale->u_lc)
						? strcoll_l (__lhs, __rhs, __locale->u_lc)
						: strcoll   (__lhs, __rhs)
				)
				: strcoll (__lhs, __rhs)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare_n__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, const __mu0_i18nlocale_t__ * __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale->u_lc)
						? __mu0_strncoll_l__ (__lhs, __rhs, __n, __locale)
						: __mu0_strncoll__   (__lhs, __rhs, __n)
				)
				: __mu0_strncoll__ (__lhs, __rhs, __n)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

#	endif
#	endif

#	if !MU0_HAVE_I18NLOCALE

		typedef void * __mu0_i18nlocale_t__;

		__mu0_static_inline__
		__mu0_i18nlocale_t__ * __mu0_i18nlocale_new__(const ___mu0_sint4_t___ __mask, const ___mu0_tint1_t___ * __locale, const __mu0_i18nlocale_t__ * __base __mu0_nullable__)
		{
			__mu0_unused__(__mask);
			__mu0_unused__(__locale);
			__mu0_unused__(__base);
			return __mu0_nullptr__;
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ * __mu0_i18nlocale_usecopy__(const __mu0_i18nlocale_t__ * __locale)
		{
			__mu0_unused__(__locale);
			return __mu0_nullptr__;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_exists__(const ___mu0_tint1_t___ * __id)
		{
			__mu0_unused__(__id);
			return -1;
		}

		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, const __mu0_i18nlocale_t__ * __locale)
		{
			__mu0_unused__(__category);
			__mu0_unused__(__locale);

#			if MU0_HAVE_POSIX1_2001
			return "C.UTF-8";
#			else
			return "en_US.UTF-8";
#			endif
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __identifier_language [12]
			, ___mu0_tint1_t___ __identifier_territory[12] __mu0_nullable__
		) {
#			if MU0_HAVE_POSIX1_2001
				__mu0_memcpy__(__identifier_language, "C.UTF-8\0"    ,  8);
#			else
				__mu0_memcpy__(__identifier_language, "en_US.UTF-8\0", 12);
#			endif
			if (__mu0_not_nullptr__(__identifier_territory)) {
				__mu0_memcpy__(__identifier_territory, __identifier_language, 12);
			}
		}

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_set__(const ___mu0_sint4_t___ __category, const ___mu0_tint1_t___ * __locale)
		{
#			if MU0_HAVE_POSIX1_2001
			return "C.UTF-8";
#			else
			return "en_US.UTF-8";
#			endif
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ * __locale)
		{
			__mu0_unused__(__locale);
			return 0;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const __mu0_i18nlocale_t__ * __locale __mu0_nullable__)
		{
			__mu0_unused__(__locale);
			const ___mu0_sint4_t___ r = strcmp (__lhs, __rhs);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare_n__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, const __mu0_i18nlocale_t__ * __locale __mu0_nullable__)
		{
			__mu0_unused__(__locale);
			const ___mu0_sint4_t___ r = strncmp (__lhs, __rhs, __n);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

#	endif

__mu0_static_inline__
const ___mu0_tint1_t___ * __mu0_i18nlocale_make__(const ___mu0_tint1_t___ * __lg, const ___mu0_tint1_t___ * __cn, const ___mu0_tint1_t___ * __md __mu0_nullable__)
{
	__mu0_static__ ___mu0_tint1_t___   s_id[48];
	               ___mu0_tint1_t___ * variant;
	               ___mu0_uint4_t___   have_name = 0;
	               ___mu0_uint8_t___   k, l, p   = 0;

	//#! XPG syntax:[language[territory[.codeset]][@modifier[+variant]]
	__mu0_memset__(s_id, 0, __mu0_sizeof__(s_id));
	if (__mu0_not_nullptr__(__lg)) {
		k = __mu0_memlen__(__lg);
		if (k > 0) {
			l  = k;
			__mu0_memcpy__(s_id + p, __lg, l);
			p += l;
			if (__mu0_not_nullptr__(__cn)) {
				k  = __mu0_memlen__(__cn);
				if (k > 0) {
					l  = __mu0_sizeof__(___mu0_tint1_t___);
					__mu0_memcpy__(s_id + p, "_", __mu0_min__(6, l));
					p += l;
					l  = k;
					__mu0_memcpy__(s_id + p, __cn, __mu0_min__(16, l));
					p += l;
					l  =  __mu0_sizeof__(___mu0_tint1_t___) * 6;
					__mu0_memcpy__(s_id + p, ".UTF-8", l);
					have_name = 1;
				}
				if (__mu0_not_nullptr__(__md)) {
					variant = strchr(__md, '+');
					if (__mu0_not_nullptr__(variant)) {
						k = variant - __md;
					} else {
						k = __mu0_memlen__(__md);
					}
					if (k > 0) {
						p += l;
						l  = __mu0_sizeof__(___mu0_tint1_t___);
						__mu0_memcpy__(s_id + p, "@", l);
						p += l;
						l  = k ;
						__mu0_memcpy__(s_id + p, __md, __mu0_min__(16, l));
					}
				}
			}
		}
	}
	return (have_name == 1) ? s_id : __mu0_nullptr__;
}

#endif /* !MU0_I18NLOCALE_H */

/* EOF */