#!/bin/bash

mkdir build

if [ $? -ne 0 ]
then
  echo "Making build directory failed!"
fi

cd build

cmake .. && make

if [ $? -ne 0 ]
then
  echo "Build failed! See output for info"
  exit 1
fi

echo "Make finished, to install globally, run 'cd build; sudo make install'"
