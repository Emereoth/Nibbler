# NIBBLER

This is a small 'Snake' game, made in C++ using 3 graphical libs: SFML, SDL and OpenGL. It's main goal is to manage mulitple 
dynamic libraries and to be able to switch between them during the game.

# Installing

Simply run 

```
run.sh.command
```

and it will download sources, update brew and compile the game.
The game will install in ~/Library, and a shortcut will be created on the Desktop. The game must be started from the Desktop shortcut, or from ~/Library/nibbler with the command line.

When using the command line, the following usage must be respected:

```
./nibbler --lib=[sfml|sdl|opengl] --size=[WxH]
```

# Uninstalling

Same as above, but with the uninstalling script.

```
uninstall.sh.command
```

# How to play

Simply use the arrow keys to move the snake and keys 1, 2 and 3 to switch between libraries (in order: SFML, SDL and OpenGL).
Press Escape to quit.

# About the game

- The map obstacles are randomly generated for each game.
- When the player reaches a certain snake size, music will change to signify the activation of Hardcore Mode.
- Hardcore Mode: the snake is now significantly quicker, and the food will teleport away if it isn't eaten quick enough.
- Each library has 2 different soundtracks, one for normal game and one for Hardcore Mode.



This project was made by Andras COTTIER and Rafael VIEVILLE, students at 42 (Paris).

Feel free to leave feedback, and thanks for trying out our game!
