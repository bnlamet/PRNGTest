#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

uint32_t xor32()
{
    static uint32_t x = 2463534242UL;
    x^=(x<<13); x^=(x>>17); return (x^=(x<<15));
}

