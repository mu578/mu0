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

// mu0_random.c
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_random.h>

typedef struct
{
	mu0_uint64_t u_state;
	mu0_uint64_t u_value;
} mu0_random_context_t;

#	define mu0_pcg32_initializer \
	{ __mu0_uint64_const__(9600629759793949339), __mu0_uint64_const__(15726070495360670683) }

__mu0_static__                  mu0_random_context_t __mu0_random_ctx__ = mu0_pcg32_initializer;
__mu0_static__ __mu0_volatile__ mu0_uint32_t         __mu0_random_ini__ = 0U;
__mu0_static__                  __mu0_spinlock_t__   __mu0_random_lck__ = __mu0_spinlock_initializer__;

__mu0_static_inline__
void mu0_pcg32_context_seed_build(mu0_uint64_t * seed, mu0_uint64_t * incr)
{
#	if MU0_HAVE_CPUCLICK
	*seed = __mu0_cpuclick__();
#	else
	*seed = __mu0_nanotime_act__() / 100000UL;
#	endif
	*incr = (*seed >> 1UL) | 1UL;
}

__mu0_static_inline__
mu0_uint32_t mu0_pcg32_random_r(mu0_random_context_t * ctx)
{
	mu0_uint64_t s = ctx->u_state;
	ctx->u_state   = s * __mu0_uint64_const__(6364136223846793005) + ctx->u_value;
	mu0_uint32_t y = (((s >> 18U) ^ s) >> 27U) & 0xFFFFFFFF;
	mu0_uint32_t r = s >> 59U;
	return (y >> r) | (y << ((-r) & 31U));
}

__mu0_static_inline__
mu0_uint32_t mu0_pcg32_random_bounded_r(mu0_random_context_t * ctx, const mu0_uint32_t bound)
{
	const mu0_uint32_t t = -bound % bound;
	mu0_uint32_t r;
	while (1) {
		r = mu0_pcg32_random_r(ctx);
		if (r >= t) { return r % bound; }
	}
	return t;
}

__mu0_static_inline__
mu0_uint64_t mu0_pcg32_64_random_r(mu0_random_context_t * ctx)
{
	const mu0_uint64_t hi = (mu0_uint64(mu0_pcg32_random_r(ctx))) << 32U;
	const mu0_uint64_t lo = (mu0_uint64(mu0_pcg32_random_r(ctx))) & 0xFFFFFFFF;
	return (hi | lo);
}

__mu0_static_inline__
mu0_uint16_t mu0_pcg32_16_random_r(mu0_random_context_t * ctx)
{
	return mu0_uint16(mu0_pcg32_random_bounded_r(ctx, mu0_uint32(mu0_uint16_max)));
}

__mu0_static_inline__
mu0_uint64_t mu0_pcg32_64_random_bounded_r(mu0_random_context_t * ctx, const mu0_uint64_t bound)
{
	const mu0_uint64_t t = -bound % bound;
	mu0_uint64_t r;
	while (1) {
		r = mu0_pcg32_64_random_r(ctx);
		if (r >= t) { return r % bound; }
	}
	return t;
}

__mu0_static_inline__
mu0_uint16_t mu0_pcg32_16_random_bounded_r(mu0_random_context_t * ctx, const mu0_uint16_t bound)
{
	return mu0_uint16(mu0_pcg32_random_bounded_r(ctx, mu0_uint32(bound)));
}

__mu0_static_inline__
void mu0_pcg32_srandom_r(
	 mu0_random_context_t * ctx
	, const mu0_uint64_t    seed
	, const mu0_uint64_t    incr
) {
	ctx->u_state = 0U;
	ctx->u_value = (incr << 1U) | 1U;
	mu0_pcg32_random_r(ctx);
	ctx->u_state = ctx->u_state + seed;
	mu0_pcg32_random_r(ctx);
}

__mu0_static_inline__
void mu0_pcg32_srandom(
	  const mu0_uint64_t seed
	, const mu0_uint64_t incr
) { mu0_pcg32_srandom_r(&__mu0_random_ctx__, seed, incr); }

__mu0_static_inline__
void mu0_pcg32_ssrandom_r(mu0_random_context_t * ctx)
{
	mu0_uint64_t seed, incr;
	__mu0_spinlock_lock__(&__mu0_random_lck__);
	if (__mu0_random_ini__ == 0U) {
		mu0_pcg32_context_seed_build(&seed, &incr);
		mu0_pcg32_srandom_r(ctx, seed, incr);
		__mu0_random_ini__ = 1U;
	}
	__mu0_spinlock_unlock__(&__mu0_random_lck__);
}

