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
	tcase_add_test(tc_seq, test_seq_empty_fails);
	tcase_add_test(tc_seq, test_seq_single_item);

	return 0;
}

