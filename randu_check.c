#include <check.h>
#include <talloc.h>

#include "rngod.h"
#include "randu.h"

struct rngod *randu;

static void randu_init(void) {
	randu = rngod_randu_add_default();
}

static void randu_shutdown(void) {
	talloc_free(randu);
}

#define RESULT(expected_, randu_)				\
	do {						\
		int res_ = randu_->rand(randu_);		\
		ck_assert_int_eq(expected_, res_);	\
	} while (0)


START_TEST(test_randu_create) {
	ck_assert(randu != NULL);
} END_TEST

START_TEST(test_randu_single_value) {
	RESULT(2, randu);
} END_TEST

START_TEST(test_randu_many_values) {
	RESULT(2, randu);
	RESULT(7, randu);
	RESULT(77, randu);
	RESULT(77, randu);
	RESULT(77, randu);
	RESULT(77, randu);
} END_TEST

int
randu_check(Suite *s) {
	TCase *tc_randu = tcase_create("RNG Randu");

        tcase_add_checked_fixture(tc_randu, randu_init, randu_shutdown);
	suite_add_tcase(s, tc_randu);

	tcase_add_test(tc_randu, test_randu_create);
	tcase_add_test(tc_randu, test_randu_single_value);
	tcase_add_test(tc_randu, test_randu_many_values);

	return 0;
}


