#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <talloc.h>

#include "xorshift.h"
#include "rngod.h"
#include "rng-private.h"

enum {
	DEFAULT_X = 123456789,
	DEFAULT_Y = 362436069,
	DEFAULT_Z = 521288629,
	DEFAULT_W = 88675123,
};

struct rng_xor {
	struct rngod rng;

	uint32_t x, y, z, w;
};

static uint32_t
rngod_xorshift_method_rand(struct rngod *rng) {
	struct rng_xor *rngx = talloc_get_type(rng, struct rng_xor);
	// FIXME: Error reporting policy/mechanism
	if (!rngx) return -1;

	uint32_t tmp;

	tmp = rngx->x ^ (rngx->x << 11);
	rngx->x = rngx->y;
	rngx->y = rngx->z;
	rngx->z = rngx->w;
	rngx->w = rngx->x ^ (rngx->w >> 19) ^ (tmp ^ (tmp >> 8));

	return rngx->w;
}

struct rngod *
rngod_xorshift_add(uint32_t x, uint32_t y, uint32_t z, uint32_t w) {
	struct rng_xor *rngx;

	rngx = talloc(NULL, struct rng_xor);
	if (!rngx) return NULL;

	rngx->x = x;	
	rngx->y = y;	
	rngx->z = z;	
	rngx->w = w;

	rngx->rng.rand = rngod_xorshift_method_rand;
	default_init(&rngx->rng);
	return &rngx->rng;
}

/**
 * Add a Xorshift generator with the default values:
 * 	123456789, 362436069, 521288629, 88675123
 *
 * @return A new Xorshift RNG.
 */
struct rngod *
rngod_xorshift_add_default(void) {
	return rngod_xorshift_add(DEFAULT_X, DEFAULT_Y, DEFAULT_Z, DEFAULT_W);
}

