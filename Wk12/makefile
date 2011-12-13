CFLAGS= -Wall -W -ansi -pedantic -g

quiz: quiz.o
	gcc quiz.o -o quiz

quiz.o: quiz.h quiz.c
	gcc $(CFLAGS) -c quiz.c -o quiz.o
