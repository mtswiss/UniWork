CC := clang
CFLAGS := -Wall -Wformat -Wformat-security -pedantic -std=gnu99 -g -O0 -lm

EX_SRCS  := $(shell find . -maxdepth 1 -name "Ex*.c" | sort)
EX_PROGS := $(EX_SRCS:%.c=%)

OTHER_SRCS  := $(shell find . -maxdepth 1 -name "*.c" | grep -v "^Ex")
OTHER_PROGS := $(OTHER_SRCS:%.c=%)

.PHONY: all
all:
	@echo "This Makefile supports the following targets:"
	@echo
	@echo "  make exercises         - Makes all Ex*.c programs."
	@echo "  make clean             - Removes all Ex* programs."
	@echo "  make <foo>             - Builds program <foo> from source <foo>.c"
	@echo
	@echo "  Remember: To run any program once it is built, type"
	@echo
	@echo "               % ./<program>"
	@echo
	@echo "  on the command line."

.PHONY: exercises
exercises: $(EX_PROGS)

.PHONY: clean
clean:
	rm -rf $(EX_PROGS) $(OTHER_PROGS) *~

