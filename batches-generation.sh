#!/bin/bash

# Number of dataset to produce
BATCHES=25

cd bin/

for ((i = 1; i <= BATCHES; i++))
do
    ./compute_approximation.exe
    mv "data/" "dataset_$i/"
done
