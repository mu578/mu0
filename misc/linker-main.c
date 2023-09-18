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

// linker-main.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition.h>
#include <mu0/mu0_floating.h>
#include <mu0/mu0_integer.h>
#include <mu0/mu0_random.h>
#include <mu0/mu0_locale.h>
#include <mu0/mu0_string.h>
#include <mu0/mu0_string8.h>

int main(int argc, const char * argv[])
{
	mu0_unused(argc);
	mu0_unused(argv);

	mu0_uint64_t u64 =  0x0102030405060708;
	mu0_sint64_t s64 = -0x0102030405060708;

	mu0_console_log("bswap64 of u64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", u64, u64, __mu0_bswap_64__(u64));
	mu0_console_log("bswap64 of u64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", u64, u64, __mu0_bswap_64__(__mu0_bswap_64__(u64)));
	mu0_console_log("bswap64 of u64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", u64, u64, __mu0_bswap_64__(__mu0_bswap_64__(__mu0_bswap_64__(u64))));
	mu0_console_log("bswap64 of u64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", u64, u64, __mu0_bswap_64__(__mu0_bswap_64__(__mu0_bswap_64__(__mu0_bswap_64__(u64)))));
	mu0_console_log("bswap64 of s64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", s64, s64, __mu0_bswap_64__(s64));
	mu0_console_log("bswap64 of s64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", s64, s64, __mu0_bswap_64__(__mu0_bswap_64__(s64)));
	mu0_console_log("bswap64 of s64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", s64, s64, __mu0_bswap_64__(__mu0_bswap_64__(__mu0_bswap_64__(s64))));
	mu0_console_log("bswap64 of s64 %16" PRIx64 " [ %16" PRIx64 " , %16" PRIx64 " ] \n", s64, s64, __mu0_bswap_64__(__mu0_bswap_64__(__mu0_bswap_64__(__mu0_bswap_64__(s64)))));

	return 0;
}

/* EOF */