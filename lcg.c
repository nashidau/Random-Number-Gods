#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "lcg.h"
#include "rngod.h"
#include "rng-private.h"

/** Todo: Paramaterise the A & C values */

struct rng_lcg {
	struct rngod rng;
	uint32_t seed;
};

enum {
	LCG_A = 1664525,
	LCG_C = 1013904223,
};

static uint32_t lcg_rand(struct rngod *rng);

struct rngod *
lcg_add_default(void){
	return lcg_add(time(NULL) ^ (getpid() << 1));
}

struct rngod *
lcg_add(uint32_t seed){
	struct rng_lcg *rngl;

	rngl = talloc(NULL, struct rng_lcg);

	/** FIXME: Magic */
	rngl->seed = seed;
	rngl->rng.rand = lcg_rand;
	default_init(&rngl->rng);
	return (struct rngod *)rngl;
}


static uint32_t
lcg_rand(struct rngod *rng) {
	struct rng_lcg *rngl = (struct rng_lcg *)rng;

	rngl->seed = ((uint64_t)rngl->seed * LCG_A + LCG_C);
	return rngl->seed;
}
