#!/bin/bash
mkdir build
cd build
if [ $1 == "release" ]; then
	cmake -DDEBUG=OFF .. && make
else
	cmake .. && make
fi
cd ..
rm -rf build
