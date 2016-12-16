#include "slider.h"
#include "sliderio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUIT '-'
#define BLANK '*'

#define SQUARE 7
#define INDEX 8

static const char cmdstr[] = "wsad";
static const char* const cmddes[] = { "UP", "DOWN", "LEFT", "RIGHT", NULL };

static const char *const gidstr[]={"Normal","Game Over!"};

int main(void)
{
    char ch;
    unsigned int key, move = 0;
    unsigned int sq[WxH*WxH];
	unsigned int gid;
	unsigned int seed;

    initseed(seed=time(NULL));
    initsq(sq);
    randomsq(sq, INDEX);

    do {
        printsq(sq, SQUARE, INDEX);
        printf("Press key -> ");
        fflush(stdout);

        ch = getchar();
        fflush(stdin);

        if ((key = mapcmd(cmdstr, ch)) != -1U) {
            if ((slide(sq, key, INDEX)) != -1U)
                move++;
			printf("Seed:%u\n", seed);
            printf("Move(s):%u\n", move);
            printf("Key ID: %u(%s)\n", key, cmddes[key]);
			gid=gameid(sq);
			printf("Game ID: %u(%s)\n\n",gid,gidstr[gid]);
        }
    } while (ch != QUIT && gid != gid_over);
	
	printsq(sq, SQUARE, INDEX);
    return 0;
}