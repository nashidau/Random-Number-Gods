#include <stdint.h>
#include <talloc.h>

#include "rngod.h"
#include "rng-private.h"


int
rng_free(struct rngod *rng){
	return talloc_free(rng);
}

uint32_t
default_dx(struct rngod *rng, uint32_t x){
       if (x < 1) x = 1;
       return rng->rand(rng) % x + 1;
}


uint32_t
default_ndx(struct rngod *rng, uint32_t n, uint32_t x){
	uint32_t i;
        uint32_t total;

        if (n == 0) return 0;
        if (x == 0) return 0;

        for (total = 0, i = 0 ; i < n ; i ++){
                total += rng->dx(rng, x);
        }
        return total;

}

uint64_t
default_range(struct rngod *rng, uint64_t min, uint64_t max){
        int range = max - min  + 1;
        return min + rng->dx(rng, range) - 1;
}

int
default_init(struct rngod *rng){
	if (!rng) return -1;
	rng->dx = default_dx;
	rng->ndx = default_ndx;
	rng->range = default_range;
	return 0;
}
