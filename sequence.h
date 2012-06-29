#include <stdbool.h>
#include <stdint.h>

struct rngod;

struct rngod *rngod_sequence_add(int nitems, const int *items);
int rngod_sequence_sequence_set(struct rngod *, int nitems, const int *items);
int rngod_sequence_loop_set(struct rngod *, bool loop);
