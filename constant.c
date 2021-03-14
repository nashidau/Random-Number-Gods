#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "rngod.h"
#include "rng-private.h"
#include "constant.h"

struct rng_constant {
	struct rngod rng;
	uint64_t value;
};

static uint64_t constant_rand(struct rngod *rng);
static uint32_t constant_dx(struct rngod *rng, uint32_t x);
static uint64_t constant_range(struct rngod *rng, uint64_t min, uint64_t max);

struct rngod *
rngod_constant_add_default(void){
	return rngod_constant_add(7);
}

struct rngod *
rngod_constant_add(uint64_t value){
	struct rng_constant *rngc;

	rngc = talloc(NULL, struct rng_constant);

	default_init(&rngc->rng);
	rngc->value = value;
	rngc->rng.rand = constant_rand;
	rngc->rng.dx = constant_dx;
	rngc->rng.range = constant_range;
	return (struct rngod *)rngc;
}

int
rngod_constant_constant_set(struct rngod *rng, uint64_t seed) {
	struct rng_constant *rngc = talloc_get_type(rng, struct rng_constant);
	if (!rngc) return -1;

	rngc->value = seed;
	return 0;
}

static uint64_t
constant_rand(struct rngod *rng) {
	struct rng_constant *rngc = talloc_get_type(rng, struct rng_constant);
	return rngc->value;
}

static uint32_t
constant_dx(struct rngod *rng, uint32_t x) {
	return constant_range(rng, 1, x);
}

static uint64_t
constant_range(struct rngod *rng, uint64_t min, uint64_t max) {
	struct rng_constant *rngc = talloc_get_type(rng, struct rng_constant);
	if (rngc->value > max)
		return max;
	else if (rngc->value < min)
		return min;
	else
		return rngc->value;
}

