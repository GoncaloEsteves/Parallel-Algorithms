#!/bin/sh

#PBS -l walltime=1:00:00
#PBS -l nodes=1:r652:ppn=20
#PBS -q cpar

cd /home/a85731/CPD/AP/TP1/C

module load gcc/5.3.0

make clean
make

echo "Implementation,Cost,Steps,Execution Time" >> ./results/05_decreasing.txt

for dec in 0.9 0.99 0.999 0.9999 0.99999
do
    echo "Decreasing $dec" >> ./results/05_decreasing.txt
    ./bin/rooms.exe 10000 10 f $dec >> ./results/05_decreasing.txt
    echo "" >> ./results/05_decreasing.txt
    sleep 1
done
