#ifndef RNGOD_H
#define RNGOD_H "TheOneTruePath"

#include <stdint.h>

struct rngod {
	uint64_t magic;
	uint64_t (*rand)(struct rngod*);
	uint64_t (*range)(struct rngod *, uint64_t min, uint64_t max);
	uint32_t (*dx)(struct rngod *, uint32_t x);
	uint32_t (*ndx)(struct rngod *, uint32_t n, uint32_t x);
};

int rng_free(struct rngod *);

#endif /* RNGOD_H */
