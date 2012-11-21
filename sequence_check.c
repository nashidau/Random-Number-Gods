#include <check.h>
#include <talloc.h>

#include "rngod.h"
#include "sequence.h"

struct rngod *seq;

static void sequence_init(void) {
	const int initial[] = { 2, 7, 77 };

	seq = rngod_sequence_add(3, initial);
}

static void sequence_shutdown(void) {
	talloc_free(seq);
}

#define RESULT(expected_, seq_)				\
	do {						\
		int res_ = seq_->rand(seq_);		\
		ck_assert_int_eq(expected_, res_);	\
	} while (0)

#define RANGE_RESULT(expected_, seq_, min_, max_)	\
	do {						\
		int res_ = seq_->range(seq_, min_, max_);	\
		ck_assert_int_eq(expected_, res_);	\
	} while (0)

START_TEST(test_seq_create) {
	ck_assert(seq != NULL);
} END_TEST

START_TEST(test_seq_single_value) {
	RESULT(2, seq);
} END_TEST

START_TEST(test_seq_all_values) {
	RESULT(2, seq);
	RESULT(7, seq);
	RESULT(77, seq);
} END_TEST

START_TEST(test_seq_loops) {
	RESULT(2, seq);
	RESULT(7, seq);
	RESULT(77, seq);

	RESULT(2, seq);
	RESULT(7, seq);
	RESULT(77, seq);
} END_TEST

START_TEST(test_seq_repeats_last) {
	ck_assert_int_eq(0, rngod_sequence_loop_set(seq, false));
	RESULT(2, seq);
	RESULT(7, seq);
	RESULT(77, seq);
	RESULT(77, seq);
	RESULT(77, seq);
	RESULT(77, seq);

} END_TEST

START_TEST(test_seq_change_updates) {
	int nvalues[] = { 20, 4, 9,  20, 11, 11 };
	rngod_sequence_sequence_set(seq, 6, nvalues);
	RESULT(20, seq);
	RESULT(4, seq);
	RESULT(9, seq);
	RESULT(20, seq);
	RESULT(11, seq);
	RESULT(11, seq);
	RESULT(20, seq);
} END_TEST

START_TEST(test_seq_change_resets_pos) {
	int nvalues[] = { 20, 4, 9,  20, 11, 11 };

	RESULT(2, seq);
	RESULT(7, seq);

	rngod_sequence_sequence_set(seq, 6, nvalues);

	RESULT(20, seq);
	RESULT(4, seq);
	RESULT(9, seq);
	RESULT(20, seq);
	RESULT(11, seq);
	RESULT(11, seq);
	RESULT(20, seq);
} END_TEST


START_TEST(test_seq_empty_fails) {
	int nvalues[] = { 42 };
	ck_assert_int_eq(-1, rngod_sequence_sequence_set(seq, 0, nvalues));
	ck_assert_int_eq(-1, rngod_sequence_sequence_set(seq, 1, NULL));
} END_TEST

START_TEST(test_seq_single_item) {
	int nvalues[] = { 42 };
	ck_assert_int_eq(0, rngod_sequence_sequence_set(seq, 1, nvalues));
	RESULT(42, seq);
	RESULT(42, seq);
	RESULT(42, seq);
} END_TEST

START_TEST(test_seq_range_sane) {
	int values[] = { 1, 1, 5, 10 };
	rngod_sequence_sequence_set(seq, 4, values);
	RANGE_RESULT(1, seq, 1, 10);
	RANGE_RESULT(1, seq, 0, 3);
	RANGE_RESULT(5, seq, 1, 5);
	RANGE_RESULT(10, seq, 1, 20);
} END_TEST

START_TEST(test_seq_range_outside) {
	int values[] = { 10 };
	rngod_sequence_sequence_set(seq, 1, values);
	RANGE_RESULT(1, seq, 1, 5);
	RANGE_RESULT(3, seq, 1, 4);
	RANGE_RESULT(30, seq, 20, 30);
	RANGE_RESULT(20, seq, 20, 29);
	RANGE_RESULT(15, seq, 13, 20);
} END_TEST

int
sequence_check(Suite *s) {
	TCase *tc_seq = tcase_create("RNG Sequence");

        tcase_add_checked_fixture(tc_seq, sequence_init, sequence_shutdown);
	suite_add_tcase(s, tc_seq);

	tcase_add_test(tc_seq, test_seq_create);
	tcase_add_test(tc_seq, test_seq_single_value);
	tcase_add_test(tc_seq, test_seq_all_values);
	tcase_add_test(tc_seq, test_seq_loops);
	tcase_add_test(tc_seq, test_seq_repeats_last);
	tcase_add_test(tc_seq, test_seq_change_updates);
	tcase_add_test(tc_seq, test_seq_change_resets_pos);
	tcase_add_test(tc_seq, test_seq_empty_fails);
	tcase_add_test(tc_seq, test_seq_single_item);
	tcase_add_test(tc_seq, test_seq_range_sane);
	tcase_add_test(tc_seq, test_seq_range_outside);

	return 0;
}


