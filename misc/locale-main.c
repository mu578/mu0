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

// locale-main.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_locale.h>

int main(int argc, const char * argv[])
{
	const mu0_tchar8_t * s1 = mu0_utf8_const("éducation");
	const mu0_tchar8_t * s2 = mu0_utf8_const("Education");

	const mu0_tchar8_t * s3 = mu0_utf8_const("érudition");
	const mu0_tchar8_t * s4 = mu0_utf8_const("Érudition");

	mu0_locale_t locale;

	mu0_unused(argc);
	mu0_unused(argv);

	mu0_console_log("\n");

	mu0_console_log("%p \n", (locale = mu0_locale_create("fr", "FR", mu0_nullptr, mu0_false)));
	mu0_console_log("%02d s1 <> s1\n", mu0_locale_compare(s1, s1, locale));
	mu0_console_log("%02d s1 <> s2\n", mu0_locale_compare(s1, s2, locale));
	mu0_console_log("%02d s1 <> s2\n", mu0_locale_compare(s2, s1, locale));
	mu0_console_log("%02d s3 <> s4\n", mu0_locale_compare(s3, s4, locale));
	mu0_console_log("%02d s4 <> s3\n", mu0_locale_compare(s4, s3, locale));
	mu0_console_log("%02d \n", mu0_locale_delete(locale));

	mu0_console_log("\n");

	mu0_console_log("%02d \n", mu0_locale_global("fr", "FR", mu0_nullptr, mu0_true));
	mu0_console_log("%02d s1 <> s1\n", mu0_locale_compare(s1, s1, mu0_nullptr));
	mu0_console_log("%02d s1 <> s2\n", mu0_locale_compare(s1, s2, mu0_nullptr));
	mu0_console_log("%02d s1 <> s2\n", mu0_locale_compare(s2, s1, mu0_nullptr));
	mu0_console_log("%02d s3 <> s4\n", mu0_locale_compare(s3, s4, mu0_nullptr));
	mu0_console_log("%02d s4 <> s3\n", mu0_locale_compare(s4, s3, mu0_nullptr));

	mu0_console_log("\n");

	mu0_console_log("%02d \n", mu0_locale_global("en", "US", mu0_nullptr, mu0_true));
	mu0_console_log("%02d s1 <> s1\n", mu0_locale_compare(s1, s1, mu0_nullptr));
	mu0_console_log("%02d s1 <> s2\n", mu0_locale_compare(s1, s2, mu0_nullptr));
	mu0_console_log("%02d s1 <> s2\n", mu0_locale_compare(s2, s1, mu0_nullptr));
	mu0_console_log("%02d s3 <> s4\n", mu0_locale_compare(s3, s4, mu0_nullptr));
	mu0_console_log("%02d s4 <> s3\n", mu0_locale_compare(s4, s3, mu0_nullptr));

	mu0_console_log("\n");
	mu0_console_log("%s \n", mu0_locale_interface());
	mu0_console_log("\n");

	return 0;
}

/* EOF */