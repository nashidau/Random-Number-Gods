#include <pthread.h>

#include <talloc.h>

#include "dethread.h"
#include "rngod.h"
#include "rng-private.h"

struct rng_dethread {
	struct rngod rng;
	pthread_mutex_t lock;
	struct rngod *locked;
};

static uint64_t dethread_rand(struct rngod*);
static uint64_t dethread_range(struct rngod *, uint64_t min, uint64_t max);
static uint32_t dethread_dx(struct rngod *, uint32_t x);
static uint32_t dethread_ndx(struct rngod *, uint32_t n, uint32_t x);

struct rngod *
rngod_dethread_add(struct rngod *rng) {
	struct rng_dethread *rngd;

	rngd = talloc(NULL, struct rng_dethread);

	rngd->rng.rand = dethread_rand;
	rngd->rng.dx = dethread_dx;
	rngd->rng.ndx = dethread_ndx;
	rngd->rng.range = dethread_range;

	rngd->locked = rng;

	/* Take ownership */
	talloc_steal(rngd, rng);

	pthread_mutex_init(&rngd->lock, NULL);

	return (struct rngod *)rngd;
}


static uint64_t
dethread_rand(struct rngod *rng){
	uint64_t rv;
	struct rng_dethread *rngd = (struct rng_dethread *)rng;
	pthread_mutex_lock(&rngd->lock);
	rv = rngd->locked->rand(rngd->locked);
	pthread_mutex_unlock(&rngd->lock);
	return rv;
}

static uint64_t
dethread_range(struct rngod *rng, uint64_t min, uint64_t max){
	uint32_t rv;
	struct rng_dethread *rngd = (struct rng_dethread *)rng;
	pthread_mutex_lock(&rngd->lock);
	rv = rngd->locked->range(rngd->locked, min, max);
	pthread_mutex_unlock(&rngd->lock);
	return rv;
}

static uint32_t
dethread_dx(struct rngod *rng, uint32_t x){
	uint32_t rv;
	struct rng_dethread *rngd = (struct rng_dethread *)rng;
	pthread_mutex_lock(&rngd->lock);
	rv = rngd->locked->dx(rngd->locked, x);
	pthread_mutex_unlock(&rngd->lock);
	return rv;
}

static uint32_t
dethread_ndx(struct rngod *rng, uint32_t n, uint32_t x){
	uint32_t rv;
	struct rng_dethread *rngd = (struct rng_dethread *)rng;
	pthread_mutex_lock(&rngd->lock);
	rv = rngd->locked->ndx(rngd->locked, n, x);
	pthread_mutex_unlock(&rngd->lock);
	return rv;
}



