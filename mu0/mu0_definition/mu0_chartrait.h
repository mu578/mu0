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

// mu0_chartrait.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_definition/mu0_byteswap.h>
#include <mu0/mu0_definition/mu0_language.h>

#ifndef MU0_CHARTRAIT_H
#define MU0_CHARTRAIT_H 1

MU0_BEGIN_CDECL

#	if ((MU0_HAVE_C11 || MU0_HAVE_CPP11) && !defined(__APPLE__))
#	include <uchar.h>
typedef char32_t          ___mu0_uchar4_t___;
typedef ___mu0_sint4_t___ ___mu0_schar4_t___;
typedef char32_t          ___mu0_tchar4_t___;

typedef char16_t          ___mu0_uchar2_t___;
typedef ___mu0_sint2_t___ ___mu0_schar2_t___;
typedef char16_t          ___mu0_tchar2_t___;

typedef ___mu0_uint1_t___ ___mu0_uchar1_t___;
typedef ___mu0_sint1_t___ ___mu0_schar1_t___;
typedef ___mu0_tint1_t___ ___mu0_tchar1_t___;
#	else
typedef ___mu0_uint4_t___ ___mu0_uchar4_t___;
typedef ___mu0_sint4_t___ ___mu0_schar4_t___;
typedef ___mu0_uint4_t___ ___mu0_tchar4_t___;

typedef ___mu0_uint2_t___ ___mu0_uchar2_t___;
typedef ___mu0_sint2_t___ ___mu0_schar2_t___;
typedef ___mu0_uint2_t___ ___mu0_tchar2_t___;

typedef ___mu0_uint1_t___ ___mu0_uchar1_t___;
typedef ___mu0_sint1_t___ ___mu0_schar1_t___;
typedef ___mu0_tint1_t___ ___mu0_tchar1_t___;
#	endif

#	define __mu0_cfind_n__(_CharT, __src, __pos, __n, __char, __r)                       \
__mu0_scope_begin__                                                                     \
	___mu0_uint4_t___ __mu0_cfind_n__x__ = 0U;                                           \
	___mu0_sint8_t___ __mu0_cfind_n__p__ = __mu0_const_cast__(___mu0_sint8_t___, __pos); \
	___mu0_sint8_t___ __mu0_cfind_n__n__ = __mu0_const_cast__(___mu0_sint8_t___, __n);   \
	___mu0_sint8_t___ __mu0_cfind_n__i__;                                                \
	if (__mu0_cfind_n__p__ < __mu0_cfind_n__n__) {                                       \
		__r                = __src              + __mu0_cfind_n__p__;                     \
		__mu0_cfind_n__i__ = __mu0_cfind_n__n__ - __mu0_cfind_n__p__;                     \
		for (; __mu0_cfind_n__i__; (void) --__mu0_cfind_n__i__) {                         \
			if (*__r == __char) {                                                          \
				__mu0_cfind_n__x__ = 1U;                                                    \
				break;                                                                      \
			}                                                                              \
			++__r;                                                                         \
		}                                                                                 \
	}                                                                                    \
	if (!__mu0_cfind_n__x__) {                                                           \
		__r = __mu0_nullptr__;                                                            \
	}                                                                                    \
__mu0_scope_end__

#	define __mu0_cfind__(_CharT, __src_first, __src_last, __char, __r)                \
__mu0_scope_begin__                                                                  \
	__mu0_cfind_n__(_CharT, __src_first, 0, (__src_last - __src_first), __char, __r); \
	if (__mu0_is_nullptr__(__r)) {                                                    \
		__r = __src_last;                                                              \
	}                                                                                 \
__mu0_scope_end__

#	define __mu0_slength__(_CharT, __src, __r)                                         \
__mu0_scope_begin__                                                                   \
	const _CharT * __mu0_slength__i__ = __mu0_const_cast__(_CharT *, __src);           \
	const _CharT   __mu0_slength__z__ = __mu0_const_cast__(_CharT  , 0);               \
	__r                               = 0;                                             \
	for (; (*__mu0_slength__i__ != __mu0_slength__z__); (void) ++__mu0_slength__i__) { \
		++__r;                                                                          \
	}                                                                                  \
