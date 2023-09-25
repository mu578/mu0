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
#	undef  MU0_HAVE_LOCALTIME
#	undef  MU0_HAVE_DATEFORMAT
#	undef  MU0_HAVE_ZULUTIME
#	define MU0_HAVE_LOCALTIME    0
#	define MU0_HAVE_ZULUTIME     0
#	define MU0_HAVE_DATEFORMAT   0
#	define MU0_HAVE_I18NDATETIME 0

#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW

	struct __mu0_tm__
	{
		struct tm          u_tm;
		___mu0_sintx_t___  u_usec;
		___mu0_sintx_t___  u_gmtoff;
		___mu0_tchar1_t___ u_zone[6];
	};

#	define __mu0_tm_usec__(__tm)   (__tm)->u_usec
#	define __mu0_tm_gmtoff__(__tm) (__tm)->u_gmtoff
#	define __mu0_tm_zone__(__tm)   (__tm)->u_zone

#	else

	struct __mu0_tm__
	{
		struct tm         u_tm;
		___mu0_sintx_t___ u_usec;
	};

#	define __mu0_tm_usec__(__tm)   (__tm)->u_usec
#	define __mu0_tm_gmtoff__(__tm) (__tm)->u_tm.tm_gmtoff
#	define __mu0_tm_zone__(__tm)   (__tm)->u_tm.tm_zone

#	endif

#	define __mu0_tm_year__(__tm)   (__tm)->u_tm.tm_year
#	define __mu0_tm_yday__(__tm)   (__tm)->u_tm.tm_yday
#	define __mu0_tm_mon__(__tm)    (__tm)->u_tm.tm_mon
#	define __mu0_tm_wday__(__tm)   (__tm)->u_tm.tm_wday
#	define __mu0_tm_mday__(__tm)   (__tm)->u_tm.tm_mday
#	define __mu0_tm_hour__(__tm)   (__tm)->u_tm.tm_hour
#	define __mu0_tm_min__(__tm)    (__tm)->u_tm.tm_min
#	define __mu0_tm_sec__(__tm)    (__tm)->u_tm.tm_min
#	define __mu0_tm_isdst__(__tm)  (__tm)->u_tm.tm_isdst

#	if !MU0_HAVE_LOCALTIME
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#	undef  MU0_HAVE_LOCALTIME
#	define MU0_HAVE_LOCALTIME 1

	__mu0_static_inline__
	void __mu0_i18ndatetime_local__(struct __mu0_tm__ * __date)
	{
		struct __mu0_timeval__  utc;
		struct __mu0_timezone__ tz;
		__mu0_gettimeofday__(&utc, &tz);
		__mu0_memset__(__date, 0, __mu0_sizeof__(struct __mu0_tm__));
		localtime_s(&__date->u_tm, &utc.tv_sec);
		__date->u_gmtoff = tz.tz_minuteswest * 3600;
		__mu0_memset__(__date->u_zone, 0, 6);
		if (__date->u_tm.tm_isdst == 1) {
			__mu0_memcpy__(__date->u_zone, _tzname[1], __mu0_memlen__(_tzname[1]));
		} else {
			__mu0_memcpy__(__date->u_zone, _tzname[0], __mu0_memlen__(_tzname[0]));
		}
		__date->u_usec = utc.tv_usec;
	}

#	endif
#	endif

#	if !MU0_HAVE_LOCALTIME
#	if MU0_HAVE_POSIX1_2001
#	undef  MU0_HAVE_LOCALTIME
#	define MU0_HAVE_LOCALTIME 1

__mu0_static_inline__
void __mu0_i18ndatetime_local__(struct __mu0_tm__ * __date)
{
	struct __mu0_timeval__  utc;
	__mu0_gettimeofday__(&utc, __mu0_nullptr__);
	__mu0_memcpy__(&__date->u_tm, localtime(&utc.tv_sec), __mu0_sizeof__(struct tm));
	__date->u_usec = utc.tv_usec;
}

#	endif
#	endif

#	if !MU0_HAVE_ZULUTIME
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#	undef  MU0_HAVE_ZULUTIME
#	define MU0_HAVE_ZULUTIME 1

	__mu0_static_inline__
	void __mu0_i18ndatetime_zulu__(struct __mu0_tm__ * __date)
	{
		struct __mu0_timeval__  utc;
		struct __mu0_timezone__ tz;
		__mu0_gettimeofday__(&utc, &tz);
		__mu0_memset__(__date, 0, __mu0_sizeof__(struct __mu0_tm__));
		gmtime_s(&__date->u_tm, &utc.tv_sec);
		__date->u_gmtoff = tz.tz_minuteswest * 3600;
		__mu0_memset__(__date->u_zone, 0, 6);
		__mu0_memcpy__(__date->u_zone, "UTC", 3);
		__date->u_usec   = utc.tv_usec;
	}

#	endif
#	endif

#	if !MU0_HAVE_ZULUTIME
#	if MU0_HAVE_POSIX1_2001
#	undef  MU0_HAVE_ZULUTIME
#	define MU0_HAVE_ZULUTIME 1

__mu0_static_inline__
void __mu0_i18ndatetime_zulu__(struct __mu0_tm__ * __date)
{
	struct __mu0_timeval__  utc;
	__mu0_gettimeofday__(&utc, __mu0_nullptr__);
	__mu0_memset__(__date, 0, __mu0_sizeof__(struct __mu0_tm__));
	__mu0_memcpy__(&__date->u_tm, gmtime(&utc.tv_sec)   , __mu0_sizeof__(struct tm));
	__date->u_usec = utc.tv_usec;
}

