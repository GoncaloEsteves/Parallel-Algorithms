CC=gcc

all: rooms.exe

rooms.exe: src/roomsMAIN.c src/rooms.c src/roomsSA.c src/roomsGreedy.c include/rooms.h src/auxiliar.c include/auxiliar.h
	$(CC) -o bin/rooms.exe -O3 -Wall -std=c99 -fopenmp src/roomsMAIN.c src/rooms.c src/roomsSA.c src/roomsGreedy.c src/auxiliar.c -lm

.PHONY: clean

clean:
	rm -f bin/*.exe