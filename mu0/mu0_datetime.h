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