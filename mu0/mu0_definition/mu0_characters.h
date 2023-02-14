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

// mu0_characters.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_CHARACTERS_H
#define MU0_CHARACTERS_H 1

#	if !MU0_HAVE_WINDOWS && !MU0_HAVE_ANDROID
#		include <xlocale.h>
#	endif

#include <locale.h>
#include <string.h>

#	define __mu0_memset__  memset
#	define __mu0_memcpy__  memcpy
#	define __mu0_memmove__ memmove
#	define __mu0_strlen__  strlen
#	define __mu0_strchr__  strchr

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
#		define __mu0_locale_t__                        _locale_t
#		define __mu0_setlocale__(category, name)       setlocale(category, name)
#		define __mu0_newlocale__(category, name)       _create_locale(category, name)
#		define __mu0_freelocale__(locale)              _free_locale(((__mu0_locale_t__)locale))
#		define __MU0_LOCALE_CATEGORY_ALL__             LC_ALL
#		define __MU0_LOCALE_CATEGORY_COLLATE__         LC_COLLATE
#		define __MU0_LOCALE_CATEGORY_CTYPE__           LC_CTYPE
#		define __MU0_LOCALE_CATEGORY_MESSAGES__        LC_MESSAGES
#		define __MU0_LOCALE_CATEGORY_MONETARY__        LC_MONETARY
#		define __MU0_LOCALE_CATEGORY_NUMERIC__         LC_NUMERIC
#		define __MU0_LOCALE_CATEGORY_TIME__            LC_TIME
#		define __MU0_LOCALE_CATEGORY_MASK_ALL__        LC_ALL
#		define __MU0_LOCALE_CATEGORY_MASK_COLLATE__    LC_COLLATE
#		define __MU0_LOCALE_CATEGORY_MASK_CTYPE__      LC_CTYPE
#		define __MU0_LOCALE_CATEGORY_MASK_MESSAGES__   LC_MESSAGES
#		define __MU0_LOCALE_CATEGORY_MASK_MONETARY__   LC_MONETARY
#		define __MU0_LOCALE_CATEGORY_MASK_NUMERIC__    LC_NUMERIC
#		define __MU0_LOCALE_CATEGORY_MASK_TIME__       LC_TIME
#	elif MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_LOCALE
#		define MU0_HAVE_LOCALE 1
#		define __mu0_locale_t__                        locale_t
#		define __mu0_setlocale__(category, name)       setlocale(category, name)
#		define __mu0_newlocale__(category, name)       newlocale(category, name, NULL)
#		define __mu0_freelocale__(locale)              freelocale(((__mu0_locale_t__)locale))
#		define __MU0_LOCALE_CATEGORY_ALL__             LC_ALL
#		define __MU0_LOCALE_CATEGORY_COLLATE__         LC_COLLATE
#		define __MU0_LOCALE_CATEGORY_CTYPE__           LC_CTYPE
#		define __MU0_LOCALE_CATEGORY_MESSAGES__        LC_MESSAGES
#		define __MU0_LOCALE_CATEGORY_MONETARY__        LC_MONETARY
#		define __MU0_LOCALE_CATEGORY_NUMERIC__         LC_NUMERIC
#		define __MU0_LOCALE_CATEGORY_TIME__            LC_TIME
#		define __MU0_LOCALE_CATEGORY_MASK_ALL__        LC_ALL_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_COLLATE__    LC_COLLATE_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_CTYPE__      LC_CTYPE_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_MESSAGES__   LC_MESSAGES_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_MONETARY__   LC_MONETARY_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_NUMERIC__    LC_NUMERIC_MASK
#		define __MU0_LOCALE_CATEGORY_MASK_TIME__       LC_TIME_MASK
#	endif

#	if MU0_HAVE_LOCALE
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		define __mu0_strcoll__(lhs, rhs)            strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale)  _strcoll_l(lhs, rhs, ((__mu0_locale_t__)locale))
#		define __mu0_locale_cmp__(lhs, rhs, locale) ((locale) ? __mu0_strcoll_l__(lhs, rhs, locale) : __mu0_strcoll__(lhs, rhs))
#	elif MU0_HAVE_POSIX1_2001
#		define __mu0_strcoll__(lhs, rhs)            strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale)  strcoll_l(lhs, rhs, ((__mu0_locale_t__)locale))
#		define __mu0_locale_cmp__(lhs, rhs, locale) ((locale) ? __mu0_strcoll_l__(lhs, rhs, locale) : __mu0_strcoll__(lhs, rhs))
#	endif
#	endif

#	if !MU0_HAVE_LOCALE
#		error mu0_characters.h
#	endif

#endif /* !MU0_CHARACTERS_H */

/* EOF */