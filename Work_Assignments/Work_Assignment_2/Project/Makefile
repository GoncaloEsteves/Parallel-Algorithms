CC=gcc

all: poisson.exe

poisson.exe: src/poissonMain.c src/poissonJac.c src/poissonGS.c src/poissonGSRB.c src/poissonSORRB.c include/poisson.h src/auxiliar.c include/auxiliar.h
	$(CC) -o bin/poisson.exe -O3 -Wall -fopenmp src/poissonMain.c src/poissonJac.c src/poissonGS.c src/poissonGSRB.c src/poissonSORRB.c src/auxiliar.c -lm

.PHONY: clean

clean:
	rm -f bin/*.exe