__mu0_static_inline__
void mu0_pcg32_ssrandom(void)
{ mu0_pcg32_ssrandom_r(&__mu0_random_ctx__); }

__mu0_static_inline__
mu0_uint32_t mu0_pcg32_random(void)
{
	return mu0_pcg32_random_r(&__mu0_random_ctx__);
}

__mu0_static_inline__
mu0_uint64_t mu0_pcg32_64_random(void)
{
	return mu0_pcg32_64_random_r(&__mu0_random_ctx__);
}

__mu0_static_inline__
mu0_uint16_t mu0_pcg32_16_random(void)
{
	return mu0_pcg32_16_random_r(&__mu0_random_ctx__);
}

__mu0_static_inline__
mu0_uint32_t mu0_pcg32_random_bounded(const mu0_uint32_t bound)
{
	return mu0_pcg32_random_bounded_r(&__mu0_random_ctx__, bound);
}

__mu0_static_inline__
mu0_uint64_t mu0_pcg32_64_random_bounded(const mu0_uint64_t bound)
{
	return mu0_pcg32_64_random_bounded_r(&__mu0_random_ctx__, bound);
}

__mu0_static_inline__
mu0_uint16_t mu0_pcg32_16_random_bounded(const mu0_uint16_t bound)
{
	return mu0_pcg32_16_random_bounded_r(&__mu0_random_ctx__, bound);
}

void mu0_random_seed(const mu0_uint32_t seed, const mu0_uint32_t incr)
{
	mu0_pcg32_srandom_r(&__mu0_random_ctx__, seed, incr);
}

void mu0_random_init(void)
{
	mu0_pcg32_ssrandom_r(&__mu0_random_ctx__);
}

mu0_uint128_t mu0_random_u128(void)
{
#	if MU0_HAVE_INT128
#	error "mu0_random.c"
#	else
	return mu0_random_u64();
#	endif
}

mu0_uint64_t mu0_random_u64(void)
{
	mu0_pcg32_ssrandom();
	const mu0_uint64_t hi = (mu0_uint64(mu0_pcg32_random())) << 32U;
	const mu0_uint64_t lo = (mu0_uint64(mu0_pcg32_random())) & 0xFFFFFFFFU;
	return (hi | lo);
}

mu0_uint32_t mu0_random_u32(void)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_random();
}

mu0_uint16_t mu0_random_u16(void)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_16_random();
}

mu0_sint128_t mu0_random_i128(void)
{
#	if MU0_HAVE_INT128
#	error "mu0_random.c"
#	else
	mu0_pcg32_ssrandom();
	return mu0_uint128(mu0_pcg32_64_random_bounded(mu0_sint128_max));
#	endif

}
mu0_sint64_t mu0_random_i64 (void)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_64_random_bounded(mu0_sint64_max);
}

mu0_sint32_t mu0_random_i32 (void)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_random_bounded(mu0_sint32_max);
}

mu0_sint16_t mu0_random_i16 (void)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_16_random_bounded(mu0_sint16_max);
}

mu0_uint128_t mu0_random_bounded_u128(const mu0_uint128_t upper_bound)
{
#	if MU0_HAVE_INT128
#	error "mu0_random.c"
#	else
	mu0_pcg32_ssrandom();
	return mu0_pcg32_64_random_bounded(upper_bound);
#	endif
}

mu0_uint64_t mu0_random_bounded_u64(const mu0_uint64_t upper_bound)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_64_random_bounded(upper_bound);
}

mu0_uint32_t mu0_random_bounded_u32(const mu0_uint32_t upper_bound)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_random_bounded(upper_bound);
}

mu0_uint16_t mu0_random_bounded_u16(const mu0_uint16_t upper_bound)
{
	mu0_pcg32_ssrandom();
	return mu0_pcg32_16_random_bounded(upper_bound);
}

mu0_uint128_t mu0_random_ranged_u128(
	  const mu0_uint128_t lower_bound
	, const mu0_uint128_t upper_bound
) {
	mu0_uint128_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_uint64_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_uint64_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_u128() % diff) + lo;
}

mu0_uint64_t mu0_random_ranged_u64(
	  const mu0_uint64_t  lower_bound
	, const mu0_uint64_t  upper_bound
) {
	mu0_uint64_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_uint64_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_uint64_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_u64() % diff) + lo;
}

