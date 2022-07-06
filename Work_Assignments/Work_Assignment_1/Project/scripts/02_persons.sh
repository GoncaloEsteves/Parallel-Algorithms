#!/bin/sh

#PBS -l walltime=1:00:00
#PBS -l nodes=1:r652:ppn=20
#PBS -q cpar

cd /home/a85731/CPD/AP/TP1/C

module load gcc/5.3.0

make clean
make

echo "Implementation,Cost,Steps,Execution Time" >> ./results/02_persons.txt

for persons in 100 500 1000 5000 10000
do
    echo "Size $persons" >> ./results/02_persons.txt
    ./bin/rooms.exe $persons 10 a >> ./results/02_persons.txt
    echo "" >> ./results/02_persons.txt
    sleep 1
done
