#!/bin/bash -l
# NOTE the -l flag!
#
#SBATCH -J test
#SBATCH -o test."%j".out
#SBATCH -e test."%j".err
# Default in slurm
#SBATCH --mail-user $bettencb@ksu.edu
#SBATCH --mail-type=ALL
# Request 5 hours run time
#SBATCH -t 5:0:0
#SBATCH --mem=4000
#SBATCH -p normal

./pthread_string;
