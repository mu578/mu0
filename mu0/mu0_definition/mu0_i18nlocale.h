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

#ifndef MU0_I18NLOCALE_H
#define MU0_I18NLOCALE_H 1

#	undef  MU0_HAVE_I18NLOCALE
#	undef  __mu0_alloca__
#	undef  __mu0_malloc__
#	undef  __mu0_free__
#	undef  __mu0_memset__
#	undef  __mu0_memcpy__

#	undef  __mu0_strcoll_l__
#	undef  __mu0_strcoll__
#	undef  __mu0_strcmp__
#	undef  __mu0_strlen__
#	undef  __mu0_strncoll_l__
#	undef  __mu0_strncoll__
#	undef  __mu0_strncmp__
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
#	include <string.h>

#	if !MU0_HAVE_I18NLOCALE
#	if MU0_HAVE_WINDOWS
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1

#		define __mu0_malloc__      malloc
#		define __mu0_free__        free
#		define __mu0_memset__      memset
#		define __mu0_memcpy__      memcpy
#		define __mu0_strcoll_l__   _strcoll_l
#		define __mu0_strcoll__     strcoll
#		define __mu0_strlen__      strlen
#		define __mu0_strncoll_l__  _strncoll_l
#		define __mu0_strncoll__    _strncoll

		struct ___mu0_i18nlocale_t___
		{
			___mu0_tint1_t___ u_id[64];
			___mu0_sint4_t___ u_ct;
			_locale_t         u_lc;
		};
		typedef struct ___mu0_i18nlocale_t___ * __mu0_i18nlocale_t__;

#		define LC_ALL_MASK      0
#		define LC_COLLATE_MASK  0
#		define LC_CTYPE_MASK    0
#		define LC_MESSAGES_MASK 0
#		define LC_MONETARY_MASK 0
#		define LC_NUMERIC_MASK  0
#		define LC_TIME_MASK     0

		__mu0_static_inline__
		__mu0_i18nlocale_t__ __mu0_i18nlocale_new__(const ___mu0_sint4_t___ __mask, const ___mu0_tint1_t___ * __locale, __mu0_i18nlocale_t__ __base)
		{
			__mu0_i18nlocale_t__ locale = __mu0_malloc__(__mu0_sizeof__(struct ___mu0_i18nlocale_t___));
			___mu0_uint8_t___      len;
			__mu0_unused__(__mask);
			__mu0_unused__(__base);
			if (__mu0_not_nullptr__(locale)) {
				__mu0_memset__(locale, 0, __mu0_sizeof__(struct ___mu0_i18nlocale_t___));
				len                      = __mu0_const_cast__(___mu0_uint8_t___, __mu0_strlen__(__locale));
				__mu0_memcpy__(locale->u_id, __locale, len);
				locale->u_ct             = LC_ALL;
				locale->u_lc             = _create_locale(locale->u_ct, __locale);
				if (__mu0_is_nullptr__(locale->u_lc)) {
					__mu0_free__(locale);
					locale                = __mu0_nullptr__;
				}
			}
			return locale;
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ __mu0_i18nlocale_usecopy__(__mu0_i18nlocale_t__ __locale)
		{
			__mu0_i18nlocale_t__ locale = __mu0_i18nlocale_new__(
				  LC_ALL_MASK
				, setlocale(LC_ALL, __mu0_nullptr__)
				, __mu0_nullptr__
			);
			if (__mu0_not_nullptr__(__locale)) {
				_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
				setlocale(LC_ALL, __locale->u_id);
			}
			return locale;
		}

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
		{
			__mu0_unused__(__category);
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(LC_ALL, __mu0_nullptr__);
			}
			return __locale->u_id;
		}

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_set__(const ___mu0_sint4_t___ __category, const ___mu0_tint1_t___ * __locale)
		{
			__mu0_unused__(__category);
			return setlocale(LC_ALL, __locale);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ __locale)
		{
			if (__mu0_not_nullptr__(__locale)) {
				if (__mu0_not_nullptr__(__locale->u_lc)) {
					_free_locale(__locale->u_lc);
				}
				__mu0_free__(__locale);
				__locale = __mu0_nullptr__;
				return 0;
			}
			return -1;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, __mu0_i18nlocale_t__ __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale->u_lc)
						? __mu0_strcoll_l__ (__lhs, __rhs, __locale->u_lc)
						: __mu0_strcoll__   (__lhs, __rhs)
				)
				: __mu0_strcoll__ (__lhs, __rhs)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare_n__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, __mu0_i18nlocale_t__ __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale->u_lc)
						? __mu0_strncoll_l__ (__lhs, __rhs, __n, __locale->u_lc)
						: __mu0_strncoll__   (__lhs, __rhs, __n)
				)
				: __mu0_strncoll__ (__lhs, __rhs, __n)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

