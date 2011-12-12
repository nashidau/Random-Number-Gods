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
	uint32_t value;
};

static uint32_t constant_rand(struct rngod *rng);
static uint32_t constant_dx(struct rngod *rng, int x);

struct rngod *
rngod_constant_add_default(void){
	return rngod_constant_add(7);
}

struct rngod *
rngod_constant_add(uint32_t value){
	struct rng_constant *rngc;

	rngc = talloc(NULL, struct rng_constant);

	default_init(&rngc->rng);
	rngc->value = value;
	rngc->rng.rand = constant_rand;
	rngc->rng.dx = constant_dx;
	return (struct rngod *)rngc;
}


static uint32_t
constant_rand(struct rngod *rng) {
	struct rng_constant *rngc = (struct rng_constant *)rng;
	return rngc->value;
}

static uint32_t
constant_dx(struct rngod *rng, int x) {
	struct rng_constant *rngc = (struct rng_constant *)rng;
	// FIXME: Ignores 'X'
	return rngc->value;
}


