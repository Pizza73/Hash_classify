#!/bin/bash

echo "-------------------- Start Compile --------------------"
cd src
make && make clean 
echo "-------------------- Done Compile --------------------"
../bin/shake $1 $2 $3