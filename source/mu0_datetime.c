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

const mu0_calendar_date_t * mu0_datetime_querytime(mu0_calendar_date_t * date, const mu0_bool_t zulu)
{
	const mu0_calendar_date_t * p = date;

	struct __mu0_tm__ tm;
	if (zulu == mu0_false) {
		__mu0_i18ndatetime_localtime__(&tm);
	} else {
		__mu0_i18ndatetime_zulutime__ (&tm);
	}

	date->u_year         = mu0_const_cast(mu0_uint32_t, (__mu0_struct_tm_field_year__   (tm) + 1900));
	date->u_dayofyear    = mu0_const_cast(mu0_uint16_t,  __mu0_struct_tm_field_yday__   (tm));
	date->u_month        = mu0_const_cast(mu0_uint16_t,  __mu0_struct_tm_field_mon__    (tm));
	date->u_weekday      = mu0_const_cast(mu0_uint16_t,  __mu0_struct_tm_field_wday__   (tm));
	date->u_day          = mu0_const_cast(mu0_uint16_t,  __mu0_struct_tm_field_mday__   (tm));
	date->u_hours        = mu0_const_cast(mu0_uint16_t,  __mu0_struct_tm_field_hour__   (tm));
	date->u_minutes      = mu0_const_cast(mu0_uint16_t,  __mu0_struct_tm_field_min__    (tm));
	date->u_seconds      = mu0_const_cast(mu0_uint16_t,  __mu0_struct_tm_field_sec__    (tm));
	date->u_microseconds = mu0_const_cast(mu0_uint32_t,  __mu0_struct_tm_field_usec__   (tm));
	date->u_daylight     = mu0_const_cast(mu0_sint16_t,  __mu0_struct_tm_field_isdst__  (tm));
	date->u_offset       = mu0_const_cast(mu0_sint16_t,  __mu0_struct_tm_field_gmtoff__ (tm));
	memset(date->u_timezone, 0, 6);
	memcpy(
		  date->u_timezone
		,        __mu0_struct_tm_field_zone__(tm)
		, strlen(__mu0_struct_tm_field_zone__(tm))
	);

	return p;

}

const mu0_calendar_date_t * mu0_datetime_localtime(mu0_calendar_date_t * date)
{ return mu0_datetime_querytime(date, mu0_false); }

const mu0_calendar_date_t * mu0_datetime_zulutime(mu0_calendar_date_t * date)
{ return mu0_datetime_querytime(date, mu0_true); }

const mu0_tchar8_t * mu0_datetime_formatting(
	  const      mu0_calendar_date_t * date
	, const enum mu0_dateformat        format
	,            mu0_locale_t *        locale   __mu0_nullable__
	,            mu0_tchar8_t          dest[32]
) {
	const mu0_tchar8_t * p = dest;

	struct __mu0_tm__ tm;
	memset(&tm, 0, __mu0_sizeof__(struct __mu0_tm__));

	__mu0_struct_tm_field_year__   (tm) = date->u_year - 1900U;
	__mu0_struct_tm_field_yday__   (tm) = date->u_dayofyear;
	__mu0_struct_tm_field_mon__    (tm) = date->u_month;
	__mu0_struct_tm_field_wday__   (tm) = date->u_weekday;
	__mu0_struct_tm_field_mday__   (tm) = date->u_day;
	__mu0_struct_tm_field_hour__   (tm) = date->u_hours;
	__mu0_struct_tm_field_min__    (tm) = date->u_minutes;
	__mu0_struct_tm_field_sec__    (tm) = date->u_seconds;
	__mu0_struct_tm_field_usec__   (tm) = date->u_microseconds;
	__mu0_struct_tm_field_isdst__  (tm) = date->u_daylight;
	__mu0_struct_tm_field_gmtoff__ (tm) = date->u_offset;

	__mu0_i18ndatetime_formatting__(&tm, format, locale, dest);

	return p;
}

/* EOF */