#include <stdint.h>

struct rngod *rngod_constant_add(uint64_t seed);
struct rngod *rngod_constant_add_default(void);
int rngod_constant_constant_set(struct rngod *, uint64_t seed);

