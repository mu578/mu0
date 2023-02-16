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

#include <mu0/mu0_integer.h>

#ifndef MU0_STRING_H
#define MU0_STRING_H 1

MU0_BEGIN_CDECL

typedef          char  mu0_tchar8_t;
typedef unsigned char  mu0_uchar8_t;
typedef signed   char  mu0_schar8_t;

typedef mu0_tchar8_t * mu0_vtchar8_t;
typedef mu0_uchar8_t * mu0_vuchar8_t;
typedef mu0_schar8_t * mu0_vschar8_t;

typedef mu0_vtchar8_t  mu0_string8_t;
typedef mu0_vuchar8_t  mu0_binary8_t;

mu0_usize_t mu0_string8_length(const mu0_string8_t src);
mu0_usize_t mu0_string8_size  (const mu0_string8_t src);
mu0_usize_t mu0_string8_count (const mu0_string8_t src);

MU0_END_CDECL

#endif /* !MU0_STRING_H */

/* EOF */