#!/bin/bash
#making release version
if [ ! -d "Release" ]; then
	mkdir Release
fi
cd Release
cmake -DDEBUG=OFF .. && make
cd ..

#making debug version
if [ ! -d "Debug" ]; then
	mkdir Debug
fi
cd Debug
cmake .. && make