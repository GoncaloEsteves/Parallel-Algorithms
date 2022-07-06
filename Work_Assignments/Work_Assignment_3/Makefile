CC=gcc

CCFLAGS = -O3 -fopenmp -g -march=native -Wall

all: asp matrixmult stencil2d

asp: src/ASP.c
	$(CC) -o bin/asp.exe $(CCFLAGS) src/ASP.c

matrixmult: src/MatrixMult.c
	$(CC) -o bin/matrixmult.exe $(CCFLAGS) src/MatrixMult.c

stencil2d: src/Stencil2D.c
	$(CC) -o bin/stencil2d.exe $(CCFLAGS) src/Stencil2D.c

.PHONY: clean

clean:
	rm -f bin/*.exe