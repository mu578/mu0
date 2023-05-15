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

// mu0_clocktime.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_platform.h>
#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_CLOCKTIME_H
#define MU0_CLOCKTIME_H 1

#	undef  MU0_HAVE_CLOCKTIME
#	undef  MU0_HAVE_NANOTIME_ABS
#	undef  MU0_HAVE_NANOTIME_UTC
#	define MU0_HAVE_CLOCKTIME    0
#	define MU0_HAVE_NANOTIME_UTC 0
#	define MU0_HAVE_NANOTIME_ABS 0

#	include <time.h>
#	include <unistd.h>

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_C11 && defined(TIME_MONOTONIC)
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_abs__(void)
		{
			struct timespec ts;
			if (TIME_MONOTONIC == timespec_get(&ts, TIME_MONOTONIC)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && !defined(_POSIX_TIMERS)
#		include <mach/clock.h>
#		include <mach/mach.h>
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_abs__(void)
		{
			return __mu0_const_cast__(___mu0_uint8_t___, mach_absolute_time());
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && defined(CLOCK_MONOTONIC_RAW)
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_abs__(void)
		{
			return __mu0_const_cast__(___mu0_uint8_t___, clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && defined(CLOCK_MONOTONIC)
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_abs__(void)
		{
			return __mu0_const_cast__(___mu0_uint8_t___, clock_gettime_nsec_np(CLOCK_MONOTONIC));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_POSIX1_2001 && defined(CLOCK_MONOTONIC_RAW)
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_abs__(void)
		{
			struct timespec ts;
			if (0 == clock_gettime(CLOCK_MONOTONIC_RAW, ts)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_POSIX1_2001 && defined(CLOCK_MONOTONIC)
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_abs__(void)
		{
			struct timespec ts;
			if (0 == clock_gettime(CLOCK_MONOTONIC, ts)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		include <profileapi.h>
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_abs__(void)
		{
			__mu0_static__ LARGE_INTEGER ts;
			               LARGE_INTEGER tv;
			               __int64       ssec;
			               __int64       nsec;
			if (!ts.QuadPart) { QueryPerformanceFrequency(&ts); if (ts.QuadPart) { return 0U; }}
			QueryPerformanceCounter(&tv);
			ssec = __mu0_const_cast__(__int64, (tv.QuadPart / ts.QuadPart));
			nsec = __mu0_const_cast__(__int64, (((tv.QuadPart % ts.QuadPart) * 1000000000i64) / ts.QuadPart));
			return __mu0_const_cast__(___mu0_uint8_t___, (sec * 1000000000i64 + nsec));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_UTC
#	if MU0_HAVE_C11 && defined(TIME_UTC)
#		undef  MU0_HAVE_NANOTIME_UTC
#		define MU0_HAVE_NANOTIME_UTC 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_utc__(void)
		{
			struct timespec ts;
			if (TIME_UTC == timespec_get(&ts, TIME_UTC)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_UTC
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && !defined(_POSIX_TIMERS)
#		include <mach/clock.h>
#		include <mach/mach.h>
#		undef  MU0_HAVE_NANOTIME_UTC
#		define MU0_HAVE_NANOTIME_UTC 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_utc__(void)
		{
			clock_serv_t    ck;
			mach_timespec_t ts;
			host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &ck);
			clock_get_time(ck, &mts);
			mach_port_deallocate(mach_task_self(), ck);
			return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_UTC
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && defined(CLOCK_REALTIME)
#		undef  MU0_HAVE_NANOTIME_UTC
#		define MU0_HAVE_NANOTIME_UTC 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_utc__(void)
		{
			return __mu0_const_cast__(___mu0_uint8_t___, clock_gettime_nsec_np(CLOCK_REALTIME));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_UTC
#	if MU0_HAVE_POSIX1_2001 && defined(CLOCK_REALTIME)
#		undef  MU0_HAVE_NANOTIME_UTC
#		define MU0_HAVE_NANOTIME_UTC 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_utc__(void)
		{
			struct timespec ts;
			if (0 == clock_gettime(CLOCK_REALTIME, ts)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_UTC
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_NANOTIME_UTC
#		define MU0_HAVE_NANOTIME_UTC 1
#		include <sysinfoapi.h>
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_utc__(void)
		{
			FILETIME       ft;
			ULARGE_INTEGER lv;
			__int64 tm, ssec, nsec;
			GetSystemTimeAsFileTime(&ft);
			lv.LowPart  = ft.dwLowDateTime;
			lv.HighPart = ft.dwHighDateTime;
			tm          = __mu0_const_cast__(__int64, (lv.QuadPart - 116444736000000000Ui64));
			ssec        = tm / 10000000i64;
			nsec        = tm % 10000000i64 * 100i64;
			return __mu0_const_cast__(___mu0_uint8_t___, (sec * 1000000000i64 + nsec));
		}
#	endif
#	endif

#	if MU0_HAVE_NANOTIME_ABS && MU0_HAVE_NANOTIME_UTC
#	undef  MU0_HAVE_CLOCKTIME
#	define MU0_HAVE_CLOCKTIME 1
#	endif

#	if !MU0_HAVE_CLOCKTIME
#		error mu0_clocktime.h
#	endif

#endif /* !MU0_CLOCKTIME_H */

/* EOF */