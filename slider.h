#ifndef _SLIDER_H_
#define _SLIDER_H_

#include <stdlib.h>

#define WxH 3

#ifndef RANDLOOP
#define RANDLOOP 100
#endif

struct point {
    unsigned int y, x;
};

enum {
    cmd_up,
    cmd_down,
    cmd_left,
    cmd_right
};

enum {
    gid_normal,
    gid_over
};

void initseed(unsigned int seed);

unsigned int initsq(unsigned int* const sq);

int randomsq(unsigned int* const sq, unsigned int index);

void swap(unsigned int* const a, unsigned int* const b);

unsigned int getindex(const unsigned int* const sq, unsigned int blank);

void getxy(unsigned int index, struct point* const p);

unsigned int slide(unsigned int* const sq, unsigned int kid, unsigned int _index);

void slidesq(unsigned int* const sq, const unsigned int* const cmdsq, unsigned int n, unsigned int index);

unsigned int gameid(const unsigned int* const sq);

#endif