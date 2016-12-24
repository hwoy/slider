#ifndef RANDLOOP
#define RANDLOOP 1000
#endif

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

static const char* const opt[] = { "-s:", "-b:", "-h", NULL };
static const char* const optstr[] = { "Seed Number", "Blank Charecter", "Show Help", NULL };
enum {
    opt_s,
    opt_b,
    opt_h
};

static const char* const err[] = { "Not a Number", "Blank not match", "Invalid option", NULL };
enum {
    err_nan,
    err_bnm,
    err_inopt
};

static void showkey(const char* const key, const char* const keystr[])
{
    unsigned int i;

    for (i = 0; key[i]; ++i)
        printf(" %c(%s) ", key[i], keystr[i]);
}

static void initgame(unsigned int* const sq, unsigned int* seed, unsigned int index, unsigned int hw)
{
    initsq(sq, hw);
    randomsq(sq, index, hw, seed);
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

static unsigned int showerr(const char* const str[], unsigned int id, const char* const opt, const char* const param)
{
    fprintf(stderr, "Error Report\n\n");
    if (opt)
        fprintf(stderr, "Option: %s\n", opt);
    if (param)
        fprintf(stderr, "Param: %s\n", param);
    fprintf(stderr, "Error code: %u = %s\n", id, str[id]);

    return id;
}

static const char* const grappath(const char* const path)
{
    unsigned int i, j;
    for (j = 0, i = 0; path[i]; i++) {
        if (path[i] == '\\' || path[i] == '/')
            j = i + 1;
    }

    return path + j;
}

static void showhelp(const char* const opt[], const char* const optstr[], const char* const path, char ch)
{
    unsigned int i;

    fprintf(stderr, "%s is a cross platform slider game\n\n", grappath(path));

    fprintf(stderr, "Options\n");
    for (i = 0; opt[i]; ++i)
        fprintf(stderr, "%s = %s\n", opt[i], optstr[i]);

    fprintf(stderr, "\nExample\n");
    fprintf(stderr, "%s %s%u\n", grappath(path), opt[opt_s], 100);
    fprintf(stderr, "%s %s%c\n", grappath(path), opt[opt_b], ch);
}

int main(int argc, const char* const argv[])
{
    char ch;
    unsigned int key, move = 0;
    unsigned int sq[WxH * WxH];
    unsigned int gid = gid_normal;
    unsigned int seed, origseed, index;

    origseed = seed = time(NULL);
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
                if (!isUint(buff))
                    return showerr(err, err_nan, opt[opt_s], buff) + 1;

                origseed = seed = s2ui(buff);
                break;
            case opt_b:
                if (sLen(buff) != 1 || (index = getsqstrindex(sqstr, buff[0])) == -1U)
                    return showerr(err, err_bnm, opt[opt_b], buff) + 1;

                break;
            case opt_h:
                showhelp(opt, optstr, argv[0], sqstr[0]);
                return 0;
                break;

            default:
                showhelp(opt, optstr, argv[0], sqstr[0]);
                fprintf(stderr, "\n\n");
                return showerr(err, err_inopt, buff, NULL) + 1;
            }
        }
    }

    initgame(sq, &seed, index, WxH);

    do {
        printf("Seed: %u\n", origseed);
        printf("Random Engine: %s\n\n", randomengine());
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
            seed = origseed;
            initgame(sq, &seed, index, WxH);
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