#	endif
#	endif

#	if !MU0_HAVE_I18NLOCALE
#	if MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_I18NLOCALE
#		define MU0_HAVE_I18NLOCALE 1

#		define __mu0_alloca__     alloca
#		define __mu0_memset__     memset
#		define __mu0_memcpy__     memcpy
#		define __mu0_strlen__     strlen
#		define __mu0_strcoll_l__  strcoll_l
#		define __mu0_strcoll__    strcoll
#		define __mu0_strncoll_l__ ___mu0_strncoll_l___
#		define __mu0_strncoll__   ___mu0_strncoll___

		typedef locale_t __mu0_i18nlocale_t__;

		__mu0_static_inline__
		const ___mu0_sint4_t___ ___mu0_strncoll_l___(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, __mu0_i18nlocale_t__ __locale __mu0_nullable__)
		{
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
				? __mu0_strcoll_l__ (need_a ? a : __lhs, need_b ? b : __rhs, __locale)
				: __mu0_strcoll__   (need_a ? a : __lhs, need_b ? b : __rhs)
			;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ ___mu0_strncoll___(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n)
		{
			return ___mu0_strncoll_l___(__lhs, __rhs, __n, __mu0_nullptr__);
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ __mu0_i18nlocale_new__(const ___mu0_sint4_t___ __mask, const ___mu0_tint1_t___ * __locale, __mu0_i18nlocale_t__ __base)
		{
			return newlocale(__mask, __locale, __base);
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ __mu0_i18nlocale_usecopy__(__mu0_i18nlocale_t__ __locale)
		{
			__mu0_i18nlocale_t__ locale = uselocale(__locale);
			return duplocale(locale);
		}

#		if !MU0_HAVE_ANDROID && !MU0_HAVE_LINUX && !MU0_HAVE_NUTTX && !MU0_HAVE_MINGW

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
		{
			___mu0_sint4_t___ mask;
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, __mu0_nullptr__);
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
			return querylocale(mask, __locale);
		}

#		elif !MU0_HAVE_MINGW && defined(NL_LOCALE_NAME)

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
		{
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, __mu0_nullptr__);
			}
			return nl_langinfo_l(NL_LOCALE_NAME(__category), __locale);
		}

#		elif !MU0_HAVE_MINGW && defined(_NL_LOCALE_NAME)

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
		{
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, __mu0_nullptr__);
			}
			return nl_langinfo_l(_NL_LOCALE_NAME(__category), __locale);
		}

#		elif !MU0_HAVE_MINGW && defined(_NL_ITEM) && defined(_NL_ITEM_INDEX)

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
		{
			if (__mu0_is_nullptr__(__locale)) {
				return setlocale(__category, __mu0_nullptr__);
			}
			return nl_langinfo_l(_NL_ITEM((__category), _NL_ITEM_INDEX(-1)), __locale);
		}

#		else

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
		{
			__mu0_unused__(__category);
			__mu0_unused__(__locale);
			return "en_EN.UTF-8";
		}

#		endif

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_set__(const ___mu0_sint4_t___ __category, const ___mu0_tint1_t___ * __locale)
		{
			return setlocale(__category, __locale);
		}

#		if !MU0_HAVE_ANDROID && !MU0_HAVE_LINUX && !MU0_HAVE_NUTTX && !MU0_HAVE_MINGW

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ __locale)
		{
			return freelocale(__locale);
		}

#		else

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ __locale)
		{
			freelocale(__locale);
			return 0;
		}

