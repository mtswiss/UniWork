CC := clang
CFLAGS := -Wall -Wformat -Wformat-security -pedantic -std=gnu99 -g -O0
LDFLAGS :=

SOURCES := $(shell ls *.c)
OBJECTS := $(SOURCES:%.c=%.o)
PROG := MyProg

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

depends:
	$(CC) $(CFLAGS) -MM $(SOURCES) > Makefile.depends

-include Makefile.depends

.PHONY: clean
clean:
	rm -rf $(PROG) $(OBJECTS) *~

