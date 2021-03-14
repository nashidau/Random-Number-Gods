#ifndef RNGOD_TEMPLE_LCG_H
#define RNGOD_TEMPL_LCG_H 1
#include <stdint.h>

enum {
	RNGOD_TEMPLE_LIN_CONGRUE_A = UINT64_C(6364136223846793005),
	RNDO_TEMPLE_LIN_CONGRUE_C = UINT64_C(1442695040888963407),
};

struct rngod *rngod_temple_lcg_add(uint64_t seed, uint64_t a, uint64_t c);
struct rngod *rngod_temple_lcg_seed(uint64_t seed);
struct rngod *rngod_temple_lcg_default(void);
#endif
