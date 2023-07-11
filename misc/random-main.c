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

// random-main.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_random.h>

int main(int argc, const char * argv[])
{
	mu0_unused(argc);
	mu0_unused(argv);

	mu0_uinteger_t i, k = 0;

	mu0_srandom(20, 2);
	mu0_console_log("\n");

	for (; k < 8; ++k) {
		i = 0;
		for (; i < 8; ++i) {
			mu0_console_log("%06u ", mu0_random_u16());
		}

		mu0_console_log("\n");
		i = 0;
		for (; i < 8; ++i) {
			mu0_console_log("%06u ", mu0_bounded_random_u32(8));
		}

		mu0_console_log("\n");
		i = 0;
		for (; i < 8; ++i) {
			mu0_console_log("%.04f ", mu0_random_fp64());
		}
		mu0_console_log("\n\n");
	}

	mu0_ssrandom();
	mu0_console_log("\n");

	k = 0;
	for (; k < 8; ++k) {
		i = 0;
		for (; i < 8; ++i) {
			mu0_console_log("%06u ", mu0_random_u16());
		}

		mu0_console_log("\n");
		i = 0;
		for (; i < 8; ++i) {
			mu0_console_log("%06u ", mu0_bounded_random_u32(32));
		}

		mu0_console_log("\n");
		i = 0;
		for (; i < 8; ++i) {
			mu0_console_log("%.04f ", mu0_random_fp64());
		}
		mu0_console_log("\n\n");
	}
	mu0_console_log("\n");

	return 0;
}

/* EOF */