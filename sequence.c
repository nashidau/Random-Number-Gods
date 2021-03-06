/**
 * FIXME: Check that ndx behaves as expected, and adjust if necessary
 */

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "sequence.h"
#include "rngod.h"
#include "rng-private.h"

struct rng_seq {
	struct rngod rng;

	size_t cur;
	bool loop;

	size_t nitems;
	uint64_t *items;
};

static uint64_t
rngod_sequence_method_rand(struct rngod *rng) {
	struct rng_seq *rngs = talloc_get_type(rng, struct rng_seq);

	if (rngs->cur < rngs->nitems) {
		return rngs->items[rngs->cur ++];
	}

	if (rngs->loop) {
		rngs->cur = 0;
		return rngs->items[rngs->cur ++];
	}

	return rngs->items[rngs->nitems - 1];
}

static uint64_t
rngod_sequence_method_range(struct rngod *rng, uint64_t min, uint64_t max) {
	if (!rng) return 0;
	uint64_t val = rng->rand(rng);
	if (val >= min && val <= max) {
		return val;
	}
	int range = max - min + 1;
	val = val % range;
	val += min;
	return val;
}

struct rngod *
rngod_sequence_add(size_t nitems, const uint64_t *items) {
	struct rng_seq *rngs;

	if (nitems < 1 || items == NULL) return NULL;

	rngs = talloc(NULL, struct rng_seq);
	if (!rngs) return NULL;

	rngs->rng.rand = rngod_sequence_method_rand;
	default_init(&rngs->rng);
	rngs->rng.range = rngod_sequence_method_range;
	rngs->loop = true;
	rngs->cur = 0;
	rngs->nitems = 0;
	rngs->items = NULL;

	int rv = rngod_sequence_sequence_set(&rngs->rng, nitems, items);
	if (rv != 0) {
		talloc_free(rngs);
		return NULL;
	}
	return &rngs->rng;
}

int
rngod_sequence_sequence_set(struct rngod *rng, size_t nitems, const uint64_t *items) {
	struct rng_seq *rngs = talloc_get_type(rng, struct rng_seq);
	if (rngs->rng.rand != rngod_sequence_method_rand) {
		return -1;
	}
	if (nitems < 1 || items == NULL) return -1;

	if (rngs->items) talloc_free(rngs->items);

	rngs->items = talloc_array(rngs, uint64_t, nitems);
	if (rngs->items == NULL) {
		rngs->nitems = 0;
		return -1;
	}
	memcpy(rngs->items, items, nitems * sizeof(uint64_t));
	rngs->nitems = nitems;
	rngs->cur = 0;

	return 0;
}

/**
 * Do we repeat the last item, or loop
 */
int
rngod_sequence_loop_set(struct rngod *rng, bool loop) {
	struct rng_seq *rngs = talloc_get_type(rng, struct rng_seq);
	if (rngs->rng.rand != rngod_sequence_method_rand) {
		return -1;
	}

	rngs->loop = loop;
	return 0;
}
