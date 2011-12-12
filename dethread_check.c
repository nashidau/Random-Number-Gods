


#include <stdio.h>
#include <check.h>
#include <talloc.h>

#include "dethread.h"
#include "constant.h"
#include "rngod.h"

struct rngod *dthrd;

static void dethread_init(void) {
	struct rngod *con;

	con = rngod_constant_add_default();
	dthrd = rngod_dethread_add(con);
}

static void dethread_shutdown(void) {
	talloc_free(dthrd);
}

START_TEST(test_d10_returns_seven) {
	ck_assert_int_eq(7, dthrd->dx(dthrd, 10));
} END_TEST

int
dethread_check(Suite *s) {
        TCase *tc_dth = tcase_create("RNG Dethread");
	suite_add_tcase(s, tc_dth);

        tcase_add_checked_fixture(tc_dth, dethread_init, dethread_shutdown);

	tcase_add_test(tc_dth, test_d10_returns_seven);

	return 0;
}


