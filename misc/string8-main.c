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

// string8-main.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_string8.h>

int main(int argc, const char * argv[])
{
	      mu0_usize_t i;
	      mu0_sint32_t width;
	const mu0_tchar8_t * glyph;

	const mu0_tchar8_t * s1   = mu0_utf8_const("éducation");
	const mu0_tchar8_t * s2   = mu0_utf8_const("Education");
	const mu0_tchar8_t * s3   = mu0_utf8_const("她就心緒翻湧惡意難消");
	const mu0_tchar8_t * s4   = mu0_utf8_const("Un ciel étoilé");
	      mu0_tchar8_t s5[17] = mu0_utf8_const("Un ciel étoilé\0");

	mu0_unused(argc);
	mu0_unused(argv);

	mu0_console_log("\n");

	mu0_console_log("s1.length : %zu\n", mu0_string8_length(s1));
	mu0_console_log("s1.size   : %zu\n", mu0_string8_width(s1) );
	mu0_console_log("s1.count  : %zu\n", mu0_string8_count(s1) );

	mu0_console_log("\n");

	mu0_console_log("s2.length : %zu\n", mu0_string8_length(s2));
	mu0_console_log("s2.size   : %zu\n", mu0_string8_width(s2) );
	mu0_console_log("s2.count  : %zu\n", mu0_string8_count(s2) );

	mu0_console_log("\n");

	mu0_console_log("s3.length : %zu\n", mu0_string8_length(s3));
	mu0_console_log("s3.size   : %zu\n", mu0_string8_width(s3) );
	mu0_console_log("s3.count  : %zu\n", mu0_string8_count(s3) );

	mu0_console_log("\n");

	mu0_console_log("s4.length : %zu\n", mu0_string8_length(s4));
	mu0_console_log("s4.size   : %zu\n", mu0_string8_width(s4) );
	mu0_console_log("s4.count  : %zu\n", mu0_string8_count(s4) );

	mu0_console_log("\n");

	mu0_console_log("s3.check() : %d\n" , mu0_string8_check(s3));
	for (i = 0; i < mu0_string8_count(s3); ++i) {
		glyph = mu0_string8_at(s3, i, &width);
		mu0_console_log("s3.at(%02zu) : %.*s\n", i, width, glyph);
	}

	mu0_console_log("\n");

	mu0_console_log("s4.check() : %d\n" , mu0_string8_check(s4));
	for (i = 0; i < mu0_string8_count(s4); ++i) {
		glyph = mu0_string8_at(s4, i, &width);
		mu0_console_log("s4.at(%02zu) : %.*s\n", i, width, glyph);
	}

	mu0_console_log("\n");

	mu0_console_log("s5.check() : %d\n" , mu0_string8_check(s5));
	mu0_string8_range_reverse(s5 + 3, s5 + 7);
	for (i = 0; i < mu0_string8_count(s5); ++i) {
		glyph = mu0_string8_at(s5, i, &width);
		mu0_console_log("s5.at(%02zu) : %.*s\n", i, width, glyph);
	}

	mu0_console_log("\n");

	return 0;
}

/* EOF */