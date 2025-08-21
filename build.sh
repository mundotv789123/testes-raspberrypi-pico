#!/bin/sh -e

if [ "$1" = "clean" ]; then
  rm -rf ./build
  mkdir ./build
fi

cd ./build
cmake -DPICO_SDK_PATH=../pico-sdk -DPICO_BOARD=pico ..
make hello_world
