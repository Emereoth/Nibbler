#!/bin/bash

NAME="${PWD##*/}"

cd ..
if [ $NAME != "nibbler" ]
	then
		cp $NAME nibbler
fi
mv nibbler ~/Library/
cd ~/Library/nibbler
#git clone https://github.com/Emereoth/Nibbler.git nibbler
# cd nibbler
make install
make
./setup.sh snake snake.png
cp nibbler snake.app/Contents/MacOS/snake
chmod +x snake.app
cp -r snake.app ~/Desktop
