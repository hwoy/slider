#ifndef _SLIDERIO_H_
#define _SLIDERIO_H_

char peter(char ch, unsigned int i, unsigned int j, unsigned int d);

void frame(const unsigned int* sq, unsigned int n, unsigned int d, unsigned int index);

void printsq(const unsigned int* const sq, unsigned int square, unsigned int index);

unsigned int mapcmd(const char* const cmdstr, char ch);

void slidesqstr(unsigned int* const sq, const char* const cmdstr, const char* const str, unsigned int index);

#endif