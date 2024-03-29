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

#include <mu0/mu0_definition/mu0_attribute.h>
#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_CLOCKTIME_H
#define MU0_CLOCKTIME_H 1

#	undef  MU0_HAVE_CLOCKTIME
#	undef  MU0_HAVE_GETTIMEOFDAY
#	undef  MU0_HAVE_MICROSLEEP
#	undef  MU0_HAVE_NANOSLEEP
#	undef  MU0_HAVE_NANOTIME_ABS
#	undef  MU0_HAVE_NANOTIME_UTC
#	undef  MU0_HAVE_NANOTIME_ACT
#	undef  MU0_HAVE_NANOTIME_THR
#	undef  MU0_HAVE_NANOTIME_THR
#	define MU0_HAVE_MICROSLEEP   0
#	define MU0_HAVE_NANOSLEEP    0
#	define MU0_HAVE_GETTIMEOFDAY 0
#	define MU0_HAVE_NANOTIME_UTC 0
#	define MU0_HAVE_NANOTIME_ABS 0
#	define MU0_HAVE_NANOTIME_ACT 0
#	define MU0_HAVE_NANOTIME_THR 0
#	define MU0_HAVE_CLOCKTIME    0

#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#	include <errno.h>
#	endif

#	if MU0_HAVE_POSIX1_2001
#	include <sys/time.h>
#	endif
#	include <time.h>

#	if (((MU0_HAVE_MACOSX && !MU0_HAVE_MACOSX12) || (MU0_HAVE_IOS && !MU0_HAVE_IOS10)) && !defined(_POSIX_TIMERS))
#		warning MU0_HAVE_MACOSX12
#		warning MU0_HAVE_IOS10
#		include <mach/clock.h>
#		include <mach/mach.h>
#		include <mach/mach_time.h>
#		include <sched.h>
#		include <errno.h>

#		ifndef CLOCK_REALTIME
#			define CLOCK_REALTIME           0
#			endif
#		ifndef CLOCK_MONOTONIC
#			define CLOCK_MONOTONIC          1
#		endif
#		ifndef CLOCK_MONOTONIC_RAW
#			define CLOCK_MONOTONIC_RAW      2
#		endif
#		ifndef CLOCK_PROCESS_CPUTIME_ID
#			define CLOCK_PROCESS_CPUTIME_ID 3
#		endif
#		ifndef CLOCK_THREAD_CPUTIME_ID
#			define CLOCK_THREAD_CPUTIME_ID  4
#		endif

#	if !defined(_POSIX_TIMERS)
	typedef ___mu0_sint4_t___ clockid_t;
#	endif

#	pragma weak clock_gettime
	___mu0_sint4_t___ clock_gettime(clockid_t __clk_id, struct timespec * __tp)
	{
		__mu0_static__ mach_timebase_info_data_t s_info;
		clock_id_t                               cid;
		clock_serv_t                             clk;
		mach_timespec_t                          mtp;
		kern_return_t                            kret;

		___mu0_sint4_t___ ret = -1;
		___mu0_uint8_t___ start, end, delta, nano;

		switch (__clk_id)
		{
			case CLOCK_REALTIME      :
			case CLOCK_MONOTONIC     :
			case CLOCK_MONOTONIC_RAW :
			{
				cid = __clk_id == CLOCK_REALTIME ? CALENDAR_CLOCK : SYSTEM_CLOCK;
				if (KERN_SUCCESS == (kret = host_get_clock_service(mach_host_self(), cid, &clk))) {
					if (KERN_SUCCESS == (kret = clock_get_time(clk, &mtp))) {
						__tp->tv_sec  = mtp.tv_sec;
						__tp->tv_nsec = mtp.tv_nsec;
						ret           = 0;
					}
				}
				if (KERN_SUCCESS != kret) {
					errno = EINVAL;
					ret   = -1;
				}
			}
			break;
			case CLOCK_PROCESS_CPUTIME_ID :
			case CLOCK_THREAD_CPUTIME_ID  :
			{
				start         = mach_absolute_time();
				if (__clk_id == CLOCK_PROCESS_CPUTIME_ID) {
					getpid();
				} else {
					sched_yield();
				}
				end           = mach_absolute_time();
				delta         = end - start;	
				if (0 == s_info.denom) {
					mach_timebase_info(&s_info);
				}
				nano          = delta * s_info.numer / s_info.denom;
				__tp->tv_sec  = nano  * 1000000000UL;
				__tp->tv_nsec = nano  - (__tp->tv_sec * 1000000000UL);
				ret = 0;
			}
			break;
			default:
				errno = EINVAL;
				ret   = -1;
		}
		return ret;
	}

