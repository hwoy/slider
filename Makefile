CC=gcc
FORMAT=clang-format

bin=slider
CFLAGS=-g -std=c90 -pedantic -Wall -Wextra
FORMATFLAGS=-i -style=WebKit


.PHONY: all clean format

all: $(bin)

$(bin): main.o slider.o sliderio.o function.o opt.o lcg.o minstd.o
	$(CC) $(LDFLAGS) -o $(bin) main.o slider.o sliderio.o function.o opt.o lcg.o minstd.o

clean:
	rm -f *.o $(bin) *.exe
format:
	$(FORMAT) $(FORMATFLAGS) *.c *.h


function.o: function.c function.h
main.o: main.c slider.h sliderio.h opt.h function.h
opt.o: opt.c opt.h
slider.o: slider.c slider.h
sliderio.o: sliderio.c sliderio.h slider.h
lcg.o: lcg.c lcg.h
minstd.o: minstd.c minstd.h lcg.h
