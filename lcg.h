#include <stdint.h>

/* Stateless LCG implementation */

struct rng *lcg_add(uint32_t seed);
struct rng *lcg_add_default(void);

