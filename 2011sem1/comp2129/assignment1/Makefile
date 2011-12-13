CC = gcc
CFLAGS = -g -O0 -pedantic -Wall -W -std=c99
LDFLAGS = 
TESTER = ~comp2129/assignment1/mark-sample

BINARIES = minesweeper

.PHONY: all clean depends test

all: $(BINARIES)

clean:
	-rm -f *.o
	-rm -f $(BINARIES)

depends:
	$(CC) $(CFLAGS) -MM *.c > Makefile.depends

test: test_minesweeper

minesweeper: minesweeper.o
	$(CC) $(LDFLAGS) $^ -o $@

test_minesweeper: minesweeper
	$(TESTER) question1 ./minesweeper

-include Makefile.depends
