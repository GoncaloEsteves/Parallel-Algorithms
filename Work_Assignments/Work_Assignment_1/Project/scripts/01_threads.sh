#!/bin/sh

#PBS -l walltime=1:00:00
#PBS -l nodes=1:r652:ppn=20
#PBS -q cpar

cd /home/a85731/CPD/AP/TP1/C

module load gcc/5.3.0

make clean
make

echo "Implementation,Cost,Steps,Execution Time" >> ./results/01_threads.txt

./bin/rooms.exe 10000 20 p >> ./results/01_threads.txt