#	endif
#	endif

#	if !MU0_HAVE_DATEFORMAT
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#	undef  MU0_HAVE_DATEFORMAT
#	define MU0_HAVE_DATEFORMAT 1

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18ndatetime_format__(
	  const struct __mu0_tm__ *           __date
	, const        ___mu0_uint4_t___      __format
	,              __mu0_i18nlocale_t__ * __locale   __mu0_nullable__
	,             ___mu0_tint1_t___       __dest[32]
) {
	                     ___mu0_tint1_t___   buf[4];
	__mu0_static__ const ___mu0_tint1_t___ * fmt[6] =
	{
		  "%Y-%m-%dT%H:%M:%S.000%z"
		, "%Y-%m-%dT%H:%M:%S%z"
		, "%Y-%m-%dT%H:%M:%SZ"
		, "%Y-%m-%d %H:%M:%S.000%z"
		, "%Y-%m-%d %H:%M:%S%z"
		, "%Y-%m-%d %H:%M:%SZ"
	};
	__mu0_memset__(__dest, 0, __mu0_sizeof__(___mu0_tint1_t___) * 32U);
	if (__mu0_is_nullptr__(__locale)) {
		strftime(__dest, __mu0_sizeof__(___mu0_tint1_t___) * 31U
			, (__format >= 0 && __format < 6) ? fmt[__format] : fmt[0]
			, &__date->u_tm
		);
	} else {
		_strftime_l(__dest, __mu0_sizeof__(___mu0_tint1_t___) * 31U
			, (__format >= 0 && __format < 6U) ? fmt[__format] : fmt[0]
			, &__date->u_tm
			, __locale->u_lc
		);
	}
	if (__format == 0 || __format == 3) {
		snprintf(buf, 4, "%03ld", __mu0_cast__(___mu0_sintx_t___, __date->u_usec / 1000)); buf[3] = '\0';
		__dest[20] = buf[0];
		__dest[21] = buf[1];
		__dest[22] = buf[2];
		if (__mu0_tm_gmtoff__(__date) == 0) {
			__dest[23] = '+';
			__dest[24] = '0';
			__dest[25] = '0';
			__dest[26] = '0';
			__dest[27] = '0';
		}
	} else if (__format == 1 || __format == 4) {
		if (__mu0_tm_gmtoff__(__date) == 0) {
			__dest[19] = '+';
			__dest[20] = '0';
			__dest[21] = '0';
			__dest[22] = '0';
			__dest[23] = '0';
		}
	}
	return 0;
}

#	endif
#	endif

#	if !MU0_HAVE_DATEFORMAT
#	if MU0_HAVE_POSIX1_2001
#	undef  MU0_HAVE_DATEFORMAT
#	define MU0_HAVE_DATEFORMAT 1

__mu0_static_inline__
const ___mu0_sint4_t___ __mu0_i18ndatetime_format__(
	  const struct __mu0_tm__ *    __date
	, const ___mu0_uint4_t___      __format
	,       __mu0_i18nlocale_t__ * __locale   __mu0_nullable__
	,       ___mu0_tint1_t___      __dest[32]
) {
	      ___mu0_tint1_t___   buf[4];
	const ___mu0_tint1_t___ * fmt[6] =
	{
		  "%Y-%m-%dT%H:%M:%S.000%z"
		, "%Y-%m-%dT%H:%M:%S%z"
		, "%Y-%m-%dT%H:%M:%SZ"
		, "%Y-%m-%d %H:%M:%S.000%z"
		, "%Y-%m-%d %H:%M:%S%z"
		, "%Y-%m-%d %H:%M:%SZ"
	};
	__mu0_memset__(__dest, 0, __mu0_sizeof__(___mu0_tint1_t___) * 32U);
	if (__mu0_is_nullptr__(__locale)) {
		strftime(__dest, __mu0_sizeof__(___mu0_tint1_t___) * 31U
			, (__format >= 0 && __format < 6) ? fmt[__format] : fmt[0]
			, &__date->u_tm
		);
	} else {
		strftime_l(__dest, __mu0_sizeof__(___mu0_tint1_t___) * 31U
			, (__format >= 0 && __format < 6U) ? fmt[__format] : fmt[0]
			, &__date->u_tm
			, __locale->u_lc
		);
	}
	if (__format == 0 || __format == 3) {
		snprintf(buf, 4, "%03ld", __mu0_cast__(___mu0_sintx_t___, __date->u_usec / 1000)); buf[3] = '\0';
		__dest[20] = buf[0];
		__dest[21] = buf[1];
		__dest[22] = buf[2];
		if (__mu0_tm_gmtoff__(__date) == 0) {
			__dest[23] = '+';
			__dest[24] = '0';
			__dest[25] = '0';
			__dest[26] = '0';
			__dest[27] = '0';
		}
	} else if (__format == 1 || __format == 4) {
		if (__mu0_tm_gmtoff__(__date) == 0) {
			__dest[19] = '+';
			__dest[20] = '0';
			__dest[21] = '0';
			__dest[22] = '0';
			__dest[23] = '0';
		}
	}
	return 0;
}

#	endif
#	endif

#	if MU0_HAVE_LOCALTIME && MU0_HAVE_ZULUTIME && MU0_HAVE_DATEFORMAT
#	undef  MU0_HAVE_I18NDATETIME
#	define MU0_HAVE_I18NDATETIME 1
#	endif

#	if !MU0_HAVE_I18NDATETIME
#		error mu0_i18ndatetime.h
#	endif

#endif /* !MU0_I18NDATETIME_H */

/* EOF */