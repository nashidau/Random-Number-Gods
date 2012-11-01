/**
 * Todo: test this
 */

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
	uint32_t a, c;
};

static uint32_t lcg_rand(struct rngod *rng);

struct rngod *
rngod_lcg_add_default(void){
	return rngod_lcg_add_seed(time(NULL) ^ (getpid() << 1));
}

struct rngod *
rngod_lcg_add_seed(uint32_t seed) {
	return rngod_lcg_add(seed, RNGOD_LCG_DEFAULT_A, RNGOD_LCG_DEFAULT_C);
}

struct rngod *
rngod_lcg_add(uint32_t seed, uint32_t a, uint32_t c){
	struct rng_lcg *rngl;

	rngl = talloc(NULL, struct rng_lcg);

	rngl->seed = seed;
	rngl->a = a;
	rngl->c = c;
	rngl->rng.rand = lcg_rand;
	default_init(&rngl->rng);
	return (struct rngod *)rngl;
}

static uint32_t
lcg_rand(struct rngod *rng) {
	struct rng_lcg *rngl = talloc_get_type(rng, struct rng_lcg);

	rngl->seed = ((uint64_t)rngl->seed * rngl->a + rngl->c);
	return rngl->seed;
}
