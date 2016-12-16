#include "slider.h"
#include "sliderio.h"
#include <stdio.h>

#define QUIT '-'
#define BLANK '*'

#define SQUARE 7
#define INDEX 0

static unsigned int sq[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
static const char cmdstr[] = "wsad";
static const char* const cmddes[] = { "UP", "DOWN", "LEFT", "RIGHT", NULL };

int main(void)
{

    char ch;
    unsigned int key, move = 0;
    do {
        printsq(sq, SQUARE, INDEX);
        printf("Press key -> ");
        fflush(stdout);

        ch = getchar();
        fflush(stdin);

        if ((key = mapcmd(cmdstr, ch)) != -1U) {
            if (slide(sq, key, INDEX) != -1U)
                move++;

            printf("Move(s):%u\n", move);
            printf("KeyID: %u(%s)\n\n", key, cmddes[key]);
        }
    } while (ch != QUIT);

    return 0;
}