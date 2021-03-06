#include <stdio.h>
#include <check.h>

#include "dethread.h"
#include "constant.h"
#include "rngod.h"

struct rngod *cnst;

static void constant_init(void) {
	cnst = rngod_constant_add_default();
}

static void constant_shutdown(void) {
	rng_free(cnst);
}

START_TEST(test_constant_returns_seven) {
	ck_assert_uint_eq(7, cnst->rand(cnst));
} END_TEST

START_TEST(test_constant_d10_returns_seven) {
	ck_assert_uint_eq(7, cnst->dx(cnst, 10));
} END_TEST

START_TEST(test_constant_d5_returns_five) {
	ck_assert_uint_eq(5, cnst->dx(cnst, 5));
} END_TEST

START_TEST(test_constant_zero_returns_one) {
	struct rngod *zcnst = rngod_constant_add(0);
	ck_assert_uint_eq(1, zcnst->dx(zcnst, 5));
} END_TEST

START_TEST(test_constant_range_returns_value) {
	ck_assert_uint_eq(7, cnst->range(cnst, 0, 10));
} END_TEST

START_TEST(test_constant_range_returns_min) {
	ck_assert_uint_eq(10, cnst->range(cnst, 10,  20));
} END_TEST

START_TEST(test_constant_range_returns_max) {
	ck_assert_uint_eq(5, cnst->range(cnst, 3, 5));
} END_TEST

START_TEST(test_constant_ndx) {
	ck_assert_uint_eq(35, cnst->ndx(cnst, 5, 10));
} END_TEST

START_TEST(test_constant_ndx_overflow) {
	ck_assert_uint_eq(50, cnst->ndx(cnst, 10, 5));
} END_TEST

START_TEST(test_constant_change_value) {
	ck_assert_uint_eq(7, cnst->rand(cnst));
	rngod_constant_constant_set(cnst, 99);
	ck_assert_uint_eq(99, cnst->rand(cnst));
} END_TEST

int
constant_check(Suite *s) {
        TCase *tc_cnst = tcase_create("RNG Constant");
	suite_add_tcase(s, tc_cnst);

        tcase_add_checked_fixture(tc_cnst, constant_init, constant_shutdown);

	tcase_add_test(tc_cnst, test_constant_returns_seven);
	tcase_add_test(tc_cnst, test_constant_d10_returns_seven);
	tcase_add_test(tc_cnst, test_constant_d5_returns_five);
	tcase_add_test(tc_cnst, test_constant_zero_returns_one);
	tcase_add_test(tc_cnst, test_constant_range_returns_value);
	tcase_add_test(tc_cnst, test_constant_range_returns_min);
	tcase_add_test(tc_cnst, test_constant_range_returns_max);
	tcase_add_test(tc_cnst, test_constant_ndx);
	tcase_add_test(tc_cnst, test_constant_ndx_overflow);

	tcase_add_test(tc_cnst, test_constant_change_value);

	return 0;
}

