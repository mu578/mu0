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
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_datetime.h>

void mu0_datetime_localtime (mu0_calendar_date_t * date)
{
	__mu0_i18ndatetime_localtime__(date);
}

void mu0_datetime_zulutime  (mu0_calendar_date_t * date)
{
	__mu0_i18ndatetime_zulutime__(date);
}

void mu0_datetime_formatting(
	  const      mu0_calendar_date_t * date
	, const enum mu0_dateformat        format
	,            mu0_locale_t          locale   __mu0_nullable__
	,            mu0_tchar8_t          dest[32]
) {
	__mu0_i18ndatetime_formatting__(date, format, locale, dest);
}

/* EOF */