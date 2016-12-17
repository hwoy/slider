#include "slider.h"
#include <stdlib.h>

void swap(unsigned int* const a, unsigned int* const b)
{
    unsigned int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

unsigned int getindex(const unsigned int* const sq, unsigned int blank)
{
    unsigned int i;

    for (i = 0; i < WxH * WxH; ++i) {
        if (sq[i] == blank)
            return i;
    }

    return -1u;
}

void getxy(unsigned int index, struct point* const p)
{
    p->y = index / WxH;
    p->x = index % WxH;
}

unsigned int slide(unsigned int* const sq, unsigned int kid, unsigned int _index)
{
    struct point p;
    unsigned int index, ret = -1U;

    getxy(index = getindex(sq, _index), &p);

    if (kid == cmd_up && p.y > 0) {
        swap(sq + index, sq + index - WxH);
        ret = kid;
    }

    else if (kid == cmd_down && p.y < WxH - 1) {
        swap(sq + index, sq + index + WxH);
        ret = kid;
    }

    else if (kid == cmd_left && p.x > 0) {
        swap(sq + index - 1, sq + index);
        ret = kid;
    }

    else if (kid == cmd_right && p.x < WxH - 1) {
        swap(sq + index + 1, sq + index);
        ret = kid;
    }

    return ret;
}

void slidesq(unsigned int* const sq, const unsigned int* const cmdsq, unsigned int n, unsigned int index)
{
    unsigned int i;
    for (i = 0; i < n; ++i)
        slide(sq, cmdsq[i], index);
}

unsigned int initsq(unsigned int* const sq)
{
    unsigned int i;

    for (i = 0; i < WxH * WxH; ++i)
        sq[i] = i;

    return WxH;
}

void initseed(unsigned int seed)
{
    srand(seed);
}

unsigned int canmovesq(const unsigned int* const sq, unsigned int index)
{
    struct point p;
    unsigned int i = 0xf;

    getxy(index = getindex(sq, index), &p);

    if (!p.y)
        i ^= (1 << 0);
    if (!p.x)
        i ^= (1 << 2);

    if (p.y == WxH - 1)
        i ^= (1 << 1);
    if (p.x == WxH - 1)
        i ^= (1 << 3);

    return i;
}

unsigned int extractcanmovesq(unsigned int* const d, unsigned int value)
{
    unsigned int i, j;

    for (i = 0, j = 0; i < 4; ++i) {
        if (value & (1 << i))
            d[j++] = i;
    }

    return j;
}

unsigned int randomsq(unsigned int* const sq, unsigned int index)
{
    unsigned int i, d[4], j;

    for (i = 0; i < RANDLOOP; ++i) {
        j = extractcanmovesq(d, canmovesq(sq, index));
        slide(sq, d[rand() % j], index);
    }

    return RANDLOOP;
}

unsigned int gameid(const unsigned int* const sq)
{
    unsigned int i;

    for (i = 0; i < WxH * WxH; ++i)
        if (sq[i] != i)
            return gid_normal;

    return gid_over;
}