__mu0_scope_end__

#	define ___mu0_sutfxxto8_n___(_CharxxT, _Char8T, __src, __n, __dest, __endian, __swap_xx, __r)                                    \
__mu0_scope_begin__                                                                                                                 \
	const ___mu0_uint4_t___ ___mu0_sutfxxto8_n___x__ = __mu0_not_nullptr__(__dest) ? 1U : 0U;                                        \
	const _CharxxT *        ___mu0_sutfxxto8_n___i__ = __mu0_const_cast__(_CharxxT *, __src);                                        \
	      _Char8T  *        ___mu0_sutfxxto8_n___j__ = ___mu0_sutfxxto8_n___x__ ? __mu0_cast__(_Char8T *, __dest) : __mu0_nullptr__; \
	      _CharxxT          ___mu0_sutfxxto8_n___g__;                                                                                \
	      ___mu0_sint8_t___ ___mu0_sutfxxto8_n___n__ = __mu0_const_cast__(___mu0_sint8_t___, __n);                                   \
	      ___mu0_uint4_t___ ___mu0_sutfxxto8_n___c__ = 0x0000;                                                                       \
	__r                                              = 0;                                                                            \
	for (; ___mu0_sutfxxto8_n___n__ != 0; --___mu0_sutfxxto8_n___n__) {                                                              \
		___mu0_sutfxxto8_n___g__ = __endian != __mu0_byte_order__ ? __swap_xx(*___mu0_sutfxxto8_n___i__) : *___mu0_sutfxxto8_n___i__; \
		if (___mu0_sutfxxto8_n___g__ >= 0xD800 && ___mu0_sutfxxto8_n___g__ <= 0xDBFF) {                                               \
			___mu0_sutfxxto8_n___c__ = ((___mu0_sutfxxto8_n___g__ - 0xD800) << 0xA) + 0x10000;                                         \
		} else {                                                                                                                      \
			if (___mu0_sutfxxto8_n___g__ >= 0xDC00 && ___mu0_sutfxxto8_n___g__ <= 0xDFFF) {                                            \
				___mu0_sutfxxto8_n___c__ |= ___mu0_sutfxxto8_n___g__ - 0xDC00;                                                          \
			} else {                                                                                                                   \
				___mu0_sutfxxto8_n___c__ = ___mu0_sutfxxto8_n___g__;                                                                    \
			}                                                                                                                          \
			if (___mu0_sutfxxto8_n___c__ <= 0x7F) {                                                                                    \
				if (___mu0_sutfxxto8_n___x__) {                                                                                         \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, ___mu0_sutfxxto8_n___c__);                                   \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
				}                                                                                                                       \
				++__r;                                                                                                                  \
			} else if (___mu0_sutfxxto8_n___c__ <= 0x7FF) {                                                                            \
				if (___mu0_sutfxxto8_n___x__) {                                                                                         \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0xC0 | ((___mu0_sutfxxto8_n___c__ >> 0x6)  & 0x1F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0x80 | (___mu0_sutfxxto8_n___c__           & 0x3F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
				}                                                                                                                       \
				++__r;                                                                                                                  \
				++__r;                                                                                                                  \
			} else if (___mu0_sutfxxto8_n___c__ <= 0xFFFF) {                                                                           \
				if (___mu0_sutfxxto8_n___x__) {                                                                                         \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0xE0 | ((___mu0_sutfxxto8_n___c__ >> 0xC)  & 0x0F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0x80 | ((___mu0_sutfxxto8_n___c__ >> 0x6)  & 0x3F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0x80 | (___mu0_sutfxxto8_n___c__           & 0x3F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
				}                                                                                                                       \
				++__r;                                                                                                                  \
				++__r;                                                                                                                  \
				++__r;                                                                                                                  \
			} else {                                                                                                                   \
				if (___mu0_sutfxxto8_n___x__) {                                                                                         \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0xF0 | ((___mu0_sutfxxto8_n___c__ >> 0x12) & 0x07)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0x80 | ((___mu0_sutfxxto8_n___c__ >> 0xC)  & 0x3F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0x80 | ((___mu0_sutfxxto8_n___c__ >> 0x6)  & 0x3F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
					*___mu0_sutfxxto8_n___j__ = __mu0_const_cast__(_Char8T, (0x80 | (___mu0_sutfxxto8_n___c__           & 0x3F)));       \
					++___mu0_sutfxxto8_n___j__;                                                                                          \
				}                                                                                                                       \
				++__r;                                                                                                                  \
				++__r;                                                                                                                  \
				++__r;                                                                                                                  \
				++__r;                                                                                                                  \
			}                                                                                                                          \
			___mu0_sutfxxto8_n___c__ = 0x0000;                                                                                         \
		}                                                                                                                             \
		++___mu0_sutfxxto8_n___i__;                                                                                                   \
	}                                                                                                                                \
__mu0_scope_end__

#	define __mu0_scmp_n__(_CharT, __src1, __src2, __n, __r)                                         \
__mu0_scope_begin__                                                                                \
	const _CharT *    __mu0_scmp_n__i__ = __mu0_const_cast__(_CharT *, __src1);                     \
	const _CharT *    __mu0_scmp_n__j__ = __mu0_const_cast__(_CharT *, __src2);                     \
	___mu0_sint8_t___ __mu0_scmp_n__n__ = __mu0_const_cast__(___mu0_sint8_t___, __n);               \
	__r                                 = 0;                                                        \
	for (; __mu0_scmp_n__n__ != 0; --__mu0_scmp_n__n__, ++__mu0_scmp_n__i__, ++__mu0_scmp_n__j__) { \
		if (*__mu0_scmp_n__i__ < *__mu0_scmp_n__j__) {                                               \
			__r = -1;                                                                                 \
			break;                                                                                    \
		}                                                                                            \
		if (*__mu0_scmp_n__j__ <  *__mu0_scmp_n__i__) {                                              \
			__r = 1;                                                                                  \
			break;                                                                                    \
		}                                                                                            \
	}                                                                                               \
__mu0_scope_end__

#	define __mu0_cutf8_width__(_Char8T, __char, __r)                                                                   \
__mu0_scope_begin__                                                                                                   \
		const _Char8T           __mu0_cutf8_width__c__ = __mu0_const_cast__(_Char8T, __char);                           \
		const ___mu0_uint1_t___ __mu0_cutf8_width__g__ = __mu0_const_cast__(___mu0_uint1_t___, __mu0_cutf8_width__c__); \
		     if((__mu0_cutf8_width__g__) == 0)                       { __r =  0; }                                      \
		else if((__mu0_cutf8_width__g__ & 0b10000000) == 0)          { __r =  1; }                                      \
		else if((__mu0_cutf8_width__g__ & 0b11100000) == 0b11000000) { __r =  2; }                                      \
		else if((__mu0_cutf8_width__g__ & 0b11110000) == 0b11100000) { __r =  3; }                                      \
		else if((__mu0_cutf8_width__g__ & 0b11111000) == 0b11110000) { __r =  4; }                                      \
		else                                                         { __r = -1; }                                      \
__mu0_scope_end__

#	define __mu0_sutf8_width__(_Char8T, __src_first, __src_last, __r)                             \
__mu0_scope_begin__                                                                              \
	const _CharT *          __mu0_sutf8_width__i__ = __mu0_const_cast__(_Char8T  *, __src_first); \
	      ___mu0_sint8_t___ __mu0_sutf8_width__n__ = __src_last - __src_first;                    \
	      ___mu0_sint2_t___ __mu0_sutf8_width__w__;                                               \
	      ___mu0_sint8_t___ __mu0_sutf8_width__v__ = 0;                                           \
	while (__mu0_sutf8_width__i__ != __src_last && __mu0_sutf8_width__n__) {                      \
		__mu0_cutf8_width__(_Char8T, *__mu0_sutf8_width__i__, __mu0_sutf8_width__w__);             \
		if (__mu0_sutf8_width__w__ < 0) {                                                          \
			__mu0_sutf8_width__v__ = -1                                                             \
			break;                                                                                  \
		}                                                                                          \
		if (!__mu0_sutf8_width__w__) {                                                             \
			break;                                                                                  \
		}                                                                                          \
		++__mu0_sutf8_width__v__;                                                                  \
		--__mu0_sutf8_width__n__;                                                                  \
		__mu0_sutf8_width__i__ = __mu0_sutf8_width__i__ + __mu0_sutf8_width__w__;                  \
	}                                                                                             \
	__r                                            = __mu0_sutf8_width__v__;                      \
__mu0_scope_end__

#	define __mu0_sutf8_utf16_width__(_Char8T, __src_first, __src_last, __r)                        \
__mu0_scope_begin__                                                                               \
	const _CharT *          __mu0_sutf8_utf16_width__i__ = __src_first;                            \
	      ___mu0_sint8_t___ __mu0_sutf8_utf16_width__v__ = 0;                                      \
	      ___mu0_uint1_t___ __mu0_sutf8_utf16_width__c__ ;                                         \
	while (__mu0_sutf8_width__i__ != __src_last) {                                                 \
		__mu0_sutf8_utf16_width__c__  = __mu0_const_cast__(_Char8T, *__mu0_sutf8_width__i__);       \
		__mu0_sutf8_utf16_width__v__ += ((__mu0_sutf8_utf16_width__c__  - 0x80U) >= 0x40U) ? 1 : 0; \
		__mu0_sutf8_utf16_width__v__ += ((__mu0_sutf8_utf16_width__c__)          >= 0xF0U) ? 1 : 0; \
		++__mu0_sutf8_width__i__;                                                                   \
	}                                                                                              \
	__r                                                  = __mu0_sutf8_utf16_width__v__;           \
__mu0_scope_end__

#	define __mu0_sutf8_utf32_width__(_Char8T, __src_first, __src_last, __r) \
	__mu0_sutf8_width__(_Char8T, __src_first, __src_last, __r)

#	define __mu0_sutf8_to_utf32__(_Char8T, _Char32T, __src_first, __src_last, __dest_first)                         \
__mu0_scope_begin__                                                                                                \
	const _Char8T  *        __mu0_sutf8_to_utf32__i__ = __mu0_const_cast__(_Char8T  *, __src_first);                \
	const _Char32T *        __mu0_sutf8_to_utf32__j__ = __mu0_const_cast__(_Char32T *, __dest_first);               \
	      ___mu0_sint2_t___ __mu0_sutf8_to_utf32__k__;                                                              \
	      ___mu0_uint1_t___ __mu0_sutf8_to_utf32__c0__;                                                             \
	      ___mu0_uint1_t___ __mu0_sutf8_to_utf32__c1__;                                                             \
	      ___mu0_uint1_t___ __mu0_sutf8_to_utf32__c2__;                                                             \
	      ___mu0_uint1_t___ __mu0_sutf8_to_utf32__c3__;                                                             \
	while (__mu0_sutf8_to_utf32__i__ != __src_last) {                                                               \
		__mu0_cutf8_width__(_Char8T, *__mu0_sutf8_to_utf32__i__, __mu0_sutf8_to_utf32__k__);                         \
		switch (__mu0_sutf8_to_utf32__k__)                                                                           \
		{                                                                                                            \
			case 4 :                                                                                                  \
			{                                                                                                         \
				__mu0_sutf8_to_utf32__c0__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 0U)); \
				__mu0_sutf8_to_utf32__c1__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 1U)); \
				__mu0_sutf8_to_utf32__c2__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 2U)); \
				__mu0_sutf8_to_utf32__c3__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 3U)); \
				*__mu0_sutf8_to_utf32__j__ = (                                                                         \
					  (__mu0_sutf8_to_utf32__c0__ & ~0b11111000) << 18U                                                 \
					| (__mu0_sutf8_to_utf32__c1__ &  0b00111111) << 12U                                                 \
					| (__mu0_sutf8_to_utf32__c2__ &  0b00111111) <<  6U                                                 \
					| (__mu0_sutf8_to_utf32__c3__ &  0b00111111)                                                        \
				);                                                                                                     \
			}                                                                                                         \
			break;                                                                                                    \
			case 3 :                                                                                                  \
			{                                                                                                         \
				__mu0_sutf8_to_utf32__c0__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 0U)); \
				__mu0_sutf8_to_utf32__c1__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 1U)); \
				__mu0_sutf8_to_utf32__c2__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 2U)); \
				*__mu0_sutf8_to_utf32__j__ = (                                                                         \
					  (__mu0_sutf8_to_utf32__c0__ & ~0b11110000) << 12U                                                 \
					| (__mu0_sutf8_to_utf32__c1__ &  0b00111111) <<  6U                                                 \
					| (__mu0_sutf8_to_utf32__c2__ &  0b00111111)                                                        \
				);                                                                                                     \
			}                                                                                                         \
			break;                                                                                                    \
			case 2 :                                                                                                  \
			{                                                                                                         \
				__mu0_sutf8_to_utf32__c0__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 0U)); \
				__mu0_sutf8_to_utf32__c1__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 1U)); \
				*__mu0_sutf8_to_utf32__j__ = (                                                                         \
					  (__mu0_sutf8_to_utf32__c0__ & ~0b11100000) <<  6U                                                 \
					| (__mu0_sutf8_to_utf32__c1__ &  0b00111111)                                                        \
				);                                                                                                     \
			}                                                                                                         \
			break;                                                                                                    \
			case 1 :                                                                                                  \
			{                                                                                                         \
				__mu0_sutf8_to_utf32__c0__ = __mu0_const_cast__(___mu0_uint1_t___, *(__mu0_sutf8_to_utf32__i__ + 0U)); \
				*__mu0_sutf8_to_utf32__j__ = (                                                                         \
					  (__mu0_sutf8_to_utf32__c0__ & ~0b10000000)                                                        \
				);                                                                                                     \
			}                                                                                                         \
			break;                                                                                                    \
			default:                                                                                                  \
			{ /***/ }                                                                                                 \
			break;                                                                                                    \
		}                                                                                                            \
		if (__mu0_sutf8_to_utf32__k__ < 0) {                                                                         \
			break;                                                                                                    \
		}                                                                                                            \
		if (!__mu0_sutf8_to_utf32__k__) {                                                                            \
			break;                                                                                                    \
		}                                                                                                            \
		__mu0_sutf8_to_utf32__i__ = __mu0_sutf8_to_utf32__i__ + __mu0_sutf8_to_utf32__k__;                           \
		++__mu0_sutf8_to_utf32__j__;                                                                                 \
	}                                                                                                               \
