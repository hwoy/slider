#include "slider.h"
#include "sliderio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUIT '-'
#define BLANK '*'

#define SQUARE 7
#define BNUM 9

static const char cmdstr[] = "wsad";
static const char* const cmddes[] = { "UP", "DOWN", "LEFT", "RIGHT", NULL };

static const char* const gidstr[] = { "Normal", "Game Over!" };

static const char num[] = "123456789";

int main(void)
{
    char ch;
    unsigned int key, move = 0;
    unsigned int sq[WxH * WxH];
    unsigned int gid;
    unsigned int seed;

    initseed(seed = time(NULL));
    initsq(sq);
    randomsq(sq, BNUM - 1);

    do {
        printsq(sq, num, SQUARE, BNUM - 1);
        printf("Press key -> ");
        fflush(stdout);

        ch = getchar();
        fflush(stdin);

        if ((key = mapcmd(cmdstr, ch)) != -1U) {
            if ((slide(sq, key, BNUM - 1)) != -1U)
                move++;
            printf("Seed:%u\n", seed);
            printf("Move(s):%u\n", move);
            printf("Key ID: %u(%s)\n", key, cmddes[key]);
            gid = gameid(sq);
            printf("Game ID: %u(%s)\n\n", gid, gidstr[gid]);
        }
    } while (ch != QUIT && gid != gid_over);

    printsq(sq, num, SQUARE, BNUM - 1);
    return 0;
}