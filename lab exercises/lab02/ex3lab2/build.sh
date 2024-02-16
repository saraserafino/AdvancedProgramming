#!/bin/bash

set -x

g++ -std=c++11 statistics.cpp main.cpp -o main

set +x

if [ $? -eq 0 ]; then
    echo "Build successful! You can run the program using ./main"
else
    echo "Build failed."
fi