__mu0_scope_end__

#	define __mu0_sutf8to32_n__(_Char8T, _Char32T, __src, __n, __dest, __endian, __r)                                                               \
__mu0_scope_begin__                                                                                                                               \
	const ___mu0_uint4_t___ __mu0_sutf8to32_n__x__ = __mu0_not_nullptr__(__dest) ? 1U : 0U;                                                        \
	const _Char8T  *        __mu0_sutf8to32_n__i__ = __mu0_const_cast__(_Char8T *, __src);                                                         \
	      _Char32T *        __mu0_sutf8to32_n__j__ = __mu0_sutf8to32_n__x__ ? __mu0_cast__(_Char32T *, __dest) : __mu0_nullptr__;                  \
	      ___mu0_sint8_t___ __mu0_sutf8to32_n__n__ = __mu0_const_cast__(___mu0_sint8_t___, __n);                                                   \
	      ___mu0_uint4_t___ __mu0_sutf8to32_n__w__ = 0x0000U;                                                                                      \
	      ___mu0_uint1_t___ __mu0_sutf8to32_n__c__;                                                                                                \
	__r                                            = 0;                                                                                            \
	for (; __mu0_sutf8to32_n__n__ != 0; --__mu0_sutf8to32_n__n__) {                                                                                \
		__mu0_sutf8to32_n__c__ = __mu0_const_cast__(___mu0_uint1_t___, *__mu0_sutf8to32_n__i__);                                                    \
		     if (__mu0_sutf8to32_n__c__ <= 0x7FU) { __mu0_sutf8to32_n__w__ = __mu0_sutf8to32_n__c__;                                              } \
		else if (__mu0_sutf8to32_n__c__ <= 0xBFU) { __mu0_sutf8to32_n__w__ = (__mu0_sutf8to32_n__w__ << 0x6U) | (__mu0_sutf8to32_n__c__ & 0x3FU); } \
		else if (__mu0_sutf8to32_n__c__ <= 0xDFU) { __mu0_sutf8to32_n__w__ = __mu0_sutf8to32_n__c__ & 0x1FU;                                      } \
		else if (__mu0_sutf8to32_n__c__ <= 0xEFU) { __mu0_sutf8to32_n__w__ = __mu0_sutf8to32_n__c__ & 0x0FU;                                      } \
		else                                      { __mu0_sutf8to32_n__w__ = __mu0_sutf8to32_n__c__ & 0x07U;                                      } \
		++__mu0_sutf8to32_n__i__;                                                                                                                   \
		if (((*__mu0_sutf8to32_n__i__ & 0xC0U) != 0x80U) && (__mu0_sutf8to32_n__w__ <= 0x10FFFFU)) {                                                \
			if (__mu0_sutf8to32_n__x__) {                                                                                                            \
				__mu0_sutf8to32_n__w__  = __endian != __mu0_byte_order__ ? __mu0_bswap_32__(__mu0_sutf8to32_n__w__) : __mu0_sutf8to32_n__w__;         \
				*__mu0_sutf8to32_n__j__ = __mu0_const_cast__(_Char32T, __mu0_sutf8to32_n__w__);                                                       \
				++__mu0_sutf8to32_n__j__;                                                                                                             \
			}                                                                                                                                        \
			++__r;                                                                                                                                   \
		}                                                                                                                                           \
	}                                                                                                                                              \
