#!/bin/bash -x

echo $0
num_processes=$1

echo "Spawning $num_processes processes"
for i in $(eval echo {1..$num_processes})
do
    time ./dummy_client &
done
