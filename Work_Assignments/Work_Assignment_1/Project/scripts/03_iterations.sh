#!/bin/sh

#PBS -l walltime=1:00:00
#PBS -l nodes=1:r652:ppn=20
#PBS -q cpar

cd /home/a85731/CPD/AP/TP1/C

module load gcc/5.3.0

make clean
make

echo "Implementation,Cost,Steps,Execution Time" >> ./results/03_iterations.txt

for iter in 50 75 100 125 150
do
    echo "Iterations $iter" >> ./results/03_iterations.txt
    ./bin/rooms.exe 10000 10 i $iter >> ./results/03_iterations.txt
    echo "" >> ./results/03_iterations.txt
    sleep 1
done
