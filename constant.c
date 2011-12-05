#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "rng.h"
#include "rng-private.h"
#include "constant.h"

struct rng_constant {
	struct rng rng;
	uint32_t value;
};

static uint32_t constant_rand(struct rng *rng);
static uint32_t constant_dx(struct rng *rng, int x);

struct rng *
rngod_constant_add_default(void){
	return rngod_constant_add(7);
}

struct rng *
rngod_constant_add(uint32_t value){
	struct rng_constant *rngc;

	rngc = talloc(NULL, struct rng_constant);

	default_init(&rngc->rng);
	rngc->value = value;
	rngc->rng.rand = constant_rand;
	rngc->rng.dx = constant_dx;
	return (struct rng *)rngc;
}


static uint32_t
constant_rand(struct rng *rng) {
	struct rng_constant *rngc = (struct rng_constant *)rng;
	return rngc->value;
}

static uint32_t
constant_dx(struct rng *rng, int x) {
	struct rng_constant *rngc = (struct rng_constant *)rng;
	// FIXME: Ignores 'X'
	return rngc->value;
}


