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

// datetime-main.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_datetime.h>

int main(int argc, const char * argv[])
{
	mu0_calendar_date_t calendar_date;
	mu0_locale_t * locale = mu0_nullptr;
	mu0_tchar8_t        date_string[32];

	mu0_unused(argc);
	mu0_unused(argv);

	mu0_console_log("\n");

	mu0_datetime_localtime (&calendar_date);
	mu0_datetime_formatting(&calendar_date, mu0_dateformat_iso8601_full, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_iso8601_long, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_iso8601_zulu, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_rfc3339_full, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_rfc3339_long, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_rfc3339_zulu, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_console_log("\n");

	mu0_datetime_zulutime (&calendar_date);
	mu0_datetime_formatting(&calendar_date, mu0_dateformat_iso8601_full, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_iso8601_long, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_iso8601_zulu, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_rfc3339_full, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_rfc3339_long, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_datetime_formatting(&calendar_date, mu0_dateformat_rfc3339_zulu, locale, date_string);
	mu0_console_log("%s \n", date_string);

	mu0_console_log("\n");

	return 0;
}

/* EOF */