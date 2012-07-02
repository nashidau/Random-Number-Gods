#include <stdint.h>

struct rngod;

struct rngod *rngod_xorshift_add(uint32_t, uint32_t, uint32_t, uint32_t);
struct rngod *rngod_xorshift_add_default(void);
