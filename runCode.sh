#!/bin/bash
clear

if [ "$1" == "remake" ]; then
	rm -rf build/
    mkdir build && cd build
    cmake .. -Wno-dev
    make
    #clear
    #ctest

elif [ "$1" == "maketest" ]; then
	cd build
    make
    ./queue_tests

elif [ "$1" == "delete" ]; then
	rm -rf build/
	echo "Deleted Build!"

else
    echo "You forgot the command: remake, maketest or delete!"
	echo "remake: Deletes build, does cmake and make;"
	echo "maketest: does make and runs tests;"
	echo "delete: Deletes build"
fi


