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

// random-main.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_random.h>
#include <stdio.h>

int main(int argc, const char * argv[])
{
	mu0_unused(argc);
	mu0_unused(argv);

	mu0_uinteger_t i, k = 0;

	mu0_srandom(20, 2);
	printf("\n");

	for (; k < 8; ++k) {
		i = 0;
		for (; i < 8; ++i) {
			printf("%06u ", mu0_random_u16());
		}

		printf("\n");
		i = 0;
		for (; i < 8; ++i) {
			printf("%06u ", mu0_bounded_random_u32(8));
		}

		printf("\n");
		i = 0;
		for (; i < 8; ++i) {
			printf("%.04f ", mu0_random_fp64());
		}
		printf("\n\n");
	}

	mu0_ssrandom();
	printf("\n");

	k = 0;
	for (; k < 8; ++k) {
		i = 0;
		for (; i < 8; ++i) {
			printf("%06u ", mu0_random_u16());
		}

		printf("\n");
		i = 0;
		for (; i < 8; ++i) {
			printf("%06u ", mu0_bounded_random_u32(32));
		}

		printf("\n");
		i = 0;
		for (; i < 8; ++i) {
			printf("%.04f ", mu0_random_fp64());
		}
		printf("\n\n");
	}
	printf("\n");

	return 0;
}

/* EOF */