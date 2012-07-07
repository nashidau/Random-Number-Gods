

#include <stdbool.h>
#include <stdio.h>
#include <check.h>
#include <talloc.h>

#include "dethread.h"
#include "constant.h"
#include "rngod.h"

int dethread_check(Suite *s);
int constant_check(Suite *s);
int sequence_check(Suite *s);
int randu_check(Suite *s);

struct tests {
	const char *name;
	int (*add)(Suite *);
} tests[] = {
	{ "dethread", dethread_check },
	{ "constant", constant_check },
	{ "sequence", sequence_check },
	{ "randu", randu_check },
};
#define N_TESTS (sizeof(tests)/sizeof(tests[0]))

int
main(int argc, char **argv) {
	bool verbose = false;
	int nfail;
	int i, j;
	Suite *s = suite_create("RNGods");

	if (argv[1] && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "help"))){
		printf("Run RnGod tests\n");
		printf("No arguments to run all tests\n");
		printf("Otherwise specify tests to run\n");
		printf("Available tests:\n");
		for (i = 0 ; i < N_TESTS ; i ++){
			printf("\t%s\n", tests[i].name);
		}
		exit(0);
	}
		
	if (!argv[1]) {
		for (i = 0 ; i < N_TESTS ; i ++){
			tests[i].add(s);
		}
	} else {
		for (i = 1 ; argv[i] ; i ++){
			for (j = 0 ; j < N_TESTS ; j ++) {
				if (strcmp(tests[j].name, argv[i]))
					continue;
				tests[j].add(s);
				break;
			}
			if (j == N_TESTS) {
				printf("Unkown test '%s'\n", argv[i]);
				exit(2);
			}
		}
		verbose = true;
	}

        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, verbose? CK_VERBOSE : CK_NORMAL);
        nfail = srunner_ntests_failed(sr);
        srunner_free(sr);

        if (nfail)
                printf("\e[0;31mFail\e[0;0m\n");
        else
                printf("\e[0;32mPass\e[0;0m\n");

	return !!nfail;
}