mu0_uint32_t mu0_random_ranged_u32(
	  const mu0_uint32_t  lower_bound
	, const mu0_uint32_t  upper_bound
) {
	mu0_uint32_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_uint32_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_uint32_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_u32() % diff) + lo;
}

mu0_uint16_t mu0_random_ranged_u16(
	  const mu0_uint16_t  lower_bound
	, const mu0_uint16_t  upper_bound
) {
	mu0_uint16_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_uint16_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_uint16_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_u16() % diff) + lo;
}

mu0_sint128_t mu0_random_ranged_i128(
	  const mu0_sint128_t lower_bound
	, const mu0_sint128_t upper_bound
) {
	mu0_sint128_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_sint128_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_sint128_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_i128() % diff) + lo;
}

mu0_sint64_t mu0_random_ranged_i64(
	  const mu0_sint64_t  lower_bound
	, const mu0_sint64_t  upper_bound
) {
	mu0_sint64_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_sint64_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_sint64_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_i64() % diff) + lo;
}

mu0_sint32_t mu0_random_ranged_i32(
	  const mu0_sint32_t  lower_bound
	, const mu0_sint32_t  upper_bound
) {
	mu0_sint32_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_sint32_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_sint32_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_i32() % diff) + lo;
}

mu0_sint16_t mu0_random_ranged_i16(
	  const mu0_sint16_t  lower_bound
	, const mu0_sint16_t  upper_bound
) {
	mu0_sint16_t lo, hi, diff;

	if (lower_bound < upper_bound) {
		lo = lower_bound;
		hi = upper_bound < mu0_sint16_max ? upper_bound + 1 : upper_bound;
	} else {
		lo = upper_bound < mu0_sint16_max ? upper_bound + 1 : upper_bound;
		hi = lower_bound;
	}
	diff  = hi - lo;
	diff  = diff != 0 ? diff : 1;
	return (mu0_random_i16() % diff) + lo;
}

mu0_fp128_t mu0_random_fp128(void)
{
#	if MU0_HAVE_FLOAT128
	return mu0_fp128(mu0_random_fp64());
#	else
	return mu0_fpex(mu0_random_fp64());
#	endif
}

mu0_fp64_t mu0_random_fp64(void)
{
	const mu0_uint64_t k = __mu0_uint64_const__(0x1FFFFFFFFFFFFF);
	const mu0_uint64_t a = mu0_random_u64() % k;
	return (mu0_fp64(a) / mu0_fp64(k));
}

mu0_fp32_t mu0_random_fp32(void)
{
	const mu0_uint32_t k = __mu0_uint32_const__(0x1000001);
	const mu0_uint32_t a = mu0_random_u32() % k;
	return (mu0_fp32(a) / mu0_fp32(k));
}

mu0_fp16_t mu0_random_fp16(void)
{
	const mu0_uint16_t k = __mu0_uint16_const__(0xFFE0);
	const mu0_uint16_t a = mu0_random_u16() % k;
	return (mu0_fp16(a) / mu0_fp16(k));
}

mu0_fp128_t mu0_random_ranged_fp128(
	  const mu0_fp128_t lower_bound
	, const mu0_fp128_t upper_bound
) {
	const mu0_fp128_t k = mu0_random_fp128();
	const mu0_fp128_t d = lower_bound + k * (upper_bound - lower_bound);
	return d;
}

mu0_fp64_t mu0_random_ranged_fp64(
	  const mu0_fp64_t  lower_bound
	, const mu0_fp64_t  upper_bound
) {
	const mu0_fp64_t k = mu0_random_fp64();
	const mu0_fp64_t d = lower_bound + k * (upper_bound - lower_bound);
	return d;
}

mu0_fp32_t mu0_random_ranged_fp32(
	  const mu0_fp32_t  lower_bound
	, const mu0_fp32_t  upper_bound
) {
	const mu0_fp32_t k = mu0_random_fp32();
	const mu0_fp32_t d = lower_bound + k * (upper_bound - lower_bound);
	return d;
}

mu0_fp16_t mu0_random_ranged_fp16(
	  const mu0_fp16_t  lower_bound
	, const mu0_fp16_t  upper_bound
) {
	const mu0_fp16_t k = mu0_random_fp16();
	const mu0_fp16_t d = lower_bound + k * (upper_bound - lower_bound);
	return d;
}

/* EOF */