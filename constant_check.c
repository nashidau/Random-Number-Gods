


#include <stdio.h>
#include <check.h>

#include "dethread.h"
#include "constant.h"
#include "rng.h"

struct rng *cnst;

static void constant_init(void) {
	cnst = rngod_constant_add_default();
}

static void constant_shutdown(void) {
	rng_free(cnst);
}

START_TEST(test_constant_returns_seven) {
	ck_assert_int_eq(7, cnst->rand(cnst));
} END_TEST

START_TEST(test_constant_d10_returns_seven) {
	ck_assert_int_eq(7, cnst->dx(cnst, 10));
} END_TEST

int
constant_check(Suite *s) {
        TCase *tc_cnst = tcase_create("RNG Constant");
	suite_add_tcase(s, tc_cnst);

        tcase_add_checked_fixture(tc_cnst, constant_init, constant_shutdown);

	tcase_add_test(tc_cnst, test_constant_returns_seven);
	tcase_add_test(tc_cnst, test_constant_d10_returns_seven);

	return 0;
}

