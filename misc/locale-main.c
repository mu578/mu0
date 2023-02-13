#include <mu0/mu0_locale.h>
#include <stdio.h>

int main(int argc, const char * argv[])
{
	const mu0_string8_t s1 = u8"éducation";
	const mu0_string8_t s2 = u8"Education";

	const mu0_string8_t s3 = u8"érudition";
	const mu0_string8_t s4 = u8"Érudition";

	mu0_locale_t locale;

	mu0_unused(argc);
	mu0_unused(argv);

	printf("\n");

	printf("%p \n", (locale = mu0_locale_create("fr", "FR", mu0_nullptr, mu0_true)));
	printf("%02d s1 <> s1\n", mu0_locale_compare(s1, s1, locale));
	printf("%02d s1 <> s2\n", mu0_locale_compare(s1, s2, locale));
	printf("%02d s1 <> s2\n", mu0_locale_compare(s2, s1, locale));
	printf("%02d s3 <> s4\n", mu0_locale_compare(s3, s4, locale));
	printf("%02d s4 <> s3\n", mu0_locale_compare(s4, s3, locale));
	printf("%02d \n", mu0_locale_delete(locale));

	printf("\n");

	printf("%02d \n", mu0_locale_global("fr", "FR", mu0_nullptr, mu0_true));
	printf("%02d s1 <> s1\n", mu0_locale_compare(s1, s1, mu0_nullptr));
	printf("%02d s1 <> s2\n", mu0_locale_compare(s1, s2, mu0_nullptr));
	printf("%02d s1 <> s2\n", mu0_locale_compare(s2, s1, mu0_nullptr));
	printf("%02d s3 <> s4\n", mu0_locale_compare(s3, s4, mu0_nullptr));
	printf("%02d s4 <> s3\n", mu0_locale_compare(s4, s3, mu0_nullptr));

	printf("\n");

	printf("%02d \n", mu0_locale_global("en", "US", mu0_nullptr, mu0_true));
	printf("%02d s1 <> s1\n", mu0_locale_compare(s1, s1, mu0_nullptr));
	printf("%02d s1 <> s2\n", mu0_locale_compare(s1, s2, mu0_nullptr));
	printf("%02d s1 <> s2\n", mu0_locale_compare(s2, s1, mu0_nullptr));
	printf("%02d s3 <> s4\n", mu0_locale_compare(s3, s4, mu0_nullptr));
	printf("%02d s4 <> s3\n", mu0_locale_compare(s4, s3, mu0_nullptr));

	printf("\n");

	return 0;
}

/* EOF */