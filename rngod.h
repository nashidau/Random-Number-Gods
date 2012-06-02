#ifndef RNGOD_H
#define RNGOD_H TheOneTruePath

#include <stdint.h>


struct rngod {
	uint32_t magic;
	uint32_t (*rand)(struct rngod*);
	uint32_t (*dx)(struct rngod *, int x);
	uint32_t (*ndx)(struct rngod *, int n, int x);
	uint32_t (*range)(struct rngod *, int min, int max);
};

int rng_free(struct rngod *);

#endif /* RNGOD_H */