__mu0_scope_end__

#	define __mu0_sutf8to32__(_Char8T, _Char32T, __src_first, __src_last, __dest_first, __endian, _r)                                       \
__mu0_scope_begin__                                                                                                                       \
	_Char32T *        __mu0_sutf8to32__p__ = __dest_first;                                                                                 \
	_Char32T *        __mu0_sutf8to32__q__ = __mu0_nullptr__;                                                                              \
	___mu0_sint8_t___ __mu0_sutf8to32__r__, __mu0_sutf8to32__i__;                                                                          \
	__mu0_sutf8to32_n__(_Char8T, _Char32T, __src_first, (__src_last - __src_first), __mu0_sutf8to32__p__, __endian, __mu0_sutf8to32__r__); \
	if (__mu0_not_nullptr__(__mu0_sutf8to32__p__)) {                                                                                       \
		__mu0_sutf8to32__q__ = __mu0_sutf8to32__p__ + __mu0_sutf8to32__r__;                                                                 \
	}                                                                                                                                      \
	_r = __mu0_sutf8to32__q__;                                                                                                             \
__mu0_scope_end__

#	define __mu0_sutf32to8_n__(_Char32T, _Char8T, __src, __n, __dest, __endian, __r) \
	___mu0_sutfxxto8_n___(_Char32T, _Char8T, __src, __n, __dest, __endian, __mu0_bswap_32__, __r)

