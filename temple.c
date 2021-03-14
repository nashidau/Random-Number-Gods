
/*
 * Derived from the TempleOS system (code released into the public domain).
 *
 * A simple LCG with the added fun of inserting the current time stamp.
 *
 * Obviously this is no better than a normal RNG.
 */

#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "temple.h"
#include "rngod.h"
#include "rng-private.h"

struct rng_temple_lcg {
	struct rngod rng;
	uint64_t seed;
	uint64_t a, c;
};

static uint64_t
holyrand(struct rngod *rng) {
	struct rng_temple_lcg *trng = talloc_get_type(rng, struct rng_temple_lcg);
	if (!trng) {
		// FIXME: Should have a better eror process
		return 0;
	}
	uint64_t s = trng->seed;
	s = trng->a * s ^ ((s & 0xFFFFFFFF0000) >> 16) + trng->c;
#if 0
	s ^= __rdtsc();
#endif
	return (trng->seed = s);
}

struct rngod *
rngod_temple_lcg_add(uint64_t seed, uint64_t a, uint64_t c) {
	struct rng_temple_lcg *trng;

	trng = talloc(NULL, struct rng_temple_lcg);

	// A zero seed we set to a random time.
	if (seed == 0) {
		seed = time(NULL);
	}

	trng->seed = seed;
	trng->a = a;
	trng->c = c;
	trng->rng.rand = holyrand;
	default_init(&trng->rng);
	return (struct rngod *)trng;
}

struct rngod *
rngod_temple_lcg_seed(uint64_t seed) {
	return rngod_temple_lcg_add(seed, RNGOD_TEMPLE_LIN_CONGRUE_A, RNDO_TEMPLE_LIN_CONGRUE_C);
}

struct rngod *
rngod_temple_lcg_default(void) {
	return rngod_temple_lcg_add(0, RNGOD_TEMPLE_LIN_CONGRUE_A, RNDO_TEMPLE_LIN_CONGRUE_C);
}
