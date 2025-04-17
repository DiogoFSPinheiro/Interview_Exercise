#!/bin/bash


if [ "$1" == "remake" ]; then
    rm -rf build/
    mkdir build && cd build
    cmake ..
    make
    clear
    ctest

elif [ "$1" == "maketest" ]; then
    cd build
    make
    ./queue_tests

elif [ "$1" == "delete" ]; then
	rm -rf build/
	echo "Deleted Build!"

else
    echo "You forgot the order: remake, maketest or delete!"
fi


