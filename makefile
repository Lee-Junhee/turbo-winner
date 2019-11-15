ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o dirinf main.o

main.o: main.c
	$(CC) -c main.c

run: all
	./dirinf

clean:
	touch main.o
	touch a.out
	rm *.o
	rm a.out
