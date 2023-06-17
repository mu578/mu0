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

// mu0_arithmetic.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_integer.h>
#include <mu0/mu0_floating.h>

#ifndef MU0_ARITHMETIC_H
#define MU0_ARITHMETIC_H 1

MU0_BEGIN_CDECL

#	if MU0_HAVE_STDCOMPLEX
#	define __mu0_arithmetic_initialize__(_Tp, __value) \
	__mu0_issame__(mu0_cfp16_t, _Tp)                   \
		? mu0_cfp16(__value, 0)                         \
		: (__mu0_issame__(mu0_cfp32_t, _Tp)             \
			? mu0_cfp32(__value, 0)                      \
			: (__mu0_issame__(mu0_cfp64_t, _Tp)          \
				? mu0_cfp64(__value, 0)                   \
				: (__mu0_issame__(mu0_cfp128_t, _Tp)      \
					? mu0_cfp128(__value, 0)               \
					: (_Tp) { __value }                    \
		)))
#	else
#	define __mu0_arithmetic_initialize__(_Tp, __value) (_Tp) { __value }
#	endif

MU0_END_CDECL

#endif /* !MU0_ARITHMETIC_H */

/* EOF */