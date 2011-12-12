#include <stdint.h>

/* Stateless LCG implementation */

struct rngod *lcg_add(uint32_t seed);
struct rngod *lcg_add_default(void);

