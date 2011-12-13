CFLAGS= -Wall -W -ansi -pedantic -g

pracquiz: main.o util.o pracquiz.o
	gcc main.o util.o pracquiz.o -o pracquiz

main.o: pracquiz.h main.c
	gcc $(CFLAGS) -c main.c -o main.o

util.o: pracquiz.h util.c
	gcc $(CFLAGS) -c util.c -o util.o

pracquiz.o: pracquiz.h pracquiz.c
	gcc $(CFLAGS) -c pracquiz.c -o pracquiz.o
