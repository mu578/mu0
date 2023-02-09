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

// mu0_attribute.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_compiler.h>

#ifndef MU0_ATTRIBUTE_H
#define MU0_ATTRIBUTE_H 1

MU0_BEGIN_CDECL

#	undef  MU0_HAVE_VOLATILE
#	undef  __mu0_volatile__
#	define MU0_HAVE_VOLATILE 0
#	if 1
#		undef  MU0_HAVE_VOLATILE
#		define MU0_HAVE_VOLATILE 1
#		define __mu0_volatile__  volatile
#	else
#		define __mu0_volatile__ 
#	endif

#	undef  MU0_HAVE_STATIC
#	undef  __mu0_static__
#	define MU0_HAVE_STATIC 0
#	if 1
#		undef  MU0_HAVE_STATIC
#		define MU0_HAVE_STATIC   1
#		define __mu0_static__    static
#	else
#		define __mu0_static__ 
#	endif

#	undef  MU0_HAVE_INLINE
#	undef  __mu0_inline__
#	define MU0_HAVE_INLINE 0
#	if 1
#		undef  MU0_HAVE_INLINE
#		define MU0_HAVE_INLINE   1
#		define __mu0_inline__    inline
#	else
#		define __mu0_inline__
#	endif

#	undef  MU0_HAVE_INLINE_ALWAYS
#	undef  __mu0_inline_always__
#	define MU0_HAVE_INLINE_ALWAYS 0
#	if 1
#		if MU0_HAVE_CC_MSVC
#			undef  MU0_HAVE_INLINE_ALWAYS
#			define MU0_HAVE_INLINE_ALWAYS 1
#			define __mu0_inline_always__ __forceinline
#		elif MU0_HAVE_CC_GNUC || MU0_HAVE_CC_CLANG
#			undef  MU0_HAVE_INLINE_ALWAYS
#			define MU0_HAVE_INLINE_ALWAYS 1
#			define __mu0_inline_always__  __inline__ __attribute__((always_inline))
#		else
#			define __mu0_inline_always__  __mu0_inline__
#		endif
#	else
#		define __mu0_inline_always__ __mu0_inline__
#	endif

#	undef  MU0_HAVE_INLINE_NEVER
#	undef  __mu0_inline_never__
#	define MU0_HAVE_INLINE_NEVER 0
#	if 1
#		if MU0_HAVE_CC_MSVC
#			undef  MU0_HAVE_INLINE_NEVER
#			define MU0_HAVE_INLINE_NEVER 1
#			define __mu0_inline_never__ __declspec(noinline)
#		elif MU0_HAVE_CC_GNUC || MU0_HAVE_CC_CLANG
#			undef  MU0_HAVE_INLINE_NEVER
#			define MU0_HAVE_INLINE_NEVER 1
#			define __mu0_inline_never__  __attribute__((noinline))
#		else
#			define __mu0_inline_never__
#		endif
#	else
#		define __mu0_inline_never__
#	endif

#	undef  MU0_HAVE_STATIC_INLINE
#	undef  __mu0_static_inline__
#	define MU0_HAVE_STATIC_INLINE 0
#	if 1
#		undef  MU0_HAVE_STATIC_INLINE
#		define MU0_HAVE_STATIC_INLINE 1
#		define __mu0_static_inline__  __mu0_static__ __mu0_inline_always__
#	else
#		define __mu0_static_inline__
#	endif

#	undef  MU0_HAVE_OVERLOAD
#	undef  __mu0_overload__
#	define MU0_HAVE_OVERLOAD 0
#	if defined(__clang__)
#		if __has_attribute(__overloadable__)
#			undef  MU0_HAVE_OVERLOAD
#			define MU0_HAVE_OVERLOAD 1
#			define __mu0_overload__  __mu0_static__ __attribute__((__overloadable__, __always_inline__, __unused__))
#		else
#			define __mu0_overload__
#		endif
#	else
#		define __mu0_overload__
#	endif

MU0_END_CDECL

#endif /* !MU0_ATTRIBUTE_H */

/* EOF */