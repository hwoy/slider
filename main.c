#include "slider.h"
#include "sliderio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef SQUARE
#define SQUARE 7
#endif

#define BNUM 9

static const char cmdstr[] = "wsad";
static const char* const cmddes[] = { "UP", "DOWN", "LEFT", "RIGHT", NULL };

static const char* const gidstr[] = { "Normal", "Game Over!" };

static const char num[] = "123456789";

static const char keycmd[] = "-+";
static const char* const keycmdstr[] = { "Quit", "Reset", NULL };
enum {
    kid_quit,
    kid_reset
};

static void showkey(const char* const key, const char* const keystr[])
{
    unsigned int i;

    for (i = 0; key[i]; ++i)
        printf(" %c(%s) ", key[i], keystr[i]);
}

static void initgame(unsigned int* const sq, unsigned int seed, unsigned int index)
{
    initseed(seed);
    initsq(sq);
    randomsq(sq, index);
}

int main(void)
{
    char ch;
    unsigned int key, move = 0;
    unsigned int sq[WxH * WxH];
    unsigned int gid = gid_normal;
    unsigned int seed, index;

    seed = time(NULL);
    index = BNUM - 1;

    initgame(sq, seed, index);

    do {
        showkey(cmdstr, cmddes);
        putchar('\n');
        showkey(keycmd, keycmdstr);
        printf("\n\n");
        printsq(sq, num, SQUARE, index);
        printf("Press a key -> ");
        fflush(stdout);

        ch = getchar();
        fflush(stdin);

        if (ch == keycmd[kid_quit]) {
            break;
        } else if (ch == keycmd[kid_reset]) {
            initgame(sq, seed, index);
            continue;
        }

        if ((key = mapcmd(cmdstr, ch)) != -1U) {
            if ((slide(sq, key, index)) != -1U)
                move++;
            printf("Seed:%u\n", seed);
            printf("Move(s):%u\n", move);
            printf("Key ID: %u(%s)\n", key, cmddes[key]);
            gid = gameid(sq);
            printf("Game ID: %u(%s)\n\n", gid, gidstr[gid]);
        }
    } while (gid != gid_over);

    printsq(sq, num, SQUARE, index);
    return 0;
}