#	define __mu0_sutf32to8__(_Char32T, _Char8T, __src_first, __src_last, __dest_first, __endian, __r) \
__mu0_scope_begin__                                                                                                                       \
	_Char8T *         __mu0_sutf32to8__p__ = __dest_first;                                                                                 \
	_Char8T *         __mu0_sutf32to8__q__ = __mu0_nullptr__;                                                                              \
	___mu0_sint8_t___ __mu0_sutf32to8__r__, __mu0_sutf32to8__i__;                                                                          \
	__mu0_sutf32to8_n__(_Char32T, _Char8T, __src_first, (__src_last - __src_first), __mu0_sutf32to8__p__, __endian, __mu0_sutf32to8__r__); \
	if (__mu0_not_nullptr__(__mu0_sutf32to8__p__)) {                                                                                       \
		__mu0_sutf32to8__q__ = __mu0_sutf32to8__p__ + __mu0_sutf32to8__r__;                                                                 \
	}                                                                                                                                      \
	_r = __mu0_sutf32to8__q__;                                                                                                             \
__mu0_scope_end__

#	define __mu0_sutf8to16_n__(_Char8T, _Char16T, __src, __n, __dest, __endian, __r)                                                               \
__mu0_scope_begin__                                                                                                                               \
	const ___mu0_uint4_t___ __mu0_sutf8to16_n__x__ = __mu0_not_nullptr__(__dest) ? 1U : 0U;                                                        \
	const _Char8T  *        __mu0_sutf8to16_n__i__ = __mu0_const_cast__(_Char8T *, __src);                                                         \
	      _Char16T *        __mu0_sutf8to16_n__j__ = __mu0_sutf8to16_n__x__ ? __mu0_cast__(_Char16T *, __dest) : __mu0_nullptr__;                  \
	      _Char16T          __mu0_sutf8to16_n__g__;                                                                                                \
	      ___mu0_sint8_t___ __mu0_sutf8to16_n__n__ = __mu0_const_cast__(___mu0_sint8_t___, __n);                                                   \
	      ___mu0_uint4_t___ __mu0_sutf8to16_n__w__ = 0x0000U;                                                                                      \
	      ___mu0_uint1_t___ __mu0_sutf8to16_n__c__;                                                                                                \
	__r                                            = 0;                                                                                            \
	for (; __mu0_sutf8to16_n__n__ != 0; --__mu0_sutf8to16_n__n__) {                                                                                \
		__mu0_sutf8to16_n__c__ = __mu0_const_cast__(___mu0_uint1_t___, *__mu0_sutf8to16_n__i__);                                                    \
		     if (__mu0_sutf8to16_n__c__ <= 0x7FU) { __mu0_sutf8to16_n__w__ = __mu0_sutf8to16_n__c__;                                              } \
		else if (__mu0_sutf8to16_n__c__ <= 0xBFU) { __mu0_sutf8to16_n__w__ = (__mu0_sutf8to16_n__w__ << 0x6U) | (__mu0_sutf8to16_n__c__ & 0x3FU); } \
		else if (__mu0_sutf8to16_n__c__ <= 0xDFU) { __mu0_sutf8to16_n__w__ = __mu0_sutf8to16_n__c__ & 0x1FU;                                      } \
		else if (__mu0_sutf8to16_n__c__ <= 0xEFU) { __mu0_sutf8to16_n__w__ = __mu0_sutf8to16_n__c__ & 0x0FU;                                      } \
		else                                      { __mu0_sutf8to16_n__w__ = __mu0_sutf8to16_n__c__ & 0x07U;                                      } \
		++__mu0_sutf8to16_n__i__;                                                                                                                   \
		if (((*__mu0_sutf8to16_n__i__ & 0xC0U) != 0x80U) && (__mu0_sutf8to16_n__w__ <= 0x10FFFFU)) {                                                \
			if (__mu0_sutf8to16_n__w__ > 0xFFFFU) {                                                                                                  \
				if (__mu0_sutf8to16_n__x__) {                                                                                                         \
					 __mu0_sutf8to16_n__g__ = __mu0_const_cast__(_Char16T, (0xD800U + ((__mu0_sutf8to16_n__w__ - 0x10000U) >> 0xAU)));                 \
					*__mu0_sutf8to16_n__j__ = __endian != __mu0_byte_order__ ? __mu0_bswap_16__(__mu0_sutf8to16_n__g__) : __mu0_sutf8to16_n__g__;      \
					++__mu0_sutf8to16_n__j__;                                                                                                          \
					 __mu0_sutf8to16_n__g__ = __mu0_const_cast__(_Char16T, (0xDC00U + ((__mu0_sutf8to16_n__w__ - 0x10000U) & 0x03FFU)));               \
					*__mu0_sutf8to16_n__j__ = __endian != __mu0_byte_order__ ? __mu0_bswap_16__(__mu0_sutf8to16_n__g__) : __mu0_sutf8to16_n__g__;      \
					++__mu0_sutf8to16_n__j__;                                                                                                          \
				}                                                                                                                                     \
				++__r;                                                                                                                                \
				++__r;                                                                                                                                \
			} else if (__mu0_sutf8to16_n__w__ < 0xD800U || __mu0_sutf8to16_n__w__ >= 0xE000U) {                                                      \
				if (__mu0_sutf8to16_n__x__) {                                                                                                         \
					 __mu0_sutf8to16_n__g__ = __mu0_const_cast__(_Char16T, __mu0_sutf8to16_n__w__);                                                    \
					*__mu0_sutf8to16_n__j__ = __endian != __mu0_byte_order__ ? __mu0_bswap_16__(__mu0_sutf8to16_n__g__) : __mu0_sutf8to16_n__g__;      \
					++__mu0_sutf8to16_n__j__;                                                                                                          \
				}                                                                                                                                     \
				++__r;                                                                                                                                \
			} else {                                                                                                                                 \
				__r = 0;                                                                                                                              \
				break;                                                                                                                                \
			}                                                                                                                                        \
		}                                                                                                                                           \
	}                                                                                                                                              \
