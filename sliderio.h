#ifndef _SLIDERIO_H_
#define _SLIDERIO_H_

#define WxH 3

#include <stdio.h>

char peter(char ch, unsigned int i, unsigned int j, unsigned int d)
{

    if (i == (d % 2 ? d - 1 : d) / 2 && j == (d % 2 ? d - 1 : d) / 2)
        return ch;

    else if (i > 0 && i < d - 1 && j > 0 && j < d - 1)
        return 0x20;

    return '#';
}

void frame(const unsigned int* sq, unsigned int n, unsigned int d, unsigned int index)
{
    unsigned int i, j;

    for (i = 0; i < d; ++i) {
        for (j = 0; j < d * n; ++j) {
            if (sq[j / d] == index)
                putchar(0x20);
            else
                printf("%c", peter(sq[j / d] + '0', i, j % d, d));

            if (!((j + 1) % d))
                printf(" ");
        }
        putchar('\n');
    }
}

void printsq(const unsigned int* const sq, unsigned int square, unsigned int index)
{
    unsigned int i;

    for (i = 0; i < WxH; ++i) {
        frame(sq + i * WxH, WxH, square, index);
        putchar('\n');
    }
}

unsigned int mapcmd(const char* const cmdstr, char ch)
{
    unsigned int i;

    for (i = 0; cmdstr[i]; ++i)
        if (ch == cmdstr[i])
            return i;

    return -1;
}

void slidesqstr(unsigned int* const sq, const char* const cmdstr, const char* const str, unsigned int index)
{
    unsigned int i;
    for (i = 0; str[i]; ++i)
        slide(sq, mapcmd(cmdstr, str[i]), index);
}

#endif