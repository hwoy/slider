CC=gcc
FORMAT=clang-format

bin=slider
CFLAGS=-g -std=c90 -pedantic -Wall
FORMATFLAGS=-i -style=WebKit


.PHONY: all clean format

all: $(bin)

$(bin): main.o slider.o sliderio.o
	$(CC) $(LDFLAGS) -o $(bin) main.o slider.o sliderio.o

clean:
	rm -f *.o $(bin) *.exe
format:
	$(FORMAT) $(FORMATFLAGS) *.c *.h


main.o: main.c slider.h sliderio.h
slider.o: slider.c slider.h
sliderio.o: sliderio.c sliderio.h
