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

// mu0_string.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition.h>

#ifndef MU0_STRING_H
#define MU0_STRING_H 1

MU0_BEGIN_CDECL

typedef ___mu0_uchar4_t___       mu0_uchar32_t;
typedef ___mu0_schar4_t___       mu0_schar32_t;
typedef ___mu0_tchar4_t___       mu0_tchar32_t;

typedef ___mu0_uchar2_t___       mu0_uchar16_t;
typedef ___mu0_schar2_t___       mu0_schar16_t;
typedef ___mu0_tchar2_t___       mu0_tchar16_t;

typedef ___mu0_uchar1_t___       mu0_uchar8_t;
typedef ___mu0_uchar1_t___       mu0_schar8_t;
typedef ___mu0_tchar1_t___       mu0_tchar8_t;

#	define mu0_uchar32(__x)       __mu0_cast__(mu0_uchar32_t, __x)
#	define mu0_const_uchar32(__x) __mu0_const_cast__(mu0_uchar32_t, __x)
#	define mu0_schar32(__x)       __mu0_cast__(mu0_schar32_t, __x)
#	define mu0_const_schar32(__x) __mu0_const_cast__(mu0_schar32_t, __x)
#	define mu0_tchar32(__x)       __mu0_cast__(mu0_tchar32_t, __x)
#	define mu0_const_tchar32(__x) __mu0_const_cast__(mu0_tchar32_t, __x)

#	define mu0_uchar16(__x)       __mu0_cast__(mu0_uchar16_t, __x)
#	define mu0_const_uchar16(__x) __mu0_const_cast__(mu0_uchar16_t, __x)
#	define mu0_schar16(__x)       __mu0_cast__(mu0_schar16_t, __x)
#	define mu0_const_schar16(__x) __mu0_const_cast__(mu0_schar16_t, __x)
#	define mu0_tchar16(__x)       __mu0_cast__(mu0_tchar16_t, __x)
#	define mu0_const_tchar16(__x) __mu0_const_cast__(mu0_tchar16_t, __x)

#	define mu0_uchar8(__x)        __mu0_cast__(mu0_uchar8_t, __x)
#	define mu0_const_uchar8(__x)  __mu0_const_cast__(mu0_uchar8_t, __x)
#	define mu0_schar8(__x)        __mu0_cast__(mu0_schar8_t, __x)
#	define mu0_const_schar8(__x)  __mu0_const_cast__(mu0_schar8_t, __x)
#	define mu0_tchar8(__x)        __mu0_cast__(mu0_tchar8_t, __x)
#	define mu0_const_tchar8(__x)  __mu0_const_cast__(mu0_tchar8_t, __x)

#	define mu0_utf8_const(__s)    __mu0_literal_utf8__(__s)
#	define mu0_utf16_const(__s)   __mu0_literal_utf16__(__s)
#	define mu0_utf32_const(__s)   __mu0_literal_utf32__(__s)

#	define mu0_string_length(_CharT, __src, __len) \
	__mu0_slength__(_CharT, __src, __len)

#	define mu0_string_width(_CharT, __src, __size) \
	__mu0_swidth__(_CharT, __src, __size)

#	define mu0_string_find(_CharT, __src_first, __src_last, __char, __d_pos) \
	__mu0_cfind__(_CharT, __src_first, __src_last, __char, __d_pos)

#	define mu0_string_find_n(_CharT, __src, __n, __char, __d_pos) \
	__mu0_cfind_n__(_CharT, __src, __n, __char, __d_pos)

MU0_END_CDECL

#endif /* !MU0_STRING_H */

/* EOF */