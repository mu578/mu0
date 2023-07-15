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

struct __mu0_tm__
{
	struct tm         u_tm;
	___mu0_sintx_t___ u_us;
#	if MU0_HAVE_WINDOWS
	___mu0_sintx_t___ u_off;
	___mu0_sint1_t___ u_tz[6];
#	endif
};

__mu0_static_inline__
void __mu0_i18ndatetime_localtime__(struct __mu0_tm__ * __date)
{
#	if 0
	const time_t utc = time(__mu0_nullptr__);
#	endif
	struct __mu0_timeval__  utc;
#	if MU0_HAVE_WINDOWS
	struct __mu0_timezone__ tz;
	__mu0_gettimeofday__(&utc, &tz);
	memset(__date, 0, sizeof(struct __mu0_tm__));
	localtime_s(&__date->u_tm, &utc.tv_sec);
	__date->u_off = tz.tz_minuteswest * 3600;
	if (__date->u_tm.tm_isdst == 1) {
		memset(__date->u_tz, _tzname[1], strlen(_tzname[1]));
	} else {
		memset(__date->u_tz, _tzname[0], strlen(_tzname[0]));
	}
#	else
	__mu0_gettimeofday__(&utc, __mu0_nullptr__);
	memcpy(&__date->u_tm, localtime(&utc.tv_sec), __mu0_sizeof__(struct tm));
#	endif
	__date->u_us = utc.tv_usec;
}

__mu0_static_inline__
void __mu0_i18ndatetime_zulutime__(struct __mu0_tm__ * __date)
{
#	if 0
	const time_t utc = time(__mu0_nullptr__);
#	endif
	struct __mu0_timeval__  utc;
#	if MU0_HAVE_WINDOWS
	struct __mu0_timezone__ tz;
	__mu0_gettimeofday__(&utc, &tz);
	memset(__date, 0, sizeof(struct __mu0_tm__));
	gmtime_s(&__date->u_tm, &utc.tv_sec);
	__date->u_off = tz.tz_minuteswest * 3600;
	memset(__date->u_tz, 0, 6);
	memcpy(__date->u_tz, "UTC", 3);
#	else
	__mu0_gettimeofday__(&utc, __mu0_nullptr__);
	memset(__date, 0, sizeof(struct __mu0_tm__));
	memcpy(&__date->u_tm, gmtime(&utc.tv_sec)   , __mu0_sizeof__(struct tm));
#	endif
	__date->u_us = utc.tv_usec;
}

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18ndatetime_formatting__(
	  const struct __mu0_tm__ *    __date
	, const ___mu0_uint4_t___      __format
	,       __mu0_i18nlocale_t__ * __locale   __mu0_nullable__
	,       ___mu0_tint1_t___      __dest[32]
) {
	                     ___mu0_tint1_t___   buf[4];
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
#	endif
	}
	if (__format == 0 || __format == 3) {
		snprintf(buf, 4, "%03ld", __mu0_cast__(___mu0_sintx_t___, __date->u_us / 1000)); buf[3] = '\0';
		__dest[20] = buf[0];
		__dest[21] = buf[1];
		__dest[22] = buf[2];
#	if MU0_HAVE_WINDOWS
		if (__date->u_off == 0) {
			__dest[23] = '+';
			__dest[24] = '0';
			__dest[25] = '0';
			__dest[26] = '0';
			__dest[27] = '0';
		}
#	else
		if (__date->u_tm.tm_gmtoff == 0) {
			__dest[23] = '+';
			__dest[24] = '0';
			__dest[25] = '0';
			__dest[26] = '0';
			__dest[27] = '0';
		}
#	endif
	} else if (__format == 1 || __format == 4) {
#	if MU0_HAVE_WINDOWS
		if (__date->u_off == 0) {
			__dest[19] = '+';
			__dest[20] = '0';
			__dest[21] = '0';
			__dest[22] = '0';
			__dest[23] = '0';
		}
#	else
		if (__date->u_tm.tm_gmtoff == 0) {
			__dest[19] = '+';
			__dest[20] = '0';
			__dest[21] = '0';
			__dest[22] = '0';
			__dest[23] = '0';
		}
#	endif
	}
	return 0;
}

#	if !MU0_HAVE_I18NDATETIME
#		error mu0_i18ndatetime.h
#	endif

#endif /* !MU0_I18NDATETIME_H */

/* EOF */