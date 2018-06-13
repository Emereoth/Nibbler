#!/bin/bash

cd "$(dirname -- "$0")"
make install
make
./setup.sh snake snake.png
cp nibbler snake.app/Contents/MacOS/snake
