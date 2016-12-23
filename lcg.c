#include "lcg.h"

uint32_t linear_congruential_generator(uint32_t* sd, uint32_t a, uint32_t c, uint32_t m)
{
    uint32_t hi;
    uint32_t lo;

    hi = (*sd + c) / (m / a);
    lo = (*sd + c) % (m / a);

    *sd = a * lo - (m % a) * hi;

    return (int32_t)*sd <= 0 ? *sd += m : *sd;
}