#	endif

#	if !MU0_HAVE_GETTIMEOFDAY
#	if MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_GETTIMEOFDAY
#		define MU0_HAVE_GETTIMEOFDAY 1

#		define __mu0_timezone__ timezone
#		define __mu0_timeval__  timeval

	__mu0_static_inline__
	___mu0_sint4_t___ __mu0_gettimeofday__(struct __mu0_timeval__ * __tv, struct __mu0_timezone__ * __tz)
	{ return gettimeofday(__tv, __tz); }

#	endif
#	endif

#	if !MU0_HAVE_GETTIMEOFDAY
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_GETTIMEOFDAY
#		define MU0_HAVE_GETTIMEOFDAY 1
#		include <sysinfoapi.h>

	struct __mu0_timeval__  { ___mu0_sint8_t___ tv_sec;         ___mu0_sintx_t___ tv_usec;    };
	struct __mu0_timezone__ { ___mu0_sint4_t___ tz_minuteswest; ___mu0_sint4_t___ tz_dsttime; };

	__mu0_static_inline__
	___mu0_sint4_t___ __mu0_gettimeofday__(struct __mu0_timeval__ * __tv, struct __mu0_timezone__ * __tz)
	{
		TIME_ZONE_INFORMATION tz;
		DWORD                 tzi;
		FILETIME              ft;
		ULARGE_INTEGER        lv;
		__int64               usec;
		if (__mu0_not_nullptr__(__tv)) {
	#	if _WIN32_WINNT >= _WIN32_WINNT_WIN8
			GetSystemTimePreciseAsFileTime(&ft);
	#	else
			GetSystemTimeAsFileTime(&ft);
	#	endif
			lv.LowPart    = ft.dwLowDateTime;
			lv.HighPart   = ft.dwHighDateTime;
			usec          = lv.QuadPart / 10Ui64 - 11644473600000000Ui64;
			__tv->tv_sec  = __mu0_const_cast__(time_t, (usec / 1000000Ui64));
			__tv->tv_usec = __mu0_const_cast__(___mu0_sintx_t___, (usec % 1000000Ui64));
		}
		if (__mu0_not_nullptr__(__tz)) {
			tzi = GetTimeZoneInformation(&tz);
			if (tzi != TIME_ZONE_ID_INVALID) {
				__tz->tz_minuteswest = tz.Bias;
				__tz->tz_dsttime     = tzi == TIME_ZONE_ID_DAYLIGHT ? 1 : 0;
			} else {
				__tz->tz_minuteswest = 0;
				__tz->tz_dsttime     = -1;
			}
		}
		return 0;
	}

#	endif
#	endif

#	if !MU0_HAVE_MICROSLEEP
#	if MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_MICROSLEEP
#		define MU0_HAVE_MICROSLEEP 1

#		define __mu0_useconds_t__ useconds_t

	__mu0_static_inline__
	___mu0_sint4_t___ __mu0_usleep__(__mu0_useconds_t__ __us)
	{ return usleep(__us); }

#	endif
#	endif

#	if !MU0_HAVE_MICROSLEEP
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_MICROSLEEP
#		define MU0_HAVE_MICROSLEEP 1
#		include <synchapi.h>

