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

// mu0_datetime.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_locale.h>

#ifndef MU0_DATETIME_H
#define MU0_DATETIME_H 1

MU0_BEGIN_CDECL

typedef struct
{
	mu0_sint64_t u_baseseconds;
	mu0_sint64_t u_nanoseconds;
} mu0_interval_t;

typedef struct
{
	mu0_sint64_t u_meantime;
	mu0_sint16_t u_daylight;
} mu0_timezone_t;

typedef struct
{
	mu0_uint32_t u_year;
	mu0_uint16_t u_dayofyear;
	mu0_uint16_t u_month;
	mu0_uint16_t u_weekday;
	mu0_uint16_t u_day;
	mu0_uint16_t u_hours;
	mu0_uint16_t u_minutes;
	mu0_uint16_t u_seconds;
	mu0_uint32_t u_microseconds;
	mu0_sint16_t u_daylight;
	mu0_sint16_t u_offset;
	mu0_tchar8_t u_timezone[6];
} mu0_calendar_date_t;

enum mu0_dateformat
{
	  mu0_dateformat_iso8601_full = 0
	, mu0_dateformat_iso8601_long = 1
	, mu0_dateformat_iso8601_zulu = 2
	, mu0_dateformat_rfc3339_full = 3
	, mu0_dateformat_rfc3339_long = 4
	, mu0_dateformat_rfc3339_zulu = 5
};

mu0_sint32_t                mu0_datetime_timeofday (
	  mu0_interval_t * interval
	, mu0_timezone_t * timezone __mu0_nullable__
);

const mu0_calendar_date_t * mu0_datetime_querytime (mu0_calendar_date_t * date, const mu0_bool_t zulu);
const mu0_calendar_date_t * mu0_datetime_localtime (mu0_calendar_date_t * date);
const mu0_calendar_date_t * mu0_datetime_zulutime  (mu0_calendar_date_t * date);

const mu0_tchar8_t *        mu0_datetime_formatting(
	  const      mu0_calendar_date_t * date
	, const enum mu0_dateformat        format
	,            mu0_locale_t        * locale   __mu0_nullable__
	,            mu0_tchar8_t          dest[32]
);

MU0_END_CDECL

#endif /* !MU0_DATETIME_H */

/* EOF */