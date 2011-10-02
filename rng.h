#include <stdint.h>


struct rng {
	uint32_t magic;
	uint32_t (*rand)(struct rng*);
	uint32_t (*dx)(struct rng *, int x);
	uint32_t (*ndx)(struct rng *, int n, int x);
	uint32_t (*range)(struct rng *, int min, int max);
};

int rng_free(struct rng *);

