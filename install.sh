#!/bin/bash

brew list wget &> /dev/null || brew install wget
brew list glew &> /dev/null || brew install glew
brew list sdl2 &> /dev/null || brew install sdl2
brew list sdl2_image &> /dev/null || brew install sdl2_image
brew list sdl2_mixer &> /dev/null || brew install sdl2_mixer
