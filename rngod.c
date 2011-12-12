#include <stdint.h>
#include <talloc.h>

#include "rngod.h"
#include "rng-private.h"


int rng_free(struct rngod *rng){
	return talloc_free(rng);
}

uint32_t
default_dx(struct rngod *rng, int x){
       if (x < 1) x = 1;
       return rng->rand(rng) % x + 1;
}


uint32_t
default_ndx(struct rngod *rng, int n, int x){
	     int i;
        int total;

        if (n == 0) return 0;
        if (x == 0) return 0;

        for (total = 0, i = 0 ; i < n ; i ++){
                total += rng->dx(rng, x);
        }
        return total;

}

uint32_t
default_range(struct rngod *rng, int min, int max){
        int range = max - min;
        return min + rng->dx(rng, range) - 1;

}

int
default_init(struct rngod *rng){
	if (!rng) return -1;
	// FIXME: check range is defined?
	rng->dx = default_dx;
	rng->ndx = default_ndx;
	rng->range = default_range;
	return 0;
}
