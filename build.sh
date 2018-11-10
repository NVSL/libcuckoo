#!/bin/bash
mkdir -p bin
cd bin

if [ ! -f 'examples/hellohash' ]; then
    cmake -DBUILD_EXAMPLES=1 ..
    make -j
fi

exit 0
