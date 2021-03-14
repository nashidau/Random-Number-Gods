#include <stdbool.h>
#include <stdint.h>

struct rngod;

struct rngod *rngod_sequence_add(size_t nitems, const uint64_t *items);
int rngod_sequence_sequence_set(struct rngod *, size_t nitems, const uint64_t *items);
int rngod_sequence_loop_set(struct rngod *, bool loop);
