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

// mu0_byteswap.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_byteorder.h>
#include <mu0/mu0_definition/mu0_platform.h>

#ifndef MU0_BYTESWAP_H
#define MU0_BYTESWAP_H 1

#	undef  MU0_HAVE_BYTESWAP
#	undef  __mu0_bswap_16__
#	undef  __mu0_bswap_32__
#	undef  __mu0_bswap_64__
#	define MU0_HAVE_BYTESWAP 0

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_CC_ARMCC || MU0_HAVE_CC_APLCC || MU0_HAVE_CC_CLANG || MU0_HAVE_CC_GNUCC || MU0_HAVE_CC_MSVCL
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) __builtin_bswap16(__x)
#		define __mu0_bswap_32__(__x) __builtin_bswap32(__x)
#		define __mu0_bswap_64__(__x) __builtin_bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_CC_ITLCC
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) _bswap16(__x)
#		define __mu0_bswap_32__(__x) _bswap(__x)
#		define __mu0_bswap_64__(__x) _bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_CC_MSVCC
#		include <stdlib.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) _byteswap_ushort(__x)
#		define __mu0_bswap_32__(__x) _byteswap_ulong(__x)
#		define __mu0_bswap_64__(__x) _byteswap_uint64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_DARWIN
#		include <libkern/OSByteOrder.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) OSSwapInt16(__x)
#		define __mu0_bswap_32__(__x) OSSwapInt32(__x)
#		define __mu0_bswap_64__(__x) OSSwapInt64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_SOLARIS
#		include <sys/byteorder.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) BSWAP_16(__x)
#		define __mu0_bswap_32__(__x) BSWAP_32(__x)
#		define __mu0_bswap_64__(__x) BSWAP_64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_FREEBSD
#		include <sys/endian.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) bswap16(__x)
#		define __mu0_bswap_32__(__x) bswap32(__x)
#		define __mu0_bswap_64__(__x) bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_OPENBSD
#		include <sys/endian.h>
#		include <sys/types.h>
#		include <endian.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) swap16(__x)
#		define __mu0_bswap_32__(__x) swap32(__x)
#		define __mu0_bswap_64__(__x) swap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_NETBSD
#		include <sys/types.h>
#		include <machine/bswap.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) bswap16(__x)
#		define __mu0_bswap_32__(__x) bswap32(__x)
#		define __mu0_bswap_64__(__x) bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_DRAGONFLYBSD
#		include <sys/endian.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) bswap16(__x)
#		define __mu0_bswap_32__(__x) bswap32(__x)
#		define __mu0_bswap_64__(__x) bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_ANDROID || MU0_HAVE_LINUX || MU0_HAVE_NUTTX
#		include <endian.h>
#		include <byteswap.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) bswap_16(__x)
#		define __mu0_bswap_32__(__x) bswap_32(__x)
#		define __mu0_bswap_64__(__x) bswap_64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_MINIX
#		include <sys/bswap.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP     1
#		define __mu0_bswap_16__(__x) bswap16(__x)
#		define __mu0_bswap_32__(__x) bswap32(__x)
#		define __mu0_bswap_64__(__x) bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP

	__mu0_static_inline__
	const ___mu0_sint2_t___ __mu0_const_bswap16_const__(const ___mu0_sint2_t___ __x)
	{
		___mu0_sint2_t___ y = __x;
		return ((y << 8U) & 0xFF00U) | ((y >> 8U) & 0x00FFU);
	}

	__mu0_static_inline__
	const ___mu0_sint4_t___ __mu0_const_bswap32_const__(const ___mu0_uint4_t___ __x)
	{
		___mu0_uint4_t___ y = __x;
		return (
			  ((y << 24U) & 0xFF000000U)
			| ((y <<  8U) & 0x00FF0000U)
			| ((y >>  8U) & 0x0000FF00U)
			| ((y >> 24U) & 0X000000FFU)
		);
	}

	__mu0_static_inline__
	const ___mu0_sint8_t___ __mu0_const_bswap64_const__(const ___mu0_sint8_t___ __x)
	{
		___mu0_sint8_t___ y = __x;
#		if MU0_HAVE_LP64
#		if MU0_HAVE_C99 || MU0_HAVE_CPP11
		return (
			  ((y << 56U) & 0xFF00000000000000ULL)
			| ((y << 40U) & 0x00FF000000000000ULL)
			| ((y << 24U) & 0x0000FF0000000000ULL)
			| ((y <<  8U) & 0x000000FF00000000ULL)
			| ((y >>  8U) & 0x00000000FF000000ULL)
			| ((y >> 24U) & 0x0000000000FF0000ULL)
			| ((y >> 40U) & 0x000000000000FF00ULL)
			| ((y >> 56U) & 0x00000000000000FFULL)
		);
#		else
		return (
			  ((y << 56U) & 0xFF00000000000000UL)
			| ((y << 40U) & 0x00FF000000000000UL)
			| ((y << 24U) & 0x0000FF0000000000UL)
			| ((y <<  8U) & 0x000000FF00000000UL)
			| ((y >>  8U) & 0x00000000FF000000UL)
			| ((y >> 24U) & 0x0000000000FF0000UL)
			| ((y >> 40U) & 0x000000000000FF00UL)
			| ((y >> 56U) & 0x00000000000000FFUL)
		);
#		endif
#		else
#		if MU0_HAVE_C99 || MU0_HAVE_CPP11
		const ___mu0_sint4_t___ hi = __mu0_const_bswap32_const__(__mu0_const_cast__(___mu0_sint4_t___, ( y         & 0x00000000FFFFFFFFULL)));
		const ___mu0_sint4_t___ lo = __mu0_const_bswap32_const__(__mu0_const_cast__(___mu0_sint4_t___, ((y >> 32U) & 0X00000000FFFFFFFFULL)));
#		else
		const ___mu0_sint4_t___ hi = __mu0_const_bswap32_const__(__mu0_const_cast__(___mu0_sint4_t___, ( y         & 0x00000000FFFFFFFFUL )));
		const ___mu0_sint4_t___ lo = __mu0_const_bswap32_const__(__mu0_const_cast__(___mu0_sint4_t___, ((y >> 32U) & 0X00000000FFFFFFFFUL )));
#		endif
		return (__mu0_const_cast__(___mu0_sint8_t___, hi) << 32U) | lo;
#		endif
	}

