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

// mu0_i18ndatetime.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_clocktime.h>
#include <mu0/mu0_definition/mu0_i18nlocale.h>

#ifndef MU0_I18NDATETIME_H
#define MU0_I18NDATETIME_H 1

#	undef  MU0_HAVE_I18NDATETIME
#	define MU0_HAVE_I18NDATETIME 0

typedef struct tm __mu0_calendar_date_t__;

#	define __mu0_layout_iso8601_full__      "%Y-%m-%dT%H:%M:%OS%z"
#	define __mu0_layout_iso8601__           "%Y-%m-%dT%H:%M:%S%z"
#	define __mu0_layout_iso8601_full_utc__  "%Y-%m-%dT%H:%M:%OSZ"
#	define __mu0_layout_iso8601_utc__       "%Y-%m-%dT%H:%M:%SZ"

#	define __mu0_layout_rfc3339_full__      "%Y-%m-%d %H:%M:%OS%z"
#	define __mu0_layout_rfc3339__           "%Y-%m-%d %H:%M:%S%z"
#	define __mu0_layout_rfc3339_full_utc__  "%Y-%m-%d %H:%M:%OSZ"
#	define __mu0_layout_rfc3339_utc__       "%Y-%m-%d %H:%M:%SZ"

#	define __mu0_format_iso8601_full__      0
#	define __mu0_format_iso8601__           1
#	define __mu0_format_iso8601_full_utc__  2
#	define __mu0_format_iso8601_utc__       3

#	define __mu0_format_rfc3339_full__      4
#	define __mu0_format_rfc3339__           5
#	define __mu0_format_rfc3339_full_utc__  6
#	define __mu0_format_rfc3339_utc__       7

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18ndatetime_formatting__(
	  const __mu0_calendar_date_t__ * __date
	, const ___mu0_sint4_t___         __format
	, const __mu0_i18nlocale_t__      __locale __mu0_nullable__
	, ___mu0_tint1_t___               __dest[64]
) {
	return 0;
}

#	if !MU0_HAVE_I18NDATETIME
#		error mu0_i18ndatetime.h
#	endif

#endif /* !MU0_I18NDATETIME_H */

/* EOF */