__mu0_scope_end__

#	define __mu0_sutf8to16__(_Char8T, _Char16T, __src_first, __src_last, __dest_first, __endian, _r)                                       \
__mu0_scope_begin__                                                                                                                       \
	_Char16T *        __mu0_sutf8to16__p__ = __dest_first;                                                                                 \
	_Char16T *        __mu0_sutf8to16__q__ = __mu0_nullptr__;                                                                              \
	___mu0_sint8_t___ __mu0_sutf8to16__r__, __mu0_sutf8to16__i__;                                                                          \
	__mu0_sutf8to16_n__(_Char8T, _Char16T, __src_first, (__src_last - __src_first), __mu0_sutf8to16__p__, __endian, __mu0_sutf8to16__r__); \
	if (__mu0_not_nullptr__(__mu0_sutf8to16__p__)) {                                                                                       \
		__mu0_sutf8to16__q__ = __mu0_sutf8to16__p__ + __mu0_sutf8to16__r__;                                                                 \
	}                                                                                                                                      \
	_r = __mu0_sutf8to16__q__;                                                                                                             \
__mu0_scope_end__

#	define __mu0_sutf16to8_n__(_Char16T, _Char8T, __src, __n, __dest, __endian, __r) \
	___mu0_sutfxxto8_n___(_Char16T, _Char8T, __src, __n, __dest, __endian, __mu0_bswap_16__, __r)

#	define __mu0_sutf16to8__(_Char16T, _Char8T, __src_first, __src_last, __dest_first, __endian, __r) \
__mu0_scope_begin__                                                                                                                       \
	_Char8T *         __mu0_sutf16to8__p__ = __dest_first;                                                                                 \
	_Char8T *         __mu0_sutf16to8__q__ = __mu0_nullptr__;                                                                              \
	___mu0_sint8_t___ __mu0_sutf16to8__r__, __mu0_sutf16to8__i__;                                                                          \
	__mu0_sutf16to8_n__(_Char16T, _Char8T, __src_first, (__src_last - __src_first), __mu0_sutf16to8__p__, __endian, __mu0_sutf16to8__r__); \
	if (__mu0_not_nullptr__(__mu0_sutf16to8__p__)) {                                                                                       \
		__mu0_sutf16to8__q__ = __mu0_sutf16to8__p__ + __mu0_sutf16to8__r__;                                                                 \
	}                                                                                                                                      \
	_r = __mu0_sutf16to8__q__;                                                                                                             \
__mu0_scope_end__

MU0_END_CDECL

#endif /* !MU0_CHARTRAIT_H */

/* EOF */