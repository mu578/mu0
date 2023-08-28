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
#	endif
#	if !MU0_HAVE_WINDOWS
#	include <stdlib.h>
#	endif
#	include <ctype.h>

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

#		define LC_MESSAGES      LC_ALL

#		define LC_ALL_MASK      0
#		define LC_COLLATE_MASK  0
#		define LC_CTYPE_MASK    0
#		define LC_MESSAGES_MASK 0
#		define LC_MONETARY_MASK 0
#		define LC_NUMERIC_MASK  0
#		define LC_TIME_MASK     0

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
		const ___mu0_tint1_t___ * __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __language[3]  __mu0_nullable__
			, ___mu0_tint1_t___ __territory[3] __mu0_nullable__
		) {
			const ___mu0_uint4_t___ have_language  = __mu0_not_nullptr__(__language);
			const ___mu0_uint4_t___ have_territory = __mu0_not_nullptr__(__territory);

			__mu0_static__ ___mu0_tint1_t___ s_id[12];
			 WCHAR buff[LOCALE_NAME_MAX_LENGTH] = { 0 };

			if (0 != GetUserDefaultLocaleName(buff, LOCALE_NAME_MAX_LENGTH)) {
				__mu0_memset__(s_id, 0, __mu0_sizeof__(s_id));
				WideCharToMultiByte(CP_UTF8, 0, buff, 5, s_id, 12, __mu0_nullptr__, __mu0_nullptr__);
				if (s_id[2] == '_' || s_id[2] == '-') {
					_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
					___mu0_tint1_t___ id[48]     = { 0 };
					s_id[2]                      = '_'; __mu0_memcpy__(s_id + 5, ".UTF-8", 6); s_id[11] = '\0';
					___mu0_tint1_t___ * s        = setlocale(LC_ALL, "");
					if (__mu0_not_nullptr__(s)) {
						__mu0_memcpy__(id, s, __mu0_sizeof__(id));
					} else {
#						if MU0_HAVE_POSIX1_2001
						__mu0_memcpy__(id, "C.UTF-8"    ,  7); id[7]  = '\0';
#						else
						__mu0_memcpy__(id, "en_US.UTF-8", 11); id[11] = '\0';
#						endif
					}
					if (__mu0_not_nullptr__(setlocale(LC_ALL, s_id))) {
						setlocale(LC_ALL, id);
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					___mu0_tint1_t___ wk[12]     = { 0 };
					__mu0_memcpy__(wk, s_id, __mu0_sizeof__(s_id));
					wk[3] = toupper(__mu0_const_cast__(___mu0_uint1_t___, wk[0]));
					wk[4] = toupper(__mu0_const_cast__(___mu0_uint1_t___, wk[1]));
					if (__mu0_not_nullptr__(setlocale(LC_ALL, wk))) {
						setlocale(LC_ALL, id);
						__mu0_memcpy__(s_id, wk, __mu0_sizeof__(wk));
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					__mu0_memcpy__(wk, s_id, __mu0_sizeof__(s_id));
					wk[0] = tolower(__mu0_const_cast__(___mu0_uint1_t___, wk[3]));
					wk[1] = tolower(__mu0_const_cast__(___mu0_uint1_t___, wk[4]));
					if (__mu0_not_nullptr__(setlocale(LC_ALL, wk))) {
						setlocale(LC_ALL, id);
						__mu0_memcpy__(s_id, wk, __mu0_sizeof__(wk));
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					setlocale(LC_ALL, id);
				}
			}
#			if MU0_HAVE_POSIX1_2001
			__mu0_memcpy__(s_id, "C.UTF-8"    ,  7); s_id[7]  = '\0';
#			else
			__mu0_memcpy__(s_id, "en_US.UTF-8", 11); s_id[11] = '\0';
#			endif
			return s_id;
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
		const ___mu0_tint1_t___ * __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __language[3]  __mu0_nullable__
			, ___mu0_tint1_t___ __territory[3] __mu0_nullable__
		) {
			const ___mu0_uint4_t___ have_language  = __mu0_not_nullptr__(__language);
			const ___mu0_uint4_t___ have_territory = __mu0_not_nullptr__(__territory);

			__mu0_static__ ___mu0_tint1_t___ s_id[12];
			FILE * fp;

			if ((fp = popen("defaults read .GlobalPreferences AppleLocale", "r"))) {
				__mu0_memset__(s_id, 0, __mu0_sizeof__(s_id));
				fgets(s_id, __mu0_sizeof__(s_id) - 1U, fp);
				if (s_id[2] == '_' || s_id[2] == '-') {
					pclose(fp);
					___mu0_tint1_t___ id[48] = { 0 };
					s_id[2]                  = '_'; __mu0_memcpy__(s_id + 5, ".UTF-8", 6); s_id[11] = '\0';
					___mu0_tint1_t___ * s    = setlocale(LC_ALL, "");
					if (__mu0_not_nullptr__(s)) {
						__mu0_memcpy__(id, s, __mu0_sizeof__(id));
					} else {
#						if MU0_HAVE_POSIX1_2001
						__mu0_memcpy__(id, "C.UTF-8"    ,  7); id[7]  = '\0';
#						else
						__mu0_memcpy__(id, "en_US.UTF-8", 11); id[11] = '\0';
#						endif
					}
					if (__mu0_not_nullptr__(setlocale(LC_ALL, s_id))) {
						setlocale(LC_ALL, id);
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					___mu0_tint1_t___ wk[12] = { 0 };
					__mu0_memcpy__(wk, s_id, __mu0_sizeof__(s_id));
					wk[3] = toupper(__mu0_const_cast__(___mu0_uint1_t___, wk[0]));
					wk[4] = toupper(__mu0_const_cast__(___mu0_uint1_t___, wk[1]));
					if (__mu0_not_nullptr__(setlocale(LC_ALL, wk))) {
						setlocale(LC_ALL, id);
						__mu0_memcpy__(s_id, wk, __mu0_sizeof__(wk));
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					__mu0_memcpy__(wk, s_id, __mu0_sizeof__(s_id));
					wk[0] = tolower(__mu0_const_cast__(___mu0_uint1_t___, wk[3]));
					wk[1] = tolower(__mu0_const_cast__(___mu0_uint1_t___, wk[4]));
					if (__mu0_not_nullptr__(setlocale(LC_ALL, wk))) {
						setlocale(LC_ALL, id);
						__mu0_memcpy__(s_id, wk, __mu0_sizeof__(wk));
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					setlocale(LC_ALL, id);
				}
				pclose(fp);
			}
#			if MU0_HAVE_POSIX1_2001
			__mu0_memcpy__(s_id, "C.UTF-8"    ,  7); s_id[7]  = '\0';
			if (have_language) {
				__language[0]  = 'C'; __language[1]  = '\0'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'C'; __territory[1] = '\0'; __territory[2] = '\0';
			}
#			else
			__mu0_memcpy__(s_id, "en_US.UTF-8", 11); s_id[11] = '\0';
			if (have_language) {
				__language[0]  = 'e'; __language[1]  = 'n'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'U'; __territory[1] = 'S'; __territory[2] = '\0';
			}
#			endif
			return s_id;
		}

#	elif MU0_HAVE_IOS

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __language[3]  __mu0_nullable__
			, ___mu0_tint1_t___ __territory[3] __mu0_nullable__
		) {
			const ___mu0_uint4_t___ have_language  = __mu0_not_nullptr__(__language);
			const ___mu0_uint4_t___ have_territory = __mu0_not_nullptr__(__territory);

			__mu0_static__ ___mu0_tint1_t___ s_id[12];
			__mu0_memset__(s_id, 0, __mu0_sizeof__(s_id));

			if (CFStringGetCString(CFLocaleGetValue(CFLocaleCopyCurrent(), kCFLocaleIdentifier), s_id, __mu0_sizeof__(s_id) - 1U, kCFStringEncodingUTF8)) {
				if (s_id[2] == '_' || s_id[2] == '-') {
					___mu0_tint1_t___ id[48] = { 0 };
					s_id[2]                  = '_'; __mu0_memcpy__(s_id + 5, ".UTF-8", 6); s_id[11] = '\0';
					___mu0_tint1_t___ * s    = setlocale(LC_ALL, "");
					if (__mu0_not_nullptr__(s)) {
						__mu0_memcpy__(id, s, __mu0_sizeof__(id));
					} else {
#						if MU0_HAVE_POSIX1_2001
						__mu0_memcpy__(id, "C.UTF-8"    ,  7); id[7]  = '\0';
#						else
						__mu0_memcpy__(id, "en_US.UTF-8", 11); id[11] = '\0';
#						endif
					}
					if (__mu0_not_nullptr__(setlocale(LC_ALL, s_id))) {
						setlocale(LC_ALL, id);
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					___mu0_tint1_t___ wk[12] = { 0 };
					__mu0_memcpy__(wk, s_id, __mu0_sizeof__(s_id));
					wk[3] = toupper(__mu0_const_cast__(___mu0_uint1_t___, wk[0]));
					wk[4] = toupper(__mu0_const_cast__(___mu0_uint1_t___, wk[1]));
					if (__mu0_not_nullptr__(setlocale(LC_ALL, wk))) {
						setlocale(LC_ALL, id);
						__mu0_memcpy__(s_id, wk, __mu0_sizeof__(wk));
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					__mu0_memcpy__(wk, s_id, __mu0_sizeof__(s_id));
					wk[0] = tolower(__mu0_const_cast__(___mu0_uint1_t___, wk[3]));
					wk[1] = tolower(__mu0_const_cast__(___mu0_uint1_t___, wk[4]));
					if (__mu0_not_nullptr__(setlocale(LC_ALL, wk))) {
						setlocale(LC_ALL, id);
						__mu0_memcpy__(s_id, wk, __mu0_sizeof__(wk));
						if (have_language) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__language[0]  = 'C';     __language[1]  = '\0';    __language[2]  = '\0';
							} else {
								__language[0]  = s_id[0]; __language[1]  = s_id[1]; __language[2]  = '\0';
							}
						}
						if (have_territory) {
							if (s_id[0] == 'C' || s_id[0] == 'P') {
								__territory[0] = 'C';     __territory[1] = '\0';    __territory[2] = '\0';
							} else {
								__territory[0] = s_id[3]; __territory[1] = s_id[4]; __territory[2] = '\0';
							}
						}
						return s_id;
					}
					setlocale(LC_ALL, id);
				}
			}
#			if MU0_HAVE_POSIX1_2001
			__mu0_memcpy__(s_id, "C.UTF-8"    ,  7); s_id[7]  = '\0';
			if (have_language) {
				__language[0]  = 'C'; __language[1]  = '\0'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'C'; __territory[1] = '\0'; __territory[2] = '\0';
			}
#			else
			__mu0_memcpy__(s_id, "en_US.UTF-8", 11); s_id[11] = '\0';
			if (have_language) {
				__language[0]  = 'e'; __language[1]  = 'n'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'U'; __territory[1] = 'S'; __territory[2] = '\0';
			}
#			endif
			return s_id;
		}

#	else

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __language[3]  __mu0_nullable__
			, ___mu0_tint1_t___ __territory[3] __mu0_nullable__
		) {
			const ___mu0_uint4_t___ have_language  = __mu0_not_nullptr__(__language);
			const ___mu0_uint4_t___ have_territory = __mu0_not_nullptr__(__territory);
			const ___mu0_tint1_t___ * id           = __mu0_i18nlocale_get__(LC_ALL, __mu0_nullptr__);

			if (__mu0_not_nullptr__(id)) {
				if (have_language) {
					if (id[0] == 'C' || id[0] == 'P') {
						__language[0]  = 'C';    __language[1]  = '\0';   __language[2]  = '\0';
					} else {
						__language[0]  = id[0]; __language[1]  = id[1]; __language[2]  = '\0';
					}
				}
				if (have_territory) {
					if (id[0] == 'C' || id[0] == 'P') {
						__territory[0] = 'C';    __territory[1] = '\0';   __territory[2] = '\0';
					} else {
						__territory[0] = id[3]; __territory[1] = id[4]; __territory[2] = '\0';
					}
				}
				return id;
			}
#			if MU0_HAVE_POSIX1_2001
			if (have_language) {
				__language[0]  = 'C'; __language[1]  = '\0'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'C'; __territory[1] = '\0'; __territory[2] = '\0';
			}
			return "C.UTF-8";
#			else
			if (have_language) {
				__language[0]  = 'e'; __language[1]  = 'n'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'U'; __territory[1] = 'S'; __territory[2] = '\0';
			}
			return "en_US.UTF-8";
#			endif
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
		const ___mu0_tint1_t___ * __mu0_i18nlocale_user__(
			  ___mu0_tint1_t___ __language[3]  __mu0_nullable__
			, ___mu0_tint1_t___ __territory[3] __mu0_nullable__
		) {
			const ___mu0_uint4_t___ have_language  = __mu0_not_nullptr__(__language);
			const ___mu0_uint4_t___ have_territory = __mu0_not_nullptr__(__territory);

			__mu0_unused__(__category);
			__mu0_unused__(__locale);

#			if MU0_HAVE_POSIX1_2001
			if (have_language) {
				__language[0]  = 'C'; __language[1]  = '\0'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'C'; __territory[1] = '\0'; __territory[2] = '\0';
			}
			return "C.UTF-8";
#			else
			if (have_language) {
				__language[0]  = 'e'; __language[1]  = 'n'; __language[2]  = '\0';
			}
			if (have_territory) {
				__territory[0] = 'U'; __territory[1] = 'S'; __territory[2] = '\0';
			}
			return "en_US.UTF-8";
#			endif
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
	__mu0_static__
	___mu0_tint1_t___   s_id[48];
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