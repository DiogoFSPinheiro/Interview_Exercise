#!/bin/bash
clear

rm -rf build/
mkdir build && cd build
cmake ..
make

clear
ctest
