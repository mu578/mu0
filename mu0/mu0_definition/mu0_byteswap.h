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
#	if MU0_HAVE_CC_GNUC
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    __builtin_bswap16(__x)
#		define __mu0_bswap_32__(__x)    __builtin_bswap32(__x)
#		define __mu0_bswap_64__(__x)    __builtin_bswap64(__x)
#	elif MU0_HAVE_CC_CLANG
#		if (__has_builtin(__builtin_bswap64))
#			undef  MU0_HAVE_BYTESWAP
#			define MU0_HAVE_BYTESWAP     1
#			define __mu0_bswap_16__(__x) __builtin_bswap16(__x)
#			define __mu0_bswap_32__(__x) __builtin_bswap32(__x)
#			define __mu0_bswap_64__(__x) __builtin_bswap64(__x)
#		endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_CC_MSVC
#		include <stdlib.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    _byteswap_ushort(__x)
#		define __mu0_bswap_32__(__x)    _byteswap_ulong(__x)
#		define __mu0_bswap_64__(__x)    _byteswap_uint64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_CC_ICC
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    _bswap16(__x)
#		define __mu0_bswap_32__(__x)    _bswap(__x)
#		define __mu0_bswap_64__(__x)    _bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_MACOSX || MU0_HAVE_IOS
#		include <libkern/OSByteOrder.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    OSSwapInt16(__x)
#		define __mu0_bswap_32__(__x)    OSSwapInt32(__x)
#		define __mu0_bswap_64__(__x)    OSSwapInt64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_SOLARIS
#		include <sys/byteorder.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    BSWAP_16(__x)
#		define __mu0_bswap_32__(__x)    BSWAP_32(__x)
#		define __mu0_bswap_64__(__x)    BSWAP_64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_FREEBSD
#		include <sys/endian.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    bswap16(__x)
#		define __mu0_bswap_32__(__x)    bswap32(__x)
#		define __mu0_bswap_64__(__x)    bswap32(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_OPENBSD
#		include <sys/types.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    swap16(__x)
#		define __mu0_bswap_32__(__x)    swap32(__x)
#		define __mu0_bswap_64__(__x)    swap32(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_NETBSD
#		include <sys/types.h>
#		include <machine/bswap.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    bswap16(__x)
#		define __mu0_bswap_32__(__x)    bswap32(__x)
#		define __mu0_bswap_64__(__x)    bswap64(__x)
#	endif
#	endif

#	if !MU0_HAVE_BYTESWAP
#	if MU0_HAVE_ANDROID || MU0_HAVE_LINUX
#		include <byteswap.h>
#		undef  MU0_HAVE_BYTESWAP
#		define MU0_HAVE_BYTESWAP        1
#		define __mu0_bswap_16__(__x)    bswap_16(__x)
#		define __mu0_bswap_32__(__x)    bswap_32(__x)
#		define __mu0_bswap_64__(__x)    bswap_64(__x)
#	endif
#	endif

#	if MU0_HAVE_BYTESWAP
#	if   __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#		define __mu0_htobe16__(__x)     __mu0_bswap_16__(__x)
#		define __mu0_htole16__(__x)     (__x)
#		define __mu0_be16toh__(__x)     __mu0_bswap_16__(__x)
#		define __mu0_le16toh__(__x)     (__x)
#		define __mu0_htobe32__(__x)     __mu0_bswap_32__(__x)
#		define __mu0_htole32__(__x)     (__x)
#		define __mu0_be32toh__(__x)     __mu0_bswap_32__(__x)
#		define __mu0_le32toh__(__x)     (__x)
#		define __mu0_htobe64__(__x)     __mu0_bswap_64__(__x)
#		define __mu0_htole64__(__x)     (__x)
#		define __mu0_be64toh__(__x)     __mu0_bswap_64__(__x)
#		define __mu0_le64toh__(__x)     (__x)
#	elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#		define __mu0_htobe16__(__x)     (__x)
#		define __mu0_htole16__(__x)     __mu0_bswap_16__(__x)
#		define __mu0_be16toh__(__x)     (__x)
#		define __mu0_le16toh__(__x)     __mu0_bswap_16__(__x)
#		define __mu0_htobe32__(__x)     (__x)
#		define __mu0_htole32__(__x)     __mu0_bswap_32__(__x)
#		define __mu0_be32toh__(__x)     (__x)
#		define __mu0_le32toh__(__x)     __mu0_bswap_32__(__x)
#		define __mu0_htobe64__(__x)     (__x)
#		define __mu0_htole64__(__x)     __mu0_bswap_64__(__x)
#		define __mu0_be64toh__(__x)     (__x)
#		define __mu0_le64toh__(__x)     __mu0_bswap_64__(__x)
#	endif
#	endif

#endif /* !MU0_BYTESWAP_H */

/* EOF */