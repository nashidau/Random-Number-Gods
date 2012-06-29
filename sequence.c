#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "sequence.h"
#include "rngod.h"
#include "rng-private.h"

struct rng_seq {
	struct rngod rng;

	int cur;
	bool loop;

	int nitems;
	int *items;
};

static uint32_t
rngod_sequence_method_rand(struct rngod *rng) {
	struct rng_seq *rngs = (struct rng_seq *)rng;

	if (rngs->cur < rngs->nitems) {
		return rngs->items[rngs->cur ++];
	}

	if (rngs->loop) {
		rngs->cur = 0;
		return rngs->items[rngs->cur ++];
	}

	return rngs->items[rngs->nitems - 1];
}

struct rngod *
rngod_sequence_add(int nitems, const int *items) {
	struct rng_seq *rngs;

	if (nitems < 1 || items == NULL) return NULL;

	rngs = talloc(NULL, struct rng_seq);
	if (!rngs) return NULL;

	rngs->rng.rand = rngod_sequence_method_rand;
	default_init(&rngs->rng);
	rngs->loop = true;
	rngs->cur = 0;

	rngod_sequence_sequence_set(&rngs->rng, nitems, items);
	return &rngs->rng;
}

int
rngod_sequence_sequence_set(struct rngod *rng, int nitems, const int *items) {
	struct rng_seq *rngs = (struct rng_seq *)rng;
	if (rngs->rng.rand != rngod_sequence_method_rand) {
		return -1;
	}
	if (nitems < 1 || items == NULL) return -1;

	if (rngs->items) talloc_free(rngs->items);

	rngs->items = talloc_memdup(rngs, items, nitems * sizeof(int));
	if (rngs->items == NULL) {
		rngs->nitems = 0;
		return -1;
	}
	rngs->nitems = nitems;
	rngs->cur = 0;

	return 0;
}

/**
 * Do we repeat the last item, or loop
 */
int
rngod_sequence_loop_set(struct rngod *rng, bool loop) {
	struct rng_seq *rngs = (struct rng_seq *)rng;
	if (rngs->rng.rand != rngod_sequence_method_rand) {
		return -1;
	}

	rngs->loop = loop;
	return 0;
}
