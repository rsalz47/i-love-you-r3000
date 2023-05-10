#!/bin/bash

make clean
make
start=$SECONDS
./pipeline-driver
duration=$(( SECONDS - start ))
echo "Completed in $SECONDS seconds"
