#include <stdio.h>
#include <check.h>
#include <talloc.h>

#include "xorshift.h"
#include "rngod.h"

struct rngod *xorshift;

static void xorsft_init(void) {
	xorshift = rngod_xorshift_add_default();
}

static void xorsft_shutdown(void) {
	talloc_free(xorshift);
}

#define RESULT(expected_, rngod_)                       \
        do {                                            \
                int res_ = rngod_->rand(rngod_);        \
                ck_assert_int_eq(expected_, res_);      \
        } while (0)


START_TEST(test_xorshift_d10) {
	int res = xorshift->dx(xorshift, 10);
	ck_assert_int_eq(5, res);
} END_TEST

START_TEST(test_xorshift_rand) {
	RESULT(-865074372, xorshift);
} END_TEST

START_TEST(test_xorshift_many_rands) {
	RESULT(-865074372, xorshift);
	RESULT(-656381277, xorshift);
	RESULT(-1962388471, xorshift);
	RESULT(-2115155483, xorshift);
	RESULT(-1798967231, xorshift);
	RESULT(1348895040, xorshift);
} END_TEST

START_TEST(test_xorshift_different_seed) {
	struct rngod *lxorshift = rngod_xorshift_add(1,-1,55555555,12345678);
	RESULT(-2079, lxorshift);
	talloc_free(lxorshift);
} END_TEST

int
xorshift_check(Suite *s) {
        TCase *tc_xft = tcase_create("RNG XorShift");
	suite_add_tcase(s, tc_xft);

        tcase_add_checked_fixture(tc_xft, xorsft_init, xorsft_shutdown);

	tcase_add_test(tc_xft, test_xorshift_d10);
	tcase_add_test(tc_xft, test_xorshift_rand);
	tcase_add_test(tc_xft, test_xorshift_many_rands);
	tcase_add_test(tc_xft, test_xorshift_different_seed);

	return 0;
}


