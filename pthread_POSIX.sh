#!/bin/bash -l
# NOTE the -l flag!
#
#SBATCH -J pthread_main
#SBATCH -o pthread_main."%j".out
#SBATCH -e pthread_main."%j".err
# Default in slurm
#SBATCH --mail-user $bettencb@ksu.edu
#SBATCH --mail-type=ALL
# Request 5 hours run time
#SBATCH -t 5:0:0
#SBATCH --mem=4000
#SBATCH -p normal

./pthread_main;
