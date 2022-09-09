#!/bin/bash

echo "-------------------- Start Compile --------------------"
make && make clean
echo "-------------------- Done Compile --------------------"
./shake $1 $2 $3