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

// mu0_definition.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#ifndef MU0_DEFINITION_H
#define MU0_DEFINITION_H 1

#	include <mu0/mu0_definition/mu0_attribute.h>
#	include <mu0/mu0_definition/mu0_bitset.h>
#	include <mu0/mu0_definition/mu0_byteorder.h>
#	include <mu0/mu0_definition/mu0_byteswap.h>
#	include <mu0/mu0_definition/mu0_compiler.h>
#	include <mu0/mu0_definition/mu0_console.h>
#	include <mu0/mu0_definition/mu0_cpuyield.h>
#	include <mu0/mu0_definition/mu0_feature.h>
#	include <mu0/mu0_definition/mu0_language.h>
#	include <mu0/mu0_definition/mu0_memfence.h>
#	include <mu0/mu0_definition/mu0_platform.h>

MU0_BEGIN_CDECL

#	if MU0_HAVE_TYPEOF && MU0_HAVE_EXTENSION
#	define mu0_min(__a, __b)                      \
	__mu0_extension__ ({                          \
		__mu0_typeof__(__a) __m0_max__a__ = (__a); \
		__mu0_typeof__(__b) __m0_max__b__ = (__b); \
		(__m0_max__a__ < __m0_max__b__             \
			? __m0_max__a__                         \
			: __m0_max__b__                         \
		);                                         \
	})
#	define mu0_max(__a, __b)                      \
	__mu0_extension__ ({                          \
		__mu0_typeof__(__a) __m0_max__a__ = (__a); \
		__mu0_typeof__(__b) __m0_max__b__ = (__b); \
		(__m0_max__a__ > __m0_max__b__             \
			? __m0_max__a__                         \
			: __m0_max__b__                         \
		);                                         \
	})
#	else
#	define mu0_min(__a, __b)        (((__a) < (__b)) ? (__a) : (__b))
#	define mu0_max(__a, __b)        (((__a) > (__b)) ? (__a) : (__b))
#	endif

#	define mu0_scope_begin          do     {
#	define mu0_scope_end            break; } while (0)

#	define mu0_nullptr              NULL
#	define mu0_is_nullptr(__x)      ((__x) == NULL ? 1 : 0)
#	define mu0_not_nullptr(__x)     ((__x) != NULL ? 1 : 0)

#	define mu0_cast(_Tp, __x)       (_Tp)(__x)
#	define mu0_const_cast(_Tp, __x) (const _Tp)(__x)

#	define mu0_unused(__x)          mu0_cast(void, __x)

MU0_END_CDECL

#endif /* !MU0_DEFINITION_H */

/* EOF */