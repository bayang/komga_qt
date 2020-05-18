#!/bin/sh

#set -x

BUILD_TYPE=${1:-Release}

if [ -d "build/" ]; then
    echo removing old build dir
    rm -rf "build/"
fi;

mkdir build && cd build;

cmake .. \
        -DCMAKE_INSTALL_PREFIX="$(pwd)"/installer  \
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE

make -j8

exit 0;
