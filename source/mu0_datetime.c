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

// mu0_datetime.c
//
// Copyright (C) 2023 mu578. All rights reservetm.
//

#include <mu0/mu0_datetime.h>

mu0_sint32_t                mu0_datetime_timeofday (
	  mu0_interval_t * interval
	, mu0_timezone_t * timezone __mu0_nullable__
) {
	struct __mu0_timeval__  tm;
	struct __mu0_timezone__ tz;

	mu0_sint32_t ret        = -1;
	interval->u_baseseconds =  0;
	interval->u_nanoseconds =  0;
	if (mu0_not_nullptr(timezone)) {
		timezone->u_meantime =  0;
		timezone->u_daylight =  0;
		ret = __mu0_gettimeofday__(&tm, &tz);
		if (ret == 0) {
			timezone->u_meantime = mu0_const_cast(mu0_sint64_t, tz.tz_minuteswest);
			timezone->u_daylight = mu0_const_cast(mu0_sint16_t, tz.tz_dsttime);
		}
	} else {
		ret = __mu0_gettimeofday__(&tm, mu0_nullptr);
	}
	if (ret == 0) {
		interval->u_baseseconds = mu0_const_cast(mu0_sint64_t, tm.tv_sec);
		interval->u_nanoseconds = mu0_const_cast(mu0_sint64_t, tm.tv_usec * 1000);
	}
	return ret;
}

const mu0_calendar_date_t * mu0_datetime_localtime(mu0_calendar_date_t * date)
{
	const mu0_calendar_date_t * p = date;

	struct __mu0_tm__ tm;
	__mu0_i18ndatetime_localtime__(&tm);

	date->u_year         = mu0_const_cast(mu0_uint32_t, (tm.u_tm.tm_year + 1900));
	date->u_dayofyear    = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_yday);
	date->u_month        = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_mon);
	date->u_weekday      = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_wday);
	date->u_day          = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_mday);
	date->u_hours        = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_hour);
	date->u_minutes      = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_min);
	date->u_seconds      = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_sec);
	date->u_microseconds = mu0_const_cast(mu0_uint32_t,  tm.u_us);
	date->u_daylight     = mu0_const_cast(mu0_sint16_t,  tm.u_tm.tm_isdst);

#	if MU0_HAVE_WINDOWS
	date->u_offset       = mu0_const_cast(mu0_sint16_t,  tm.u_off);
	memset(date->u_timezone, 0, 6);
	memcpy(date->u_timezone, tm.u_tz, 6);
#	else
	date->u_offset       = mu0_const_cast(mu0_sint16_t,  tm.u_tm.tm_gmtoff);
	memset(date->u_timezone, 0, 6);
	if (mu0_not_nullptr(tm.u_tm.tm_zone)) {
		memcpy(date->u_timezone, tm.u_tm.tm_zone, strlen(tm.u_tm.tm_zone));
	}
#	endif

	return p;
}

const mu0_calendar_date_t * mu0_datetime_zulutime(mu0_calendar_date_t * date)
{
	const mu0_calendar_date_t * p = date;

	struct __mu0_tm__ tm;
	__mu0_i18ndatetime_zulutime__(&tm);

	date->u_year         = mu0_const_cast(mu0_uint32_t, (tm.u_tm.tm_year + 1900U));
	date->u_dayofyear    = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_yday);
	date->u_month        = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_mon);
	date->u_weekday      = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_wday);
	date->u_day          = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_mday);
	date->u_hours        = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_hour);
	date->u_minutes      = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_min);
	date->u_seconds      = mu0_const_cast(mu0_uint16_t,  tm.u_tm.tm_sec);
	date->u_microseconds = mu0_const_cast(mu0_uint32_t,  tm.u_us);
	date->u_daylight     = mu0_const_cast(mu0_sint16_t,  tm.u_tm.tm_isdst);

#	if MU0_HAVE_WINDOWS
	date->u_offset       = mu0_const_cast(mu0_sint16_t,  tm.u_off);
	memset(date->u_timezone, 0, 6);
	memcpy(date->u_timezone, tm.u_tz, 6);
#	else
	date->u_offset       = mu0_const_cast(mu0_sint16_t,  tm.u_tm.tm_gmtoff);
	memset(date->u_timezone, 0, 6);
	if (mu0_not_nullptr(tm.u_tm.tm_zone)) {
		memcpy(date->u_timezone, tm.u_tm.tm_zone, strlen(tm.u_tm.tm_zone));
	}
#	endif

	return p;
}

const mu0_tchar8_t * mu0_datetime_formatting(
	  const      mu0_calendar_date_t * date
	, const enum mu0_dateformat        format
	,            mu0_locale_t *        locale   __mu0_nullable__
	,            mu0_tchar8_t          dest[32]
) {
	const mu0_tchar8_t * p = dest;

	struct __mu0_tm__ tm;
	memset(&tm, 0, __mu0_sizeof__(struct __mu0_tm__));

	tm.u_tm.tm_sec    = date->u_seconds;
	tm.u_tm.tm_min    = date->u_minutes;
	tm.u_tm.tm_hour   = date->u_hours;
	tm.u_tm.tm_mday   = date->u_day;
	tm.u_tm.tm_mon    = date->u_month;
	tm.u_tm.tm_year   = date->u_year - 1900U;
	tm.u_tm.tm_wday   = date->u_weekday;
	tm.u_tm.tm_yday   = date->u_dayofyear;
	tm.u_tm.tm_isdst  = date->u_daylight;
	tm.u_us           = date->u_microseconds;

#	if MU0_HAVE_WINDOWS
	tm.u_off          = date->u_offset;
	memset(tm.u_tz, 0, 6);
	memcpy(tm.u_tz, date->u_timezone, 6);
#	else
	tm.u_tm.tm_gmtoff = date->u_offset;
#	endif

	__mu0_i18ndatetime_formatting__(&tm, format, locale, dest);
	return p;
}

/* EOF */