#		endif

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, __mu0_i18nlocale_t__ __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale)
						? __mu0_strcoll_l__ (__lhs, __rhs, __locale)
						: __mu0_strcoll__   (__lhs, __rhs)
				)
				: __mu0_strcoll__ (__lhs, __rhs)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare_n__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, __mu0_i18nlocale_t__ __locale __mu0_nullable__)
		{
			const ___mu0_sint4_t___ r = (__mu0_not_nullptr__(__locale)
				? (
					__mu0_not_nullptr__(__locale)
						? __mu0_strncoll_l__ (__lhs, __rhs, __n, __locale)
						: __mu0_strncoll__   (__lhs, __rhs, __n)
				)
				: __mu0_strncoll__(__lhs, __rhs, __n)
			);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

#	endif
#	endif

#	if !MU0_HAVE_I18NLOCALE
#		define __mu0_strcmp__  strcmp
#		define __mu0_strncmp__ strncmp

		typedef void * __mu0_i18nlocale_t__;

		__mu0_static_inline__
		__mu0_i18nlocale_t__ __mu0_i18nlocale_new__(const ___mu0_sint4_t___ __mask, const ___mu0_tint1_t___ * __locale, __mu0_i18nlocale_t__ __base)
		{
			__mu0_unused__(__mask);
			__mu0_unused__(__locale);
			__mu0_unused__(__base);
			return __mu0_nullptr__;
		}

		__mu0_static_inline__
		__mu0_i18nlocale_t__ __mu0_i18nlocale_usecopy__(__mu0_i18nlocale_t__ __locale)
		{
			__mu0_unused__(__locale);
			return __mu0_nullptr__;
		}

		const ___mu0_tint1_t___ * __mu0_i18nlocale_get__(const ___mu0_sint4_t___ __category, __mu0_i18nlocale_t__ __locale)
		{
			__mu0_unused__(__category);
			__mu0_unused__(__locale);
			return "en_EN.UTF-8";
		}

		__mu0_static_inline__
		const ___mu0_tint1_t___ * __mu0_i18nlocale_set__(const ___mu0_sint4_t___ __category, const ___mu0_tint1_t___ * __locale)
		{
			return "en_EN.UTF-8";
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_free__(__mu0_i18nlocale_t__ __locale)
		{
			__mu0_unused__(__locale);
			return 0;
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, __mu0_i18nlocale_t__ __locale __mu0_nullable__)
		{
			__mu0_unused__(__locale);
			const ___mu0_sint4_t___ r = __mu0_strcmp__ (__lhs, __rhs);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

		__mu0_static_inline__
		const ___mu0_sint4_t___ __mu0_i18nlocale_compare_n__(const ___mu0_tint1_t___ * __lhs, const ___mu0_tint1_t___ * __rhs, const ___mu0_uint4_t___ __n, __mu0_i18nlocale_t__  __locale __mu0_nullable__)
		{
			__mu0_unused__(__locale);
			const ___mu0_sint4_t___ r = __mu0_strncmp__ (__lhs, __rhs, __n);
			return (r > 0) ? 1 : ((r < 0) ? -1 : 0);
		}

#	endif

#	if MU0_HAVE_I18NLOCALE

	__mu0_static_inline__
	const ___mu0_tint1_t___ * __mu0_i18nlocale_id__(const ___mu0_tint1_t___ * __lg, const ___mu0_tint1_t___ * __cn, const ___mu0_tint1_t___ * __md __mu0_nullable__)
	{
		__mu0_static__
		___mu0_tint1_t___   s_name[48];
		___mu0_tint1_t___ * variant;
		___mu0_uint4_t___   have_name = 0;
		___mu0_uint8_t___   k, l, p   = 0;

		//#! XPG syntax:[language[territory[.codeset]][@modifier[+variant]]
		__mu0_memset__(s_name, 0, __mu0_sizeof__(s_name));
		if (__mu0_not_nullptr__(__lg)) {
			k = __mu0_strlen__(__lg);
			if (k > 0) {
				l  = k;
				__mu0_memcpy__(s_name + p, __lg, l);
				p += l;
				if (__mu0_not_nullptr__(__cn)) {
					k  = __mu0_strlen__(__cn);
					if (k > 0) {
						l  = __mu0_sizeof__(___mu0_tint1_t___);
						__mu0_memcpy__(s_name + p, "_", __mu0_min__(6, l));
						p += l;
						l  = k;
						__mu0_memcpy__(s_name + p, __cn, __mu0_min__(16, l));
						p += l;
						l  =  __mu0_sizeof__(___mu0_tint1_t___) * 6;
						__mu0_memcpy__(s_name + p, ".UTF-8", l);
						have_name = 1;
					}
					if (__mu0_not_nullptr__(__md)) {
						variant = strchr(__md, '+');
						if (__mu0_not_nullptr__(variant)) {
							k = variant - __md;
						} else {
							k = __mu0_strlen__(__md);
						}
						if (k > 0) {
							p += l;
							l  = __mu0_sizeof__(___mu0_tint1_t___);
							__mu0_memcpy__(s_name + p, "@", l);
							p += l;
							l  = k ;
							__mu0_memcpy__(s_name + p, __md, __mu0_min__(16, l));
						}
					}
				}
			}
		}
		return (have_name == 1) ? s_name : __mu0_nullptr__;
	}

#	endif

#	if !MU0_HAVE_I18NLOCALE

	__mu0_static_inline__
	const ___mu0_tint1_t___ * __mu0_i18nlocale_id__(const ___mu0_tint1_t___ * __lg, const ___mu0_tint1_t___ * __cn, const ___mu0_tint1_t___ * __md __mu0_nullable__)
	{
		__mu0_unused__(__lg);
		__mu0_unused__(__cn);
		__mu0_unused__(__md);

		return __mu0_nullptr__;
	}

#	endif

#endif /* !MU0_I18NLOCALE_H */

/* EOF */