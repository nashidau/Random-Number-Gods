#include <stdint.h>

enum {
	RNGOD_LCG_DEFAULT_A = 1664525,
	RNGOD_LCG_DEFAULT_C = 1013904223,
};

struct rngod *lcg_add(uint32_t seed, uint32_t a, uint32_t c);
struct rngod *lcg_add_default(void);

