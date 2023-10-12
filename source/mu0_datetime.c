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

	struct ___mu0_tm___ tm;
	if (zulu == mu0_false) {
		__mu0_i18ndatetime_local__(&tm);
	} else {
		__mu0_i18ndatetime_zulu__ (&tm);
	}
	__mu0_memset__(date, 0, __mu0_sizeof__(mu0_calendar_date_t));
	date->u_year         = mu0_const_cast(mu0_sint32_t, (__mu0_tm_year__   (&tm) + 1900));
	date->u_dayofyear    = mu0_const_cast(mu0_uint16_t,  __mu0_tm_yday__   (&tm));
	date->u_month        = mu0_const_cast(mu0_uint16_t,  __mu0_tm_mon__    (&tm) + 1);
	date->u_weekday      = mu0_const_cast(mu0_uint16_t,  __mu0_tm_wday__   (&tm));
	date->u_day          = mu0_const_cast(mu0_uint16_t,  __mu0_tm_mday__   (&tm));
	date->u_hours        = mu0_const_cast(mu0_uint16_t,  __mu0_tm_hour__   (&tm));
	date->u_minutes      = mu0_const_cast(mu0_uint16_t,  __mu0_tm_min__    (&tm));
	date->u_seconds      = mu0_const_cast(mu0_uint16_t,  __mu0_tm_sec__    (&tm));
	date->u_microseconds = mu0_const_cast(mu0_uint32_t,  __mu0_tm_usec__   (&tm));
	date->u_daylight     = mu0_const_cast(mu0_sint16_t,  __mu0_tm_isdst__  (&tm));
	date->u_offset       = mu0_const_cast(mu0_sint16_t,  __mu0_tm_gmtoff__ (&tm));

	__mu0_memcpy__(date->u_timezone, __mu0_tm_zone__(&tm), __mu0_memlen__(__mu0_tm_zone__(&tm)));

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

	struct ___mu0_tm___ tm;
	__mu0_memset__(&tm, 0, __mu0_sizeof__(struct ___mu0_tm___));
	__mu0_tm_year__   (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_year - 1900);
	__mu0_tm_yday__   (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_dayofyear);
	__mu0_tm_mon__    (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_month - 1);
	__mu0_tm_wday__   (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_weekday);
	__mu0_tm_mday__   (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_day);
	__mu0_tm_hour__   (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_hours);
	__mu0_tm_min__    (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_minutes);
	__mu0_tm_sec__    (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_seconds);
	__mu0_tm_usec__   (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_microseconds);
	__mu0_tm_isdst__  (&tm) = mu0_const_cast(___mu0_sint4_t___, date->u_daylight);
	__mu0_tm_gmtoff__ (&tm) = mu0_const_cast(___mu0_sintx_t___, date->u_offset);

	__mu0_i18ndatetime_format__(&tm, format, locale, dest);

	return p;
}

/* EOF */