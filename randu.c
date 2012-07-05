#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "randu.h"
#include "rngod.h"
#include "rng-private.h"

struct rng_randu {
	struct rngod rng;

	uint32_t val;
};

static uint32_t
rngod_randu_method_rand(struct rngod *rng) {
	// FIXME: use talloc
	struct rng_randu *rngr = (struct rng_randu *)rng;

	rngr->val = ((rngr->val << 16) + (rngr->val << 1) + rngr->val) &
		0x7fffffff;

	return rngr->val;
}

struct rngod *
rngod_randu_add(uint32_t seed) {
	struct rng_randu *rngr;

	rngr = talloc(NULL, struct rng_randu);
	if (!rngr) return NULL;

	rngr->val = seed;

	rngr->rng.rand = rngod_randu_method_rand;
	default_init(&rngr->rng);
	return &rngr->rng;
}

struct rngod *
rngod_randu_add_default(void) {
	return rngod_randu_add(1);
}
