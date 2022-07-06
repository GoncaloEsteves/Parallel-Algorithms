#!/bin/sh

#PBS -l walltime=2:00:00
#PBS -l nodes=1:r641:ppn=16
#PBS -q mei

cd /home/a85731/CPD/AP/TP3

module load gcc/5.3.0
export OMP_NUM_THREADS=32
export OMP_PROC_BIND=true

make clean
make

for i in 0 1 2 3 4
do
	perf stat -o ./results/results_matrix_mult_perf_$i.txt ./bin/matrixmult.exe >> ./results/results_matrix_mult.txt
done

for i in 0 1 2 3 4
do
	perf stat -o ./results/results_stencil2d_perf_$i.txt ./bin/stencil2d.exe >> ./results/results_stencil2d.txt
done