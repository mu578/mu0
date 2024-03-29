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

// mu0_random.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_floating.h>
#include <mu0/mu0_integer.h>

#ifndef MU0_RANDOM_H
#define MU0_RANDOM_H 1

MU0_BEGIN_CDECL

void          mu0_random_seed         (const mu0_uint32_t seed, const mu0_uint32_t incr);
void          mu0_random_init         (void);

mu0_uint128_t mu0_random_u128         (void);
mu0_uint64_t  mu0_random_u64          (void);
mu0_uint32_t  mu0_random_u32          (void);
mu0_uint16_t  mu0_random_u16          (void);

mu0_sint128_t mu0_random_i128         (void);
mu0_sint64_t  mu0_random_i64          (void);
mu0_sint32_t  mu0_random_i32          (void);
mu0_sint16_t  mu0_random_i16          (void);

mu0_uint128_t mu0_random_bounded_u128 (const mu0_uint128_t upper_bound);
mu0_uint64_t  mu0_random_bounded_u64  (const mu0_uint64_t  upper_bound);
mu0_uint32_t  mu0_random_bounded_u32  (const mu0_uint32_t  upper_bound);
mu0_uint16_t  mu0_random_bounded_u16  (const mu0_uint16_t  upper_bound);

mu0_uint128_t mu0_random_ranged_u128  (const mu0_uint128_t lower_bound, const mu0_uint128_t upper_bound);
mu0_uint64_t  mu0_random_ranged_u64   (const mu0_uint64_t  lower_bound, const mu0_uint64_t  upper_bound);
mu0_uint32_t  mu0_random_ranged_u32   (const mu0_uint32_t  lower_bound, const mu0_uint32_t  upper_bound);
mu0_uint16_t  mu0_random_ranged_u16   (const mu0_uint16_t  lower_bound, const mu0_uint16_t  upper_bound);

mu0_sint128_t mu0_random_ranged_i128  (const mu0_sint128_t lower_bound, const mu0_sint128_t upper_bound);
mu0_sint64_t  mu0_random_ranged_i64   (const mu0_sint64_t  lower_bound, const mu0_sint64_t  upper_bound);
mu0_sint32_t  mu0_random_ranged_i32   (const mu0_sint32_t  lower_bound, const mu0_sint32_t  upper_bound);
mu0_sint16_t  mu0_random_ranged_i16   (const mu0_sint16_t  lower_bound, const mu0_sint16_t  upper_bound);

mu0_fp128_t   mu0_random_fp128        (void);
mu0_fp64_t    mu0_random_fp64         (void);
mu0_fp32_t    mu0_random_fp32         (void);
mu0_fp16_t    mu0_random_fp16         (void);

mu0_fp128_t   mu0_random_ranged_fp128 (const mu0_fp128_t lower_bound, const mu0_fp128_t upper_bound);
mu0_fp64_t    mu0_random_ranged_fp64  (const mu0_fp64_t  lower_bound, const mu0_fp64_t  upper_bound);
mu0_fp32_t    mu0_random_ranged_fp32  (const mu0_fp32_t  lower_bound, const mu0_fp32_t  upper_bound);
mu0_fp16_t    mu0_random_ranged_fp16  (const mu0_fp16_t  lower_bound, const mu0_fp16_t  upper_bound);

MU0_END_CDECL

#endif /* !MU0_RANDOM_H */

/* EOF */