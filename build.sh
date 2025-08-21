#!/bin/sh -e

rm -rf ./build
mkdir ./build
cd ./build
cmake -DPICO_SDK_PATH=../pico-sdk -DPICO_BOARD=pico ..
make hello_world
