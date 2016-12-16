#ifndef _SLIDER_H_
#define _SLIDER_H_

struct point {
    unsigned int y, x;
};

enum {
    cmd_up,
    cmd_down,
    cmd_left,
    cmd_right
};

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

    for (i = 0; i < 9; ++i) {
        if (sq[i] == blank)
            return i;
    }

    return -1u;
}

void getxy(unsigned int index, struct point* const p)
{
    p->y = index / 3;
    p->x = index % 3;
}

unsigned int slide(unsigned int* const sq, unsigned int kid, unsigned int _index)
{
    struct point p;
    unsigned int index, ret = -1U;

    getxy(index = getindex(sq, _index), &p);

    if (kid == cmd_up && p.y > 0) {
        swap(sq + index, sq + index - 3);
        ret = kid;
    }

    else if (kid == cmd_down && p.y < 2) {
        swap(sq + index, sq + index + 3);
        ret = kid;
    }

    else if (kid == cmd_left && p.x > 0) {
        swap(sq + index - 1, sq + index);
        ret = kid;
    }

    else if (kid == cmd_right && p.x < 2) {
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

#endif