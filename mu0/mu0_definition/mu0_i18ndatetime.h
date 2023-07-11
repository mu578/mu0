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

#	undef  __mu0_dateformat_iso8601_full__
#	undef  __mu0_dateformat_iso8601_long__
#	undef  __mu0_dateformat_iso8601_zulu__

#	undef  __mu0_dateformat_rfc3339_full__
#	undef  __mu0_dateformat_rfc3339_long__
#	undef  __mu0_dateformat_rfc3339_zulu__

#	define __mu0_dateformat_iso8601_full__ 0
#	define __mu0_dateformat_iso8601_long__ 1
#	define __mu0_dateformat_iso8601_zulu__ 2

#	define __mu0_dateformat_rfc3339_full__ 3
#	define __mu0_dateformat_rfc3339_long__ 4
#	define __mu0_dateformat_rfc3339_zulu__ 5

typedef struct
{
	struct tm         u_tm;
	___mu0_sintx_t___ u_us;
} __mu0_calendar_date_t__;

__mu0_static_inline__
void __mu0_i18ndatetime_localtime__(__mu0_calendar_date_t__ * __date)
{
#	if 0
	const time_t utc = time(__mu0_nullptr__);
#	endif
	struct __mu0_timeval__ utc;
	__mu0_gettimeofday__(&utc, __mu0_nullptr__);
	memset(__date, 0, sizeof(__mu0_calendar_date_t__));
#	if MU0_HAVE_WINDOWS
	localtime_s(&__date->u_tm, &utc.tv_sec);
#	else
	memcpy(&__date->u_tm, localtime(&utc.tv_sec), __mu0_sizeof__(__mu0_calendar_date_t__));
#	endif
	__date->u_us = utc.tv_usec;
}

__mu0_static_inline__
void __mu0_i18ndatetime_zulutime__(__mu0_calendar_date_t__ * __date)
{
#	if 0
	const time_t utc = time(__mu0_nullptr__);
#	endif
	struct __mu0_timeval__ utc;
	__mu0_gettimeofday__(&utc, __mu0_nullptr__);
	memset(__date, 0, sizeof(__mu0_calendar_date_t__));
#	if MU0_HAVE_WINDOWS
	gmtime_s(&__date->u_tm, &utc.tv_sec);
#	else
	memcpy(&__date->u_tm, gmtime(&utc.tv_sec)   , __mu0_sizeof__(__mu0_calendar_date_t__));
#	endif
	__date->u_us = utc.tv_usec;
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18ndatetime_formatting__(
	  const __mu0_calendar_date_t__ * __date
	, const ___mu0_uint4_t___         __format
	,       __mu0_i18nlocale_t__    * __locale   __mu0_nullable__
	,       ___mu0_tint1_t___         __dest[32]
) {
	___mu0_tint1_t___                        buf[4];
	__mu0_static__ const ___mu0_tint1_t___ * s_dateformat[6] =
	{
		  "%Y-%m-%dT%H:%M:%S.000%z"
		, "%Y-%m-%dT%H:%M:%S%z"
		, "%Y-%m-%dT%H:%M:%SZ"
		, "%Y-%m-%d %H:%M:%S.000%z"
		, "%Y-%m-%d %H:%M:%S%z"
		, "%Y-%m-%d %H:%M:%SZ"
	};

	memset(__dest, 0, __mu0_sizeof__(___mu0_tint1_t___) * 32U);
	if (__mu0_is_nullptr__(__locale)) {
		strftime(__dest, __mu0_sizeof__(___mu0_tint1_t___) * 31U
			, (__format >= 0 && __format < 6) ? s_dateformat[__format] : s_dateformat[0]
			, &__date->u_tm
		);
	} else {
#	if MU0_HAVE_WINDOWS
		_strftime_l(__dest, __mu0_sizeof__(___mu0_tint1_t___) * 31U
			, (__format >= 0 && __format < 6U) ? s_dateformat[__format] : s_dateformat[0]
			, &__date->u_tm
			, __locale->u_lc
		);
#	else
		strftime_l(__dest, __mu0_sizeof__(___mu0_tint1_t___) * 31U
			, (__format >= 0 && __format < 6U) ? s_dateformat[__format] : s_dateformat[0]
			, &__date->u_tm
			, __locale->u_lc
		);
	}
#	endif
	if (__format == 0 || __format == 3) {
		snprintf(buf, 4, "%03ld", __date->u_us / 1000); buf[3] = '\0';
		__dest[20] = buf[0];
		__dest[21] = buf[1];
		__dest[22] = buf[2];
	}
	return 0;
}

#	if !MU0_HAVE_I18NDATETIME
#		error mu0_i18ndatetime.h
#	endif

#endif /* !MU0_I18NDATETIME_H */

/* EOF */