#		define __mu0_useconds_t__ ___mu0_uint8_t___

	__mu0_static_inline__
	___mu0_sint4_t___ __mu0_usleep__(__mu0_useconds_t__ __us)
	{
		___mu0_sint4_t___ ret = -1;
		HANDLE            tm;
		LARGE_INTEGER     ft;
		ft.QuadPart           = __mu0_const_cast__(___mu0_sint8_t___, (10Ui64 * __us));
		ft.QuadPart           = -ft.QuadPart;
		if ((tm = CreateWaitableTimer(__mu0_nullptr__, TRUE, __mu0_nullptr__))) {
			if (SetWaitableTimer(tm, &ft, 0, __mu0_nullptr__, __mu0_nullptr__, FALSE)) {
				if (WAIT_OBJECT_0 == WaitForSingleObject(tm, INFINITE)) {
					ret = 0;
				} else {
					_set_errno(EINTR);
				}
			}
			CloseHandle(tm);
		}
		return ret;
	}

#	endif
#	endif

#	if !MU0_HAVE_NANOSLEEP
#	if MU0_HAVE_POSIX1_2001
#		undef  MU0_HAVE_NANOSLEEP
#		define MU0_HAVE_NANOSLEEP 1

	__mu0_static_inline__
	___mu0_sint4_t___ __mu0_nanosleep__(const struct timespec * __rqtp, struct timespec * __rmtp)
	{ return nanosleep(__rqtp, __rmtp); }

#	endif
#	endif

#	if !MU0_HAVE_NANOSLEEP
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_NANOSLEEP
#		define MU0_HAVE_NANOSLEEP 1

	__mu0_static_inline__
	___mu0_sint4_t___ __mu0_nanosleep__(const struct timespec * __rqtp, struct timespec * __rmtp)
	{
		___mu0_sint4_t___ ret = -1;
		___mu0_sint8_t___ ns  = 1000 * 1000 * 1000 * __rqtp->tv_sec + __rqtp->tv_nsec;
		__rmtp->tv_sec        = __rqtp->tv_sec;
		__rmtp->tv_nsec       = __rqtp->tv_nsec;
		if (ns > 0 && ns < 999999999) {
			ret = __mu0_usleep__(__mu0_const_cast__(___mu0_uint8_t___, (ns / 1000U)));
			if (ret == 0) {
				__rmtp->tv_sec  = 0;
				__rmtp->tv_nsec = 0;
			} else {
				_set_errno(EINTR);
			}
		} else {
			_set_errno(EINVAL);
		}
		return ret;
	}

