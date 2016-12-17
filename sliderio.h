#ifndef _SLIDERIO_H_
#define _SLIDERIO_H_

#ifndef FRAMECH1
#define FRAMECH1 '#'
#endif

#ifndef FRAMECH2
#define FRAMECH2 0x20
#endif

char peter(char ch, unsigned int i, unsigned int j, unsigned int d);

void frame(const unsigned int* const sq, const char* const num, unsigned int n, unsigned int d, unsigned int index);

void printsq(const unsigned int* const sq, const char* const num, unsigned int square, unsigned int index, unsigned int hw);

unsigned int mapcmd(const char* const cmdstr, char ch);

void slidesqstr(unsigned int* const sq, const char* const cmdstr, const char* const str, unsigned int index, unsigned int hw);

#endif