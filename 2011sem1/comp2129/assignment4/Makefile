CC = gcc
CFLAGS = -g -O0 -pedantic -Wall -W -std=gnu99
LDFLAGS = -lm -lpthread

SOURCES = $(shell find . -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

TESTER = ~comp2129/assignment4/mark-sample
BINARIES = pagerank

.PHONY: all clean depends test

all: $(BINARIES)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(BINARIES)

depends:
	$(CC) $(CFLAGS) -MM $(SOURCES) > Makefile.depends

test: test_counter

counter: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

test_counter: counter
	$(TESTER) question1 ./pagerank

-include Makefile.depends
