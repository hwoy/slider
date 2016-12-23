#include "minstd.h"

uint32_t minstd_rand0(uint32_t* sd)
{
    return linear_congruential_generator(sd, Astd0, Cstd, Mstd);
}

uint32_t minstd_rand(uint32_t* sd)
{
    return linear_congruential_generator(sd, Astd, Cstd, Mstd);
}
