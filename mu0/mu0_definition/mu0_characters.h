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

#	if   MU0_HAVE_WINDOWS && !(defined(__MINGW32__) || defined(__MINGW64__))

#		define __mu0_locale_t__                        _locale_t
#		define __mu0_setlocale__(category, name)       setlocale(category, name)
#		define __mu0_newlocale__(category, name)       _create_locale(category, name)
#		define __mu0_freelocale__(locale)              _free_locale(((__mu0_locale_t__)locale))

#		define __MU0_LOCALE_ALL__                      LC_ALL
#		define __MU0_LOCALE_COLLATE__                  LC_COLLATE
#		define __MU0_LOCALE_CTYPE__                    LC_CTYPE
#		define __MU0_LOCALE_MESSAGES__                 LC_MESSAGES
#		define __MU0_LOCALE_MONETARY__                 LC_MONETARY
#		define __MU0_LOCALE_NUMERIC__                  LC_NUMERIC
#		define __MU0_LOCALE_TIME__                     LC_TIME

#		define __MU0_LOCALE_MASK_ALL__                 LC_ALL
#		define __MU0_LOCALE_MASK_COLLATE__             LC_COLLATE
#		define __MU0_LOCALE_MASK_CTYPE__               LC_CTYPE
#		define __MU0_LOCALE_MASK_MESSAGES__            LC_MESSAGES
#		define __MU0_LOCALE_MASK_MONETARY__            LC_MONETARY
#		define __MU0_LOCALE_MASK_NUMERIC__             LC_NUMERIC
#		define __MU0_LOCALE_MASK_TIME__                LC_TIME

#	elif MU0_HAVE_POSIX1_2001

#		define __mu0_locale_t__                        locale_t
#		define __mu0_setlocale__(category, name)       setlocale(category, name)
#		define __mu0_newlocale__(category, name)       newlocale(category, name, NULL)
#		define __mu0_freelocale__(locale)              freelocale(((__mu0_locale_t__)locale))

#		define __MU0_LOCALE_ALL__                      LC_ALL
#		define __MU0_LOCALE_COLLATE__                  LC_COLLATE
#		define __MU0_LOCALE_CTYPE__                    LC_CTYPE
#		define __MU0_LOCALE_MESSAGES__                 LC_MESSAGES
#		define __MU0_LOCALE_MONETARY__                 LC_MONETARY
#		define __MU0_LOCALE_NUMERIC__                  LC_NUMERIC
#		define __MU0_LOCALE_TIME__                     LC_TIME

#		define __MU0_LOCALE_MASK_ALL__                 LC_ALL_MASK
#		define __MU0_LOCALE_MASK_COLLATE__             LC_COLLATE_MASK
#		define __MU0_LOCALE_MASK_CTYPE__               LC_CTYPE_MASK
#		define __MU0_LOCALE_MASK_MESSAGES__            LC_MESSAGES_MASK
#		define __MU0_LOCALE_MASK_MONETARY__            LC_MONETARY_MASK
#		define __MU0_LOCALE_MASK_NUMERIC__             LC_NUMERIC_MASK
#		define __MU0_LOCALE_MASK_TIME__                LC_TIME_MASK

#	else
#	error "mu0_characters.h"
# endif

#	if MU0_HAVE_WINDOWS && !(defined(__MINGW32__) || defined(__MINGW64__))
#		define __mu0_strcoll__(lhs, rhs)           strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale) _strcoll_l(lhs, rhs, ((__mu0_locale_t__)locale))
#	elif MU0_HAVE_POSIX1_2001
#		define __mu0_strcoll__(lhs, rhs)           strcoll(lhs, rhs)
#		define __mu0_strcoll_l__(lhs, rhs, locale) strcoll_l(lhs, rhs, ((__mu0_locale_t__)locale))
#	else
#	error "mu0_characters.h"
# endif

#endif /* !MU0_CHARACTERS_H */

/* EOF */