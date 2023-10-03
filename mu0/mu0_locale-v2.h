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

// mu0_locale-v2.h
//
// Copyright (C) 2023 mu578. All rights reserved.
//

#include <mu0/mu0_integer.h>
#include <mu0/mu0_string.h>

#ifndef MU0_LOCALE_V2_H
#define MU0_LOCALE_V2_H 1

MU0_BEGIN_CDECL

#	define __mu0_i18nlocale_group_collator__  (1U << 1U)
#	define __mu0_i18nlocale_group_monetary__  (1U << 2U)
#	define __mu0_i18nlocale_group_numerics__  (1U << 3U)
#	define __mu0_i18nlocale_group_datetime__  (1U << 4U)
#	define __mu0_i18nlocale_group_telephone__ (1U << 5U)
#	define __mu0_i18nlocale_group_addresses__ (1U << 6U)

enum mu0_locale_group
{
	  mu0_locale_group_collator  = __mu0_i18nlocale_group_collator__
	, mu0_locale_group_monetary  = __mu0_i18nlocale_group_monetary__
	, mu0_locale_group_numerics  = __mu0_i18nlocale_group_numerics__
	, mu0_locale_group_datetime  = __mu0_i18nlocale_group_datetime__
	, mu0_locale_group_telephone = __mu0_i18nlocale_group_telephone__
	, mu0_locale_group_addresses = __mu0_i18nlocale_group_addresses__
};

typedef mu0_uint32_t         mu0_locale_grouping_t;
typedef __mu0_i18nlocale_t__ mu0_locale_t;

mu0_integral_constant(mu0_locale_grouping_t , mu0_locale_grouping_language
	, ( mu0_locale_group_collator
	  | mu0_locale_group_numerics
));

mu0_integral_constant(mu0_locale_grouping_t , mu0_locale_grouping_territory
	, ( mu0_locale_group_monetary
	  | mu0_locale_group_datetime
	  | mu0_locale_group_telephone
	  | mu0_locale_group_addresses
));

mu0_integral_constant(mu0_locale_grouping_t , mu0_locale_grouping_complete
	, ( mu0_locale_group_collator
	  | mu0_locale_group_numerics
	  | mu0_locale_group_monetary
	  | mu0_locale_group_datetime
	  | mu0_locale_group_telephone
	  | mu0_locale_group_addresses
));

mu0_locale_t *       mu0_locale_create     (
	  const mu0_tchar8_t *        language
	, const mu0_tchar8_t *        territory
	, const mu0_tchar8_t *        modifier  __mu0_nullable__
	, const mu0_locale_grouping_t grouping
);

mu0_sint32_t         mu0_locale_global     (
	  const mu0_locale_t * locale __mu0_nullable__
);

mu0_sint32_t         mu0_locale_interface  (
	  mu0_locale_t ** language
	, mu0_locale_t ** territory __mu0_nullable__
);

const mu0_tchar8_t * mu0_locale_identifier (
	  const enum mu0_locale_group group
	, const      mu0_locale_t *   locale __mu0_nullable__
);

mu0_sint32_t         mu0_locale_delete     (
	mu0_locale_t * locale
);

enum mu0_ordering    mu0_locale_compare    (
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_locale_t * locale __mu0_nullable__
);

enum mu0_ordering    mu0_locale_compare_n  (
	  const mu0_tchar8_t * lhs
	, const mu0_tchar8_t * rhs
	, const mu0_uint32_t   n
	, const mu0_locale_t * locale __mu0_nullable__
);

MU0_END_CDECL

#endif /* !MU0_LOCALE_V2_H */

/* EOF */