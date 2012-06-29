

#include <stdio.h>
#include <check.h>
#include <talloc.h>

#include "dethread.h"
#include "constant.h"
#include "rngod.h"

int dethread_check(Suite *s);
int constant_check(Suite *s);
int sequence_check(Suite *s);

int
main(int argc, char **argv) {
	int nfail;
	Suite *s = suite_create("RNGods");

	constant_check(s);
        dethread_check(s);
	sequence_check(s);

        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_NORMAL);
        nfail = srunner_ntests_failed(sr);
        srunner_free(sr);

        if (nfail)
                printf("\e[0;31mFail\e[0;0m\n");
        else
                printf("\e[0;32mPass\e[0;0m\n");

	return !!nfail;
}

