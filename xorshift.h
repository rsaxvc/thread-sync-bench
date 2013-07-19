#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <stdint.h>

static const uint32_t xorshift_init = 2463534242u;

static inline uint32_t xorshift( uint32_t last_state)
{
last_state ^= (last_state << 5);
last_state ^= (last_state >> 13);
last_state ^= (last_state << 6);

return last_state;
}

#endif
