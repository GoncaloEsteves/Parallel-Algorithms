#!/bin/sh

#PBS -l walltime=2:00:00
#PBS -l nodes=1:r652:ppn=20
#PBS -q cpar

#cd /home/a85516/AP/TP2/C
#cd /home/a85731/CPD/AP/TP2/C

module load gcc/7.2.0

make clean
make

for ((size=50; size<=500; size+=50))
do
    echo "  Jac $size:" >> ./results/01_sizeS.txt
    ./bin/poisson.exe j $size >> ./results/01_sizeS.txt
    echo "" >> ./results/01_sizeS.txt

    echo "  GS $size:" >> ./results/01_sizeS.txt
    ./bin/poisson.exe g $size >> ./results/01_sizeS.txt
    echo "" >> ./results/01_sizeS.txt
    
    echo "  GSRB $size:" >> ./results/01_sizeS.txt
    ./bin/poisson.exe G $size >> ./results/01_sizeS.txt
    echo "" >> ./results/01_sizeS.txt

    echo "  SORRB $size:" >> ./results/01_sizeS.txt
    ./bin/poisson.exe s $size >> ./results/01_sizeS.txt
    echo "" >> ./results/01_sizeS.txt
done