#	undef  MU0_HAVE_BYTESWAP
#	define MU0_HAVE_BYTESWAP        1
#	define __mu0_bswap_16__(__x)    __mu0_const_bswap16_const__(__x)
#	define __mu0_bswap_32__(__x)    __mu0_const_bswap32_const__(__x)
#	define __mu0_bswap_64__(__x)    __mu0_const_bswap64_const__(__x)
#	endif

#	if MU0_HAVE_BYTESWAP
#	if   __mu0_byte_order__ == __mu0_order_leen__
#		define __mu0_htobe16__(__x)  __mu0_bswap_16__(__x)
#		define __mu0_htole16__(__x)  (__x)
#		define __mu0_be16toh__(__x)  __mu0_bswap_16__(__x)
#		define __mu0_le16toh__(__x)  (__x)
#		define __mu0_htobe32__(__x)  __mu0_bswap_32__(__x)
#		define __mu0_htole32__(__x)  (__x)
#		define __mu0_be32toh__(__x)  __mu0_bswap_32__(__x)
#		define __mu0_le32toh__(__x)  (__x)
#		define __mu0_htobe64__(__x)  __mu0_bswap_64__(__x)
#		define __mu0_htole64__(__x)  (__x)
#		define __mu0_be64toh__(__x)  __mu0_bswap_64__(__x)
#		define __mu0_le64toh__(__x)  (__x)
#	elif __mu0_byte_order__ == __mu0_order_been__
#		define __mu0_htobe16__(__x)  (__x)
#		define __mu0_htole16__(__x)  __mu0_bswap_16__(__x)
#		define __mu0_be16toh__(__x)  (__x)
#		define __mu0_le16toh__(__x)  __mu0_bswap_16__(__x)
#		define __mu0_htobe32__(__x)  (__x)
#		define __mu0_htole32__(__x)  __mu0_bswap_32__(__x)
#		define __mu0_be32toh__(__x)  (__x)
#		define __mu0_le32toh__(__x)  __mu0_bswap_32__(__x)
#		define __mu0_htobe64__(__x)  (__x)
#		define __mu0_htole64__(__x)  __mu0_bswap_64__(__x)
#		define __mu0_be64toh__(__x)  (__x)
#		define __mu0_le64toh__(__x)  __mu0_bswap_64__(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#		error mu0_byteswap.h
#	endif

#endif /* !MU0_BYTESWAP_H */

/* EOF */