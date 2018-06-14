#!/bin/bash

brew list glew &> /dev/null && brew uninstall glew
brew list sdl2_mixer &> /dev/null && brew uninstall sdl2_mixer
brew list sdl2_image &> /dev/null && brew uninstall sdl2_image
brew list sdl2 &> /dev/null && brew uninstall sdl2
