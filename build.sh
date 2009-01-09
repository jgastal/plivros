#!/bin/bash
if [ ! -d "build" ]; then
	mkdir build
fi
cd build
if [ "$1" == "release" ] ; then
        cmake -DDEBUG=OFF .. && make
else
        cmake .. && make
fi
cd ..