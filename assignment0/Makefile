CC = gcc
CFLAGS = -W -Wall -Wformat -Wformat-security -pedantic -std=c99 -g -O0
LDFLAGS = 
TESTER = ~comp2129/assignment0/mark-sample

BINARIES = q1 q2

.PHONY: all clean depends test

all: $(BINARIES)

clean:
	-rm -f *.o
	-rm -f $(BINARIES)

depends:
	$(CC) $(CFLAGS) -MM *.c > Makefile.depends

test: test_q1 test_q2

q1: question1.o
	$(CC) $(LDFLAGS) $^ -o $@

q2: question2.o
	$(CC) $(LDFLAGS) $^ -o $@

test_q1: q1
	$(TESTER) question1 ./q1

test_q2: q2
	$(TESTER) question2 ./q2

-include Makefile.depends

