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
#	define MU0_HAVE_I18NDATETIME 1

#	define __mu0_dateformat_iso8601_full__ 0
#	define __mu0_dateformat_iso8601_long__ 1
#	define __mu0_dateformat_iso8601_zulu__ 2

#	define __mu0_dateformat_rfc3339_full__ 3
#	define __mu0_dateformat_rfc3339_long__ 4
#	define __mu0_dateformat_rfc3339_zulu__ 5

__mu0_static__ const ___mu0_tint1_t___ * __g_mu0_dateformat__[6] =
{
	  "%Y-%m-%dT%H:%M:%OS%z"
	, "%Y-%m-%dT%H:%M:%S%z"
	, "%Y-%m-%dT%H:%M:%SZ"
	, "%Y-%m-%d %H:%M:%OS%z"
	, "%Y-%m-%d %H:%M:%S%z"
	, "%Y-%m-%d %H:%M:%SZ"
};

typedef struct tm __mu0_calendar_date_t__;

__mu0_static_inline__
void __mu0_i18ndatetime_localtime__(__mu0_calendar_date_t__ * __date)
{
	const time_t utc = time(NULL);
#	if MU0_HAVE_WINDOWS
	localtime_s(__date, &utc);
#	else
	memcpy(__date, localtime(&utc), __mu0_sizeof__(__mu0_calendar_date_t__));
#	endif
}

__mu0_static_inline__
void __mu0_i18ndatetime_zulutime__(__mu0_calendar_date_t__ * __date)
{
	const time_t utc = time(NULL);
#	if MU0_HAVE_WINDOWS
	gmtime_s(__date, &utc);
#	else
	memcpy(__date, gmtime(&utc)  , __mu0_sizeof__(__mu0_calendar_date_t__));
#	endif
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18ndatetime_formatting__(
	  const __mu0_calendar_date_t__ * __date
	, const ___mu0_uint4_t___         __format
	,       __mu0_i18nlocale_t__    * __locale   __mu0_nullable__
	,       ___mu0_tint1_t___         __dest[32]
) {
	memset(__dest, 0, 32);
	if (__mu0_is_nullptr__(__locale)) {
		strftime(__dest, 32 - 1
			, (__format >= 0 && __format < 6)
				? __g_mu0_dateformat__[__format]
				: __g_mu0_dateformat__[0]
			, __date
		);
	}
#	if MU0_HAVE_WINDOWS
	_strftime_l(__dest, 32 - 1
		, (__format >= 0 && __format < 6)
			? __g_mu0_dateformat__[__format]
			: __g_mu0_dateformat__[0]
		, __date
		, __locale->u_lc
	);
#	else
	strftime_l(__dest, 32 - 1
		, (__format >= 0 && __format < 6)
			? __g_mu0_dateformat__[__format]
			: __g_mu0_dateformat__[0]
		, __date
		, __locale->u_lc
	);
#	endif
	return 0;
}

#	if !MU0_HAVE_I18NDATETIME
#		error mu0_i18ndatetime.h
#	endif

#endif /* !MU0_I18NDATETIME_H */

/* EOF */