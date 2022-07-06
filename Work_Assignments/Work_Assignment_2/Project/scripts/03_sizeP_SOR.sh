#!/bin/sh

#PBS -l walltime=2:00:00
#PBS -l nodes=1:r652:ppn=20
#PBS -q cpar

#cd /home/a85516/AP/TP2/C
#cd /home/a85731/CPD/AP/TP2/C

module load gcc/7.2.0

make clean
make

for ((threads=2; threads<=20; threads+=2))
do
    export OMP_NUM_THREADS=$threads
    echo "$threads threads:" >> ./results/03_sizeP_SOR.txt

    for ((size=50; size<=500; size+=50))
    do
        echo "  SORRB $size:" >> ./results/03_sizeP_SOR.txt
        ./bin/poisson.exe ps $size >> ./results/03_sizeP_SOR.txt
        echo "" >> ./results/03_sizeP_SOR.txt
    done
done
