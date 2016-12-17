#include "slider.h"
#include "sliderio.h"
#include <stdio.h>
#include <time.h>

#ifndef SQUARE
#define SQUARE 7
#endif

#define BNUM '9'

static const char cmdstr[] = "wsad";
static const char* const cmddes[] = { "UP", "DOWN", "LEFT", "RIGHT", NULL };

static const char* const gidstr[] = { "Normal", "Game Over!", NULL };

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

static void showcanmove(const unsigned int* const sq, unsigned int index, const char* const cmdstr, const char* const cmddes[])
{
    unsigned int d[4], i, j;

    j = extractcanmovesq(d, canmovesq(sq, index));
    for (i = 0; i < j; ++i)
        printf("%c(%s) ", cmdstr[d[i]], cmddes[d[i]]);
}

static unsigned int getnumindex(const char* const num, char ch)
{
    unsigned int i;
    for (i = 0; num[i]; ++i)
        if (ch == num[i])
            return i;

    return -1U;
}

int main(void)
{
    char ch;
    unsigned int key, move = 0;
    unsigned int sq[WxH * WxH];
    unsigned int gid = gid_normal;
    unsigned int seed, index;

    seed = time(NULL);
    index = getnumindex(num, BNUM);

    initgame(sq, seed, index);

    do {
        showkey(cmdstr, cmddes);
        putchar('\n');
        showkey(keycmd, keycmdstr);
        printf("\n\n");
        printsq(sq, num, SQUARE, index);
        printf("Can move: ");
        showcanmove(sq, index, cmdstr, cmddes);
        putchar('\n');
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
            printf("Seed: %u\n", seed);
            printf("Move(s): %u\n", move);
            printf("Key ID: %u(%s)\n", key, cmddes[key]);
            gid = gameid(sq);
            printf("Game ID: %u(%s)\n\n", gid, gidstr[gid]);
        }
    } while (gid != gid_over);

    printsq(sq, num, SQUARE, index);

    return 0;
}