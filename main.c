#define RANDLOOP 1000

#include "function.h"
#include "opt.h"
#include "slider.h"
#include "sliderio.h"
#include <stdio.h>
#include <time.h>

#ifndef SQUARE
#define SQUARE 7
#endif

#ifndef SQSTR
#define SQSTR "123456789"
#endif

#ifndef CMDSTR
#define CMDSTR "wsad"
#endif

#ifndef WxH
#define WxH 3
#endif

#define BSIZE 125

static const char cmdstr[] = CMDSTR;
static const char* const cmddes[] = { "UP", "DOWN", "LEFT", "RIGHT", NULL };

static const char* const gidstr[] = { "Normal", "Game Over!", NULL };

static const char sqstr[] = SQSTR;

static const char keycmd[] = "-+";
static const char* const keycmdstr[] = { "Quit", "Reset", NULL };

enum {
    kid_quit,
    kid_reset
};

const char* const opt[] = { "-s:", "-b:", "-h", NULL };
enum {
    opt_s,
    opt_b,
    opt_h
};

const char* const err[] = { "Not a Number", "Blank not match", NULL };
enum {
    err_nan,
    err_bnm
};

static void showkey(const char* const key, const char* const keystr[])
{
    unsigned int i;

    for (i = 0; key[i]; ++i)
        printf(" %c(%s) ", key[i], keystr[i]);
}

static void initgame(unsigned int* const sq, unsigned int seed, unsigned int index, unsigned int hw)
{
    initseed(seed);
    initsq(sq, hw);
    randomsq(sq, index, hw);
}

static void showcanmove(const unsigned int* const sq, unsigned int index, const char* const cmdstr, const char* const cmddes[], unsigned int hw)
{
    unsigned int d[4], i, j;

    j = extractcanmovesq(d, canmovesq(sq, index, hw));
    for (i = 0; i < j; ++i)
        printf("%c(%s) ", cmdstr[d[i]], cmddes[d[i]]);
}

static unsigned int getsqstrindex(const char* const sqstr, char ch)
{
    unsigned int i;
    for (i = 0; sqstr[i]; ++i)
        if (ch == sqstr[i])
            return i;

    return -1U;
}

int main(int argc, const char* argv[])
{
    char ch;
    unsigned int key, move = 0;
    unsigned int sq[WxH * WxH];
    unsigned int gid = gid_normal;
    unsigned int seed, index;

    seed = time(NULL);
    index = getsqstrindex(sqstr, sqstr[sLen(sqstr) - 1]);

    {
        static char buff[BSIZE];
        int i;
        unsigned int ui_cindex;
        for (ui_cindex = DSTART; (i = opt_action(argc, argv, opt, buff,
                                      BSIZE, DSTART))
             != e_optend;
             ui_cindex++) {

            switch (i) {
            case opt_s:
                if (!isUint(buff)) {
                    fprintf(stderr, "Error code:%u = %s\n", err_nan, err[err_nan]);
                    return err_nan;
                }
                seed = s2ui(buff);
                break;
            case opt_b:
                if (sLen(buff) != 1 || (index = getsqstrindex(sqstr, buff[0])) == -1U) {
                    fprintf(stderr, "Error code:%u = %s\n", err_nan, err[err_bnm]);
                    return err_bnm;
                }
            case 2:
                break;
            }
        }
    }

    initgame(sq, seed, index, WxH);

    do {
        printf("Seed: %u\n\n", seed);
        showkey(cmdstr, cmddes);
        putchar('\n');
        showkey(keycmd, keycmdstr);
        printf("\n\n");
        printsq(sq, sqstr, SQUARE, index, WxH);
        printf("Can move: ");
        showcanmove(sq, index, cmdstr, cmddes, WxH);
        putchar('\n');
        printf("Press a key -> ");
        fflush(stdout);

        ch = getchar();
        fflush(stdin);

        if (ch == keycmd[kid_quit]) {
            break;
        } else if (ch == keycmd[kid_reset]) {
            initgame(sq, seed, index, WxH);
            move = 0;
            continue;
        }

        if ((key = mapcmd(cmdstr, ch)) != -1U) {
            if ((slide(sq, key, index, WxH)) != -1U)
                move++;
            printf("Move(s): %u\n", move);
            printf("Key ID: %u(%s)\n", key, cmddes[key]);
            gid = gameid(sq, WxH);
            printf("Game ID: %u(%s)\n\n", gid, gidstr[gid]);
        }
    } while (gid != gid_over);

    printsq(sq, sqstr, SQUARE, index, WxH);

    return 0;
}