#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ABS
#	if MU0_HAVE_C11 && defined(TIME_MONOTONIC)
#	if MU0_HAVE_IOS && !MU0_HAVE_IOS13
#		undef  MU0_HAVE_NANOTIME_ABS
#		define MU0_HAVE_NANOTIME_ABS 0
#	else
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
			if (0 == clock_gettime(CLOCK_MONOTONIC_RAW, &ts)) {
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
			if (0 == clock_gettime(CLOCK_MONOTONIC, &ts)) {
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
			if (!ts.QuadPart) {
				if (0 == QueryPerformanceFrequency(&ts)) {
					return 0U;
				}
				if (!ts.QuadPart) {
					return 0U;
				}
			}
			if (0 == QueryPerformanceCounter(&tv)) {
				return 0U;
			}
			if (!tv.QuadPart) {
				return 0U;
			}
			ssec = __mu0_const_cast__(__int64, (tv.QuadPart / ts.QuadPart));
			nsec = __mu0_const_cast__(__int64, (((tv.QuadPart % ts.QuadPart) * 1000000000i64 + (ts.QuadPart >> 1U)) / ts.QuadPart));
			if (nsec >= 1000000000i64) {
				ssec = ssec + 1i64;
				nsec = nsec - 1000000000i64;
			}
			return __mu0_const_cast__(___mu0_uint8_t___, (ssec * 1000000000i64 + nsec));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_UTC
#	if MU0_HAVE_C11 && defined(TIME_UTC)
#	if MU0_HAVE_IOS && !MU0_HAVE_IOS13
#		undef  MU0_HAVE_NANOTIME_UTC
#		define MU0_HAVE_NANOTIME_UTC 0
#	else
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
			clock_get_time(ck, &ts);
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
			if (0 == clock_gettime(CLOCK_REALTIME, &ts)) {
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
	#	if _WIN32_WINNT >= _WIN32_WINNT_WIN8
			GetSystemTimePreciseAsFileTime(&ft);
	#	else
			GetSystemTimeAsFileTime(&ft);
	#	endif
			lv.LowPart  = ft.dwLowDateTime;
			lv.HighPart = ft.dwHighDateTime;
			tm          = __mu0_const_cast__(__int64, (lv.QuadPart - 116444736000000000Ui64));
			ssec        = tm / 10000000i64;
			nsec        = tm % 10000000i64 * 100i64;
			return __mu0_const_cast__(___mu0_uint8_t___, (ssec * 1000000000i64 + nsec));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ACT
#	if MU0_HAVE_C11 && defined(TIME_ACTIVE)
#	if MU0_HAVE_IOS && !MU0_HAVE_IOS13
#		undef  MU0_HAVE_NANOTIME_ACT
#		define MU0_HAVE_NANOTIME_ACT 0
#	else
#		undef  MU0_HAVE_NANOTIME_ACT
#		define MU0_HAVE_NANOTIME_ACT 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_act__(void)
		{
			struct timespec ts;
			if (TIME_ACTIVE == timespec_get(&ts, TIME_ACTIVE)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ACT
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && !defined(_POSIX_TIMERS)
#		include <mach/clock.h>
#		include <mach/mach.h>
#		undef  MU0_HAVE_NANOTIME_ACT
#		define MU0_HAVE_NANOTIME_ACT 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_act__(void)
		{
			return __mu0_const_cast__(___mu0_uint8_t___, mach_absolute_time());
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ACT
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && defined(CLOCK_PROCESS_CPUTIME_ID)
#		undef  MU0_HAVE_NANOTIME_ACT
#		define MU0_HAVE_NANOTIME_ACT 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_act__(void)
		{
			return __mu0_const_cast__(___mu0_uint8_t___, clock_gettime_nsec_np(CLOCK_PROCESS_CPUTIME_ID));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ACT
#	if MU0_HAVE_POSIX1_2001 && defined(CLOCK_PROCESS_CPUTIME_ID)
#		undef  MU0_HAVE_NANOTIME_ACT
#		define MU0_HAVE_NANOTIME_ACT 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_act__(void)
		{
			struct timespec ts;
			if (0 == clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_ACT
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_NANOTIME_ACT
#		define MU0_HAVE_NANOTIME_ACT 1
#		include <processthreadsapi.h>
#		include <realtimeapiset.h>
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_act__(void)
		{
#	if 0
			/* frequency is unknown, let's imagining it is elapsed time. */
			__int64 r;
			if (0 != QueryProcessCycleTime(GetCurrentProcess(), &r)) {
				return __mu0_const_cast__(___mu0_uint8_t___, r);
			}
			return 0U;
#	endif
			FILETIME ct, et, kt, ut;
			ULARGE_INTEGER lv;
			__int64 tm, tk, tu, ssec, nsec;
			if (0 != GetProcessTimes(GetCurrentProcess(), &ct, &et, &kt, &ut)) {
				lv.LowPart  = kt.dwLowDateTime;
				lv.HighPart = kt.dwHighDateTime;
				tk          = __mu0_const_cast__(__int64, lv.QuadPart);
				lv.LowPart  = ut.dwLowDateTime;
				lv.HighPart = ut.dwHighDateTime;
				tu          = __mu0_const_cast__(__int64, lv.QuadPart);
				tm          = tk + tu;
				ssec        = tm / 10000000i64;
				nsec        = tm % 10000000i64 * 100i64;
				return __mu0_const_cast__(___mu0_uint8_t___, (ssec * 1000000000i64 + nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_THR
#	if MU0_HAVE_C11 && defined(TIME_THREAD_ACTIVE)
#	if MU0_HAVE_IOS && !MU0_HAVE_IOS13
#		undef  MU0_HAVE_NANOTIME_THR
#		define MU0_HAVE_NANOTIME_THR 0
#	else
#		undef  MU0_HAVE_NANOTIME_THR
#		define MU0_HAVE_NANOTIME_THR 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_thr__(void)
		{
			struct timespec ts;
			if (TIME_THREAD_ACTIVE == timespec_get(&ts, TIME_THREAD_ACTIVE)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_THR
#	if MU0_HAVE_POSIX1_2001 && MU0_HAVE_DARWIN && defined(CLOCK_THREAD_CPUTIME_ID)
#		undef  MU0_HAVE_NANOTIME_THR
#		define MU0_HAVE_NANOTIME_THR 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_thr__(void)
		{
			return __mu0_const_cast__(___mu0_uint8_t___, clock_gettime_nsec_np(CLOCK_THREAD_CPUTIME_ID));
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_THR
#	if MU0_HAVE_POSIX1_2001 && defined(CLOCK_THREAD_CPUTIME_ID)
#		undef  MU0_HAVE_NANOTIME_THR
#		define MU0_HAVE_NANOTIME_THR 1
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_thr__(void)
		{
			struct timespec ts;
			if (0 == clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts)) {
				return __mu0_const_cast__(___mu0_uint8_t___, (ts.tv_sec * 1000000000L + ts.tv_nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if !MU0_HAVE_NANOTIME_THR
#	if MU0_HAVE_WINDOWS && !MU0_HAVE_MINGW
#		undef  MU0_HAVE_NANOTIME_THR
#		define MU0_HAVE_NANOTIME_THR 1
#		include <processthreadsapi.h>
#		include <realtimeapiset.h>
		__mu0_static_inline__
		const ___mu0_uint8_t___ __mu0_nanotime_thr__(void)
		{
#	if 0
			/* frequency is unknown, let's imagining it is elapsed time. */
			__int64 r;
			if (0 != QueryThreadCycleTime(GetCurrentThread(), &r)) {
				return __mu0_const_cast__(___mu0_uint8_t___, r);
			}
			return 0U;
#	endif
			FILETIME ct, et, kt, ut;
			ULARGE_INTEGER lv;
			__int64 tm, tk, tu, ssec, nsec;
			if (0 != GetThreadTimes(GetCurrentThread(), &ct, &et, &kt, &ut)) {
				lv.LowPart  = kt.dwLowDateTime;
				lv.HighPart = kt.dwHighDateTime;
				tk          = __mu0_const_cast__(__int64, lv.QuadPart);
				lv.LowPart  = ut.dwLowDateTime;
				lv.HighPart = ut.dwHighDateTime;
				tu          = __mu0_const_cast__(__int64, lv.QuadPart);
				tm          = tk + tu;
				ssec        = tm / 10000000i64;
				nsec        = tm % 10000000i64 * 100i64;
				return __mu0_const_cast__(___mu0_uint8_t___, (ssec * 1000000000i64 + nsec));
			}
			return 0U;
		}
#	endif
#	endif

#	if MU0_HAVE_GETTIMEOFDAY && MU0_HAVE_NANOTIME_ABS && MU0_HAVE_NANOTIME_UTC && MU0_HAVE_NANOTIME_ACT && MU0_HAVE_NANOTIME_THR
#	undef  MU0_HAVE_CLOCKTIME
#	define MU0_HAVE_CLOCKTIME    1
#	define __mu0_clocktime_utc__ 1U
#	define __mu0_clocktime_abs__ 2U
#	define __mu0_clocktime_act__ 3U
#	define __mu0_clocktime_thr__ 4U

__mu0_static_inline__
const ___mu0_uint8_t___ __mu0_nanotime__(const ___mu0_uint4_t___ __tid)
{
	___mu0_uint8_t___ tm;
	switch (__tid)
	{
		case __mu0_clocktime_utc__ :
		{
			tm = __mu0_nanotime_utc__();
		}
		break;
		case __mu0_clocktime_abs__ :
		{
			tm = __mu0_nanotime_abs__();
		}
		break;
		case __mu0_clocktime_act__ :
		{
			tm = __mu0_nanotime_act__();
		}
		break;
		case __mu0_clocktime_thr__ :
		{
			tm = __mu0_nanotime_thr__();
		}
		break;
		default:
		{
			tm = 0U;
		}
		break;
	}
	return tm;
}

#	endif

#	if !MU0_HAVE_CLOCKTIME
#		error mu0_clocktime.h
#	endif

#endif /* !MU0_CLOCKTIME_H */

/* EOF */